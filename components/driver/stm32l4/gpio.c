#include "stm_hal.h"
#include "stm_log.h"

#include "driver/gpio.h"

#define GPIO_SPEED_FREQ_DEFAULT     GPIO_SPEED_FREQ_VERY_HIGH   /*!< GPIO speed frequency default */
#define GPIO_LEVEL_DEFAULT          0                           /*!< GPIO level default */

#define GPIO_INIT_ERR_STR           "gpio_config error"
#define GPIO_SET_LEVEL_ERR_STR      "gpio_set_level error"
#define GPIO_TOGGLE_LEVEL_ERR_STR   "gpio_toggle_level error"

static const char* GPIO_TAG = "DRIVER GPIO";
#define GPIO_CHECK(a, str, ret)  if(!(a)) {                                             \
        STM_LOGE(GPIO_TAG,"%s:%d (%s):%s", __FILE__, __LINE__, __FUNCTION__, str);      \
        return (ret);                                                                   \
        }

GPIO_TypeDef* GPIOx_MAPPING[GPIO_PORT_MAX] = {
    GPIOA,          
    GPIOB,          
    GPIOC,          
    GPIOD,          
    GPIOE,
    GPIOF,          
    GPIOG,          
    GPIOH, 
    GPIOI          
};

uint16_t GPIO_PIN_MAPPING[GPIO_NUM_MAX] = {
    GPIO_PIN_0,     
    GPIO_PIN_1,     
    GPIO_PIN_2,     
    GPIO_PIN_3,     
    GPIO_PIN_4,     
    GPIO_PIN_5,     
    GPIO_PIN_6,     
    GPIO_PIN_7,     
    GPIO_PIN_8,     
    GPIO_PIN_9,     
    GPIO_PIN_10,    
    GPIO_PIN_11,    
    GPIO_PIN_12,    
    GPIO_PIN_13,    
    GPIO_PIN_14,    
    GPIO_PIN_15     
};

uint32_t GPIO_REG_PULL_MAPPING[GPIO_REG_PULL_MAX] = {
    GPIO_NOPULL,    
    GPIO_PULLUP,    
    GPIO_PULLDOWN   
};

uint32_t RCC_AHB2ENR_GPIOxEN_MAPPING[GPIO_PORT_MAX] = {
    RCC_AHB2ENR_GPIOAEN,    
    RCC_AHB2ENR_GPIOBEN,    
    RCC_AHB2ENR_GPIOCEN,    
    RCC_AHB2ENR_GPIODEN,    
    RCC_AHB2ENR_GPIOEEN, 
    RCC_AHB2ENR_GPIOFEN,    
    RCC_AHB2ENR_GPIOGEN,
    RCC_AHB2ENR_GPIOHEN, 
    RCC_AHB2ENR_GPIOIEN, 
};

uint32_t GPIO_MODE_MAPPING[GPIO_MODE_MAX] = {
    GPIO_MODE_INPUT,
    GPIO_MODE_OUTPUT_PP,
    GPIO_MODE_OUTPUT_OD,
    GPIO_MODE_AF_PP,
    GPIO_MODE_AF_OD,
    GPIO_MODE_ANALOG,
    GPIO_MODE_IT_RISING,
    GPIO_MODE_IT_FALLING,
    GPIO_MODE_IT_RISING_FALLING,
    GPIO_MODE_EVT_RISING,
    GPIO_MODE_EVT_FALLING,
    GPIO_MODE_EVT_RISING_FALLING
};

stm_err_t gpio_config(gpio_cfg_t *config)
{
    /* Check input parameters */
    GPIO_CHECK(config, GPIO_INIT_ERR_STR, STM_ERR_INVALID_ARG);
    GPIO_CHECK(config->gpio_port < GPIO_PORT_MAX, GPIO_INIT_ERR_STR, STM_ERR_INVALID_ARG);
    GPIO_CHECK(config->gpio_num < GPIO_NUM_MAX, GPIO_INIT_ERR_STR, STM_ERR_INVALID_ARG);
    GPIO_CHECK(config->mode < GPIO_MODE_MAX, GPIO_INIT_ERR_STR, STM_ERR_INVALID_ARG);
    GPIO_CHECK(config->reg_pull_mode < GPIO_REG_PULL_MAX, GPIO_INIT_ERR_STR, STM_ERR_INVALID_ARG);

    /* Check if hardware is not valid in this STM32 target */
    GPIO_CHECK(GPIOx_MAPPING[config->gpio_port], GPIO_INIT_ERR_STR, STM_ERR_INVALID_ARG);

    /* Enable GPIO Port clock */
    uint32_t tmpreg = 0x00;
    SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOxEN_MAPPING[config->gpio_port]);
    tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOxEN_MAPPING[config->gpio_port]);
    UNUSED(tmpreg);

    /* Initialize GPIO function */
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_MAPPING[config->gpio_num];
    GPIO_InitStruct.Mode = GPIO_MODE_MAPPING[config->mode];
    GPIO_InitStruct.Pull = GPIO_REG_PULL_MAPPING[config->reg_pull_mode];
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_DEFAULT;
    HAL_GPIO_Init(GPIOx_MAPPING[config->gpio_port], &GPIO_InitStruct);

    return STM_OK;
}

stm_err_t gpio_set_level(gpio_port_t gpio_port, gpio_num_t gpio_num, bool state)
{
    /* Check input parameters */
    GPIO_CHECK(gpio_port < GPIO_PORT_MAX, GPIO_SET_LEVEL_ERR_STR, STM_ERR_INVALID_ARG);
    GPIO_CHECK(gpio_num < GPIO_NUM_MAX, GPIO_SET_LEVEL_ERR_STR, STM_ERR_INVALID_ARG);

    /* Check if hardware is not valid in this STM32 target */
    GPIO_CHECK(GPIOx_MAPPING[gpio_port], GPIO_SET_LEVEL_ERR_STR, STM_ERR_INVALID_ARG);

    /* Set GPIO level */
    HAL_GPIO_WritePin(GPIOx_MAPPING[gpio_port], GPIO_PIN_MAPPING[gpio_num], state);

    return STM_OK;
}

stm_err_t gpio_toggle_level(gpio_port_t gpio_port, gpio_num_t gpio_num)
{
    /* Check input parameters */
    GPIO_CHECK(gpio_port < GPIO_PORT_MAX, GPIO_TOGGLE_LEVEL_ERR_STR, STM_ERR_INVALID_ARG);
    GPIO_CHECK(gpio_num < GPIO_NUM_MAX, GPIO_TOGGLE_LEVEL_ERR_STR, STM_ERR_INVALID_ARG);

    /* Check if hardware is not valid in this STM32 target */
    GPIO_CHECK(GPIOx_MAPPING[gpio_port], GPIO_TOGGLE_LEVEL_ERR_STR, STM_ERR_INVALID_ARG);

    /* Toggle GPIO level */
    HAL_GPIO_TogglePin(GPIOx_MAPPING[gpio_port], GPIO_PIN_MAPPING[gpio_num]);
    
    return STM_OK;
}

bool gpio_get_level(gpio_port_t gpio_port, gpio_num_t gpio_num) 
{
    /* Check input parameters */
    GPIO_CHECK(gpio_port < GPIO_PORT_MAX, GPIO_TOGGLE_LEVEL_ERR_STR, STM_ERR_INVALID_ARG);
    GPIO_CHECK(gpio_num < GPIO_NUM_MAX, GPIO_TOGGLE_LEVEL_ERR_STR, STM_ERR_INVALID_ARG);

    /* Check if hardware is not valid in this STM32 target */
    GPIO_CHECK(GPIOx_MAPPING[gpio_port], GPIO_TOGGLE_LEVEL_ERR_STR, STM_ERR_INVALID_ARG);

    return HAL_GPIO_ReadPin(GPIOx_MAPPING[gpio_port], GPIO_PIN_MAPPING[gpio_num]);
}



