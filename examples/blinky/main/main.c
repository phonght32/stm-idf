#include "stm32f4xx_hal.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static void blinky_task(void* arg)
{
    __HAL_RCC_GPIOD_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    while(1)
    {
        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
        vTaskDelay(200/portTICK_PERIOD_MS);
    }
}

int main(void)
{
    xTaskCreate(blinky_task, "blinky_task", 512, NULL, 5, NULL);
    vTaskStartScheduler();
}