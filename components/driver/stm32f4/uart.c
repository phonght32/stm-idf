#include "stm_hal.h"
#include "stm_log.h"

#include "driver/uart.h"

#define UART_WORDLENGTH_DEFAULT         UART_WORDLENGTH_8B      /*!< Default UART word length */
#define UART_STOPBITS_DEFAULT           UART_STOPBITS_1         /*!< Default UART stop bits */
#define UART_PARITY_DEFAULT             UART_PARITY_NONE        /*!< Default UART parity */
#define UART_HW_FLOWCTRL_DEFAULT        UART_HWCONTROL_NONE     /*!< Default UART hardware flow control */
#define UART_OVERSAMPLING_DEFAULT       UART_OVERSAMPLING_16    /*!< Default UART over sampling */
#define UART_MODE_DEFAULT               UART_MODE_TX_RX         /*!< Default UART mode */

#define UART_INIT_ERR_STR           "uart_config error"
#define UART_TRANS_ERR_STR          "uart_write_bytes error"
#define UART_REC_ERR_STR            "uart_read_bytes error"

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

#if defined(STM32F401xC)
#define UART6_PP2_HW_INFO   {0}
#else 
#define UART6_PP2_HW_INFO   {.rcc_ahbenr_gpioen_tx = RCC_AHB1ENR_GPIOGEN,    \
                             .rcc_ahbenr_gpioen_rx = RCC_AHB1ENR_GPIOGEN,    \
                             .port_tx = GPIOG,                               \
                             .port_rx = GPIOG,                               \
                             .pin_tx = GPIO_PIN_14,                          \
                             .pin_rx = GPIO_PIN_9}
#endif


static const char* UART_TAG = "DRIVER_UART";
#define UART_CHECK(a, str, ret)  if(!(a)) {                                             \
        STM_LOGE(UART_TAG,"%s:%d (%s):%s", __FILE__, __LINE__, __FUNCTION__, str);      \
        return (ret);                                                                   \
        }

static UART_HandleTypeDef uart_handle[UART_NUM_MAX];

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
    
#if !defined(STM32F401xC)
    RCC_APB1ENR_USART3EN,
    RCC_APB1ENR_UART4EN,
    RCC_APB1ENR_UART5EN,
#else
    0,
    0,
    0,
#endif

    RCC_APB2ENR_USART6EN
};

static USART_TypeDef* UART_MAPPING[UART_NUM_MAX] = {
    USART1,
    USART2,
#if !defined(STM32F401xC)
    USART3,
    UART4,
    UART5,
#else
    0,
    0,
    0,
#endif
    USART6
};

static uint32_t UART_ALTERNATE_FUNC_MAPPING[UART_NUM_MAX] = {
    GPIO_AF7_USART1,
    GPIO_AF7_USART2,
#if !defined(STM32F401xC)
    GPIO_AF7_USART3,
    GPIO_AF8_UART4,
    GPIO_AF8_UART5,
#else
    0,
    0,
    0,
#endif
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

static uart_hw_info_t _uart_get_hw_info(uart_num_t uart_num, uart_pins_pack_t uart_pins_pack)
{
    uart_hw_info_t hw_info;
    hw_info = UART_HW_INFO_MAPPING[uart_num][uart_pins_pack];

    return hw_info;
}

stm_err_t uart_config(uart_cfg_t *config)
{
    /* Check input condition */
    UART_CHECK(config, UART_INIT_ERR_STR, STM_ERR_INVALID_ARG);
    UART_CHECK(config->uart_num < UART_NUM_MAX, UART_INIT_ERR_STR, STM_ERR_INVALID_ARG);
    UART_CHECK(config->uart_pins_pack < UART_PINS_PACK_MAX, UART_INIT_ERR_STR, STM_ERR_INVALID_ARG);
    UART_CHECK(config->frame_format < UART_FRAME_MAX_TYPE, UART_INIT_ERR_STR, STM_ERR_INVALID_ARG);
    UART_CHECK(config->mode < UART_TRANSFER_MODE_MAX, UART_INIT_ERR_STR, STM_ERR_INVALID_ARG);
    UART_CHECK(config->hw_flw_ctrl < UART_HW_FLW_CTRL_MAX_TYPE, UART_INIT_ERR_STR, STM_ERR_INVALID_ARG);
    
    /* Get UART hardware information */
    uart_hw_info_t hw_info = _uart_get_hw_info(config->uart_num, config->uart_pins_pack);

    /* Check if hardware is not valid in this STM32 target */
    UART_CHECK(UART_MAPPING[config->uart_num], UART_INIT_ERR_STR, STM_ERR_INVALID_ARG);
    UART_CHECK(hw_info.port_tx, UART_INIT_ERR_STR, STM_ERR_INVALID_ARG);

    /* Enable UART clock */
    uint32_t tmpreg = 0x00;
    if ((config->uart_num == UART_NUM_1) || (config->uart_num == UART_NUM_6)) 
    {
        SET_BIT(RCC->APB2ENR, RCC_APBENR_UARTEN_MAPPING[config->uart_num]);
        tmpreg = READ_BIT(RCC->APB2ENR, RCC_APBENR_UARTEN_MAPPING[config->uart_num]);
    }
    else 
    {
        SET_BIT(RCC->APB1ENR, RCC_APBENR_UARTEN_MAPPING[config->uart_num]);
        tmpreg = READ_BIT(RCC->APB1ENR, RCC_APBENR_UARTEN_MAPPING[config->uart_num]);
    }
    UNUSED(tmpreg);

    /* Enable TX GPIO port clock */
    tmpreg = 0x00;
    SET_BIT(RCC->AHB1ENR,  hw_info.rcc_ahbenr_gpioen_tx);
    tmpreg = READ_BIT(RCC->AHB1ENR, hw_info.rcc_ahbenr_gpioen_tx);
    UNUSED(tmpreg);

    /* Enable RX GPIO port clock */
    tmpreg = 0x00;
    SET_BIT(RCC->AHB1ENR, hw_info.rcc_ahbenr_gpioen_rx);
    tmpreg = READ_BIT(RCC->AHB1ENR, hw_info.rcc_ahbenr_gpioen_rx);
    UNUSED(tmpreg);

    /* Get UART parameters */
    uint32_t word_len       = UART_FRAME_FORMAT_MAPPING[config->frame_format][FRAME_FORMAT_WORD_LEN];
    uint32_t parity         = UART_FRAME_FORMAT_MAPPING[config->frame_format][FRAME_FORMAT_PARITY];
    uint32_t stop_bit       = UART_FRAME_FORMAT_MAPPING[config->frame_format][FRAME_FORMAT_STOP_BIT];
    uint32_t mode           = UART_TRANSFER_MODE_MAPPING[config->mode];
    uint32_t hw_flw_ctrl    = UART_HW_FLW_CTRL_MAPPING[config->hw_flw_ctrl];

    /* Configure UART */
    uart_handle[config->uart_num].Instance = UART_MAPPING[config->uart_num];
    uart_handle[config->uart_num].Init.BaudRate = config->baudrate;
    uart_handle[config->uart_num].Init.WordLength = word_len;
    uart_handle[config->uart_num].Init.StopBits = stop_bit;
    uart_handle[config->uart_num].Init.Parity = parity;
    uart_handle[config->uart_num].Init.Mode = mode;
    uart_handle[config->uart_num].Init.HwFlowCtl = hw_flw_ctrl;
    uart_handle[config->uart_num].Init.OverSampling = UART_OVERSAMPLING_DEFAULT;
    UART_CHECK(!HAL_UART_Init(&uart_handle[config->uart_num]), UART_INIT_ERR_STR, STM_FAIL);

    /* Configure UART TX pins */
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = hw_info.pin_tx;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = UART_ALTERNATE_FUNC_MAPPING[config->uart_num];
    HAL_GPIO_Init(hw_info.port_tx, &GPIO_InitStruct);

    /* Configure UART RX pins */
    GPIO_InitStruct.Pin = hw_info.pin_rx;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = UART_ALTERNATE_FUNC_MAPPING[config->uart_num];
    HAL_GPIO_Init(hw_info.port_rx, &GPIO_InitStruct);

    return STM_OK;
}

stm_err_t uart_write_bytes(uart_num_t uart_num, uint8_t *data, uint16_t length, uint32_t timeout_ms)
{
    /* Check input conditions */
    UART_CHECK(uart_num < UART_NUM_MAX, UART_TRANS_ERR_STR, STM_ERR_INVALID_ARG);

    /* Check if hardware is not valid in this STM32 target */
    UART_CHECK(UART_MAPPING[uart_num], UART_TRANS_ERR_STR, STM_ERR_INVALID_ARG);

    /* UART write data */
    UART_CHECK(!HAL_UART_Transmit(&uart_handle[uart_num], data, length, timeout_ms), UART_TRANS_ERR_STR, STM_FAIL);
    
    return STM_OK;
}

stm_err_t uart_read_bytes(uart_num_t uart_num, uint8_t *buf, uint16_t length, uint32_t timeout_ms)
{
    /* Check input conditions */
    UART_CHECK(uart_num < UART_NUM_MAX, UART_REC_ERR_STR, STM_ERR_INVALID_ARG);

    /* Check if hardware is not valid in this STM32 target */
    UART_CHECK(UART_MAPPING[uart_num], UART_REC_ERR_STR, STM_ERR_INVALID_ARG);

    /* UART read data */
    UART_CHECK(!HAL_UART_Receive(&uart_handle[uart_num], buf, length, timeout_ms), UART_REC_ERR_STR, STM_FAIL);

    return STM_OK;
}

