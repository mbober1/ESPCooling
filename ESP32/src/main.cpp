#include "fan.hpp"
#include "freertos/task.h"
#include "driver/uart.h"
#include <string>

const gpio_num_t tachoPin = GPIO_NUM_34;
const gpio_num_t pwmPin = GPIO_NUM_32;
const ledc_channel_t pwmChannel = LEDC_CHANNEL_0;
const pcnt_unit_t pcntUnit = PCNT_UNIT_0;

const uart_port_t uart = UART_NUM_0; 

void uartRX();

extern "C" void app_main() {
    Fan fan(tachoPin, pwmPin, pwmChannel, pcntUnit);

    // uartRX();

    while (true)
    {
        vTaskDelay(100 / portTICK_PERIOD_MS);
        uint speed = fan.getSpeed();
        printf("C%d;G%d;S%d;T%d;", speed, speed, 69, 96);
    }
    
}





void uartRX() {
    const int bufferSize = 1024;
    uint8_t data[bufferSize];

    uart_config_t uart_config;
    uart_config.baud_rate = 115200;
    uart_config.data_bits = UART_DATA_8_BITS;
    uart_config.parity = UART_PARITY_DISABLE;
    uart_config.stop_bits = UART_STOP_BITS_1;
    uart_config.flow_ctrl = UART_HW_FLOWCTRL_DISABLE;
    uart_config.source_clk = UART_SCLK_APB;

    uart_driver_install(uart, 1024 * 2, 0, 0, NULL, 0);
    uart_param_config(uart, &uart_config);

    int length;
    static std::string bufferString;
    int separator;


    while (true)
    {
        uart_get_buffered_data_len(uart, (size_t*)&length);
        length = uart_read_bytes(uart, data, length, 20 / portTICK_RATE_MS);

        if(length > 0) {
            std::string dataString((char*)data, length);
            printf("Len: %d -> Data: %s\n", length, dataString.c_str());
            bufferString.append(dataString);
        }

        separator = bufferString.find(';');
        while(separator != std::string::npos) {
            std::string parse = bufferString.substr(0, separator);
            bufferString.erase(0, separator + 1);
            separator = bufferString.find(';');

            printf("Parsed: %s\n", parse.c_str());

            switch (parse.at(0))
            {
                case 'P': { // set pwm1 percentage
                    parse.erase(0, 1);
                    int pwm = std::atoi(parse.c_str());
                    printf("PWM1 Speed: %d\n", pwm);
                    break;
                }

                case 'W': { // set pwm2 percentage
                    parse.erase(0, 1);
                    int pwm = std::atoi(parse.c_str());
                    printf("PWM2 Speed: %d\n", pwm);
                    break;
                }
                
                default: {
                    printf("Sparsowane smieci: %s\n", parse.c_str());
                    break;
                }
            }
        }

        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
    
}