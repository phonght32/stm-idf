#include "stm_hal.h"
#include "stm_log.h"

#include "driver/adc.h"

#define ADC_INIT_ERR_STR				"adc_config error"
#define ADC_CONFIG_CHNL_ERR_STR			"adc_channel_config error"
#define ADC_GET_VALUE_ERR_STR			"adc_get_value error"
#define ADC_START_ERR_STR				"adc_start error"
#define ADC_STOP_ERR_STR				"adc_stop error"

static const char* ADC_TAG = "DRIVER_ADC";
#define ADC_CHECK(a, str, ret)  if(!(a)) {                                             \
        STM_LOGE(ADC_TAG,"%s:%d (%s):%s", __FILE__, __LINE__, __FUNCTION__, str);      \
        return (ret);                                                                  \
        }

ADC_HandleTypeDef adc_handle[ADC_NUM_MAX];

uint32_t ADC_CLK_DIV_MAPPING[ADC_CLK_DIV_MAX] = {
	ADC_CLOCK_SYNC_PCLK_DIV2,
	ADC_CLOCK_SYNC_PCLK_DIV4,
	ADC_CLOCK_SYNC_PCLK_DIV6,
	ADC_CLOCK_SYNC_PCLK_DIV8
};

uint32_t ADC_RESOLUTION_MAPPING[ADC_RESOLUTION_MAX] = {
	ADC_RESOLUTION_6B,
	ADC_RESOLUTION_8B,
	ADC_RESOLUTION_10B,
	ADC_RESOLUTION_12B
};

uint32_t ADC_DATA_ALIGN_MAPPING[ADC_DATA_ALIGN_MAX] = {
	ADC_DATAALIGN_RIGHT,
	ADC_DATAALIGN_LEFT
};

uint32_t ADC_EXT_TRIGCONV_MAPPING[ADC_EXT_TRIGCONV_MAX] = {
	ADC_EXTERNALTRIGCONVEDGE_NONE,
	ADC_EXTERNALTRIGCONVEDGE_RISING,
	ADC_EXTERNALTRIGCONVEDGE_FALLING,
	ADC_EXTERNALTRIGCONVEDGE_RISINGFALLING
};

uint32_t ADC_EOC_MODE_MAPPING[ADC_EOC_MODE_MAX] = {
	ADC_EOC_SEQ_CONV,
	ADC_EOC_SINGLE_CONV,
	ADC_EOC_SINGLE_SEQ_CONV
};

uint32_t ADC_SAMP_TIME_MAPPING[ADC_SAMP_TIME_MAX] = {
	ADC_SAMPLETIME_3CYCLES,
	ADC_SAMPLETIME_15CYCLES,
	ADC_SAMPLETIME_28CYCLES,
	ADC_SAMPLETIME_56CYCLES,
	ADC_SAMPLETIME_84CYCLES,
	ADC_SAMPLETIME_112CYCLES,
	ADC_SAMPLETIME_144CYCLES,
	ADC_SAMPLETIME_480CYCLES
};

uint32_t ADC_CHNL_MAPPING[ADC_CHNL_MAX] = {
	ADC_CHANNEL_0,
	ADC_CHANNEL_1,
	ADC_CHANNEL_2,
	ADC_CHANNEL_3,
	ADC_CHANNEL_4,
	ADC_CHANNEL_5,
	ADC_CHANNEL_6,
	ADC_CHANNEL_7,
	ADC_CHANNEL_8,
	ADC_CHANNEL_9,
	ADC_CHANNEL_10,
	ADC_CHANNEL_11,
	ADC_CHANNEL_12,
	ADC_CHANNEL_13,
	ADC_CHANNEL_14,
	ADC_CHANNEL_15
};

ADC_TypeDef *ADC_MAPPING[ADC_NUM_MAX] = {
	ADC1,

#if defined(STM32F401xC)
	0,
#else
	ADC2,
#endif

#if defined(STM32F401xC)
	0,
#else
	ADC3,
#endif
};

uint32_t RCC_APBENR_ADCEN_MAPPING[ADC_NUM_MAX] = {
	RCC_APB2ENR_ADC1EN,

#if defined(STM32F401xC)
	0,
#else
	RCC_APB2ENR_ADC2EN,
#endif

#if defined(STM32F401xC)
	0,
#else
	RCC_APB2ENR_ADC3EN,
#endif
};

stm_err_t adc_config(adc_cfg_t *config)
{
	/* Check input condition */
	ADC_CHECK(config, ADC_INIT_ERR_STR, STM_ERR_INVALID_ARG);
	ADC_CHECK(config->adc_num < ADC_NUM_MAX, ADC_INIT_ERR_STR, STM_ERR_INVALID_ARG);
	ADC_CHECK(config->resolution < ADC_RESOLUTION_MAX, ADC_INIT_ERR_STR, STM_ERR_INVALID_ARG);
	ADC_CHECK(config->clk_div < ADC_CLK_DIV_MAX, ADC_INIT_ERR_STR, STM_ERR_INVALID_ARG);
	ADC_CHECK(config->data_align < ADC_DATA_ALIGN_MAX, ADC_INIT_ERR_STR, STM_ERR_INVALID_ARG);
	ADC_CHECK(config->scan_mode < ADC_SCAN_MODE_MAX, ADC_INIT_ERR_STR, STM_ERR_INVALID_ARG);
	ADC_CHECK(config->cont_conv_mode < ADC_CONT_CONV_MODE_MAX, ADC_INIT_ERR_STR, STM_ERR_INVALID_ARG);
	ADC_CHECK(config->discont_conv_mode < ADC_DISCONT_CONV_MODE_MAX, ADC_INIT_ERR_STR, STM_ERR_INVALID_ARG);
	ADC_CHECK(config->ext_trigconv_edge < ADC_EXT_TRIGCONV_MAX, ADC_INIT_ERR_STR, STM_ERR_INVALID_ARG);
	ADC_CHECK(config->dma_cont_rqst < ADC_DMA_CONT_RQST_MAX, ADC_INIT_ERR_STR, STM_ERR_INVALID_ARG);
	ADC_CHECK(config->eoc_mode < ADC_EOC_MODE_MAX, ADC_INIT_ERR_STR, STM_ERR_INVALID_ARG);

	/* Check if hardware is not valid in this STM32 target */
	ADC_CHECK(ADC_MAPPING[config->adc_num], ADC_INIT_ERR_STR, STM_ERR_INVALID_ARG);

	/* Enable ADC clock */
  	uint32_t tmpreg = 0x00U; 
    SET_BIT(RCC->APB2ENR, RCC_APBENR_ADCEN_MAPPING[config->adc_num]);
    tmpreg = READ_BIT(RCC->APB2ENR, RCC_APBENR_ADCEN_MAPPING[config->adc_num]);
    UNUSED(tmpreg); 

    /* Configure ADC */
	adc_handle[config->adc_num].Instance = ADC_MAPPING[config->adc_num];
	adc_handle[config->adc_num].Init.ClockPrescaler = ADC_CLK_DIV_MAPPING[config->clk_div];
	adc_handle[config->adc_num].Init.Resolution = ADC_RESOLUTION_MAPPING[config->resolution];
	adc_handle[config->adc_num].Init.DataAlign = ADC_DATA_ALIGN_MAPPING[config->data_align];
	adc_handle[config->adc_num].Init.NbrOfConversion = config->num_conv;
	adc_handle[config->adc_num].Init.ScanConvMode = config->scan_mode;
	adc_handle[config->adc_num].Init.ContinuousConvMode = config->cont_conv_mode;
	adc_handle[config->adc_num].Init.DiscontinuousConvMode = config->discont_conv_mode;
	adc_handle[config->adc_num].Init.ExternalTrigConvEdge = ADC_EXT_TRIGCONV_MAPPING[config->ext_trigconv_edge];
	adc_handle[config->adc_num].Init.DMAContinuousRequests = config->dma_cont_rqst;
	adc_handle[config->adc_num].Init.EOCSelection = ADC_EOC_MODE_MAPPING[config->eoc_mode];
	ADC_CHECK(!HAL_ADC_Init(&adc_handle[config->adc_num]), ADC_INIT_ERR_STR, STM_FAIL);

	return STM_OK;
}

stm_err_t adc_channel_config(adc_num_t adc_num, adc_chnl_t adc_chnl, adc_samp_time_t samp_time, uint32_t prior)
{
	/* Check input condition */
	ADC_CHECK(adc_num < ADC_NUM_MAX				, ADC_CONFIG_CHNL_ERR_STR, STM_ERR_INVALID_ARG);
	ADC_CHECK(adc_chnl < ADC_CHNL_MAX 			, ADC_CONFIG_CHNL_ERR_STR, STM_ERR_INVALID_ARG);
	ADC_CHECK(samp_time < ADC_SAMP_TIME_MAX 	, ADC_CONFIG_CHNL_ERR_STR, STM_ERR_INVALID_ARG);
	ADC_CHECK(prior < ADC_CHNL_MAX 				, ADC_CONFIG_CHNL_ERR_STR, STM_ERR_INVALID_ARG);

	/* Check if hardware is not valid in this STM32 target */
	ADC_CHECK(ADC_MAPPING[adc_num], ADC_CONFIG_CHNL_ERR_STR, STM_ERR_INVALID_ARG);

	/* Configure ADC channel */
	ADC_ChannelConfTypeDef sConfig;
  	sConfig.Channel = ADC_CHNL_MAPPING[adc_chnl];
  	sConfig.Rank = prior;
  	sConfig.SamplingTime = ADC_SAMP_TIME_MAPPING[samp_time];
  	ADC_CHECK(!HAL_ADC_ConfigChannel(&adc_handle[adc_num], &sConfig), ADC_CONFIG_CHNL_ERR_STR, STM_FAIL);

  	return STM_OK;
}

stm_err_t adc_start(adc_num_t adc_num)
{
	/* Check input condition */
	ADC_CHECK(adc_num < ADC_NUM_MAX, ADC_START_ERR_STR, STM_ERR_INVALID_ARG);

	/* Check if hardware is not valid in this STM32 target */
	ADC_CHECK(ADC_MAPPING[adc_num], ADC_START_ERR_STR, STM_ERR_INVALID_ARG);

	/* Start ADC */
	ADC_CHECK(!HAL_ADC_Start(&adc_handle[adc_num]), ADC_START_ERR_STR, STM_FAIL);

	return STM_OK;
}

stm_err_t adc_get_value(adc_num_t adc_num, uint16_t *value)
{
	/* Check input condition */
	ADC_CHECK(adc_num < ADC_NUM_MAX, ADC_GET_VALUE_ERR_STR, STM_ERR_INVALID_ARG);

	/* Check if hardware is not valid in this STM32 target */
	ADC_CHECK(ADC_MAPPING[adc_num], ADC_GET_VALUE_ERR_STR, STM_ERR_INVALID_ARG);

	/* Get ADC value */
	*value = HAL_ADC_GetValue(&adc_handle[adc_num]);
	
	return STM_OK;
}
