#include "include/i2c.h"

#define I2C_DUTYCYCLE_DEFAULT           I2C_DUTYCYCLE_2             /*!< Default I2C duty cycle */
#define I2C_CLOCKSPEED_DEFAULT          100000                      /*!< Default I2C clock speed */
#define I2C_OWN_ADDRESS1_DEFAULT        0                           /*!< Default I2C own address 1 */
#define I2C_ADDRESSING_MODE_DEFAULT     I2C_ADDRESSINGMODE_7BIT     /*!< Default I2C address mode */
#define I2C_DUAL_ADDRESS_MODE_DEFAULT   I2C_DUALADDRESS_DISABLE     /*!< Default I2C dual address mode */
#define I2C_OWN_ADDRESS2_DEFAULT        0                           /*!< Default I2C own address 2 */
#define I2C_GENERALCALL_MODE_DEFAULT    I2C_GENERALCALL_DISABLE     /*!< Default I2C general call mode */
#define I2C_NOSTRETCH_MODE_DEFAULT      I2C_NOSTRETCH_DISABLE       /*!< Default I2C nostretch mode */

#define GPIO_MODE_DEFAULT               GPIO_MODE_AF_OD             /*!< Default GPIO mode */
#define GPIO_PULL_REG_DEFAULT           GPIO_PULLUP                 /*!< Default pull registor mode */
#define GPIO_SPEED_FREQ_DEFAULT         GPIO_SPEED_FREQ_VERY_HIGH   /*!< Default GPIO speed */

/*
 * I2C Hardware Information Define.
 */
#define I2C1_PP1_HW_INFO    {.i2c = I2C1,                                   \
                             .rcc_apbenr_i2cen = RCC_APB1ENR_I2C1EN,        \
                             .rcc_ahbenr_gpio_scl = RCC_AHB1ENR_GPIOBEN,    \
                             .rcc_ahbenr_gpio_sda = RCC_AHB1ENR_GPIOBEN,    \
                             .port_scl = GPIOB,                             \
                             .port_sda = GPIOB,                             \
                             .pin_scl = GPIO_PIN_6,                         \
                             .pin_sda = GPIO_PIN_7,                         \
                             .alternate_func = GPIO_AF4_I2C1}

#define I2C1_PP2_HW_INFO    {.i2c = I2C1,                                   \
                             .rcc_apbenr_i2cen = RCC_APB1ENR_I2C1EN,        \
                             .rcc_ahbenr_gpio_scl = RCC_AHB1ENR_GPIOBEN,    \
                             .rcc_ahbenr_gpio_sda = RCC_AHB1ENR_GPIOBEN,    \
                             .port_scl = GPIOB,                             \
                             .port_sda = GPIOB,                             \
                             .pin_scl = GPIO_PIN_8,                         \
                             .pin_sda = GPIO_PIN_9,                         \
                             .alternate_func = GPIO_AF4_I2C1}

#define I2C1_PP3_HW_INFO    {.i2c = I2C1,                                   \
                             .rcc_apbenr_i2cen = RCC_APB1ENR_I2C1EN,        \
                             .rcc_ahbenr_gpio_scl = RCC_AHB1ENR_GPIOBEN,    \
                             .rcc_ahbenr_gpio_sda = RCC_AHB1ENR_GPIOBEN,    \
                             .port_scl = GPIOB,                             \
                             .port_sda = GPIOB,                             \
                             .pin_scl = GPIO_PIN_6,                         \
                             .pin_sda = GPIO_PIN_9,                         \
                             .alternate_func = GPIO_AF4_I2C1}

#define I2C2_PP1_HW_INFO    {.i2c = I2C2,                                   \
                             .rcc_apbenr_i2cen = RCC_APB1ENR_I2C2EN,        \
                             .rcc_ahbenr_gpio_scl = RCC_AHB1ENR_GPIOBEN,    \
                             .rcc_ahbenr_gpio_sda = RCC_AHB1ENR_GPIOBEN,    \
                             .port_scl = GPIOB,                             \
                             .port_sda = GPIOB,                             \
                             .pin_scl = GPIO_PIN_10,                        \
                             .pin_sda = GPIO_PIN_11,                        \
                             .alternate_func = GPIO_AF4_I2C2}

#define I2C2_PP2_HW_INFO    {.i2c = I2C2,                                   \
                             .rcc_apbenr_i2cen = RCC_APB1ENR_I2C2EN,        \
                             .rcc_ahbenr_gpio_scl = RCC_AHB1ENR_GPIOFEN,    \
                             .rcc_ahbenr_gpio_sda = RCC_AHB1ENR_GPIOFEN,    \
                             .port_scl = GPIOF,                             \
                             .port_sda = GPIOF,                             \
                             .pin_scl = GPIO_PIN_1,                         \
                             .pin_sda = GPIO_PIN_0,                         \
                             .alternate_func = GPIO_AF4_I2C2}

#define I2C2_PP3_HW_INFO    {.i2c = I2C2,                                   \
                             .rcc_apbenr_i2cen = RCC_APB1ENR_I2C2EN,        \
                             .rcc_ahbenr_gpio_scl = RCC_AHB1ENR_GPIOHEN,    \
                             .rcc_ahbenr_gpio_sda = RCC_AHB1ENR_GPIOHEN,    \
                             .port_scl = GPIOH,                             \
                             .port_sda = GPIOH,                             \
                             .pin_scl = GPIO_PIN_4,                         \
                             .pin_sda = GPIO_PIN_5,                         \
                             .alternate_func = GPIO_AF4_I2C2}

#define I2C3_PP1_HW_INFO    {.i2c = I2C3,                                   \
                             .rcc_apbenr_i2cen = RCC_APB1ENR_I2C3EN,        \
                             .rcc_ahbenr_gpio_scl = RCC_AHB1ENR_GPIOAEN,    \
                             .rcc_ahbenr_gpio_sda = RCC_AHB1ENR_GPIOCEN,    \
                             .port_scl = GPIOA,                             \
                             .port_sda = GPIOC,                             \
                             .pin_scl = GPIO_PIN_8,                         \
                             .pin_sda = GPIO_PIN_9,                         \
                             .alternate_func = GPIO_AF4_I2C3}

#define I2C3_PP2_HW_INFO    {.i2c = I2C3,                                   \
                             .rcc_apbenr_i2cen = RCC_APB1ENR_I2C3EN,        \
                             .rcc_ahbenr_gpio_scl = RCC_AHB1ENR_GPIOHEN,    \
                             .rcc_ahbenr_gpio_sda = RCC_AHB1ENR_GPIOHEN,    \
                             .port_scl = GPIOH,                             \
                             .port_sda = GPIOH,                             \
                             .pin_scl = GPIO_PIN_7,                         \
                             .pin_sda = GPIO_PIN_8,                         \
                             .alternate_func = GPIO_AF4_I2C3}

/*
 * I2C Hardware Information Structure.
 */
typedef struct {
    I2C_TypeDef     *i2c;                   /*!< I2C */
    uint32_t        rcc_apbenr_i2cen;       /*!< I2C RCC APBENR register */
    uint32_t        rcc_ahbenr_gpio_scl;    /*!< SCL GPIO RCC AHPENR register */
    uint32_t        rcc_ahbenr_gpio_sda;    /*!< SDA GPIO RCC AHPENR register */
    GPIO_TypeDef    *port_scl;              /*!< SCL General Purpose I/O */
    GPIO_TypeDef    *port_sda;              /*!< SDA General Purpose I/O */
    uint16_t        pin_scl;                /*!< SCL GPIO Pin */
    uint16_t        pin_sda;                /*!< SDA GPIO Pin */
    uint8_t         alternate_func;         /*!< I2C Alternate Function */
} i2c_hw_info_t;

/*
 * I2C Handle Typedef.
 */
typedef struct i2c {
    i2c_num_t i2c_num;                  /*!< I2C Num */
    i2c_pins_pack_t i2c_pins_pack;      /*!< I2C Pins Pack */
    i2c_hw_info_t hw_info;              /*!< I2C Hardware Information */
    i2c_status_t i2c_status;                /*!< I2C status */
    I2C_HandleTypeDef hal_handle;       /*!< I2C_HandleTypeDef */
} i2c_t;

/*
 * I2C Hardware Information Mapping Table.
 */
i2c_hw_info_t I2C_HW_INFO_MAPPING[I2C_NUM_MAX][I2C_PINS_PACK_MAX] = {
    {I2C1_PP1_HW_INFO, I2C1_PP2_HW_INFO, I2C1_PP3_HW_INFO},
    {I2C2_PP1_HW_INFO, I2C2_PP2_HW_INFO, I2C2_PP3_HW_INFO},
    {I2C3_PP1_HW_INFO, I2C3_PP2_HW_INFO, {0}             }
};


static i2c_hw_info_t _i2c_get_hw_info(i2c_num_t i2c_num, i2c_pins_pack_t i2c_pins_pack)
{
    i2c_hw_info_t hw_info;
    hw_info = I2C_HW_INFO_MAPPING[i2c_num][i2c_pins_pack];

    return hw_info;
}

i2c_handle_t i2c_init(i2c_config_t *config)
{
    /* Check input condition */
    if (!config)
    {
        return 0;
    }

    /* Allocate memory for handle structure */
    i2c_handle_t handle;
    handle = calloc(1, sizeof(i2c_t));
    if (handle == NULL)
    {
        return 0;
    }

    /* Get I2C hardware information */
    handle->hw_info = _i2c_get_hw_info(config->i2c_num, config->i2c_pins_pack);

    /* Enable I2C clock */
    do {
        uint32_t tmpreg = 0x00;
        SET_BIT(RCC->APB1ENR, handle->hw_info.rcc_apbenr_i2cen);
        tmpreg = READ_BIT(RCC->APB1ENR, handle->hw_info.rcc_apbenr_i2cen);
        UNUSED(tmpreg);
    } while (0);

    /* Enable SCL GPIO Port clock */
    do {
        uint32_t tmpreg = 0x00;
        SET_BIT(RCC->AHB1ENR, handle->hw_info.rcc_ahbenr_gpio_scl);
        tmpreg = READ_BIT(RCC->AHB1ENR, handle->hw_info.rcc_ahbenr_gpio_scl);
        UNUSED(tmpreg);
    } while (0);

    /* Enable SDA GPIO Port clock */
    do {
        uint32_t tmpreg = 0x00;
        SET_BIT(RCC->AHB1ENR, handle->hw_info.rcc_ahbenr_gpio_sda);
        tmpreg = READ_BIT(RCC->AHB1ENR, handle->hw_info.rcc_ahbenr_gpio_sda);
        UNUSED(tmpreg);
    } while (0);

    /* Configure I2C */
    handle->hal_handle.Instance = handle->hw_info.i2c;
    handle->hal_handle.Init.ClockSpeed = I2C_CLOCKSPEED_DEFAULT;
    handle->hal_handle.Init.DutyCycle = I2C_DUTYCYCLE_DEFAULT;
    handle->hal_handle.Init.OwnAddress1 = I2C_OWN_ADDRESS1_DEFAULT;
    handle->hal_handle.Init.AddressingMode = I2C_ADDRESSING_MODE_DEFAULT;
    handle->hal_handle.Init.DualAddressMode = I2C_DUAL_ADDRESS_MODE_DEFAULT;
    handle->hal_handle.Init.OwnAddress2 = I2C_OWN_ADDRESS2_DEFAULT;
    handle->hal_handle.Init.GeneralCallMode = I2C_GENERALCALL_MODE_DEFAULT;
    handle->hal_handle.Init.NoStretchMode = I2C_NOSTRETCH_MODE_DEFAULT;
    HAL_I2C_Init(&handle->hal_handle);

    /* Configure SCL Pin */
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = handle->hw_info.pin_scl;
    GPIO_InitStruct.Mode = GPIO_MODE_DEFAULT;
    GPIO_InitStruct.Pull = GPIO_PULL_REG_DEFAULT;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_DEFAULT;
    GPIO_InitStruct.Alternate = handle->hw_info.alternate_func;
    HAL_GPIO_Init(handle->hw_info.port_scl, &GPIO_InitStruct);

    /* Configure SDA Pin */
    GPIO_InitStruct.Pin = handle->hw_info.pin_sda;
    GPIO_InitStruct.Mode = GPIO_MODE_DEFAULT;
    GPIO_InitStruct.Pull = GPIO_PULL_REG_DEFAULT;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_DEFAULT;
    GPIO_InitStruct.Alternate = handle->hw_info.alternate_func;
    HAL_GPIO_Init(handle->hw_info.port_sda, &GPIO_InitStruct);

    /* Update handle structure */
    handle->i2c_num = config->i2c_num;
    handle->i2c_pins_pack = config->i2c_pins_pack;
    handle->i2c_status = I2C_READY;

    return handle;
}

int i2c_master_write_bytes(i2c_handle_t handle, uint16_t dev_addr, uint8_t reg_addr, uint8_t *data, uint16_t length, uint32_t timeout_ms)
{
    /* Check if handle structure is empty */
    if (!handle)
    {
        return -1;
    }

    /* Create buffer transmit. The first byte is register address, then transmit data */
    uint8_t buf_trans[length + 1];
    buf_trans[0] = reg_addr;
    for (uint16_t i = 0; i < length; i++)
    {
        buf_trans[i + 1] = data[i];
    }

    /* Transmit data */
    handle->i2c_status = I2C_WRITING;
    if (HAL_I2C_Master_Transmit(&handle->hal_handle, dev_addr, buf_trans, length + 1, timeout_ms))
    {
        handle->i2c_status = I2C_ERROR;
        return -1;
    }

    handle->i2c_status = I2C_READY;
    return 0;
}

int i2c_master_read_bytes(i2c_handle_t handle, uint16_t dev_addr, uint8_t reg_addr, uint8_t *buf, uint16_t length, uint32_t timeout_ms)
{
    /* Check if handle structure is empty */
    if (!handle)
    {
        return -1;
    }

    uint8_t buf_trans[1];
    buf_trans[0] = reg_addr;

    /* Transmit start register address */
    handle->i2c_status = I2C_WRITING;
    if (HAL_I2C_Master_Transmit(&handle->hal_handle, dev_addr, buf_trans, 1, 10))
    {
        handle->i2c_status = I2C_ERROR;
        return -1;
    }

    /* Read data response */
    handle->i2c_status = I2C_READING;
    if (HAL_I2C_Master_Receive(&handle->hal_handle, dev_addr, buf, length, timeout_ms))
    {
        handle->i2c_status = I2C_ERROR;
        return -1;
    }

    handle->i2c_status = I2C_READY;
    return 0;
}