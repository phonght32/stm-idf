// MIT License

// Copyright (c) 2020 thanhphong98

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef _DRIVER_ADC_H_
#define _DRIVER_ADC_H_ 

/* 
 * Table below shows all possible pins for ADC.
 * 
 *  Channel       | ADC1 | ADC2 | ADC3 |
 * -------------- | ---- | ---- | ---- |
 * ADC Channel 0  | PA0  | PA0  | PA0  |
 * ADC Channel 1  | PA1  | PA1  | PA1  |
 * ADC Channel 2  | PA2  | PA2  | PA2  |
 * ADC Channel 3  | PA3  | PA3  | PA3  |
 * ADC Channel 4  | PA4  | PA4  | PF6  |
 * ADC Channel 5  | PA5  | PA5  | PF7  |
 * ADC Channel 6  | PA6  | PA6  | PF8  |
 * ADC Channel 7  | PA7  | PA7  | PF9  |
 * ADC Channel 8  | PB0  | PB0  | PF10 |
 * ADC Channel 9  | PB1  | PB1  | PF3  |
 * ADC Channel 10 | PC0  | PC0  | PC0  |
 * ADC Channel 11 | PC1  | PC1  | PC1  |
 * ADC Channel 12 | PC2  | PC2  | PC2  |
 * ADC Channel 13 | PC3  | PC   | PC3  |
 * ADC Channel 14 | PC4  | PC4  | PF4  |
 * ADC Channel 15 | PC5  | PC5  | PF5  |
 */


#ifdef __cplusplus
extern "C" {
#endif

#include "stm_err.h"

typedef enum {
	ADC_NUM_1 = 0,							/*!< ADC num 1 selected */
	ADC_NUM_2,								/*!< ADC num 2 selected */
	ADC_NUM_3,								/*!< ADC num 3 selected */
	ADC_NUM_MAX
} adc_num_t;

typedef enum {
	ADC_CHNL_0 = 0,   						/*!< ADC channel 0 selected */
	ADC_CHNL_1,								/*!< ADC channel 1 selected */
	ADC_CHNL_2,								/*!< ADC channel 2 selected */
	ADC_CHNL_3,								/*!< ADC channel 3 selected */
	ADC_CHNL_4,								/*!< ADC channel 4 selected */
	ADC_CHNL_5,								/*!< ADC channel 5 selected */
	ADC_CHNL_6,								/*!< ADC channel 6 selected */
	ADC_CHNL_7,								/*!< ADC channel 7 selected */
	ADC_CHNL_8,								/*!< ADC channel 8 selected */
	ADC_CHNL_9,								/*!< ADC channel 9 selected */
	ADC_CHNL_10,							/*!< ADC channel 10 selected */
	ADC_CHNL_11,							/*!< ADC channel 11 selected */
	ADC_CHNL_12,							/*!< ADC channel 12 selected */
	ADC_CHNL_13,							/*!< ADC channel 13 selected */
	ADC_CHNL_14,							/*!< ADC channel 14 selected */
	ADC_CHNL_15,							/*!< ADC channel 15 selected */
	ADC_CHNL_MAX
} adc_chnl_t;

typedef enum {
	ADC_RESOLUTION_6BIT = 0,				/*!< ADC resolution 6 bit data */
	ADC_RESOLUTION_8BIT,					/*!< ADC resolution 8 bit data */
	ADC_RESOLUTION_10BIT,					/*!< ADC resolution 10 bit data */
	ADC_RESOLUTION_12BIT,					/*!< ADC resolution 12 bit data */
	ADC_RESOLUTION_MAX
} adc_resolution_t;

typedef enum {
	ADC_CLK_DIV_2 = 0,						/*!< ADC clock divide by 2 */
	ADC_CLK_DIV_4,							/*!< ADC clock divide by 4 */
	ADC_CLK_DIV_6,							/*!< ADC clock divide by 6 */
	ADC_CLK_DIV_8,							/*!< ADC clock divide by 8 */
	ADC_CLK_DIV_MAX
} adc_clk_div_t;

typedef enum {
	ADC_SCAN_MODE_DISABLE = 0,				/*!< ADC scan mode disable */
	ADC_SCAN_MODE_ENABLE,					/*!< ADC scan mode enable */
	ADC_SCAN_MODE_MAX
} adc_scan_mode_t;

typedef enum {
	ADC_CONT_CONV_MODE_DISABLE = 0,			/*!< ADC continous conversion mode disable */
	ADC_CONT_CONV_MODE_ENABLE, 				/*!< ADC continous conversion mode enable */
	ADC_CONT_CONV_MODE_MAX
} adc_cont_conv_mode_t;

typedef enum {
	ADC_DISCONT_CONV_MODE_DISABLE = 0,		/*!< ADC discontinous conversion mode disable */
	ADC_DISCONT_CONV_MODE_ENABLE,			/*!< ADC discontinous conversion mode enable */
	ADC_DISCONT_CONV_MODE_MAX
} adc_discont_conv_mode_t;

typedef enum {
	ADC_DATA_ALIGN_RIGHT = 0,				/*!< ADC data align right */
	ADC_DATA_ALIGN_LEFT,					/*!< ADC data align left */
	ADC_DATA_ALIGN_MAX
} adc_data_align_t;

typedef enum {
	ADC_EXT_TRIGCONV_NONE = 0,				/*!< ADC external trigger conversion disable */
	ADC_EXT_TRIGCONV_RISING_EDGE,			/*!< ADC external trigger conversion rising edge */
	ADC_EXT_TRIGCONV_FALLING_EDGE,			/*!< ADC external trigger conversion falling edge */
	ADC_EXT_TRIGCONV_BOTH_EDGE,				/*!< ADC external trigger conversion both rising and falling edge */
	ADC_EXT_TRIGCONV_MAX
} adc_ext_trigconv_edge_t;

typedef enum {
	ADC_DMA_CONT_RQST_DISABLE,				/*!< DMA continous request disable */
	ADC_DMA_CONT_RQST_ENABLE,				/*!< DMA continous request enable */
	ADC_DMA_CONT_RQST_MAX
} adc_dma_cont_rqst_t;

typedef enum {
	ADC_EOC_MODE_SEQ_CONV = 0,				/*!< EOC mode sequence conversion */
	ADC_EOC_MODE_SINGLE_CONV,				/*!< EOC Mode single conversion */
	ADC_EOC_MODE_SINGLE_SEQ_CONV,			/*!< EOC mode single sequence conversion */
	ADC_EOC_MODE_MAX
} adc_eoc_mode_t;

typedef enum {
	ADC_SAMP_TIME_3CYCLES = 0,				/*!< ADC sample time 3 cycles */
	ADC_SAMP_TIME_15CYCLES,					/*!< ADC sample time 15 cycles */
	ADC_SAMP_TIME_28CYCLES,					/*!< ADC sample time 28 cycles */
	ADC_SAMP_TIME_56CYCLES,					/*!< ADC sample time 56 cycles */
	ADC_SAMP_TIME_84CYCLES,					/*!< ADC sample time 84 cycles */
	ADC_SAMP_TIME_112CYCLES,				/*!< ADC sample time 112 cycles */
	ADC_SAMP_TIME_144CYCLES,				/*!< ADC sample time 144 cycles */
	ADC_SAMP_TIME_480CYCLES,					/*!< ADC sample time 480 cycles */
	ADC_SAMP_TIME_MAX
} adc_samp_time_t;

typedef struct {
	adc_num_t 					adc_num;				/*!< ADC num selection */
	adc_resolution_t 			resolution;				/*!< ADC resolution */
	adc_clk_div_t 				clk_div;				/*!< ADC clock divider */
	adc_data_align_t 			data_align;				/*!< ADC data alignment */
	uint32_t 					num_conv;				/*!< ADC number of conversion */
	adc_scan_mode_t 			scan_mode;				/*!< ADC scan mode */
	adc_cont_conv_mode_t 		cont_conv_mode;			/*!< ADC continous conversion mode */
	adc_discont_conv_mode_t 	discont_conv_mode;		/*!< ADC discontinous conversion mode */
	adc_ext_trigconv_edge_t 	ext_trigconv_edge;		/*!< ADC external trigger conver */
	adc_dma_cont_rqst_t 		dma_cont_rqst;			/*!< ADC DMA continous requests */
	adc_eoc_mode_t 				eoc_mode;				/*!< ADC end of conversion mode */
} adc_cfg_t;

/*
 * @brief   Configure ADC.
 * @param   config Pointer to ADC configure struct.
 * @return
 *      - STM_OK:       Success.
 *      - Others:       Fail.
 */
stm_err_t adc_config(adc_cfg_t *config);

/*
 * @brief   Configure ADC channel.
 * @param   adc_num ADC num.
 * @param 	adc_chnl ADC channel.
 * @param 	samp_time sample time.
 * @param 	prior Channel priority.
 * @return
 *      - STM_OK:       Success.
 *      - Others:       Fail.
 */
stm_err_t adc_channel_config(adc_num_t adc_num, adc_chnl_t adc_chnl, adc_samp_time_t samp_time, uint32_t prior);

/*
 * @brief   Start ADC conversion.
 * @param   adc_num ADC num.
 * @return
 *      - STM_OK:       Success.
 *      - Others:       Fail.
 */
stm_err_t adc_start(adc_num_t adc_num);

/*
 * @brief   Get ADC conversion value.
 * @param   adc_num ADC num.
 * @param 	value Buffer.
 * @return
 *      - STM_OK:       Success.
 *      - Others:       Fail.
 */
stm_err_t adc_get_value(adc_num_t adc_num, uint16_t *value);

#ifdef __cplusplus
}
#endif

#endif /* _DRIVER_ADC_H_ */