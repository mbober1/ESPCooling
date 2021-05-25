#include "fan.hpp"
#include "freertos/task.h"
#include "driver/uart.h"
#include <string>

const gpio_num_t cpuTachoPin = GPIO_NUM_34;
const gpio_num_t cpuPwmPin = GPIO_NUM_32;
const pcnt_unit_t cpuPcntUnit = PCNT_UNIT_0;
const ledc_channel_t cpuPwmChannel = LEDC_CHANNEL_0;

const gpio_num_t gpuTachoPin = GPIO_NUM_35;
const gpio_num_t gpuPwmPin = GPIO_NUM_33;
const pcnt_unit_t gpuPcntUnit = PCNT_UNIT_1;
const ledc_channel_t gpuPwmChannel = LEDC_CHANNEL_1;


const uart_port_t uart = UART_NUM_0; 

int dupa[2] = {0, 0};

void uartRX(void* sock);

extern "C" void app_main() {
    Fan cpufan(cpuTachoPin, cpuPwmPin, cpuPwmChannel, cpuPcntUnit);
    Fan gpufan(gpuTachoPin, gpuPwmPin, gpuPwmChannel, gpuPcntUnit);

    xTaskCreate(uartRX, "serialRX", 4096, (void*)nullptr, 5, NULL);

    while (true)
    {
        vTaskDelay(200 / portTICK_PERIOD_MS);
        printf("C%d;G%d;S%d;T%d;", cpufan.getSpeed(), gpufan.getSpeed(), dupa[0], dupa[1]);
        cpufan.setPower(dupa[0]);
        gpufan.setPower(dupa[1]);
    }
    
}





void uartRX(void* sock) {
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
            bufferString.append(dataString);
        }

        separator = bufferString.find(';');
        while(separator != std::string::npos) {
            std::string parse = bufferString.substr(0, separator);
            bufferString.erase(0, separator + 1);
            separator = bufferString.find(';');

            switch (parse.at(0))
            {
                case 'P': { // set pwm1 percentage
                    parse.erase(0, 1);
                    dupa[0] = std::atoi(parse.c_str());
                    break;
                }

                case 'W': { // set pwm2 percentage
                    parse.erase(0, 1);
                    dupa[1] = std::atoi(parse.c_str());
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