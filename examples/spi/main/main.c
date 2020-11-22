// MIT License

// Copyright (c) 2020 phonght32

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
#include "driver/spi.h"

#define TASK_SIZE   512
#define TASK_PRIOR  5

#define SPI_NUM         SPI_NUM_1
#define SPI_PINS_PACK   SPI_PINS_PACK_1

static const char *TAG = "APP_MAIN";

static void example_task(void* arg)
{
    spi_cfg_t spi_cfg = {
        .spi_num = SPI_NUM,
        .spi_pins_pack = SPI_PINS_PACK,
        .mode = SPI_MODE_MASTER_HALF_DUPLEX,
        .cap_edge = SPI_CAP_FALLING_EDGE,
        .firstbit = SPI_TRANS_FIRSTBIT_LSB,
    };

    spi_config(&spi_cfg);

    uint8_t data_send[3] = {0x00, 0xf0, 0xaa};
    spi_write_bytes(SPI_NUM, data_send, 3, 100);

    while(1)
    {
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}

int main(void)
{
    /* Set application log output level */
    stm_log_level_set("*", STM_LOG_NONE);
    stm_log_level_set("APP_MAIN", STM_LOG_INFO);

    /* Create task */
    xTaskCreate(example_task, "example_task", TASK_SIZE, NULL, TASK_PRIOR, NULL);

    /* Start RTOS scheduler */
    vTaskStartScheduler();
}