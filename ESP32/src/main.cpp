#include "fan.hpp"
#include "freertos/task.h"
#include "driver/uart.h"

const gpio_num_t tachoPin = GPIO_NUM_34;
const gpio_num_t pwmPin = GPIO_NUM_32;
const ledc_channel_t pwmChannel = LEDC_CHANNEL_0;
const pcnt_unit_t pcntUnit = PCNT_UNIT_0;

#define BUF_SIZE (1024)
const uart_port_t uart = UART_NUM_0; 

extern "C" void app_main() {
    Fan fan(tachoPin, pwmPin, pwmChannel, pcntUnit);

    uint8_t *data = (uint8_t *) malloc(BUF_SIZE);
    // uint8_t data[] = {'d','u','p', 'a', '\n','\0'};

    uart_config_t uart_config;
    uart_config.baud_rate = 115200;
    uart_config.data_bits = UART_DATA_8_BITS;
    uart_config.parity = UART_PARITY_DISABLE;
    uart_config.stop_bits = UART_STOP_BITS_1;
    uart_config.flow_ctrl = UART_HW_FLOWCTRL_DISABLE;
    uart_config.source_clk = UART_SCLK_APB;

    // We won't use a buffer for sending data.
    uart_driver_install(uart, BUF_SIZE * 2, 0, 0, NULL, 0);
    uart_param_config(uart, &uart_config);
    // uart_set_pin(uart, 35, 34, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

    while (true)
    {
        int len = uart_read_bytes(uart, data, BUF_SIZE, 20 / portTICK_RATE_MS);
        if(len > 0) printf("dupa\n");
        // uart_write_bytes(uart, (const char *) data, len);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        uint speed = fan.getSpeed();
        printf("C%d;G%d;S%d;T%d;\n", speed, speed, 69, 96);
    }
    
}