#include "driver/ledc.h"
#include "driver/gpio.h"
#include "driver/pcnt.h"

class Fan
{
private:
    gpio_num_t tachoPin;
    gpio_num_t pwmPin;
    ledc_channel_t pwmChannel;
    pcnt_unit_t pcntUnit;
    int64_t lastCounterClear;
    ledc_channel_config_t ledc_channel = {};
    ledc_timer_config_t ledc_timer = {};
    uint16_t power;

public:
    Fan(gpio_num_t tachoPin, gpio_num_t pwmPin, ledc_channel_t pwmChannel, pcnt_unit_t pcntUnit);
    ~Fan();
    uint16_t getSpeed();
    uint16_t getPower();
    void setPower(const uint16_t percentage);
};

Fan::~Fan() {}

Fan::Fan(gpio_num_t tachoPin, gpio_num_t pwmPin, ledc_channel_t pwmChannel, pcnt_unit_t pcntUnit) : 
tachoPin(tachoPin),
pwmPin(pwmPin),
pwmChannel(pwmChannel),
pcntUnit(pcntUnit)
{
    esp_err_t err;

    // tachometr pin config
    gpio_config_t tacho_conf = {};
    tacho_conf.mode = GPIO_MODE_INPUT;
    tacho_conf.pin_bit_mask = (1ULL << tachoPin);
    err = gpio_config(&tacho_conf);

    if(!err) printf("Tacho GPIO initialized\n");
    else printf("Tacho GPIO failed with error: %d\n", err);



    // pwm pin config
    gpio_config_t pwm_conf = {};
    pwm_conf.mode = GPIO_MODE_OUTPUT;
    pwm_conf.pin_bit_mask = (1ULL << pwmPin);
    err += gpio_config(&pwm_conf);

    if(!err) printf("PWM GPIO initialized\n");
    else printf("PWM GPIO failed with error: %d\n", err);


    // pwm timer config
    ledc_timer.duty_resolution = LEDC_TIMER_10_BIT;
    ledc_timer.freq_hz = 25000;
    ledc_timer.speed_mode = LEDC_HIGH_SPEED_MODE;
    ledc_timer.timer_num = LEDC_TIMER_0;
    ledc_timer.clk_cfg = LEDC_AUTO_CLK;
    err = ledc_timer_config(&ledc_timer);

    ledc_channel.channel = pwmChannel;
    ledc_channel.duty = 0;
    ledc_channel.gpio_num = pwmPin;
    ledc_channel.speed_mode = LEDC_HIGH_SPEED_MODE;
    ledc_channel.hpoint     = 0;
    ledc_channel.timer_sel  = LEDC_TIMER_0;
    err += ledc_channel_config(&ledc_channel);

    if(!err) printf("PWM initialized, freq %d\n", ledc_get_freq(LEDC_HIGH_SPEED_MODE, LEDC_TIMER_0));
    else printf("PWM failed with error: %d\n", err);



    // pcnt config
    pcnt_config_t pcnt_config = {};
    pcnt_config.pulse_gpio_num = tachoPin;
    pcnt_config.ctrl_gpio_num = PCNT_PIN_NOT_USED;
    pcnt_config.channel = PCNT_CHANNEL_0;
    pcnt_config.unit = pcntUnit;
    pcnt_config.pos_mode = PCNT_COUNT_INC;
    pcnt_config.neg_mode = PCNT_COUNT_INC;
    pcnt_config.lctrl_mode = PCNT_MODE_KEEP;
    pcnt_config.hctrl_mode = PCNT_MODE_KEEP;
    pcnt_config.counter_h_lim = 4000;
    pcnt_config.counter_l_lim = 0; // 0
    err = pcnt_unit_config(&pcnt_config);

    err += pcnt_counter_pause(pcntUnit);
    err += pcnt_counter_clear(pcntUnit);
    err += pcnt_filter_disable(pcntUnit);
    err += pcnt_intr_disable(pcntUnit);
    err += pcnt_counter_resume(pcntUnit);
    this->lastCounterClear = esp_timer_get_time();

    if(!err) printf("Fan initialized\n");
    else printf("Fan initialization failed with error: %d\n", err);
}

uint16_t Fan::getSpeed() {
    int16_t pulses;
    pcnt_get_counter_value(this->pcntUnit, &pulses);
    pcnt_counter_clear(this->pcntUnit);
    int64_t elapsedTime = esp_timer_get_time() - lastCounterClear;
    this->lastCounterClear = esp_timer_get_time();
    uint16_t speed = pulses * ((3000*5000)/elapsedTime);
    return speed;
}


/**
 * Set motor power.
 * @param power Motor power [0, (2**duty_resolution)]
 */
inline void Fan::setPower(const uint16_t percentage) {
    this->power = percentage;
    uint16_t pow = (percentage * 1024)/100;
    ledc_set_duty(this->ledc_channel.speed_mode, this->ledc_channel.channel, pow);
    ledc_update_duty(this->ledc_channel.speed_mode, this->ledc_channel.channel);
}

/**
 * Get motor power.
 * @return Motor power
 */
inline uint16_t Fan::getPower() {
    return this->power;
}