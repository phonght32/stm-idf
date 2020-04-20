#include "stm32f4xx_hal.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "stm_log.h"
#include "timer.h"

#define TASK_SIZE   1024
#define TASK_PRIOR  5

#define TIMER_NUM           TIMER_NUM_4
#define TIMER_PINS_PACK     TIMER_PINS_PACK_2 
#define TIMER_CHANNEL       TIMER_CHANNEL_1

static const char *TAG = "APP_MAIN";

static void example_task(void* arg)
{
    pwm_config_t pwm_cfg;
    pwm_cfg.timer_num = TIMER_NUM;
    pwm_cfg.timer_pins_pack = TIMER_PINS_PACK;
    pwm_cfg.timer_channel = TIMER_CHANNEL;
    pwm_config(&pwm_cfg);

    pwm_set_frequency(TIMER_NUM, TIMER_CHANNEL, 2);
    pwm_set_duty(TIMER_NUM, TIMER_CHANNEL, 50);
    pwm_start(TIMER_NUM, TIMER_CHANNEL);

    while(1)
    {
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