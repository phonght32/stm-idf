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
#include "driver/timer.h"

/* 
 * This example shows how to use Timer as pwm function.
 *      - PD12: PWM output. To use another pwm pins, view timer tutorial.
 *      - PWM Frequency: 1 Hz.
 *      - PWM duty cycle: 50 %.
 */

#define TASK_SIZE   1024
#define TASK_PRIOR  5

#define TIMER_NUM           TIMER_NUM_4
#define TIMER_PINS_PACK     TIMER_PINS_PACK_2 
#define TIMER_CHANNEL       TIMER_CHNL_2
 
static const char *TAG = "APP_MAIN";
 
static void example_task(void* arg)
{
    /* Configure Timer pin as PWM generation output */
    pwm_config_t pwm_cfg;
    pwm_cfg.timer_num = TIMER_NUM;
    pwm_cfg.timer_pins_pack = TIMER_PINS_PACK;
    pwm_cfg.timer_chnl = TIMER_CHANNEL;
    pwm_config(&pwm_cfg);

    /* Configure PWM frequency and duty cycle */
    pwm_set_frequency(TIMER_NUM, TIMER_CHANNEL, 2);
    pwm_set_duty(TIMER_NUM, TIMER_CHANNEL, 50);

    /* Generate PWM output */
    pwm_start(TIMER_NUM, TIMER_CHANNEL);

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