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

#ifndef _DRIVER_TIMER_H_
#define _DRIVER_TIMER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stm_err.h"

typedef enum {
    TIMER_NUM_1 = 0,        /*!< Timer Num 1 selected */
    TIMER_NUM_2,            /*!< Timer Num 2 selected */
    TIMER_NUM_3,            /*!< Timer Num 3 selected */
    TIMER_NUM_4,            /*!< Timer Num 4 selected */
    TIMER_NUM_5,            /*!< Timer Num 5 selected */
    TIMER_NUM_6,            /*!< Timer Num 6 selected */
    TIMER_NUM_7,            /*!< Timer Num 7 selected */
    TIMER_NUM_8,            /*!< Timer Num 8 selected */
    TIMER_NUM_9,            /*!< Timer Num 9 selected */
    TIMER_NUM_10,           /*!< Timer Num 10 selected */
    TIMER_NUM_11,           /*!< Timer Num 11 selected */
    TIMER_NUM_12,           /*!< Timer Num 12 selected */
    TIMER_NUM_13,           /*!< Timer Num 13 selected */
    TIMER_NUM_14            /*!< Timer Num 14 selected */
} timer_num_t;

typedef enum {
    TIMER_CHNL_1 = 0,       /*!< Timer Channel 1 selected */
    TIMER_CHNL_2,           /*!< Timer Channel 2 selected */
    TIMER_CHNL_3,           /*!< Timer Channel 3 selected */
    TIMER_CHNL_4            /*!< Timer Channel 4 selected */
} timer_chnl_t;

typedef enum {
    TIMER_PINS_PACK_1 = 0,  /*!< Timer Pins Pack 1 selected */
    TIMER_PINS_PACK_2,      /*!< Timer Pins Pack 2 selected */
    TIMER_PINS_PACK_3       /*!< Timer Pins Pack 3 selected */
} timer_pins_pack_t;

typedef enum {
    TIMER_COUNTER_UP = 0,   /*!< Timer counter mode up */
    TIMER_COUNTER_DOWN      /*!< Timer counter mode down */
} timer_counter_mode_t;

typedef struct {
    timer_num_t         timer_num;              /*!< Timer Num */
    timer_chnl_t        timer_chnl;             /*!< Timer Channel */
    timer_pins_pack_t   timer_pins_pack;        /*!< Timer Pins Pack */
} pwm_config_t;

typedef struct {
    timer_num_t             timer_num;          /*!< Timer Num */
    timer_pins_pack_t       timer_pins_pack;    /*!< Timer Pins Pack */
    uint32_t                max_reload;         /*!< Timer Max Reload value */
    timer_counter_mode_t    counter_mode;       /*!< Timer Counter Mode */
} etr_config_t;

/*
 * @brief   Initialize PWM.
 * @param   config Struct pointer.
 * @return
 *      - STM_OK:       Success.
 *      - Others:       Fail.
 */
stm_err_t pwm_config(pwm_config_t *config);

/*
 * @brief   Start PWM generate.
 * @param   timer_num Timer num.
 * @param   timer_chnl Timer channel.
 * @return
 *      - STM_OK:       Success.
 *      - Others:       Fail.
 */
stm_err_t pwm_start(timer_num_t timer_num, timer_chnl_t timer_chnl);

/*
 * @brief   Stop PWM generate.
 * @param   timer_num Timer num.
 * @param   timer_chnl Timer channel.
 * @return
 *      - STM_OK:       Success.
 *      - Others:       Fail.
 */
stm_err_t pwm_stop(timer_num_t timer_num, timer_chnl_t timer_chnl);

/*
 * @brief   Set PWM frequency in Hz.
 * @param   timer_num Timer num.
 * @param   timer_chnl Timer channel.
 * @param   freq_hz Frequency in Hz.
 * @return
 *      - STM_OK:       Success.
 *      - Others:       Fail.
 */
stm_err_t pwm_set_frequency(timer_num_t timer_num, timer_chnl_t timer_chnl, uint32_t freq_hz);

/*
 * @brief   Set PWM duty cycle in %.
 * @param   timer_num Timer num.
 * @param   timer_chnl Timer channel.
 * @param   duty_percent Duty cycle in %.
 * @return
 *      - STM_OK:       Success.
 *      - Others:       Fail.
 */
stm_err_t pwm_set_duty(timer_num_t timer_num, timer_chnl_t timer_chnl, uint8_t duty_percent);

/*
 * @brief   Set PWM set frequency and duty cycle.
 * @param   timer_num Timer num.
 * @param   freq_hz Frequency in Hz.
 * @param   timer_chnl Timer channel.
 * @param   duty_percent Duty cycle in %.
 * @return
 *      - STM_OK:       Success.
 *      - Others:       Fail.
 */
stm_err_t pwm_set_params(timer_num_t timer_num, timer_chnl_t timer_chnl, uint32_t freq_hz, uint8_t duty_percent);

/*
 * @brief   Initialize External Counter input.
 * @param   config Struct pointer.
 * @return
 *      - STM_OK:       Success.
 *      - Others:       Fail.
 */
stm_err_t etr_config(etr_config_t *config);

/*
 * @brief   Start counter external pulse input.
 * @param   timer_num Timer num.
 * @return
 *      - STM_OK:       Success.
 *      - Others:       Fail.
 */
stm_err_t etr_start(timer_num_t timer_num);

/*
 * @brief   Start counter external pulse input.
 * @param   timer_num Timer num.
 * @return
 *      - STM_OK:       Success.
 *      - Others:       Fail.
 */
stm_err_t etr_stop(timer_num_t timer_num);

/*
 * @brief   Get counter value.
 * @param   timer_num Timer num.
 * @param   value Counter value.
 * @return
 *      - STM_OK:       Success.
 *      - Others:       Fail.
 */
stm_err_t etr_get_value(timer_num_t timer_num, uint32_t *value);

/*
 * @brief   Set counter value.
 * @param   timer_num Timer num.
 * @param   value Counter value.
 * @return
 *      - STM_OK:       Success.
 *      - Others:       Fail.
 */
stm_err_t etr_set_value(timer_num_t timer_num, uint32_t value);

/*
 * @brief   Set counter mode.
 * @param   timer_num Timer num.
 * @param   counter_mode Counter mode.
 * @return
 *      - STM_OK:       Success.
 *      - Others:       Fail.
 */
stm_err_t etr_set_mode(timer_num_t timer_num, timer_counter_mode_t counter_mode);


#ifdef __cplusplus
}
#endif

#endif /* _DRIVER_TIMER_H_ */
