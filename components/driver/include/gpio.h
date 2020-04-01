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

#ifndef _GPIO_H_
#define _GPIO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "stdbool.h"
#include "stdlib.h"

#include "stm32f4xx_hal.h"

/*
 * GPIO Port Select Typedef.
 */
typedef enum {
    GPIO_PORT_A = 0,    /*!< Port A selected */
    GPIO_PORT_B,        /*!< Port B selected */
    GPIO_PORT_C,        /*!< Port C selected */
    GPIO_PORT_D,        /*!< Port D selected */
    GPIO_PORT_E,        /*!< Port E selected */
    GPIO_PORT_F,        /*!< Port F selected */
    GPIO_PORT_G,        /*!< Port G selected */
    GPIO_PORT_H,        /*!< Port H selected */
    GPIO_PORT_I,        /*!< Port I selected */
    GPIO_PORT_MAX
} gpio_port_t;

/*
 * GPIO Pin Select Typedef.
 */
typedef enum {
    GPIO_NUM_0 = 0,     /*!< Pin 0 selected */
    GPIO_NUM_1,         /*!< Pin 1 selected */
    GPIO_NUM_2,         /*!< Pin 2 selected */
    GPIO_NUM_3,         /*!< Pin 3 selected */
    GPIO_NUM_4,         /*!< Pin 4 selected */
    GPIO_NUM_5,         /*!< Pin 5 selected */
    GPIO_NUM_6,         /*!< Pin 6 selected */
    GPIO_NUM_7,         /*!< Pin 7 selected */
    GPIO_NUM_8,         /*!< Pin 8 selected */
    GPIO_NUM_9,         /*!< Pin 9 selected */
    GPIO_NUM_10,        /*!< Pin 10 selected */
    GPIO_NUM_11,        /*!< Pin 11 selected */
    GPIO_NUM_12,        /*!< Pin 12 selected */
    GPIO_NUM_13,        /*!< Pin 13 selected */
    GPIO_NUM_14,        /*!< Pin 14 selected */
    GPIO_NUM_15,        /*!< Pin 15 selected */
    GPIO_NUM_MAX
} gpio_num_t;

/*
 * GPIO Mode Select Typedef.
 */
typedef enum {
    GPIO_INPUT = 0,     /*!< Input mode selected */
    GPIO_OUTPUT         /*!< Output mode selected */
} gpio_mode_t;

/*
 * GPIO Pull Registor Select Typedef.
 */
typedef enum {
    GPIO_REG_PULL_NONE = 0,     /*!< None pull registor selected */
    GPIO_REG_PULL_UP,           /*!< Registor pull up selected */
    GPIO_REG_PULL_DOWN,         /*!< Registor pull down selected*/
    GPIO_REG_PULL_MAX
} gpio_reg_pull_t;

/*
 * GPIO Configuration Typedef.
 */
typedef struct {
    gpio_port_t     gpio_port;      /*!< GPIO Port */
    gpio_num_t      gpio_num;       /*!< GPIO Pin */
    gpio_mode_t     gpio_mode;      /*!< GPIO Mode */
    gpio_reg_pull_t gpio_reg_pull;  /*!< GPIO Pull Registor */
} gpio_config_t;

/*
 * @brief   Initialize GPIO. Default logic 0 when output mode.
 * @param   config Struct pointer.
 * @return
 *      - 0: Success.
 *      - (-1): Fail.
 */
int gpio_init(gpio_config_t *config);

/*
 * @brief   Set GPIO level.
 * @param   gpio_port GPIO Port.
 * @param   gpio_num GPIO Num.
 * @param   state Level.
 * @return  None.
 */
void gpio_set_level(gpio_port_t gpio_port, gpio_num_t gpio_num, bool state);

/*
 * @brief   Toggle GPIO level.
 * @param   gpio_port GPIO Port.
 * @param   gpio_num GPIO Num.
 * @return  None.
 */
void gpio_toggle_level(gpio_port_t gpio_port, gpio_num_t gpio_num);


#ifdef __cplusplus
}
#endif

#endif /* _GPIO_H_ */