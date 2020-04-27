// MIT License

// Copyright (c) 2020 thanhphong98 & thuanpham98

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

#ifndef _ADC_H_
#define _ADC_H_ 

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"

#include "stm32f4xx_hal.h"

#include "stm_err.h"
#include "stm_log.h"

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

typedef enum {
	ADC_NUM_1 = 0,
	ADC_NUM_2,
	ADC_NUM_3,
	ADC_NUM_MAX
} adc_num_t;

typedef enum {
	ADC_CHNL_0 = 0,
	ADC_CHNL_1,
	ADC_CHNL_2,
	ADC_CHNL_3,
	ADC_CHNL_4,
	ADC_CHNL_5,
	ADC_CHNL_6,
	ADC_CHNL_7,
	ADC_CHNL_8,
	ADC_CHNL_9,
	ADC_CHNL_10,
	ADC_CHNL_11,
	ADC_CHNL_12,
	ADC_CHNL_13,
	ADC_CHNL_14,
	ADC_CHNL_15,
	ADC_CHNL_MAX
} adc_chnl_t;

typedef enum {
	ADC_RESOLUTION_6BIT = 0,
	ADC_RESOLUTION_8BIT,
	ADC_RESOLUTION_10BIT,
	ADC_RESOLUTION_12BIT,
	ADC_RESOLUTION_MAX_TYPE
} adc_resolution_t;

typedef enum {
	ADC_CLK_DIV_2 = 0,
	ADC_CLK_DIV_4,
	ADC_CLK_DIV_6,
	ADC_CLK_DIV_8,
	ADC_CLK_DIV_MAX_TYPE
} adc_clk_div_t;

typedef enum {
	ADC_SCAN_MODE_DISABLE = 0,
	ADC_SCAN_MODE_ENABLE
} adc_scan_mode_t;

typedef enum {
	ADC_CONT_CONV_MODE_DISABLE = 0,
	ADC_CONT_CONV_MODE_ENABLE
} adc_cont_conv_mode_t;

typedef enum {
	ADC_DISCONT_CONV_MODE_DISABLE = 0,
	ADC_DISCONT_CONV_MODE_ENABLE
} adc_discont_conv_mode_t;

typedef enum {
	ADC_DATA_ALIGN_RIGHT = 0,
	ADC_DATA_ALIGN_LEFT,
	ADC_DATA_ALIGN_MAX_TYPE
} adc_data_align_t;

typedef enum {
	ADC_EXT_TRIGCONV_NONE = 0,
	ADC_EXT_TRIGCONV_RISING_EDGE,
	ADC_EXT_TRIGCONV_FALING_EDGE,
	ADC_EXT_TRIGCONV_BOTH_EDGE,
	ADC_EXT_TRIGCONV_MAX
} adc_ext_trigconv_edge_t;

typedef enum {
	ADC_DMA_CONT_RQST_DISABLE,
	ADC_DMA_CONT_RQST_ENABLE
} adc_dma_cont_rqst_t;

typedef enum {
	ADC_EOC_MODE_SEQ_CONV = 0,
	ADC_EOC_MODE_SINGLE_CONV,
	ADC_EOC_MODE_SINGLE_SEQ_CONV,
	ADC_EOC_MODE_MAX
} adc_eoc_mode_t;

typedef enum {
	ADC_SAMP_TIME_3CYCLES = 0,
	ADC_SAMP_TIME_15CYCLES,
	ADC_SAMP_TIME_28CYCLES,
	ADC_SAMP_TIME_56CYCLES,
	ADC_SAMP_TIME_84CYCLES,
	ADC_SAMP_TIME_112CYCLES,
	ADC_SAMP_TIME_144CYCLES,
	ADC_SAMP_TIME_480CYCLES,
	ADC_SAMP_TIME_MAX
} adc_samp_time_t;

typedef struct {
	adc_num_t adc_num;
	adc_resolution_t resolution;
	adc_clk_div_t clk_div;
	adc_data_align_t data_align;
	uint32_t num_disconn_conv;
	adc_scan_mode_t scan_mode;
	adc_cont_conv_mode_t cont_conv_mode;
	adc_discont_conv_mode_t discont_conv_mode;
	adc_ext_trigconv_edge_t ext_trigconv_edge;
	adc_dma_cont_rqst_t dma_cont_rqst;
	adc_eoc_mode_t eoc_mode;
} adc_config_t;

stm_err_t adc_config(adc_config_t *config);
stm_err_t adc_channel_config(adc_num_t adc_num, adc_chnl_t adc_chnl, adc_samp_time_t samp_time, uint32_t prior);

#ifdef __cplusplus
}
#endif

#endif /* _ADC_H_ */