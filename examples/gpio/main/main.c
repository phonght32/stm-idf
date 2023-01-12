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
#include "driver/gpio.h"

/*
 * This test code shows how to use STM-IDF API to blink 4 leds connected to PD12,
 * PD13, PD14, PD15 on STM32F4 Discovery Board.
 */

#define TASK_SIZE   512
#define TASK_PRIOR  5
 
#define GPIO_PORT  GPIO_PORT_D 
#define GPIO_NUM   GPIO_NUM_12 

static const char *TAG = "APP_MAIN";

static void example_task(void* arg)
{
    /* Configure GPIO to output mode */
    gpio_cfg_t gpio_cfg;
    gpio_cfg.gpio_port = GPIO_PORT;
    gpio_cfg.gpio_num = GPIO_NUM;
    gpio_cfg.mode = GPIO_OUTPUT_PP;
    gpio_cfg.reg_pull_mode = GPIO_REG_PULL_NONE;
    gpio_config(&gpio_cfg);

    while(1)
    {
        /* Toggle GPIO output level */
        gpio_toggle_level(GPIO_PORT, GPIO_NUM);
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