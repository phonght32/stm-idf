// MIT License

// Copyright (c) 2020 thanhphong98 & thuanpham98

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "stm_log.h"
#include "driver/uart.h"

/* 
 * This example shows how to configure UART.
 *      - UART4: PA0 TX_Pin, PA1 RX_Pin.
 *      - Baudrate: 115200.
 *      - Frame format: 8N1.
 *      - Mode: both TX and RX.
 *      - Hardware flow control: None.
 */

#define TASK_SIZE   1024
#define TASK_PRIOR  5

#define UART_NUM            UART_NUM_4
#define UART_PINS_PACK      UART_PINS_PACK_1
#define UART_BAUDRATE       115200

static const char *TAG = "APP_MAIN";

static void example_task(void* arg)
{
    /* Configure UART */
    uart_cfg_t uart_cfg;
    uart_cfg.uart_num = UART_NUM;
    uart_cfg.uart_pins_pack = UART_PINS_PACK;
    uart_cfg.baudrate = UART_BAUDRATE;
    uart_cfg.frame_format = UART_FRAME_8N1;
    uart_cfg.mode = UART_TRANSFER_MODE_TX_RX;
    uart_cfg.hw_flw_ctrl = UART_HW_FLW_CTRL_NONE;
    uart_config(&uart_cfg);

    while(1)
    {
        /* Transmit data */
        uart_write_bytes(UART_NUM, (uint8_t *)"Welcome to STM-IDF \r\n", 21,100);
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}

int main(void)
{
    /* Set application log level */
    stm_log_level_set("*", STM_LOG_NONE);
    stm_log_level_set("APP_MAIN", STM_LOG_INFO);

    /* Create task */
    xTaskCreate(example_task, "example_task", TASK_SIZE, NULL, TASK_PRIOR, NULL);

    /* Start RTOS scheduler */
    vTaskStartScheduler();
}