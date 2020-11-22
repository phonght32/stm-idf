#include "stm_hal.h"
#include "stm_log.h"

#include "driver/spi.h"

#define SPI_INIT_ERR_STR			"spi init error"
#define SPI_WRITE_ERR_STR			"spi write error"
#define SPI_READ_ERR_STR			"spi read error"

#define SPI1_PP1_HW_INFO	{.rcc_ahbenr_gpioen_mosi = RCC_AHB1ENR_GPIOAEN,		\
							 .rcc_ahbenr_gpioen_miso = RCC_AHB1ENR_GPIOAEN,		\
							 .rcc_ahbenr_gpioen_sck  = RCC_AHB1ENR_GPIOAEN,		\
							 .port_mosi = GPIOA,								\
							 .port_miso = GPIOA,								\
							 .port_sck  = GPIOA,								\
							 .pin_mosi  = GPIO_PIN_7,							\
							 .pin_miso  = GPIO_PIN_10,							\
							 .pin_sck   = GPIO_PIN_5,							\
							}

#define SPI1_PP2_HW_INFO	{.rcc_ahbenr_gpioen_mosi = RCC_AHB1ENR_GPIOBEN,		\
							 .rcc_ahbenr_gpioen_miso = RCC_AHB1ENR_GPIOBEN,		\
							 .rcc_ahbenr_gpioen_sck  = RCC_AHB1ENR_GPIOBEN,		\
							 .port_mosi = GPIOB,								\
							 .port_miso = GPIOB,								\
							 .port_sck  = GPIOB,								\
							 .pin_mosi  = GPIO_PIN_5,							\
							 .pin_miso  = GPIO_PIN_4,							\
							 .pin_sck   = GPIO_PIN_3,							\
							}

#define SPI2_PP1_HW_INFO	{.rcc_ahbenr_gpioen_mosi = RCC_AHB1ENR_GPIOCEN,		\
							 .rcc_ahbenr_gpioen_miso = RCC_AHB1ENR_GPIOAEN,		\
							 .rcc_ahbenr_gpioen_sck  = RCC_AHB1ENR_GPIOBEN,		\
							 .port_mosi = GPIOC,								\
							 .port_miso = GPIOA,								\
							 .port_sck  = GPIOB,								\
							 .pin_mosi  = GPIO_PIN_3,							\
							 .pin_miso  = GPIO_PIN_3,							\
							 .pin_sck   = GPIO_PIN_10,							\
							}

#define SPI2_PP2_HW_INFO	{.rcc_ahbenr_gpioen_mosi = RCC_AHB1ENR_GPIOBEN,		\
							 .rcc_ahbenr_gpioen_miso = RCC_AHB1ENR_GPIOBEN,		\
							 .rcc_ahbenr_gpioen_sck  = RCC_AHB1ENR_GPIOBEN,		\
							 .port_mosi = GPIOB,								\
							 .port_miso = GPIOB,								\
							 .port_sck  = GPIOB,								\
							 .pin_mosi  = GPIO_PIN_15,							\
							 .pin_miso  = GPIO_PIN_14,							\
							 .pin_sck   = GPIO_PIN_13,							\
							}

#define SPI2_PP3_HW_INFO	{.rcc_ahbenr_gpioen_mosi = RCC_AHB1ENR_GPIOIEN,		\
							 .rcc_ahbenr_gpioen_miso = RCC_AHB1ENR_GPIOIEN,		\
							 .rcc_ahbenr_gpioen_sck  = RCC_AHB1ENR_GPIOIEN,		\
							 .port_mosi = GPIOI,								\
							 .port_miso = GPIOI,								\
							 .port_sck  = GPIOI,								\
							 .pin_mosi  = GPIO_PIN_3,							\
							 .pin_miso  = GPIO_PIN_2,							\
							 .pin_sck   = GPIO_PIN_0,							\
							}

#define SPI3_PP1_HW_INFO	{.rcc_ahbenr_gpioen_mosi = RCC_AHB1ENR_GPIOBEN,		\
							 .rcc_ahbenr_gpioen_miso = RCC_AHB1ENR_GPIOBEN,		\
							 .rcc_ahbenr_gpioen_sck  = RCC_AHB1ENR_GPIOBEN,		\
							 .port_mosi = GPIOB,								\
							 .port_miso = GPIOB,								\
							 .port_sck  = GPIOB,								\
							 .pin_mosi  = GPIO_PIN_5,							\
							 .pin_miso  = GPIO_PIN_11,							\
							 .pin_sck   = GPIO_PIN_3,							\
							}

#define SPI3_PP2_HW_INFO	{.rcc_ahbenr_gpioen_mosi = RCC_AHB1ENR_GPIOCEN,		\
							 .rcc_ahbenr_gpioen_miso = RCC_AHB1ENR_GPIOCEN,		\
							 .rcc_ahbenr_gpioen_sck  = RCC_AHB1ENR_GPIOCEN,		\
							 .port_mosi = GPIOC,								\
							 .port_miso = GPIOC,								\
							 .port_sck  = GPIOC,								\
							 .pin_mosi  = GPIO_PIN_12,							\
							 .pin_miso  = GPIO_PIN_11,							\
							 .pin_sck   = GPIO_PIN_10,							\
							}

#define SPI4_PP1_HW_INFO	{.rcc_ahbenr_gpioen_mosi = RCC_AHB1ENR_GPIOEEN,		\
							 .rcc_ahbenr_gpioen_miso = RCC_AHB1ENR_GPIOAEN,		\
							 .rcc_ahbenr_gpioen_sck  = RCC_AHB1ENR_GPIOEEN,		\
							 .port_mosi = GPIOE,								\
							 .port_miso = GPIOA,								\
							 .port_sck  = GPIOE,								\
							 .pin_mosi  = GPIO_PIN_6,							\
							 .pin_miso  = GPIO_PIN_1,							\
							 .pin_sck   = GPIO_PIN_2,							\
							}

#define SPI4_PP2_HW_INFO	{.rcc_ahbenr_gpioen_mosi = RCC_AHB1ENR_GPIOEEN,		\
							 .rcc_ahbenr_gpioen_miso = RCC_AHB1ENR_GPIOEEN,		\
							 .rcc_ahbenr_gpioen_sck  = RCC_AHB1ENR_GPIOEEN,		\
							 .port_mosi = GPIOE,								\
							 .port_miso = GPIOE,								\
							 .port_sck  = GPIOE,								\
							 .pin_mosi  = GPIO_PIN_14,							\
							 .pin_miso  = GPIO_PIN_13,							\
							 .pin_sck   = GPIO_PIN_12,							\
							}

#define SPI5_PP1_HW_INFO	{.rcc_ahbenr_gpioen_mosi = RCC_AHB1ENR_GPIOFEN,		\
							 .rcc_ahbenr_gpioen_miso = RCC_AHB1ENR_GPIODEN,		\
							 .rcc_ahbenr_gpioen_sck  = RCC_AHB1ENR_GPIOFEN,		\
							 .port_mosi = GPIOF,								\
							 .port_miso = GPIOD,								\
							 .port_sck  = GPIOF,								\
							 .pin_mosi  = GPIO_PIN_9,							\
							 .pin_miso  = GPIO_PIN_2,							\
							 .pin_sck   = GPIO_PIN_7,							\
							}

#define SPI5_PP2_HW_INFO	{.rcc_ahbenr_gpioen_mosi = RCC_AHB1ENR_GPIOFEN,		\
							 .rcc_ahbenr_gpioen_miso = RCC_AHB1ENR_GPIOHEN,		\
							 .rcc_ahbenr_gpioen_sck  = RCC_AHB1ENR_GPIOHEN,		\
							 .port_mosi = GPIOF,								\
							 .port_miso = GPIOH,								\
							 .port_sck  = GPIOH,								\
							 .pin_mosi  = GPIO_PIN_11,							\
							 .pin_miso  = GPIO_PIN_7,							\
							 .pin_sck   = GPIO_PIN_6,							\
							}

#define SPI6_PP1_HW_INFO	{.rcc_ahbenr_gpioen_mosi = RCC_AHB1ENR_GPIOGEN,		\
							 .rcc_ahbenr_gpioen_miso = RCC_AHB1ENR_GPIOCEN,		\
							 .rcc_ahbenr_gpioen_sck  = RCC_AHB1ENR_GPIOGEN,		\
							 .port_mosi = GPIOG,								\
							 .port_miso = GPIOC,								\
							 .port_sck  = GPIOG,								\
							 .pin_mosi  = GPIO_PIN_14,							\
							 .pin_miso  = GPIO_PIN_7,							\
							 .pin_sck   = GPIO_PIN_13,							\
							}

static const char* TAG = "DRIVER_SPI";
#define SPI_CHECK(a, str, ret)  if(!(a)) {                                             	\
        STM_LOGE(TAG,"%s:%d (%s):%s", __FILE__, __LINE__, __FUNCTION__, str);      		\
        return (ret);                                                                   \
        }

static SPI_HandleTypeDef spi_handle[SPI_NUM_MAX];

typedef enum {
	SPI_MODE_INDEX,
	SPI_DIR_INDEX,
	SPI_MODE_MAPPING_INDEX_MAX,
} spi_mode_mapping_index_t;

typedef struct {
	uint32_t       rcc_ahbenr_gpioen_mosi;
	uint32_t       rcc_ahbenr_gpioen_miso;
	uint32_t       rcc_ahbenr_gpioen_sck;
	GPIO_TypeDef   *port_mosi;
	GPIO_TypeDef   *port_miso;
	GPIO_TypeDef   *port_sck;
	uint16_t       pin_mosi;
	uint16_t       pin_miso;
	uint16_t       pin_sck;
} spi_hw_info_t;

static spi_hw_info_t SPI_HW_INFO_MAPPING[SPI_NUM_MAX][SPI_PINS_PACK_MAX] = {
	{SPI1_PP1_HW_INFO, SPI1_PP2_HW_INFO,              {0}},
	{SPI2_PP1_HW_INFO, SPI2_PP2_HW_INFO, SPI2_PP3_HW_INFO},
	{SPI3_PP1_HW_INFO, SPI3_PP2_HW_INFO,              {0}},
	{SPI4_PP1_HW_INFO, SPI4_PP2_HW_INFO,              {0}},
	{SPI5_PP1_HW_INFO, SPI5_PP2_HW_INFO,              {0}},
	{SPI6_PP1_HW_INFO,              {0},              {0}}
};

static uint32_t RCC_APBENR_SPIEN_MAPPING[SPI_NUM_MAX] = {
	RCC_APB2ENR_SPI1EN,
	RCC_APB1ENR_SPI2EN,
	RCC_APB1ENR_SPI3EN,

#if defined(STM32F407xx) || defined(STM32F405xx)
    0,
#else 
    RCC_APB2ENR_SPI4EN,          
#endif 

#if defined(STM32F407xx) || defined(STM32F405xx)
    0,
#else 
    RCC_APB2ENR_SPI5EN,          
#endif 

#if defined(STM32F407xx) || defined(STM32F405xx)
    0,
#else 
    RCC_APB2ENR_SPI6EN,          
#endif 
};

static SPI_TypeDef* SPI_MAPPING[SPI_NUM_MAX] = {
	SPI1,
	SPI2,
	SPI3,

#if defined(STM32F407xx) || defined(STM32F405xx)
    0,
#else 
    SPI4,          
#endif 

#if defined(STM32F407xx) || defined(STM32F405xx)
    0,
#else 
    SPI5,          
#endif 

#if defined(STM32F407xx) || defined(STM32F405xx)
    0,
#else 
    SPI6,          
#endif 
};

static uint32_t SPI_ALTERNATE_FUNC_MAPPING[SPI_NUM_MAX] = {
	GPIO_AF5_SPI1,
	GPIO_AF5_SPI2,

#if defined(STM32F407xx) || defined(STM32F405xx)
    GPIO_AF6_SPI3,
#else 
    GPIO_AF5_SPI3,          
#endif 

#if defined(STM32F407xx) || defined(STM32F405xx)     
    0,
#else 
    GPIO_AF5_SPI4,          
#endif 

#if defined(STM32F407xx) || defined(STM32F405xx)     
    0,
#else 
    GPIO_AF5_SPI5,          
#endif 

#if defined(STM32F407xx) || defined(STM32F405xx)  
    0,
#else 
    GPIO_AF5_SPI6,          
#endif 
};

static uint32_t SPI_MODE_MAPPING[SPI_MODE_MAX][SPI_MODE_MAPPING_INDEX_MAX] = {
	{SPI_MODE_MASTER, SPI_DIRECTION_2LINES       },
	{SPI_MODE_MASTER, SPI_DIRECTION_1LINE        },
	{SPI_MODE_MASTER, SPI_DIRECTION_2LINES_RXONLY},
	{SPI_MODE_MASTER, SPI_DIRECTION_2LINES       },
	{SPI_MODE_SLAVE , SPI_DIRECTION_2LINES       },
	{SPI_MODE_SLAVE , SPI_DIRECTION_1LINE        },
	{SPI_MODE_SLAVE , SPI_DIRECTION_2LINES_RXONLY},
	{SPI_MODE_SLAVE , SPI_DIRECTION_2LINES       },
};

static uint32_t SPI_CPOL_MAPPING[SPI_CAP_EDGE_MAX] = {
	SPI_POLARITY_LOW,
	SPI_POLARITY_HIGH
};

static uint32_t SPI_FIRSTBIT_MAPPING[SPI_TRANS_FIRSTBIT_MAX] = {
	SPI_FIRSTBIT_MSB,
	SPI_FIRSTBIT_LSB
};

spi_hw_info_t _spi_get_hw_info(spi_num_t spi_num, spi_pins_pack_t spi_pins_pack)
{
	return SPI_HW_INFO_MAPPING[spi_num][spi_pins_pack];
}

stm_err_t spi_config(spi_cfg_t *config)
{
	/* Check input conditions */
	SPI_CHECK(config, SPI_INIT_ERR_STR, STM_ERR_INVALID_ARG);
	SPI_CHECK(config->spi_num < SPI_NUM_MAX, SPI_INIT_ERR_STR, STM_ERR_INVALID_ARG);
	SPI_CHECK(config->spi_pins_pack < SPI_PINS_PACK_MAX, SPI_INIT_ERR_STR, STM_ERR_INVALID_ARG);

	/* Get hardware information */
	spi_hw_info_t hw_info = _spi_get_hw_info(config->spi_num, config->spi_pins_pack);
	SPI_CHECK(SPI_MAPPING[config->spi_num], SPI_INIT_ERR_STR, STM_ERR_INVALID_ARG);
	SPI_CHECK(hw_info.port_mosi , SPI_INIT_ERR_STR, STM_ERR_INVALID_ARG);

	/* Enable SPI clock */
	uint32_t tmpreg = 0x00U;
	if ((config->spi_num == SPI_NUM_2) || (config->spi_num == SPI_NUM_3)) {
		SET_BIT(RCC->APB1ENR, RCC_APBENR_SPIEN_MAPPING[config->spi_num]);
		tmpreg = READ_BIT(RCC->APB1ENR, RCC_APBENR_SPIEN_MAPPING[config->spi_num]);
	} else {
		SET_BIT(RCC->APB2ENR, RCC_APBENR_SPIEN_MAPPING[config->spi_num]);
		tmpreg = READ_BIT(RCC->APB2ENR, RCC_APBENR_SPIEN_MAPPING[config->spi_num]);
	}
	UNUSED(tmpreg);

	/* Enable MOSI GPIO Port */
    tmpreg = 0x00;
    SET_BIT(RCC->AHB1ENR,  hw_info.rcc_ahbenr_gpioen_mosi);
    tmpreg = READ_BIT(RCC->AHB1ENR, hw_info.rcc_ahbenr_gpioen_mosi);
    UNUSED(tmpreg);

    /* Enable MISO GPIO Port */
    tmpreg = 0x00;
    SET_BIT(RCC->AHB1ENR,  hw_info.rcc_ahbenr_gpioen_miso);
    tmpreg = READ_BIT(RCC->AHB1ENR, hw_info.rcc_ahbenr_gpioen_miso);
    UNUSED(tmpreg);

    /* Enable SCK GPIO Port */
    tmpreg = 0x00;
    SET_BIT(RCC->AHB1ENR,  hw_info.rcc_ahbenr_gpioen_sck);
    tmpreg = READ_BIT(RCC->AHB1ENR, hw_info.rcc_ahbenr_gpioen_sck);
    UNUSED(tmpreg);

    /* Configure SPI */
	spi_handle[config->spi_num].Instance = SPI_MAPPING[config->spi_num];
	spi_handle[config->spi_num].Init.Mode = SPI_MODE_MAPPING[config->mode][SPI_MODE_INDEX];
	spi_handle[config->spi_num].Init.Direction = SPI_MODE_MAPPING[config->mode][SPI_DIR_INDEX];
	spi_handle[config->spi_num].Init.DataSize = SPI_DATASIZE_8BIT;
	spi_handle[config->spi_num].Init.CLKPolarity = SPI_CPOL_MAPPING[config->cap_edge];
	spi_handle[config->spi_num].Init.CLKPhase = SPI_PHASE_1EDGE;
	spi_handle[config->spi_num].Init.NSS = SPI_NSS_SOFT;
	spi_handle[config->spi_num].Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
	spi_handle[config->spi_num].Init.FirstBit = SPI_FIRSTBIT_MAPPING[config->firstbit];
	spi_handle[config->spi_num].Init.TIMode = SPI_TIMODE_DISABLE;
	spi_handle[config->spi_num].Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	spi_handle[config->spi_num].Init.CRCPolynomial = 10;
	SPI_CHECK(!HAL_SPI_Init(&spi_handle[config->spi_num]), SPI_INIT_ERR_STR, STM_FAIL);

    GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* Configure SPI MOSI pins */
    GPIO_InitStruct.Pin = hw_info.pin_mosi;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = SPI_ALTERNATE_FUNC_MAPPING[config->spi_num];
    HAL_GPIO_Init(hw_info.port_mosi, &GPIO_InitStruct);

    /* Configure SPI MISO pins */
    GPIO_InitStruct.Pin = hw_info.pin_miso;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = SPI_ALTERNATE_FUNC_MAPPING[config->spi_num];
    HAL_GPIO_Init(hw_info.port_miso, &GPIO_InitStruct);

    /* Configure SPI SCK pins */
    GPIO_InitStruct.Pin = hw_info.pin_sck;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = SPI_ALTERNATE_FUNC_MAPPING[config->spi_num];
    HAL_GPIO_Init(hw_info.port_sck, &GPIO_InitStruct);

	return STM_OK;
}

stm_err_t spi_write_bytes(spi_num_t spi_num, uint8_t *data, uint16_t length, uint32_t timeout_ms)
{
	/* Check input conditions */
	SPI_CHECK(spi_num < SPI_NUM_MAX, SPI_WRITE_ERR_STR, STM_ERR_INVALID_ARG);
	SPI_CHECK(data, SPI_WRITE_ERR_STR, STM_ERR_INVALID_ARG);

	/* Check if hardware is not valid in this STM32 target */
	SPI_CHECK(SPI_MAPPING[spi_num], SPI_WRITE_ERR_STR, STM_ERR_INVALID_ARG);

	/* Write data */
	SPI_CHECK(!HAL_SPI_Transmit(&spi_handle[spi_num], data, length, timeout_ms), SPI_WRITE_ERR_STR, STM_FAIL);

	return STM_OK;
}

stm_err_t spi_read_bytes(spi_num_t spi_num, uint8_t *buf, uint16_t length, uint32_t timeout_ms)
{
	/* Check input conditions */
	SPI_CHECK(spi_num < SPI_NUM_MAX, SPI_WRITE_ERR_STR, STM_ERR_INVALID_ARG);
	SPI_CHECK(buf, SPI_WRITE_ERR_STR, STM_ERR_INVALID_ARG);

	/* Check if hardware is not valid in this STM32 target */
	SPI_CHECK(SPI_MAPPING[spi_num], SPI_WRITE_ERR_STR, STM_ERR_INVALID_ARG);

	/* Read data */
	SPI_CHECK(!HAL_SPI_Receive(&spi_handle[spi_num], buf, length, timeout_ms), SPI_WRITE_ERR_STR, STM_FAIL);

	return STM_OK;
}