#include "stm32f4xx_hal.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "stm_log.h"
#include "driver/timer.h"

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
    etr_config_t etr_cfg;
    etr_cfg.timer_num = TIMER_NUM;
    etr_cfg.timer_pins_pack = TIMER_PINS_PACK;
    etr_cfg.max_reload = 50;
    etr_cfg.counter_mode = TIMER_COUNTER_MODE;
    etr_config(&etr_cfg);
    etr_start(TIMER_NUM);

    while(1)
    {
        etr_get_value(TIMER_NUM, &cnt_value);
        STM_LOGI(TAG, "counter value: %d", cnt_value);
        vTaskDelay(100/portTICK_PERIOD_MS);
    }
}

int main(void)
{
    stm_log_level_set("*", STM_LOG_NONE);
    stm_log_level_set("APP_MAIN", STM_LOG_INFO);

    xTaskCreate(example_task, "example_task", TASK_SIZE, NULL, TASK_PRIOR, NULL);
    vTaskStartScheduler();
}