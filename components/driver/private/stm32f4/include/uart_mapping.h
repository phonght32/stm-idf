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

#ifndef _UART_MAPPING_STM32F4_H_
#define _UART_MAPPING_STM32F4_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stm_hal.h"

/* Table below shows all possible pins for each uart
 *
 *  U(S)ARTx | Pins pack 1 | Pins pack 2 | Pins pack 3 |  APB  |
 *           |  TX    RX   |  TX    RX   |  TX    RX   |       |
 *--------------------------------------------------------------
 *  USART1   |  PA9   PA10 |  PB6   PB7  |  -     -    |   2   |
 *  USART2   |  PA2   PA3  |  PD5   PD6  |  -     -    |   1   |
 *  USART3   |  PB10  PB11 |  PC10  PC11 |  PD8   PD9  |   1   |
 *  USART4   |  PA0   PA1  |  PC10  PC11 |  -     -    |   1   |
 *  USART5   |  PC12  PD2  |  -     -    |  -     -    |   1   |
 *  USART6   |  PC6   PC7  |  PG14  PG9  |  -     -    |   2   |
 *  USART7   |  PE8   PE7  |  PF7   PF6  |  -     -    |   1   |
 *  USART8   |  PE1   PE0  |  -     -    |  -     -    |   1   |
 */

#define UART_NUM_MAX        6
#define UART_PINS_PACK_MAX      3
#define UART_FRAME_MAX_TYPE     12
#define UART_TRANSFER_MODE_MAX  3
#define UART_HW_FLW_CTRL_MAX_TYPE   4

#define UART1_PP1_HW_INFO   {.rcc_ahbenr_gpioen_tx = RCC_AHB1ENR_GPIOAEN,    \
                             .rcc_ahbenr_gpioen_rx = RCC_AHB1ENR_GPIOAEN,    \
                             .port_tx = GPIOA,                               \
                             .port_rx = GPIOA,                               \
                             .pin_tx = GPIO_PIN_9,                           \
                             .pin_rx = GPIO_PIN_10}

#define UART1_PP2_HW_INFO   {.rcc_ahbenr_gpioen_tx = RCC_AHB1ENR_GPIOBEN,    \
                             .rcc_ahbenr_gpioen_rx = RCC_AHB1ENR_GPIOBEN,    \
                             .port_tx = GPIOB,                               \
                             .port_rx = GPIOB,                               \
                             .pin_tx = GPIO_PIN_7,                           \
                             .pin_rx = GPIO_PIN_7}

#define UART2_PP1_HW_INFO   {.rcc_ahbenr_gpioen_tx = RCC_AHB1ENR_GPIOAEN,    \
                             .rcc_ahbenr_gpioen_rx = RCC_AHB1ENR_GPIOAEN,    \
                             .port_tx = GPIOA,                               \
                             .port_rx = GPIOA,                               \
                             .pin_tx = GPIO_PIN_2,                           \
                             .pin_rx = GPIO_PIN_3}

#define UART2_PP2_HW_INFO   {.rcc_ahbenr_gpioen_tx = RCC_AHB1ENR_GPIODEN,    \
                             .rcc_ahbenr_gpioen_rx = RCC_AHB1ENR_GPIODEN,    \
                             .port_tx = GPIOD,                               \
                             .port_rx = GPIOD,                               \
                             .pin_tx = GPIO_PIN_5,                           \
                             .pin_rx = GPIO_PIN_6}

#define UART3_PP1_HW_INFO   {.rcc_ahbenr_gpioen_tx = RCC_AHB1ENR_GPIOBEN,    \
                             .rcc_ahbenr_gpioen_rx = RCC_AHB1ENR_GPIOBEN,    \
                             .port_tx = GPIOB,                               \
                             .port_rx = GPIOB,                               \
                             .pin_tx = GPIO_PIN_10,                          \
                             .pin_rx = GPIO_PIN_11}

#define UART3_PP2_HW_INFO   {.rcc_ahbenr_gpioen_tx = RCC_AHB1ENR_GPIOCEN,    \
                             .rcc_ahbenr_gpioen_rx = RCC_AHB1ENR_GPIOCEN,    \
                             .port_tx = GPIOC,                               \
                             .port_rx = GPIOC,                               \
                             .pin_tx = GPIO_PIN_10,                          \
                             .pin_rx = GPIO_PIN_11}

#define UART3_PP3_HW_INFO   {.rcc_ahbenr_gpioen_tx = RCC_AHB1ENR_GPIODEN,    \
                             .rcc_ahbenr_gpioen_rx = RCC_AHB1ENR_GPIODEN,    \
                             .port_tx = GPIOD,                               \
                             .port_rx = GPIOD,                               \
                             .pin_tx = GPIO_PIN_8,                           \
                             .pin_rx = GPIO_PIN_9}

#define UART4_PP1_HW_INFO   {.rcc_ahbenr_gpioen_tx = RCC_AHB1ENR_GPIOAEN,    \
                             .rcc_ahbenr_gpioen_rx = RCC_AHB1ENR_GPIOAEN,    \
                             .port_tx = GPIOA,                               \
                             .port_rx = GPIOA,                               \
                             .pin_tx = GPIO_PIN_0,                           \
                             .pin_rx = GPIO_PIN_1}

#define UART4_PP2_HW_INFO   {.rcc_ahbenr_gpioen_tx = RCC_AHB1ENR_GPIOCEN,    \
                             .rcc_ahbenr_gpioen_rx = RCC_AHB1ENR_GPIOCEN,    \
                             .port_tx = GPIOC,                               \
                             .port_rx = GPIOC,                               \
                             .pin_tx = GPIO_PIN_10,                          \
                             .pin_rx = GPIO_PIN_11}

#define UART5_PP1_HW_INFO   {.rcc_ahbenr_gpioen_tx = RCC_AHB1ENR_GPIOCEN,    \
                             .rcc_ahbenr_gpioen_rx = RCC_AHB1ENR_GPIODEN,    \
                             .port_tx = GPIOC,                               \
                             .port_rx = GPIOD,                               \
                             .pin_tx = GPIO_PIN_12,                          \
                             .pin_rx = GPIO_PIN_2}

#define UART6_PP1_HW_INFO   {.rcc_ahbenr_gpioen_tx = RCC_AHB1ENR_GPIOCEN,    \
                             .rcc_ahbenr_gpioen_rx = RCC_AHB1ENR_GPIOCEN,    \
                             .port_tx = GPIOC,                               \
                             .port_rx = GPIOC,                               \
                             .pin_tx = GPIO_PIN_6,                           \
                             .pin_rx = GPIO_PIN_7}

#define UART6_PP2_HW_INFO   {.rcc_ahbenr_gpioen_tx = RCC_AHB1ENR_GPIOGEN,    \
                             .rcc_ahbenr_gpioen_rx = RCC_AHB1ENR_GPIOGEN,    \
                             .port_tx = GPIOG,                               \
                             .port_rx = GPIOG,                               \
                             .pin_tx = GPIO_PIN_14,                          \
                             .pin_rx = GPIO_PIN_9}

typedef struct {
    uint32_t       rcc_ahbenr_gpioen_tx;    /*!< TX GPIO RCC AHPENR register */
    uint32_t       rcc_ahbenr_gpioen_rx;    /*!< RX GPIO RCC AHPENR register */
    GPIO_TypeDef   *port_tx;                /*!< TX General Purpose I/O */
    GPIO_TypeDef   *port_rx;                /*!< RX General Purpose I/O */
    uint16_t       pin_tx;                  /*!< TX GPIO Pin */
    uint16_t       pin_rx;                  /*!< RX GPIO Pin */
} uart_hw_info_t;

typedef enum {
    FRAME_FORMAT_WORD_LEN = 0,      /*!< Word length index */
    FRAME_FORMAT_PARITY,            /*!< Parity index */
    FRAME_FORMAT_STOP_BIT,          /*!< Stop bit index */
    FRAME_FORMAT_MAX_INDEX
} frame_format_index_t;

static uart_hw_info_t UART_HW_INFO_MAPPING[UART_NUM_MAX][UART_PINS_PACK_MAX] = {
    {UART1_PP1_HW_INFO, UART1_PP2_HW_INFO,               {0}},
    {UART2_PP1_HW_INFO, UART2_PP2_HW_INFO,               {0}},
    {UART3_PP1_HW_INFO, UART3_PP2_HW_INFO, UART3_PP3_HW_INFO},
    {UART4_PP1_HW_INFO, UART4_PP2_HW_INFO,               {0}},
    {UART5_PP1_HW_INFO,               {0},               {0}},
    {UART6_PP1_HW_INFO, UART6_PP2_HW_INFO,               {0}}
};

static uint32_t UART_FRAME_FORMAT_MAPPING[UART_FRAME_MAX_TYPE][FRAME_FORMAT_MAX_INDEX] = {
    {UART_WORDLENGTH_8B, UART_PARITY_NONE, UART_STOPBITS_1},
    {UART_WORDLENGTH_8B, UART_PARITY_NONE, UART_STOPBITS_2},
    {UART_WORDLENGTH_9B, UART_PARITY_NONE, UART_STOPBITS_1},
    {UART_WORDLENGTH_9B, UART_PARITY_NONE, UART_STOPBITS_2},
    {UART_WORDLENGTH_8B, UART_PARITY_EVEN, UART_STOPBITS_1},
    {UART_WORDLENGTH_8B, UART_PARITY_EVEN, UART_STOPBITS_2},
    {UART_WORDLENGTH_9B, UART_PARITY_EVEN, UART_STOPBITS_1},
    {UART_WORDLENGTH_9B, UART_PARITY_EVEN, UART_STOPBITS_2},
    {UART_WORDLENGTH_8B, UART_PARITY_ODD , UART_STOPBITS_1},
    {UART_WORDLENGTH_8B, UART_PARITY_ODD , UART_STOPBITS_2},
    {UART_WORDLENGTH_9B, UART_PARITY_ODD , UART_STOPBITS_1},
    {UART_WORDLENGTH_9B, UART_PARITY_ODD , UART_STOPBITS_2}
};

static uint32_t RCC_APBENR_UARTEN_MAPPING[UART_NUM_MAX] = {
    RCC_APB2ENR_USART1EN,
    RCC_APB1ENR_USART2EN,
    RCC_APB1ENR_USART3EN,
    RCC_APB1ENR_UART4EN,
    RCC_APB1ENR_UART5EN,
    RCC_APB2ENR_USART6EN
};

static USART_TypeDef* UART_MAPPING[UART_NUM_MAX] = {
    USART1,
    USART2,
    USART3,
    UART4,
    UART5,
    USART6
};

static uint32_t UART_ALTERNATE_FUNC_MAPPING[UART_NUM_MAX] = {
    GPIO_AF7_USART1,
    GPIO_AF7_USART2,
    GPIO_AF7_USART3,
    GPIO_AF8_UART4,
    GPIO_AF8_UART5,
    GPIO_AF8_USART6
};

static uint32_t UART_TRANSFER_MODE_MAPPING[UART_TRANSFER_MODE_MAX] = {
    UART_MODE_RX,
    UART_MODE_TX,
    UART_MODE_TX_RX
};

static uint32_t UART_HW_FLW_CTRL_MAPPING[UART_HW_FLW_CTRL_MAX_TYPE] = {
    UART_HWCONTROL_NONE,
    UART_HWCONTROL_RTS,
    UART_HWCONTROL_CTS,
    UART_HWCONTROL_RTS_CTS
};

#ifdef __cplusplus
}
#endif

#endif /* _UART_MAPPING_STM32F4_H_ */