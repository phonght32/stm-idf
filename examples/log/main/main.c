#include "stm32f4xx_hal.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "stm_log.h"

#define TASK_SIZE       512
#define TASK_PRIOR      5

static const char *TAG = "APP_MAIN";

static void example_task(void* arg)
{
    while(1)
    {
        STM_LOGI(TAG, "Welcome to stm-idf");
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