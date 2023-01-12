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
#include "driver/timer.h"

/* 
 * This test code shows how to use ETR function of TIMER to count external pulse.
 *      - PA5 is current pin input. To use another pins, view description in 
 *        timer header file.
 *      - Counter mode: up.
 *      - Reload value: 10.
 */

#define TASK_SIZE   1024
#define TASK_PRIOR  5

#define TIMER_NUM               TIMER_NUM_2 
#define TIMER_PINS_PACK         TIMER_PINS_PACK_2
#define TIMER_COUNTER_MODE      TIMER_COUNTER_UP
#define MAX_RELOAD              10

static const char *TAG = "APP_MAIN";
uint32_t cnt_value;

static void example_task(void* arg)
{
    /* Configure ETR pin */
    etr_cfg_t etr_cfg;
    etr_cfg.timer_num = TIMER_NUM;
    etr_cfg.timer_pins_pack = TIMER_PINS_PACK;
    etr_cfg.max_reload = MAX_RELOAD;
    etr_cfg.counter_mode = TIMER_COUNTER_MODE;
    etr_config(&etr_cfg);

    /* Start ETR counter */
    etr_start(TIMER_NUM);

    while(1)
    {
        /* Get counter value periodly and send log output to terminal */
        etr_get_value(TIMER_NUM, &cnt_value);
        STM_LOGI(TAG, "counter value: %d", cnt_value);
        vTaskDelay(100/portTICK_PERIOD_MS);
    }
}

int main(void)
{
    /* Set application log level */
    stm_log_level_set("*", STM_LOG_NONE);
    stm_log_level_set("APP_MAIN", STM_LOG_INFO);

    /* Create task */
    xTaskCreate(example_task, "example_task", TASK_SIZE, NULL, TASK_PRIOR, NULL);

    /* Start RTOS schedulder */
    vTaskStartScheduler();
}