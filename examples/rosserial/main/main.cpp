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
#include "gpio.h"

#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/UInt16.h>

/* 
 * This example shows how to use rosserial to communicate with ROS.
 * STM32 will publish data to "chatter" topic and subscribe "led" topic. Whenever
 * receive data from "led" topic, STM32 will toggle LED GREEN which connected to 
 * PD12 on STM32F4 Discover Board.
 *
 * Default rosserial port is UART4, PA0 TX, PA1 RX, baudrate 115200.
 */

#define TASK_SIZE   1024
#define TASK_PRIOR  5

/* Callback function */
void led_cb( const std_msgs::UInt16& cmd_msg)
{
    gpio_toggle_level(GPIO_PORT_D, GPIO_NUM_12);
} 

ros::NodeHandle nh; 
std_msgs::String str_msg; 
ros::Publisher chatter("chatter", &str_msg); 
ros::Subscriber<std_msgs::UInt16> sub("led", led_cb);

const char *hello = "Hello World !"; 

static void example_task(void* arg)
{
    /* Initialize publish and subscribe topic */
    nh.initNode(); 
    nh.advertise(chatter); 
    nh.subscribe(sub);

    /* Configure GPIO */
    gpio_config_t gpio_cfg;
    gpio_cfg.gpio_port = GPIO_PORT_D;
    gpio_cfg.gpio_num = GPIO_NUM_12;
    gpio_cfg.mode = GPIO_OUTPUT_PP;
    gpio_cfg.reg_pull_mode = GPIO_REG_PULL_NONE;
    gpio_config(&gpio_cfg);

    while (1)
    {
        /* Check if rosserial is connected */
        if (nh.connected())
        {
            /* Publish data */
            str_msg.data = hello;
            chatter.publish(&str_msg);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
        nh.spinOnce();
    }
}

int main(void)
{
    /* Create task */
    xTaskCreate(example_task, "example_task", TASK_SIZE, NULL, TASK_PRIOR, NULL);

    /* Start RTOS scheduler */
    vTaskStartScheduler();
}