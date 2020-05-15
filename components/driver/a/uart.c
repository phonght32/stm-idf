#include "stm_hal.h"
#include "stm_log.h"

#include "driver/uart.h"
#include "uart_mapping.h"

#define UART_WORDLENGTH_DEFAULT         UART_WORDLENGTH_8B      /*!< Default UART word length */
#define UART_STOPBITS_DEFAULT           UART_STOPBITS_1         /*!< Default UART stop bits */
#define UART_PARITY_DEFAULT             UART_PARITY_NONE        /*!< Default UART parity */
#define UART_HW_FLOWCTRL_DEFAULT        UART_HWCONTROL_NONE     /*!< Default UART hardware flow control */
#define UART_OVERSAMPLING_DEFAULT       UART_OVERSAMPLING_16    /*!< Default UART over sampling */
#define UART_MODE_DEFAULT               UART_MODE_TX_RX         /*!< Default UART mode */

#define UART_INIT_ERR_STR           "uart init error"
#define UART_TRANS_ERR_STR          "uart transmit error"
#define UART_REC_ERR_STR            "uart_receive error"

static const char* UART_TAG = "DRIVER UART";
#define UART_CHECK(a, str, ret)  if(!(a)) {                                             \
        STM_LOGE(UART_TAG,"%s:%d (%s):%s", __FILE__, __LINE__, __FUNCTION__, str);      \
        return (ret);                                                                   \
        }

static UART_HandleTypeDef uart_handle[UART_NUM_MAX];

static uart_hw_info_t _uart_get_hw_info(uart_num_t uart_num, uart_pins_pack_t uart_pins_pack)
{
    uart_hw_info_t hw_info;
    hw_info = UART_HW_INFO_MAPPING[uart_num][uart_pins_pack];

    return hw_info;
}

stm_err_t uart_config(uart_config_t *config)
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
    UART_CHECK(uart_num < UART_NUM_MAX, UART_TRANS_ERR_STR, STM_ERR_INVALID_ARG);
    UART_CHECK(!HAL_UART_Transmit(&uart_handle[uart_num], data, length, timeout_ms), UART_TRANS_ERR_STR, STM_FAIL);

    return STM_OK;
}

stm_err_t uart_read_bytes(uart_num_t uart_num, uint8_t *buf, uint16_t length, uint32_t timeout_ms)
{
    UART_CHECK(uart_num < UART_NUM_MAX, UART_REC_ERR_STR, STM_ERR_INVALID_ARG);
    UART_CHECK(!HAL_UART_Receive(&uart_handle[uart_num], buf, length, timeout_ms), UART_REC_ERR_STR, STM_FAIL);

    return STM_OK;
}

