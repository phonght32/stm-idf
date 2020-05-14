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

#ifndef _GPIO_MAPPING_STM32F4_H_
#define _GPIO_MAPPING_STM32F4_H_

#ifdef __cplusplus
extern "C" {
#endif

GPIO_TypeDef* GPIOx_MAPPING[GPIO_PORT_MAX] = {
    GPIOA,          
    GPIOB,          
    GPIOC,          
    GPIOD,          
    GPIOE,          
    GPIOF,          
    GPIOG,          
    GPIOH,          
    GPIOI           
};

uint16_t GPIO_PIN_MAPPING[GPIO_NUM_MAX] = {
    GPIO_PIN_0,     
    GPIO_PIN_1,     
    GPIO_PIN_2,     
    GPIO_PIN_3,     
    GPIO_PIN_4,     
    GPIO_PIN_5,     
    GPIO_PIN_6,     
    GPIO_PIN_7,     
    GPIO_PIN_8,     
    GPIO_PIN_9,     
    GPIO_PIN_10,    
    GPIO_PIN_11,    
    GPIO_PIN_12,    
    GPIO_PIN_13,    
    GPIO_PIN_14,    
    GPIO_PIN_15     
};

uint32_t GPIO_REG_PULL_MAPPING[GPIO_REG_PULL_MAX] = {
    GPIO_NOPULL,    
    GPIO_PULLUP,    
    GPIO_PULLDOWN   
};

uint32_t RCC_AHB1ENR_GPIOxEN_MAPPING[GPIO_PORT_MAX] = {
    RCC_AHB1ENR_GPIOAEN,    
    RCC_AHB1ENR_GPIOBEN,    
    RCC_AHB1ENR_GPIOCEN,    
    RCC_AHB1ENR_GPIODEN,    
    RCC_AHB1ENR_GPIOEEN,    
    RCC_AHB1ENR_GPIOFEN,    
    RCC_AHB1ENR_GPIOGEN,    
    RCC_AHB1ENR_GPIOHEN,   
    RCC_AHB1ENR_GPIOIEN,    
};

uint32_t GPIO_MODE_MAPPING[GPIO_MODE_MAX] = {
    GPIO_MODE_INPUT,
    GPIO_MODE_OUTPUT_PP,
    GPIO_MODE_OUTPUT_OD,
    GPIO_MODE_AF_PP,
    GPIO_MODE_AF_OD,
    GPIO_MODE_ANALOG,
    GPIO_MODE_IT_RISING,
    GPIO_MODE_IT_FALLING,
    GPIO_MODE_IT_RISING_FALLING,
    GPIO_MODE_EVT_RISING,
    GPIO_MODE_EVT_FALLING,
    GPIO_MODE_EVT_RISING_FALLING
};

#ifdef __cplusplus
}
#endif

#endif /* _GPIO_MAPPING_STM32F4_H_ */