#include "include/gpio.h"

#define GPIO_SPEED_FREQ_DEFAULT     GPIO_SPEED_FREQ_VERY_HIGH   /*!< GPIO speed frequency default */
#define GPIO_LEVEL_DEFAULT          0                           /*!< GPIO level default */

/*
 * GPIO Port Mapping Table.
 */
static GPIO_TypeDef *GPIOx_MAPPING[GPIO_PORT_MAX] = {
    GPIOA,          /*!< HAL GPIO Port A define */
    GPIOB,          /*!< HAL GPIO Port B define */
    GPIOC,          /*!< HAL GPIO Port C define */
    GPIOD,          /*!< HAL GPIO Port D define */
    GPIOE,          /*!< HAL GPIO Port E define */
    GPIOF,          /*!< HAL GPIO Port F define */
    GPIOG,          /*!< HAL GPIO Port G define */
    GPIOH,          /*!< HAL GPIO Port H define */
    GPIOI           /*!< HAL GPIO Port I define */
};

/*
 * GPIO Pin Mapping Table.
 */
static uint16_t GPIO_PIN_x_MAPPING[GPIO_NUM_MAX] = {
    GPIO_PIN_0,     /*!< HAL GPIO Pin 0 define */
    GPIO_PIN_1,     /*!< HAL GPIO Pin 1 define */
    GPIO_PIN_2,     /*!< HAL GPIO Pin 2 define */
    GPIO_PIN_3,     /*!< HAL GPIO Pin 3 define */
    GPIO_PIN_4,     /*!< HAL GPIO Pin 4 define */
    GPIO_PIN_5,     /*!< HAL GPIO Pin 5 define */
    GPIO_PIN_6,     /*!< HAL GPIO Pin 6 define */
    GPIO_PIN_7,     /*!< HAL GPIO Pin 7 define */
    GPIO_PIN_8,     /*!< HAL GPIO Pin 8 define */
    GPIO_PIN_9,     /*!< HAL GPIO Pin 9 define */
    GPIO_PIN_10,    /*!< HAL GPIO Pin 10 define */
    GPIO_PIN_11,    /*!< HAL GPIO Pin 11 define */
    GPIO_PIN_12,    /*!< HAL GPIO Pin 12 define */
    GPIO_PIN_13,    /*!< HAL GPIO Pin 13 define */
    GPIO_PIN_14,    /*!< HAL GPIO Pin 14 define */
    GPIO_PIN_15     /*!< HAL GPIO Pin 15 define */
};

/*
 * GPIO Pull Register Mapping Table.
 */
static uint32_t GPIO_REG_PULL_MAPPING[GPIO_REG_PULL_MAX] = {
    GPIO_NOPULL,    /*!< HAL GPIO no pull registor define */
    GPIO_PULLUP,    /*!< HAL GPIO pull up registor define */
    GPIO_PULLDOWN   /*!< HAL GPIO pull down registor define */
};

/*
 * GPIO RCC_APBENR Register Mapping Table.
 */
static uint32_t RCC_AHB1ENR_GPIOxEN_MAPPING[GPIO_PORT_MAX] = {
    RCC_AHB1ENR_GPIOAEN,    /*!< HAL GPIO Port A RCC AHBENR Register define */
    RCC_AHB1ENR_GPIOBEN,    /*!< HAL GPIO Port B RCC AHBENR Register define */
    RCC_AHB1ENR_GPIOCEN,    /*!< HAL GPIO Port C RCC AHBENR Register define */
    RCC_AHB1ENR_GPIODEN,    /*!< HAL GPIO Port D RCC AHBENR Register define */
    RCC_AHB1ENR_GPIOEEN,    /*!< HAL GPIO Port E RCC AHBENR Register define */
    RCC_AHB1ENR_GPIOFEN,    /*!< HAL GPIO Port F RCC AHBENR Register define */
    RCC_AHB1ENR_GPIOGEN,    /*!< HAL GPIO Port G RCC AHBENR Register define */
    RCC_AHB1ENR_GPIOHEN,    /*!< HAL GPIO Port H RCC AHBENR Register define */
    RCC_AHB1ENR_GPIOIEN,    /*!< HAL GPIO Port I RCC AHBENR Register define */
};

int gpio_config(gpio_config_t *config)
{
    /* Check input parameters */
    if (!config)
    {
        return -1;
    }

    /* Mapping GPIO Parameters */
    uint32_t RCC_AHB1ENR_GPIOxEN;
    uint16_t GPIO_PIN_x;
    GPIO_TypeDef *GPIOx;
    uint32_t GPIO_REG_PULL_TYPE;

    RCC_AHB1ENR_GPIOxEN = RCC_AHB1ENR_GPIOxEN_MAPPING[config->port];
    GPIO_PIN_x = GPIO_PIN_x_MAPPING[config->num];
    GPIOx = GPIOx_MAPPING[config->port];
    GPIO_REG_PULL_TYPE = GPIO_REG_PULL_MAPPING[config->pull_mode];

    /* Enable GPIO Port clock */
    uint32_t tmpreg = 0x00;
    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOxEN);
    tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOxEN);
    UNUSED(tmpreg);

    /* Initialize GPIO function */
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if (config->mode == GPIO_INPUT)        /*!< Input mode configuration */
    {
        GPIO_InitStruct.Pin = GPIO_PIN_x;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_REG_PULL_TYPE;
        HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
    }
    if (config->mode == GPIO_OUTPUT)       /*!< Output mode configuration */
    {
        HAL_GPIO_WritePin(GPIOx, GPIO_PIN_x, GPIO_PIN_RESET);
        GPIO_InitStruct.Pin = GPIO_PIN_x;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_REG_PULL_TYPE;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_DEFAULT;
        HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);

        /* Set GPIO default level */
        HAL_GPIO_WritePin(GPIOx_MAPPING[config->port], GPIO_PIN_x_MAPPING[config->num], 0);
    }

    return 0;
}

void gpio_set_level(gpio_port_t port, gpio_num_t num, bool state)
{
    HAL_GPIO_WritePin(GPIOx_MAPPING[port], GPIO_PIN_x_MAPPING[num], state);
}

void gpio_toggle_level(gpio_port_t port, gpio_num_t num)
{
    HAL_GPIO_TogglePin(GPIOx_MAPPING[port], GPIO_PIN_x_MAPPING[num]);
}



