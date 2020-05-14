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

#ifndef _ADC_MAPPING_STM32F4_H_
#define _ADC_MAPPING_STM32F4_H_

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

#define ADC_NUM_MAX 					3
#define ADC_CHNL_MAX					16	
#define ADC_RESOLUTION_MAX  			4
#define ADC_CLK_DIV_MAX					4
#define ADC_SCAN_MODE_MAX 				2
#define ADC_DISCONT_CONV_MODE_MAX		2
#define ADC_DATA_ALIGN_MAX 				2
#define ADC_EXT_TRIGCONV_MAX			4
#define ADC_DMA_CONT_RQST_MAX 			2
#define ADC_EOC_MODE_MAX 				3
#define ADC_SAMP_TIME_MAX 				8

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
	ADC2,
	ADC3
};

uint32_t RCC_APBENR_ADCEN_MAPPING[ADC_NUM_MAX] = {
	RCC_APB2ENR_ADC1EN,
	RCC_APB2ENR_ADC2EN,
	RCC_APB2ENR_ADC3EN
};

#ifdef __cplusplus
}
#endif

#endif /* _ADC_MAPPING_STM32F4_H_ */