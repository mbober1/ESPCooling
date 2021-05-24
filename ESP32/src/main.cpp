#include "fan.hpp"
#include "freertos/task.h"

const gpio_num_t tachoPin = GPIO_NUM_34;
const gpio_num_t pwmPin = GPIO_NUM_32;
const ledc_channel_t pwmChannel = LEDC_CHANNEL_0;
const pcnt_unit_t pcntUnit = PCNT_UNIT_0;

extern "C" void app_main() {
    Fan fan(tachoPin, pwmPin, pwmChannel, pcntUnit);

    while (true)
    {
        vTaskDelay(100 / portTICK_PERIOD_MS);
        uint speed = fan.getSpeed();
        printf("C%d;G%d;S%d;T%d;\n", speed, speed, 69, 96);
    }
    
}