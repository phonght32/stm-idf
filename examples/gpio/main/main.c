#include "stm32f4xx_hal.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "stm_log.h"
#include "gpio.h"

#define TASK_SIZE   1024
#define TASK_PRIOR  5

#define GPIO_PORT  GPIO_PORT_D 
#define GPIO_NUM   GPIO_NUM_12

static const char *TAG = "APP_MAIN";

static void example_task(void* arg)
{
    gpio_config_t gpio_cfg;
    gpio_cfg.gpio_port = GPIO_PORT;
    gpio_cfg.gpio_num = GPIO_NUM;
    gpio_cfg.mode = GPIO_OUTPUT;
    gpio_cfg.pull_mode = GPIO_REG_PULL_NONE;
    gpio_config(&gpio_cfg);

    while(1)
    {
        gpio_toggle_level(GPIO_PORT_D, GPIO_NUM_12);
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}

int main(void)
{
    stm_log_level_set("*", STM_LOG_NONE);
    stm_log_level_set("APP_MAIN", STM_LOG_INFO);

    xTaskCreate(example_task, "example_task", TASK_SIZE, NULL, TASK_PRIOR, NULL);
    vTaskStartScheduler();
}