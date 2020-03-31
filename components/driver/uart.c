#include "include/uart.h"

#define UART_WORDLENGTH_DEFAULT         UART_WORDLENGTH_8B      /*!< Default UART word length */
#define UART_STOPBITS_DEFAULT           UART_STOPBITS_1         /*!< Default UART stop bits */
#define UART_PARITY_DEFAULT             UART_PARITY_NONE        /*!< Default UART parity */
#define UART_HW_FLOWCTRL_DEFAULT        UART_HWCONTROL_NONE     /*!< Default UART hardware flow control */
#define UART_OVERSAMPLING_DEFAULT       UART_OVERSAMPLING_16    /*!< Default UART over sampling */
#define UART_MODE_DEFAULT               UART_MODE_TX_RX         /*!< Default UART mode */

/* UART Hardware Information */
#define UART1_PP1_HW_INFO   {.rcc_apbenr_usarten = RCC_APB2ENR_USART1EN,     \
                             .usart = USART1,                                \
                             .rcc_ahbenr_gpioen_tx = RCC_AHB1ENR_GPIOAEN,    \
                             .rcc_ahbenr_gpioen_rx = RCC_AHB1ENR_GPIOAEN,    \
                             .port_tx = GPIOA,                               \
                             .port_rx = GPIOA,                               \
                             .pin_tx = GPIO_PIN_9,                           \
                             .pin_rx = GPIO_PIN_10,                          \
                             .alternate_func = GPIO_AF7_USART1}

#define UART1_PP2_HW_INFO   {.rcc_apbenr_usarten = RCC_APB2ENR_USART1EN,     \
                             .usart = USART1,                                \
                             .rcc_ahbenr_gpioen_tx = RCC_AHB1ENR_GPIOBEN,    \
                             .rcc_ahbenr_gpioen_rx = RCC_AHB1ENR_GPIOBEN,    \
                             .port_tx = GPIOB,                               \
                             .port_rx = GPIOB,                               \
                             .pin_tx = GPIO_PIN_7,                           \
                             .pin_rx = GPIO_PIN_7,                           \
                             .alternate_func = GPIO_AF7_USART1}

#define UART2_PP1_HW_INFO   {.rcc_apbenr_usarten = RCC_APB1ENR_USART2EN,     \
                             .usart = USART2,                                \
                             .rcc_ahbenr_gpioen_tx = RCC_AHB1ENR_GPIOAEN,    \
                             .rcc_ahbenr_gpioen_rx = RCC_AHB1ENR_GPIOAEN,    \
                             .port_tx = GPIOA,                               \
                             .port_rx = GPIOA,                               \
                             .pin_tx = GPIO_PIN_2,                           \
                             .pin_rx = GPIO_PIN_3,                           \
                             .alternate_func = GPIO_AF7_USART2}

#define UART2_PP2_HW_INFO   {.rcc_apbenr_usarten = RCC_APB1ENR_USART2EN,     \
                             .usart = USART2,                                \
                             .rcc_ahbenr_gpioen_tx = RCC_AHB1ENR_GPIODEN,    \
                             .rcc_ahbenr_gpioen_rx = RCC_AHB1ENR_GPIODEN,    \
                             .port_tx = GPIOD,                               \
                             .port_rx = GPIOD,                               \
                             .pin_tx = GPIO_PIN_5,                           \
                             .pin_rx = GPIO_PIN_6,                           \
                             .alternate_func = GPIO_AF7_USART2}

#define UART3_PP1_HW_INFO   {.rcc_apbenr_usarten = RCC_APB1ENR_USART3EN,     \
                             .usart = USART3,                                \
                             .rcc_ahbenr_gpioen_tx = RCC_AHB1ENR_GPIOBEN,    \
                             .rcc_ahbenr_gpioen_rx = RCC_AHB1ENR_GPIOBEN,    \
                             .port_tx = GPIOB,                               \
                             .port_rx = GPIOB,                               \
                             .pin_tx = GPIO_PIN_10,                          \
                             .pin_rx = GPIO_PIN_11,                          \
                             .alternate_func = GPIO_AF7_USART3}

#define UART3_PP2_HW_INFO   {.rcc_apbenr_usarten = RCC_APB1ENR_USART3EN,     \
                             .usart = USART3,                                \
                             .rcc_ahbenr_gpioen_tx = RCC_AHB1ENR_GPIOCEN,    \
                             .rcc_ahbenr_gpioen_rx = RCC_AHB1ENR_GPIOCEN,    \
                             .port_tx = GPIOC,                               \
                             .port_rx = GPIOC,                               \
                             .pin_tx = GPIO_PIN_10,                          \
                             .pin_rx = GPIO_PIN_11,                          \
                             .alternate_func = GPIO_AF7_USART3}

#define UART3_PP3_HW_INFO   {.rcc_apbenr_usarten = RCC_APB1ENR_USART3EN,     \
                             .usart = USART3,                                \
                             .rcc_ahbenr_gpioen_tx = RCC_AHB1ENR_GPIODEN,    \
                             .rcc_ahbenr_gpioen_rx = RCC_AHB1ENR_GPIODEN,    \
                             .port_tx = GPIOD,                               \
                             .port_rx = GPIOD,                               \
                             .pin_tx = GPIO_PIN_8,                           \
                             .pin_rx = GPIO_PIN_9,                           \
                             .alternate_func = GPIO_AF7_USART3}

#define UART4_PP1_HW_INFO   {.rcc_apbenr_usarten = RCC_APB1ENR_UART4EN,      \
                             .usart = UART4,                                 \
                             .rcc_ahbenr_gpioen_tx = RCC_AHB1ENR_GPIOAEN,    \
                             .rcc_ahbenr_gpioen_rx = RCC_AHB1ENR_GPIOAEN,    \
                             .port_tx = GPIOA,                               \
                             .port_rx = GPIOA,                               \
                             .pin_tx = GPIO_PIN_0,                           \
                             .pin_rx = GPIO_PIN_1,                           \
                             .alternate_func = GPIO_AF8_UART4}

#define UART4_PP2_HW_INFO   {.rcc_apbenr_usarten = RCC_APB1ENR_UART4EN,      \
                             .usart = UART4,                                 \
                             .rcc_ahbenr_gpioen_tx = RCC_AHB1ENR_GPIOCEN,    \
                             .rcc_ahbenr_gpioen_rx = RCC_AHB1ENR_GPIOCEN,    \
                             .port_tx = GPIOC,                               \
                             .port_rx = GPIOC,                               \
                             .pin_tx = GPIO_PIN_10,                          \
                             .pin_rx = GPIO_PIN_11,                          \
                             .alternate_func = GPIO_AF8_UART4}

#define UART5_PP1_HW_INFO   {.rcc_apbenr_usarten = RCC_APB1ENR_UART5EN,      \
                             .usart = UART5,                                 \
                             .rcc_ahbenr_gpioen_tx = RCC_AHB1ENR_GPIOCEN,    \
                             .rcc_ahbenr_gpioen_rx = RCC_AHB1ENR_GPIODEN,    \
                             .port_tx = GPIOC,                               \
                             .port_rx = GPIOD,                               \
                             .pin_tx = GPIO_PIN_12,                          \
                             .pin_rx = GPIO_PIN_2,                           \
                             .alternate_func = GPIO_AF8_UART5}

#define UART6_PP1_HW_INFO   {.rcc_apbenr_usarten = RCC_APB2ENR_USART6EN,     \
                             .usart = USART6,                                \
                             .rcc_ahbenr_gpioen_tx = RCC_AHB1ENR_GPIOCEN,    \
                             .rcc_ahbenr_gpioen_rx = RCC_AHB1ENR_GPIOCEN,    \
                             .port_tx = GPIOC,                               \
                             .port_rx = GPIOC,                               \
                             .pin_tx = GPIO_PIN_6,                           \
                             .pin_rx = GPIO_PIN_7,                           \
                             .alternate_func = GPIO_AF8_USART6}

#define UART6_PP2_HW_INFO   {.rcc_apbenr_usarten = RCC_APB2ENR_USART6EN,     \
                             .usart = USART6,                                \
                             .rcc_ahbenr_gpioen_tx = RCC_AHB1ENR_GPIOGEN,    \
                             .rcc_ahbenr_gpioen_rx = RCC_AHB1ENR_GPIOGEN,    \
                             .port_tx = GPIOG,                               \
                             .port_rx = GPIOG,                               \
                             .pin_tx = GPIO_PIN_14,                          \
                             .pin_rx = GPIO_PIN_9,                           \
                             .alternate_func = GPIO_AF8_USART6}

/*
 * UART Hardware Information Typedef.
 */
typedef struct {
    uint32_t       rcc_apbenr_usarten;      /*!< UART RCC APBENR register */
    USART_TypeDef  *usart;                  /*!< USART */
    uint32_t       rcc_ahbenr_gpioen_tx;    /*!< TX GPIO RCC AHPENR register */
    uint32_t       rcc_ahbenr_gpioen_rx;    /*!< RX GPIO RCC AHPENR register */
    GPIO_TypeDef   *port_tx;                /*!< TX General Purpose I/O */
    GPIO_TypeDef   *port_rx;                /*!< RX General Purpose I/O */
    uint16_t       pin_tx;                  /*!< TX GPIO Pin */
    uint16_t       pin_rx;                  /*!< RX GPIO Pin */
    uint8_t        alternate_func;          /*!< UART alternative function */
} uart_hw_info_t;

/*
 * UART Handle Typedef.
 */
typedef struct uart {
    uart_num_t         uart_num;            /*!< UART Num */
    uart_pins_pack_t   uart_pins_pack;      /*!< UART Pins Pack */
    uart_hw_info_t     hw_info;             /*!< UART Hardware Information */
    uart_status_t      uart_status;
    UART_HandleTypeDef hal_handle;          /*!< UART_HandleTypeDef */
} uart_t;

/*
 * UART Hardware Information Mapping Table.
 */
uart_hw_info_t UART_HW_INFO_MAPPING[UART_NUM_MAX][UART_PINS_PACK_MAX] = {
    {UART1_PP1_HW_INFO, UART1_PP2_HW_INFO,               {0}},
    {UART2_PP1_HW_INFO, UART2_PP2_HW_INFO,               {0}},
    {UART3_PP1_HW_INFO, UART3_PP2_HW_INFO, UART3_PP3_HW_INFO},
    {UART4_PP1_HW_INFO, UART4_PP2_HW_INFO,               {0}},
    {UART5_PP1_HW_INFO,               {0},               {0}},
    {UART6_PP1_HW_INFO, UART6_PP2_HW_INFO,               {0}}
};

static uart_hw_info_t _uart_get_hw_info(uart_num_t uart_num, uart_pins_pack_t uart_pins_pack)
{
    uart_hw_info_t hw_info;
    hw_info = UART_HW_INFO_MAPPING[uart_num][uart_pins_pack];

    return hw_info;
}

static int _uart_cleanup(uart_handle_t handle)
{
    free(handle);

    return 0;
}

uart_handle_t uart_init(uart_config_t *config)
{
    /* Check input condition */
    if (!config)
    {
        return 0;
    }

    /* Allocate memory for handle structure */
    uart_handle_t handle;
    handle = calloc(1, sizeof(uart_t));
    if (handle == NULL)
    {
        return 0;
    }

    /* Get UART hardware information */
    handle->hw_info = _uart_get_hw_info(config->uart_num, config->uart_pins_pack);

    int err;

    /* Enable UART clock */
    do
    {
        uint32_t tmpreg = 0x00;
        if ((config->uart_num == UART_NUM_1) || (config->uart_num == UART_NUM_6)) {
            SET_BIT(RCC->APB2ENR, handle->hw_info.rcc_apbenr_usarten);
            tmpreg = READ_BIT(RCC->APB2ENR, handle->hw_info.rcc_apbenr_usarten);
        }
        else {
            SET_BIT(RCC->APB1ENR, handle->hw_info.rcc_apbenr_usarten);
            tmpreg = READ_BIT(RCC->APB1ENR, handle->hw_info.rcc_apbenr_usarten);
        }
        UNUSED(tmpreg);
    } while (0);

    /* Enable TX GPIO port clock */
    do {
        uint32_t tmpreg = 0x00;
        SET_BIT(RCC->AHB1ENR,  handle->hw_info.rcc_ahbenr_gpioen_tx);
        tmpreg = READ_BIT(RCC->AHB1ENR, handle->hw_info.rcc_ahbenr_gpioen_tx);
        UNUSED(tmpreg);
    } while (0);

    /* Enable RX GPIO port clock */
    do {
        uint32_t tmpreg = 0x00;
        SET_BIT(RCC->AHB1ENR, handle->hw_info.rcc_ahbenr_gpioen_rx);
        tmpreg = READ_BIT(RCC->AHB1ENR, handle->hw_info.rcc_ahbenr_gpioen_rx);
        UNUSED(tmpreg);
    } while (0);

    /* Configure UART */
    handle->hal_handle.Instance = handle->hw_info.usart;
    handle->hal_handle.Init.BaudRate = config->baudrate;
    handle->hal_handle.Init.WordLength = UART_WORDLENGTH_DEFAULT;
    handle->hal_handle.Init.StopBits = UART_STOPBITS_DEFAULT;
    handle->hal_handle.Init.Parity = UART_PARITY_DEFAULT;
    handle->hal_handle.Init.Mode = UART_MODE_DEFAULT;
    handle->hal_handle.Init.HwFlowCtl = UART_HW_FLOWCTRL_DEFAULT;
    handle->hal_handle.Init.OverSampling = UART_OVERSAMPLING_DEFAULT;
    err = HAL_UART_Init(&handle->hal_handle);
    if (err != HAL_OK)
    {
        _uart_cleanup(handle);
        return 0;
    }

    /* Configure UART TX pins */
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = handle->hw_info.pin_tx;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = handle->hw_info.alternate_func;
    HAL_GPIO_Init(handle->hw_info.port_tx, &GPIO_InitStruct);

    /* Configure UART RX pins */
    GPIO_InitStruct.Pin = handle->hw_info.pin_rx;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = handle->hw_info.alternate_func;
    HAL_GPIO_Init(handle->hw_info.port_rx, &GPIO_InitStruct);

    /* Update handle structure */
    handle->uart_num = config->uart_num;
    handle->uart_pins_pack = config->uart_pins_pack;
    handle->uart_status = UART_READY;

    return handle;
}

int uart_write_bytes(uart_handle_t handle, uint8_t *data, uint16_t length, uint32_t timeout_ms)
{
    /* Check if handle structure is empty or length equal 0 */
    if (handle == NULL || length == 0)
    {
        return -1;
    }

    /* Transmit data */
    handle->uart_status = UART_WRITING;
    if (HAL_UART_Transmit(&handle->hal_handle, data, length, timeout_ms))
    {
        handle->uart_status = UART_ERROR;
        return -1;
    }

    handle->uart_status = UART_READY;
    return 0;
}

int uart_read_bytes(uart_handle_t handle, uint8_t *buf, uint16_t length, uint32_t timeout_ms)
{
    /* Check if handle structure is empty or length equal 0 */
    if (handle == NULL || length == 0)
    {
        return -1;
    }

    /* Receive data */
    handle->uart_status = UART_READING;
    if (HAL_UART_Receive(&handle->hal_handle, buf, length, timeout_ms))
    {
        handle->uart_status = UART_ERROR;
        return -1;
    }

    handle->uart_status = UART_READY;
    return 0;
}

UART_HandleTypeDef uart_get_UART_HandleTypeDef(uart_handle_t handle)
{
    return handle->hal_handle;
}

