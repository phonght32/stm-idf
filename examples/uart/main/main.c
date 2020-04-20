#include "stm32f4xx_hal.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "stm_log.h"
#include "uart.h"

#define TASK_SIZE   1024
#define TASK_PRIOR  5

#define UART_NUM            UART_NUM_4
#define UART_PINS_PACK      UART_PINS_PACK_1
#define UART_BAUDRATE       115200

static const char *TAG = "APP_MAIN";

static void example_task(void* arg)
{
    uart_config_t uart_cfg;
    uart_cfg.uart_num = UART_NUM;
    uart_cfg.uart_pins_pack = UART_PINS_PACK;
    uart_cfg.baudrate = UART_BAUDRATE;
    uart_cfg.frame_format = UART_FRAME_8N1;
    uart_cfg.mode = UART_TRANSFER_MODE_TX_RX;
    uart_cfg.hw_flw_ctrl = UART_HW_FLW_CTRL_NONE;
    uart_config(&uart_cfg);
    STM_LOGI(TAG, "UART init complete");

    while(1)
    {
        uart_write_bytes(UART_NUM, (uint8_t *)"Welcome to STM-IDF \r\n", 21,100);
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