#include "stm_hal.h"
#include "stm_log.h"

#include "driver/adc.h"
#include "adc_mapping.h"

#define ADC_INIT_ERR_STR				"adc init error"
#define ADC_CONFIG_CHNL_ERR_STR			"adc configure channel error"
#define ADC_GET_VALUE_ERR_STR			"adc get value error"
#define ADC_START_ERR_STR				"adc start error"
#define ADC_STOP_ERR_STR				"adc stop error"

static const char* ADC_TAG = "DRIVER ADC";
#define ADC_CHECK(a, str, ret)  if(!(a)) {                                             \
        STM_LOGE(ADC_TAG,"%s:%d (%s):%s", __FILE__, __LINE__, __FUNCTION__, str);      \
        return (ret);                                                                  \
        }

ADC_HandleTypeDef adc_handle[ADC_NUM_MAX];

stm_err_t adc_config(adc_config_t *config)
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
	ADC_CHECK(adc_num < ADC_NUM_MAX, ADC_CONFIG_CHNL_ERR_STR, STM_ERR_INVALID_ARG);
	ADC_CHECK(adc_chnl < ADC_CHNL_MAX, ADC_CONFIG_CHNL_ERR_STR, STM_ERR_INVALID_ARG);
	ADC_CHECK(samp_time < ADC_SAMP_TIME_MAX, ADC_CONFIG_CHNL_ERR_STR, STM_ERR_INVALID_ARG);
	ADC_CHECK(prior < ADC_CHNL_MAX, ADC_CONFIG_CHNL_ERR_STR, STM_ERR_INVALID_ARG);

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
	ADC_CHECK(adc_num < ADC_NUM_MAX, ADC_CONFIG_CHNL_ERR_STR, STM_ERR_INVALID_ARG);

	ADC_CHECK(!HAL_ADC_Start(&adc_handle[adc_num]), ADC_START_ERR_STR, STM_FAIL);
	return STM_OK;
}

stm_err_t adc_get_value(adc_num_t adc_num, uint16_t *value)
{
	/* Check input condition */
	ADC_CHECK(adc_num < ADC_NUM_MAX, ADC_CONFIG_CHNL_ERR_STR, STM_ERR_INVALID_ARG);

	*value = HAL_ADC_GetValue(&adc_handle[adc_num]);
	return STM_OK;
}
