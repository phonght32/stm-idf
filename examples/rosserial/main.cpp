#include "stm32f4xx_hal.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "stm_log.h"
#include "gpio.h"

#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/UInt16.h>

#define TASK_SIZE   1024
#define TASK_PRIOR  5

void led_cb( const std_msgs::UInt16& cmd_msg)
{
    gpio_toggle_level(GPIO_PORT_D, GPIO_NUM_12);
} 

ros::NodeHandle nh; 
std_msgs::String str_msg; 
ros::Publisher chatter("chatter", &str_msg); 
ros::Subscriber<std_msgs::UInt16> sub("led", led_cb);

const char * hello = "Hello World !"; 


static void example_task(void* arg)
{
    nh.initNode(); 
    nh.advertise(chatter); 
    nh.subscribe(sub);

    gpio_config_t gpio_cfg;
    gpio_cfg.gpio_port = GPIO_PORT_D;
    gpio_cfg.gpio_num = GPIO_NUM_12;
    gpio_cfg.mode = GPIO_OUTPUT;
    gpio_cfg.pull_mode = GPIO_REG_PULL_NONE;
    gpio_config(&gpio_cfg);

    while (1)
    {
        if (nh.connected())
        {
            str_msg.data = hello;
            chatter.publish(&str_msg);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
        nh.spinOnce();
    }
}

int main(void)
{
    xTaskCreate(example_task, "example_task", TASK_SIZE, NULL, TASK_PRIOR, NULL);
    vTaskStartScheduler();
}