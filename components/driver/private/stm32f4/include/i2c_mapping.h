// MIT License

// Copyright (c) 2020 thanhphong98

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

#ifndef _I2C_MAPPING_STM32F4_H_
#define _I2C_MAPPING_STM32F4_H_

#ifdef __cplusplus
extern "C" {
#endif

#define I2C_NUM_MAX         3
#define I2C_PINS_PACK_MAX   3

/*
 * I2C Hardware Information Define.
 */
#define I2C1_PP1_HW_INFO    {.rcc_ahbenr_gpio_scl = RCC_AHB1ENR_GPIOBEN,    \
                             .rcc_ahbenr_gpio_sda = RCC_AHB1ENR_GPIOBEN,    \
                             .port_scl = GPIOB,                             \
                             .port_sda = GPIOB,                             \
                             .pin_scl = GPIO_PIN_6,                         \
                             .pin_sda = GPIO_PIN_7}

#define I2C1_PP2_HW_INFO    {.rcc_ahbenr_gpio_scl = RCC_AHB1ENR_GPIOBEN,    \
                             .rcc_ahbenr_gpio_sda = RCC_AHB1ENR_GPIOBEN,    \
                             .port_scl = GPIOB,                             \
                             .port_sda = GPIOB,                             \
                             .pin_scl = GPIO_PIN_8,                         \
                             .pin_sda = GPIO_PIN_9}

#define I2C1_PP3_HW_INFO    {.rcc_ahbenr_gpio_scl = RCC_AHB1ENR_GPIOBEN,    \
                             .rcc_ahbenr_gpio_sda = RCC_AHB1ENR_GPIOBEN,    \
                             .port_scl = GPIOB,                             \
                             .port_sda = GPIOB,                             \
                             .pin_scl = GPIO_PIN_6,                         \
                             .pin_sda = GPIO_PIN_9}

#define I2C2_PP1_HW_INFO    {.rcc_ahbenr_gpio_scl = RCC_AHB1ENR_GPIOBEN,    \
                             .rcc_ahbenr_gpio_sda = RCC_AHB1ENR_GPIOBEN,    \
                             .port_scl = GPIOB,                             \
                             .port_sda = GPIOB,                             \
                             .pin_scl = GPIO_PIN_10,                        \
                             .pin_sda = GPIO_PIN_11}

#define I2C2_PP2_HW_INFO    {.rcc_ahbenr_gpio_scl = RCC_AHB1ENR_GPIOFEN,    \
                             .rcc_ahbenr_gpio_sda = RCC_AHB1ENR_GPIOFEN,    \
                             .port_scl = GPIOF,                             \
                             .port_sda = GPIOF,                             \
                             .pin_scl = GPIO_PIN_1,                         \
                             .pin_sda = GPIO_PIN_0}

#define I2C2_PP3_HW_INFO    {.rcc_ahbenr_gpio_scl = RCC_AHB1ENR_GPIOHEN,    \
                             .rcc_ahbenr_gpio_sda = RCC_AHB1ENR_GPIOHEN,    \
                             .port_scl = GPIOH,                             \
                             .port_sda = GPIOH,                             \
                             .pin_scl = GPIO_PIN_4,                         \
                             .pin_sda = GPIO_PIN_5}

#define I2C3_PP1_HW_INFO    {.rcc_ahbenr_gpio_scl = RCC_AHB1ENR_GPIOAEN,    \
                             .rcc_ahbenr_gpio_sda = RCC_AHB1ENR_GPIOCEN,    \
                             .port_scl = GPIOA,                             \
                             .port_sda = GPIOC,                             \
                             .pin_scl = GPIO_PIN_8,                         \
                             .pin_sda = GPIO_PIN_9}

#define I2C3_PP2_HW_INFO    {.rcc_ahbenr_gpio_scl = RCC_AHB1ENR_GPIOHEN,    \
                             .rcc_ahbenr_gpio_sda = RCC_AHB1ENR_GPIOHEN,    \
                             .port_scl = GPIOH,                             \
                             .port_sda = GPIOH,                             \
                             .pin_scl = GPIO_PIN_7,                         \
                             .pin_sda = GPIO_PIN_8}

typedef struct {
    uint32_t        rcc_ahbenr_gpio_scl;    /*!< SCL GPIO RCC AHPENR register */
    uint32_t        rcc_ahbenr_gpio_sda;    /*!< SDA GPIO RCC AHPENR register */
    GPIO_TypeDef    *port_scl;              /*!< SCL General Purpose I/O */
    GPIO_TypeDef    *port_sda;              /*!< SDA General Purpose I/O */
    uint16_t        pin_scl;                /*!< SCL GPIO Pin */
    uint16_t        pin_sda;                /*!< SDA GPIO Pin */
} i2c_hw_info_t;

i2c_hw_info_t I2C_HW_INFO_MAPPING[I2C_NUM_MAX][I2C_PINS_PACK_MAX] = {
    {I2C1_PP1_HW_INFO, I2C1_PP2_HW_INFO, I2C1_PP3_HW_INFO},
    {I2C2_PP1_HW_INFO, I2C2_PP2_HW_INFO, I2C2_PP3_HW_INFO},
    {I2C3_PP1_HW_INFO, I2C3_PP2_HW_INFO, {0}             }
};

I2C_TypeDef* I2C_MAPPING[I2C_NUM_MAX] = {
    I2C1,
    I2C2,
    I2C3
};

uint32_t RCC_APBENR_I2CEN_MAPPING[I2C_NUM_MAX] = {
    RCC_APB1ENR_I2C1EN,
    RCC_APB1ENR_I2C2EN,
    RCC_APB1ENR_I2C3EN
};

uint32_t I2C_ALTERNATE_FUNC_MAPPING[I2C_NUM_MAX] = {
    GPIO_AF4_I2C1,
    GPIO_AF4_I2C2,
    GPIO_AF4_I2C3
};

#ifdef __cplusplus
}
#endif

#endif /* _I2C_MAPPING_STM32F4_H_ */