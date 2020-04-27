#include "driver/adc.h"

static uint32_t ADC_CLK_DIV_MAPPING[ADC_CLK_DIV_MAX_TYPE] = {
	ADC_CLOCK_SYNC_PCLK_DIV2,
	ADC_CLOCK_SYNC_PCLK_DIV4,
	ADC_CLOCK_SYNC_PCLK_DIV6,
	ADC_CLOCK_SYNC_PCLK_DIV8
};

static uint32_t ADC_RESOLUTION_MAPPING[ADC_RESOLUTION_MAX_TYPE] = {
	ADC_RESOLUTION_6B,
	ADC_RESOLUTION_8B,
	ADC_RESOLUTION_10B,
	ADC_RESOLUTION_12B
};

static uint32_t ADC_DATA_ALIGN_MAPPING[ADC_DATA_ALIGN_MAX_TYPE] = {
	ADC_DATAALIGN_RIGHT,
	ADC_DATAALIGN_LEFT
};

static uint32_t ADC_EXT_TRIGCONV_MAPPING[ADC_EXT_TRIGCONV_MAX] = {
	ADC_EXTERNALTRIGCONVEDGE_NONE,
	ADC_EXTERNALTRIGCONVEDGE_RISING,
	ADC_EXTERNALTRIGCONVEDGE_FALLING,
	ADC_EXTERNALTRIGCONVEDGE_RISINGFALLING
};

static uint32_t ADC_EOC_MODE_MAPPING[ADC_EOC_MODE_MAX] = {
	ADC_EOC_SEQ_CONV,
	ADC_EOC_SINGLE_CONV,
	ADC_EOC_SINGLE_SEQ_CONV
};

static uint32_t ADC_SAMP_TIME_MAPPING[ADC_SAMP_TIME_MAX] = {
	ADC_SAMPLETIME_3CYCLES,
	ADC_SAMPLETIME_15CYCLES,
	ADC_SAMPLETIME_28CYCLES,
	ADC_SAMPLETIME_56CYCLES,
	ADC_SAMPLETIME_84CYCLES,
	ADC_SAMPLETIME_112CYCLES,
	ADC_SAMPLETIME_144CYCLES,
	ADC_SAMPLETIME_480CYCLES
};

static uint32_t ADC_CHNL_MAPPING[ADC_CHNL_MAX] = {
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

ADC_HandleTypeDef adc_handle[ADC_NUM_MAX];

stm_err_t adc_config(adc_config_t *config)
{
	switch (config->adc_num) {
		case ADC_NUM_1:
			__HAL_RCC_ADC1_CLK_ENABLE();
			adc_handle[ADC_NUM_1].Instance = ADC1;
			break;
		case ADC_NUM_2:
			__HAL_RCC_ADC2_CLK_ENABLE();
			adc_handle[ADC_NUM_2].Instance = ADC2;
			break;
		case ADC_NUM_3:
			__HAL_RCC_ADC2_CLK_ENABLE();
			adc_handle[ADC_NUM_3].Instance = ADC3;
			break;
		default:
			break;
	}
	
	adc_handle[config->adc_num].Init.ClockPrescaler = ADC_CLK_DIV_MAPPING[config->clk_div];
	adc_handle[config->adc_num].Init.Resolution = ADC_RESOLUTION_MAPPING[config->resolution];
	adc_handle[config->adc_num].Init.DataAlign = ADC_DATA_ALIGN_MAPPING[config->data_align];
	adc_handle[config->adc_num].Init.NbrOfConversion = config->num_disconn_conv;
	adc_handle[config->adc_num].Init.ScanConvMode = config->scan_mode;
	adc_handle[config->adc_num].Init.ContinuousConvMode = config->cont_conv_mode;
	adc_handle[config->adc_num].Init.DiscontinuousConvMode = config->discont_conv_mode;
	adc_handle[config->adc_num].Init.ExternalTrigConvEdge = ADC_EXT_TRIGCONV_MAPPING[config->ext_trigconv_edge];
	adc_handle[config->adc_num].Init.DMAContinuousRequests = config->dma_cont_rqst;
	adc_handle[config->adc_num].Init.EOCSelection = ADC_EOC_MODE_MAPPING[config->eoc_mode];
	HAL_ADC_Init(&adc_handle[config->adc_num]);
}

stm_err_t adc_channel_config(adc_num_t adc_num, adc_chnl_t adc_chnl, adc_samp_time_t samp_time, uint32_t prior)
{
	ADC_ChannelConfTypeDef sConfig;
  	sConfig.Channel = ADC_CHNL_MAPPING[adc_chnl];
  	sConfig.Rank = prior;
  	sConfig.SamplingTime = ADC_SAMP_TIME_MAPPING[samp_time];
  	HAL_ADC_ConfigChannel(&adc_handle[adc_num], &sConfig);
}

