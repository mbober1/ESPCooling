#include "driver/uart.h"
#include <string>

QueueHandle_t cpuQueue, gpuQueue;

const uart_port_t uart = UART_NUM_0; 

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
                    int speed = std::atoi(parse.c_str());
                    xQueueSendToBack(cpuQueue, &speed, 0);
                    break;
                }

                case 'W': { // set pwm2 percentage
                    parse.erase(0, 1);
                    int speed = std::atoi(parse.c_str());
                    xQueueSendToBack(gpuQueue, &speed, 0);
                    break;
                }
            }
        }

        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
    
}