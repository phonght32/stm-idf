#include "include/gpio.h"

#define GPIO_SPEED_FREQ_DEFAULT     GPIO_SPEED_FREQ_VERY_HIGH   /*!< GPIO speed frequency default */
#define GPIO_LEVEL_DEFAULT          0                           /*!< GPIO level default */

/*
 * GPIO Handle Typedef.
 */
typedef struct gpio {
    gpio_port_t     gpio_port;      /*!< GPIO Port */
    gpio_num_t      gpio_num;       /*!< GPIO Pin */
    gpio_mode_t     gpio_mode;      /*!< GPIO Mode */
    gpio_reg_pull_t gpio_reg_pull;  /*!< GPIO Pull Register */
    bool            gpio_level;     /*!< GPIO Level */
} gpio_t;

/*
 * GPIO Port Mapping Table.
 */
GPIO_TypeDef *GPIOx_MAPPING[GPIO_PORT_MAX] = {
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
uint16_t GPIO_PIN_x_MAPPING[GPIO_NUM_MAX] = {
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
uint32_t GPIO_REG_PULL_MAPPING[GPIO_REG_PULL_MAX] = {
    GPIO_NOPULL,    /*!< HAL GPIO no pull registor define */
    GPIO_PULLUP,    /*!< HAL GPIO pull up registor define */
    GPIO_PULLDOWN   /*!< HAL GPIO pull down registor define */
};

/*
 * GPIO RCC_APBENR Register Mapping Table.
 */
uint32_t RCC_AHB1ENR_GPIOxEN_MAPPING[GPIO_PORT_MAX] = {
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

static void _gpio_cleanup(gpio_handle_t handle)
{
    free(handle);
}

gpio_handle_t gpio_init(gpio_config_t *config)
{
    /* Check input parameters */
    if (!config)
    {
        return 0;
    }

    /* Allocate memory for handle structre */
    gpio_handle_t handle;
    handle = calloc(1, sizeof(gpio_t));
    if (handle == NULL)
    {
        return 0;
    }

    /* Mapping GPIO Parameters */
    uint32_t RCC_AHB1ENR_GPIOxEN;
    uint16_t GPIO_PIN_x;
    GPIO_TypeDef *GPIOx;
    uint32_t GPIO_REG_PULL_TYPE;

    RCC_AHB1ENR_GPIOxEN = RCC_AHB1ENR_GPIOxEN_MAPPING[config->gpio_port];
    GPIO_PIN_x = GPIO_PIN_x_MAPPING[config->gpio_num];
    GPIOx = GPIOx_MAPPING[config->gpio_port];
    GPIO_REG_PULL_TYPE = GPIO_REG_PULL_MAPPING[config->gpio_reg_pull];

    /* Enable GPIO Port clock */
    do
    {
        uint32_t tmpreg = 0x00;
        SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOxEN);
        tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOxEN);
        UNUSED(tmpreg);
    } while (0);

    /* Initialize GPIO function */
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if (config->gpio_mode == GPIO_INPUT)        /*!< Input mode configuration */
    {
        GPIO_InitStruct.Pin = GPIO_PIN_x;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_REG_PULL_TYPE;
        HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
    }
    if (config->gpio_mode == GPIO_OUTPUT)       /*!< Output mode configuration */
    {
        HAL_GPIO_WritePin(GPIOx, GPIO_PIN_x, GPIO_PIN_RESET);
        GPIO_InitStruct.Pin = GPIO_PIN_x;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_REG_PULL_TYPE;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_DEFAULT;
        HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);

        /* Set GPIO default level */
        HAL_GPIO_WritePin(GPIOx_MAPPING[config->gpio_port], GPIO_PIN_x_MAPPING[config->gpio_num], 0);
    }

    /* Update handle structure */
    handle->gpio_port     = config->gpio_port;
    handle->gpio_num      = config->gpio_num;
    handle->gpio_mode     = config->gpio_mode;
    handle->gpio_reg_pull = config->gpio_reg_pull;
    handle->gpio_level    = GPIO_LEVEL_DEFAULT;

    return handle;
}

int gpio_deinit(gpio_handle_t handle)
{
    /* Check if handle structure is empty */
    if (!handle)
    {
        return -1;
    }

    /* Deinit GPIO pin */
    HAL_GPIO_DeInit(GPIOx_MAPPING[handle->gpio_port], GPIO_PIN_x_MAPPING[handle->gpio_num]);

    /* Clean handle structure */
    _gpio_cleanup(handle);

    return 0;
}

int gpio_set_level(gpio_handle_t handle, bool state)
{
    /* Check if handle structure is empty */
    if (!handle)
    {
        return -1;
    }
    /* Configure GPIO level */
    HAL_GPIO_WritePin(GPIOx_MAPPING[handle->gpio_port], GPIO_PIN_x_MAPPING[handle->gpio_num], state);

    /* Update handle structure */
    handle->gpio_level = state;

    return 0;
}

int gpio_toggle_level(gpio_handle_t handle)
{
    /* Check if handle structure is empty */
    if (!handle)
    {
        return -1;
    }
    /* Configure GPIO level */
    HAL_GPIO_TogglePin(GPIOx_MAPPING[handle->gpio_port], GPIO_PIN_x_MAPPING[handle->gpio_num]);

    /* Update handle structure */
    handle->gpio_level = !handle->gpio_level;

    return 0;
}

int gpio_get_level(gpio_handle_t handle)
{
    /* Check if handle structure is empty */
    if (!handle)
    {
        return -1;
    }

    /* Get GPIO level */
    if (handle->gpio_mode == GPIO_INPUT)
    {
        return HAL_GPIO_ReadPin(GPIOx_MAPPING[handle->gpio_port], GPIO_PIN_x_MAPPING[handle->gpio_num]);
    }

    if (handle->gpio_mode == GPIO_OUTPUT)
    {
        return handle->gpio_level;
    }

    return -1;
}


