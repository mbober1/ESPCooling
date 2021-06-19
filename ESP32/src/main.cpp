#include "fan.hpp"
#include "freertos/task.h"
#include "serial.hpp"

const gpio_num_t cpuTachoPin = GPIO_NUM_25;
const gpio_num_t cpuPwmPin = GPIO_NUM_33;
const pcnt_unit_t cpuPcntUnit = PCNT_UNIT_0;
const ledc_channel_t cpuPwmChannel = LEDC_CHANNEL_0;

const gpio_num_t gpuTachoPin = GPIO_NUM_35;
const gpio_num_t gpuPwmPin = GPIO_NUM_32;
const pcnt_unit_t gpuPcntUnit = PCNT_UNIT_1;
const ledc_channel_t gpuPwmChannel = LEDC_CHANNEL_1;



int speed;


extern "C" void app_main() {
    Fan cpufan(cpuTachoPin, cpuPwmPin, cpuPwmChannel, cpuPcntUnit);
    Fan gpufan(gpuTachoPin, gpuPwmPin, gpuPwmChannel, gpuPcntUnit);

    cpuQueue = xQueueCreate(10, sizeof(int));
    gpuQueue = xQueueCreate(10, sizeof(int));
    xTaskCreate(uartRX, "serialRX", 4096, (void*)nullptr, 5, NULL);

    int64_t lastTime = esp_timer_get_time();

    cpufan.setPower(30);
    gpufan.setPower(30);

    while (true)
    {        
        if(xQueueReceive(cpuQueue, &speed, 0)) cpufan.setPower(speed);
        if(xQueueReceive(gpuQueue, &speed, 0)) gpufan.setPower(speed);

        if(esp_timer_get_time() - lastTime > 100000) {
            printf("C%d;G%d;S%d;T%d;", cpufan.getSpeed(), gpufan.getSpeed(), cpufan.getPower(), gpufan.getPower());
            lastTime = esp_timer_get_time();
        }
    }
    
}





