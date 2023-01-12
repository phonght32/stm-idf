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

#include "stm32f4xx_hal.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/*
 * This test code shows how to use HAL Library to blink LED connected to PD12 
 * on STM32F4 Discovery Board.
 */

#define TASK_SIZE   512
#define TASK_PRIOR  5

#define GPIO_PORT               GPIOD
#define GPIO_OUTPUT_BIT_MASK    GPIO_PIN_12

static void blinky_task(void* arg)
{
    /* Enable GPIO Port D clock */
    __HAL_RCC_GPIOD_CLK_ENABLE();

    /* Configure GPIO */
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_OUTPUT_BIT_MASK;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIO_PORT, &GPIO_InitStruct);

    while(1)
    {
        /* Blink leds */
        HAL_GPIO_TogglePin(GPIO_PORT, GPIO_OUTPUT_BIT_MASK);
        vTaskDelay(200/portTICK_PERIOD_MS);
    }
}

int main(void)
{
    /* Create task */
    xTaskCreate(blinky_task, "blinky_task", TASK_SIZE, NULL, TASK_PRIOR, NULL);

    /* Start RTOS Scheduler */
    vTaskStartScheduler();
}