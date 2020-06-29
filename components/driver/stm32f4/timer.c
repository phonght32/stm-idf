#include "stm_hal.h"
#include "stm_log.h"

#include "driver/timer.h"

#define GPIO_MODE_DEFAULT           GPIO_MODE_AF_PP             /*!< Default GPIO mode */
#define GPIO_PULL_REG_DEFAULT       GPIO_NOPULL                 /*!< Default GPIO pull registor */
#define GPIO_SPEED_FREQ_DEFAULT     GPIO_SPEED_FREQ_VERY_HIGH   /*!< Default GPIO speed */

#define PWM_COUNTERMODE_DEFAULT     TIM_COUNTERMODE_UP          /*!< Default PWM counter mode */
#define PWM_TIM_CLOCK_DIV_DEFAULT   TIM_CLOCKDIVISION_DIV1      /*!< Default PWM timer clock divide */

#define EXT_CNT_PRES_DEFAULT        0                           /*!< Default external counter prescaler */

#define TIMER_MAX_RELOAD            0xFFFF                      /*!< User timer max value (16bit value) */

#define TIMER_NUM_ERR_STR           "timer num error"
#define TIMER_PINS_PACK_ERR_STR     "timer pins pack error"
#define TIMER_CHANNEL_ERR_STR       "timer channel error"

#define PWM_INIT_ERR_STR            "pwn init error"
#define PWM_START_ERR_STR           "pwm start error"
#define PWM_STOP_ERR_STR            "pwm stop error"
#define PWM_SET_FREQ_ERR_STR        "pwm set frequency error"
#define PWM_SET_DUTYCYCLE_ERR_STR   "pwm set duty cycle error"
#define PWM_SET_PARAMS_ERR_STR      "pwm set params error"
#define PWM_FREQUENCY_ERR_STR       "pwm frequency error"
#define PWM_DUTYCYCLE_ERR_STR       "pwm duty cycle error"

#define ETR_INIT_ERR_STR            "etr init error"
#define ETR_START_ERR_STR           "etr start error"
#define ETR_STOP_ERR_STR            "etr stop error"
#define ETR_GET_VALUE_ERR_STR       "etr get value error"
#define ETR_SET_VALUE_ERR_STR       "etr set value error"
#define ETR_SET_MODE_ERR_STR        "etr set mode error"

#define APB1_CLOCK                  (1.0f/2.0f)         /*!< APB1 clock */
#define APB2_CLOCK                  (1.0f)              /*!< APB2 clock */


#define TIM1_CH1_PP1_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOAEN,  \
                                     .port = GPIOA,                             \
                                     .pin = GPIO_PIN_8}

#define TIM1_CH1_PP2_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOEEN,  \
                                     .port = GPIOE,                             \
                                     .pin = GPIO_PIN_9}

#define TIM1_CH2_PP1_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOAEN,  \
                                     .port = GPIOA,                             \
                                     .pin = GPIO_PIN_9}

#define TIM1_CH2_PP2_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOEEN,  \
                                     .port = GPIOE,                             \
                                     .pin = GPIO_PIN_10}

#define TIM1_CH3_PP1_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOAEN,  \
                                     .port = GPIOA,                             \
                                     .pin = GPIO_PIN_10}

#define TIM1_CH3_PP2_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOEEN,  \
                                     .port = GPIOE,                             \
                                     .pin = GPIO_PIN_13}

#define TIM1_CH4_PP1_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOAEN,  \
                                     .port = GPIOA,                             \
                                     .pin = GPIO_PIN_11}

#define TIM1_CH4_PP2_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOEEN,  \
                                     .port = GPIOE,                             \
                                     .pin = GPIO_PIN_14}

#define TIM2_CH1_PP1_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOAEN,  \
                                     .port = GPIOA,                             \
                                     .pin = GPIO_PIN_0}

#define TIM2_CH1_PP2_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOAEN,  \
                                     .port = GPIOA,                             \
                                     .pin = GPIO_PIN_5}

#define TIM2_CH1_PP3_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOAEN,  \
                                     .port = GPIOA,                             \
                                     .pin = GPIO_PIN_15}

#define TIM2_CH2_PP1_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOAEN,  \
                                     .port = GPIOA,                             \
                                     .pin = GPIO_PIN_1}

#define TIM2_CH2_PP2_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOBEN,  \
                                     .port = GPIOB,                             \
                                     .pin = GPIO_PIN_3}

#define TIM2_CH3_PP1_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOAEN,  \
                                     .port = GPIOA,                             \
                                     .pin = GPIO_PIN_2}

#define TIM2_CH3_PP2_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOBEN,  \
                                     .port = GPIOB,                             \
                                     .pin = GPIO_PIN_10}

#define TIM2_CH4_PP1_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOAEN,  \
                                     .port = GPIOA,                             \
                                     .pin = GPIO_PIN_3}

#define TIM2_CH4_PP2_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOBEN,  \
                                     .port = GPIOB,                             \
                                     .pin = GPIO_PIN_11}

#define TIM3_CH1_PP1_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOAEN,  \
                                     .port = GPIOA,                             \
                                     .pin = GPIO_PIN_6}

#define TIM3_CH1_PP2_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOBEN,  \
                                     .port = GPIOB,                             \
                                     .pin = GPIO_PIN_4}

#define TIM3_CH1_PP3_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOCEN,  \
                                     .port = GPIOC,                             \
                                     .pin = GPIO_PIN_6}

#define TIM3_CH2_PP1_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOAEN,  \
                                     .port = GPIOA,                             \
                                     .pin = GPIO_PIN_7}

#define TIM3_CH2_PP2_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOBEN,  \
                                     .port = GPIOB,                             \
                                     .pin = GPIO_PIN_5}

#define TIM3_CH2_PP3_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOCEN,  \
                                     .port = GPIOC,                             \
                                     .pin = GPIO_PIN_7}

#define TIM3_CH3_PP1_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOBEN,  \
                                     .port = GPIOB,                             \
                                     .pin = GPIO_PIN_0}

#define TIM3_CH3_PP2_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOCEN,  \
                                     .port = GPIOC,                             \
                                     .pin = GPIO_PIN_8}

#define TIM3_CH4_PP1_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOBEN,  \
                                     .port = GPIOB,                             \
                                     .pin = GPIO_PIN_1}

#define TIM3_CH4_PP2_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOCEN,  \
                                     .port = GPIOC,                             \
                                     .pin = GPIO_PIN_9}


#define TIM4_CH1_PP1_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOBEN,  \
                                     .port = GPIOB,                             \
                                     .pin = GPIO_PIN_6}

#define TIM4_CH1_PP2_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIODEN,  \
                                     .port = GPIOD,                             \
                                     .pin = GPIO_PIN_12}

#define TIM4_CH2_PP1_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOBEN,  \
                                     .port = GPIOB,                             \
                                     .pin = GPIO_PIN_7}

#define TIM4_CH2_PP2_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIODEN,  \
                                     .port = GPIOD,                             \
                                     .pin = GPIO_PIN_13}

#define TIM4_CH3_PP1_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOBEN,  \
                                     .port = GPIOB,                             \
                                     .pin = GPIO_PIN_8}

#define TIM4_CH3_PP2_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIODEN,  \
                                     .port = GPIOD,                             \
                                     .pin = GPIO_PIN_14}

#define TIM4_CH4_PP1_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOBEN,  \
                                     .port = GPIOB,                             \
                                     .pin = GPIO_PIN_9}

#define TIM4_CH4_PP2_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIODEN,  \
                                     .port = GPIOD,                             \
                                     .pin = GPIO_PIN_15}

#define TIM5_CH1_PP1_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOAEN,  \
                                     .port = GPIOA,                             \
                                     .pin = GPIO_PIN_0}

#define TIM5_CH1_PP2_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOHEN,  \
                                     .port = GPIOH,                             \
                                     .pin = GPIO_PIN_10}

#define TIM5_CH2_PP1_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOAEN,  \
                                     .port = GPIOA,                     \
                                     .pin = GPIO_PIN_1}

#define TIM5_CH2_PP2_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOHEN,  \
                                     .port = GPIOH,                             \
                                     .pin = GPIO_PIN_11}

#define TIM5_CH3_PP1_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOAEN,  \
                                     .port = GPIOA,                             \
                                     .pin = GPIO_PIN_2}

#define TIM5_CH3_PP2_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOHEN,  \
                                     .port = GPIOH,                             \
                                     .pin = GPIO_PIN_12}

#define TIM5_CH4_PP1_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOAEN,  \
                                     .port = GPIOA,                             \
                                     .pin = GPIO_PIN_3}

#define TIM5_CH4_PP2_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOIEN,  \
                                     .port = GPIOI,                             \
                                     .pin = GPIO_PIN_0}

#define TIM8_CH1_PP1_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOCEN,  \
                                     .port = GPIOC,                             \
                                     .pin = GPIO_PIN_6}

#define TIM8_CH1_PP2_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOIEN,  \
                                     .port = GPIOI,                             \
                                     .pin = GPIO_PIN_15}

#define TIM8_CH2_PP1_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOCEN,  \
                                     .port = GPIOC,                             \
                                     .pin = GPIO_PIN_7}

#define TIM8_CH2_PP2_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOIEN,  \
                                     .port = GPIOI,                             \
                                     .pin = GPIO_PIN_6}

#define TIM8_CH3_PP1_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOCEN,  \
                                     .port = GPIOC,                             \
                                     .pin = GPIO_PIN_8}

#define TIM8_CH3_PP2_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOIEN,  \
                                     .port = GPIOI,                             \
                                     .pin = GPIO_PIN_7}

#define TIM8_CH4_PP1_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOCEN,  \
                                     .port = GPIOC,                             \
                                     .pin = GPIO_PIN_9}

#define TIM8_CH4_PP2_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOIEN,  \
                                     .port = GPIOI,                             \
                                     .pin = GPIO_PIN_2}

#define TIM9_CH1_PP1_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOAEN,  \
                                     .port = GPIOA,                             \
                                     .pin = GPIO_PIN_2}

#define TIM9_CH1_PP2_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOEEN,  \
                                     .port = GPIOE,                             \
                                     .pin = GPIO_PIN_5}

#define TIM9_CH2_PP1_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOAEN,  \
                                     .port = GPIOA,                             \
                                     .pin = GPIO_PIN_3}

#define TIM9_CH2_PP2_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOEEN,  \
                                     .port = GPIOE,                             \
                                     .pin = GPIO_PIN_6}

#define TIM10_CH1_PP1_HW_INFO       {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOBEN,  \
                                     .port = GPIOB,                             \
                                     .pin = GPIO_PIN_8}

#define TIM10_CH1_PP2_HW_INFO       {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOFEN,  \
                                     .port = GPIOF,                             \
                                     .pin = GPIO_PIN_6}

#define TIM11_CH1_PP1_HW_INFO       {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOBEN,  \
                                     .port = GPIOB,                             \
                                     .pin = GPIO_PIN_9}

#define TIM11_CH1_PP2_HW_INFO       {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOFEN,  \
                                     .port = GPIOF,                             \
                                     .pin = GPIO_PIN_7}

#define TIM12_CH1_PP1_HW_INFO       {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOBEN,  \
                                     .port = GPIOB,                             \
                                     .pin = GPIO_PIN_14}

#define TIM12_CH1_PP2_HW_INFO       {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOHEN,  \
                                     .port = GPIOH,                             \
                                     .pin = GPIO_PIN_6}

#define TIM12_CH2_PP1_HW_INFO       {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOBEN,  \
                                     .port = GPIOB,                             \
                                     .pin = GPIO_PIN_15}

#define TIM12_CH2_PP2_HW_INFO       {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOHEN,  \
                                     .port = GPIOH,                             \
                                     .pin = GPIO_PIN_9}

#define TIM13_CH1_PP1_HW_INFO       {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOAEN,  \
                                     .port = GPIOA,                             \
                                     .pin = GPIO_PIN_6}

#define TIM13_CH1_PP2_HW_INFO       {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOFEN,  \
                                     .port = GPIOF,                             \
                                     .pin = GPIO_PIN_8}

#define TIM14_CH1_PP1_HW_INFO       {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOAEN,  \
                                     .port = GPIOA,                             \
                                     .pin = GPIO_PIN_7}

#define TIM14_CH1_PP2_HW_INFO       {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOFEN,  \
                                     .port = GPIOF,                             \
                                     .pin = GPIO_PIN_9}

#define TIM1_PP1_ETR_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOAEN,  \
                                     .port = GPIOA,                             \
                                     .pin = GPIO_PIN_12}

#define TIM1_PP2_ETR_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOEEN,  \
                                     .port = GPIOE,                             \
                                     .pin = GPIO_PIN_7}

#define TIM2_PP1_ETR_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOAEN,  \
                                     .port = GPIOA,                             \
                                     .pin = GPIO_PIN_0}

#define TIM2_PP2_ETR_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOAEN,  \
                                     .port = GPIOA,                             \
                                     .pin = GPIO_PIN_5}

#define TIM2_PP3_ETR_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOAEN,  \
                                     .port = GPIOA,                             \
                                     .pin = GPIO_PIN_15}

#define TIM3_PP1_ETR_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIODEN,  \
                                     .port = GPIOD,                             \
                                     .pin = GPIO_PIN_2}

#define TIM4_PP1_ETR_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOEEN,  \
                                     .port = GPIOE,                             \
                                     .pin = GPIO_PIN_0}

#define TIM8_PP1_ETR_HW_INFO        {.rcc_ahbenr_gpioen = RCC_AHB1ENR_GPIOAEN,  \
                                     .port = GPIOA,                             \
                                     .pin = GPIO_PIN_0}

static const char* TIMER_TAG = "DRIVER TIMER";
#define TIMER_CHECK(a, str, ret)  if(!(a)) {                                             \
        STM_LOGE(TIMER_TAG,"%s:%d (%s):%s", __FILE__, __LINE__, __FUNCTION__, str);      \
        return (ret);                                                                  \
        }

TIM_HandleTypeDef timer_handle[TIMER_NUM_MAX];

typedef struct {
    uint32_t        rcc_ahbenr_gpioen;      /*!< GPIO RCC AHPENR register */
    GPIO_TypeDef    *port;                  /*!< General Purpose I/O */
    uint16_t        pin;                    /*!< Pin */
} tim_hw_info_t;

tim_hw_info_t TIM_HW_INFO_MAPPING[TIMER_NUM_MAX][TIMER_CHNL_MAX][TIMER_PINS_PACK_MAX] = {
    {   {TIM1_CH1_PP1_HW_INFO , TIM1_CH1_PP2_HW_INFO ,                  {0}},
        {TIM1_CH2_PP1_HW_INFO , TIM1_CH2_PP2_HW_INFO ,                  {0}},
        {TIM1_CH3_PP1_HW_INFO , TIM1_CH3_PP2_HW_INFO ,                  {0}},
        {TIM1_CH4_PP1_HW_INFO , TIM1_CH4_PP2_HW_INFO ,                  {0}}
    },

    {   {TIM2_CH1_PP1_HW_INFO , TIM2_CH1_PP2_HW_INFO , TIM2_CH1_PP3_HW_INFO},
        {TIM2_CH2_PP1_HW_INFO , TIM2_CH2_PP2_HW_INFO ,                  {0}},
        {TIM2_CH3_PP1_HW_INFO , TIM2_CH3_PP2_HW_INFO ,                  {0}},
        {TIM2_CH4_PP1_HW_INFO , TIM2_CH4_PP2_HW_INFO ,                  {0}}
    },

    {   {TIM3_CH1_PP1_HW_INFO , TIM3_CH1_PP2_HW_INFO , TIM3_CH1_PP3_HW_INFO},
        {TIM3_CH2_PP1_HW_INFO , TIM3_CH2_PP2_HW_INFO , TIM3_CH2_PP3_HW_INFO},
        {TIM3_CH3_PP1_HW_INFO , TIM3_CH3_PP2_HW_INFO ,                  {0}},
        {TIM3_CH4_PP1_HW_INFO , TIM3_CH4_PP2_HW_INFO ,                  {0}}
    },

    {   {TIM4_CH1_PP1_HW_INFO , TIM4_CH1_PP2_HW_INFO ,                  {0}},
        {TIM4_CH2_PP1_HW_INFO , TIM4_CH2_PP2_HW_INFO ,                  {0}},
        {TIM4_CH3_PP1_HW_INFO , TIM4_CH3_PP2_HW_INFO ,                  {0}},
        {TIM4_CH4_PP1_HW_INFO , TIM4_CH4_PP2_HW_INFO ,                  {0}}
    },

    {   {TIM5_CH1_PP1_HW_INFO , TIM5_CH1_PP2_HW_INFO ,                  {0}},
        {TIM5_CH2_PP1_HW_INFO , TIM5_CH2_PP2_HW_INFO ,                  {0}},
        {TIM5_CH3_PP1_HW_INFO , TIM5_CH3_PP2_HW_INFO ,                  {0}},
        {TIM5_CH4_PP1_HW_INFO , TIM5_CH4_PP2_HW_INFO ,                  {0}}
    },

    {   {                  {0},                   {0},                  {0}},
        {                  {0},                   {0},                  {0}},
        {                  {0},                   {0},                  {0}},
        {                  {0},                   {0},                  {0}}
    },

    {   {                  {0},                   {0},                  {0}},
        {                  {0},                   {0},                  {0}},
        {                  {0},                   {0},                  {0}},
        {                  {0},                   {0},                  {0}}
    },

    {   {TIM8_CH1_PP1_HW_INFO , TIM8_CH1_PP2_HW_INFO ,                  {0}},
        {TIM8_CH2_PP1_HW_INFO , TIM8_CH2_PP2_HW_INFO ,                  {0}},
        {TIM8_CH3_PP1_HW_INFO , TIM8_CH3_PP2_HW_INFO ,                  {0}},
        {TIM8_CH4_PP1_HW_INFO , TIM8_CH4_PP2_HW_INFO ,                  {0}}
    },

    {   {TIM9_CH1_PP1_HW_INFO , TIM9_CH1_PP2_HW_INFO ,                  {0}},
        {TIM9_CH2_PP1_HW_INFO , TIM9_CH2_PP2_HW_INFO ,                  {0}},
        {                  {0},                   {0},                  {0}},
        {                  {0},                   {0},                  {0}}
    },

    {   {TIM10_CH1_PP1_HW_INFO, TIM10_CH1_PP2_HW_INFO,                  {0}},
        {                  {0},                   {0},                  {0}},
        {                  {0},                   {0},                  {0}},
        {                  {0},                   {0},                  {0}}
    },

    {   {TIM11_CH1_PP1_HW_INFO, TIM11_CH1_PP2_HW_INFO,                  {0}},
        {                  {0},                   {0},                  {0}},
        {                  {0},                   {0},                  {0}},
        {                  {0},                   {0},                  {0}}
    },

    {   {TIM12_CH1_PP1_HW_INFO, TIM12_CH1_PP2_HW_INFO,                  {0}},
        {TIM12_CH2_PP1_HW_INFO, TIM12_CH2_PP2_HW_INFO,                  {0}},
        {                  {0},                   {0},                  {0}},
        {                  {0},                   {0},                  {0}}
    },

    {   {TIM13_CH1_PP1_HW_INFO, TIM13_CH1_PP2_HW_INFO,                  {0}},
        {                  {0},                   {0},                  {0}},
        {                  {0},                   {0},                  {0}},
        {                  {0},                   {0},                  {0}}
    },

    {   {TIM14_CH1_PP1_HW_INFO, TIM14_CH1_PP2_HW_INFO,                     },
        {                  {0},                   {0},                  {0}},
        {                  {0},                   {0},                  {0}},
        {                  {0},                   {0},                  {0}}
    }
};

tim_hw_info_t TIM_ETR_HW_INFO_MAPPING[TIMER_NUM_MAX][TIMER_PINS_PACK_MAX] = {
    { TIM1_PP1_ETR_HW_INFO, TIM1_PP2_ETR_HW_INFO,                  {0}},
    { TIM2_PP1_ETR_HW_INFO, TIM2_PP2_ETR_HW_INFO, TIM2_PP3_ETR_HW_INFO},
    { TIM3_PP1_ETR_HW_INFO,                  {0},                  {0}},
    { TIM4_PP1_ETR_HW_INFO,                  {0},                  {0}},
    {                  {0},                  {0},                  {0}},
    {                  {0},                  {0},                  {0}},
    {                  {0},                  {0},                  {0}},
    { TIM8_PP1_ETR_HW_INFO,                  {0},                  {0}},
    {                  {0},                  {0},                  {0}},
    {                  {0},                  {0},                  {0}},
    {                  {0},                  {0},                  {0}},
    {                  {0},                  {0},                  {0}},
    {                  {0},                  {0},                  {0}},
    {                  {0},                  {0},                  {0}},
};

static TIM_TypeDef* TIM_MAPPING[TIMER_NUM_MAX] = {
    TIM1,
    TIM2,
    TIM3,
    TIM4,
    TIM5,
    TIM6,
    TIM7,
    TIM8,
    TIM9,
    TIM10,
    TIM11,
    TIM12,
    TIM13,
    TIM14
};

uint32_t TIM_ALTERNATE_FUNC_MAPPING[TIMER_NUM_MAX] = {
    GPIO_AF1_TIM1,
    GPIO_AF1_TIM2,
    GPIO_AF2_TIM3,
    GPIO_AF2_TIM4,
    GPIO_AF2_TIM5,
    0,
    0,
    GPIO_AF3_TIM8,
    GPIO_AF3_TIM9,
    GPIO_AF3_TIM10,
    GPIO_AF3_TIM11,
    GPIO_AF9_TIM12,
    GPIO_AF9_TIM13,
    GPIO_AF9_TIM14
};

uint32_t TIM_CHANNEL_x_MAPPING[TIMER_CHNL_MAX] = {
    TIM_CHANNEL_1,      
    TIM_CHANNEL_2,      
    TIM_CHANNEL_3,      
    TIM_CHANNEL_4       
};

uint32_t TIMER_COUNTER_MODE_MAPPING[TIMER_COUNTER_MODE_MAX] = {
    TIM_COUNTERMODE_UP,
    TIM_COUNTERMODE_DOWN
};

uint32_t RCC_APBENR_TIMEN_MAPPING[TIMER_NUM_MAX] = {
    RCC_APB2ENR_TIM1EN,
    RCC_APB1ENR_TIM2EN,
    RCC_APB1ENR_TIM3EN,
    RCC_APB1ENR_TIM4EN,
    RCC_APB1ENR_TIM5EN,
    0,
    0,
    RCC_APB2ENR_TIM8EN,
    RCC_APB2ENR_TIM9EN,
    RCC_APB2ENR_TIM10EN,
    RCC_APB2ENR_TIM11EN,
    RCC_APB1ENR_TIM12EN,
    RCC_APB1ENR_TIM13EN,
    RCC_APB1ENR_TIM14EN
};

float APBx_CLOCK_MAPPING[TIMER_NUM_MAX] = {
    APB2_CLOCK,         
    APB1_CLOCK,         
    APB1_CLOCK,         
    APB1_CLOCK,         
    APB1_CLOCK,         
    APB1_CLOCK,         
    APB1_CLOCK,         
    APB1_CLOCK,         
    APB2_CLOCK,         
    APB2_CLOCK,         
    APB2_CLOCK,         
    APB1_CLOCK,         
    APB1_CLOCK,         
    APB1_CLOCK          
};

static tim_hw_info_t _tim_pwm_get_hw_info(timer_num_t timer_num, timer_chnl_t timer_chnl, timer_pins_pack_t timer_pins_pack)
{
    tim_hw_info_t hw_info;
    hw_info = TIM_HW_INFO_MAPPING[timer_num][timer_chnl][timer_pins_pack];

    return hw_info;
}

static tim_hw_info_t _tim_etr_get_hw_info(timer_num_t timer_num, timer_pins_pack_t timer_pins_pack)
{
    tim_hw_info_t hw_info;
    hw_info = TIM_ETR_HW_INFO_MAPPING[timer_num][timer_pins_pack];

    return hw_info;
}

stm_err_t pwm_config(pwm_cfg_t *config)
{
    /* Check input condition */
    TIMER_CHECK(config, PWM_INIT_ERR_STR, STM_ERR_INVALID_ARG);
    TIMER_CHECK(config->timer_num < TIMER_NUM_MAX, PWM_INIT_ERR_STR, STM_ERR_INVALID_ARG);
    TIMER_CHECK(config->timer_pins_pack < TIMER_PINS_PACK_MAX, PWM_INIT_ERR_STR, STM_ERR_INVALID_ARG);
    TIMER_CHECK(config->timer_chnl < TIMER_CHNL_MAX, PWM_INIT_ERR_STR, STM_ERR_INVALID_ARG);

    /* Get hardware information */
    tim_hw_info_t hw_info = _tim_pwm_get_hw_info(config->timer_num, config->timer_chnl, config->timer_pins_pack);

    /* Enable GPIO clock */
    uint32_t tmpreg = 0x00;
    SET_BIT(RCC->AHB1ENR, hw_info.rcc_ahbenr_gpioen);
    tmpreg = READ_BIT(RCC->AHB1ENR, hw_info.rcc_ahbenr_gpioen);
    UNUSED(tmpreg);

    /* Enable timer clock */
    tmpreg = 0x00;
    if ((config->timer_num == TIMER_NUM_1) || (config->timer_num == TIMER_NUM_8) || (config->timer_num == TIMER_NUM_9) || (config->timer_num == TIMER_NUM_10) || (config->timer_num == TIMER_NUM_11)) {
        SET_BIT(RCC->APB2ENR, RCC_APBENR_TIMEN_MAPPING[config->timer_num]);
        tmpreg = READ_BIT(RCC->APB2ENR, RCC_APBENR_TIMEN_MAPPING[config->timer_num]);
    }
    else {
        SET_BIT(RCC->APB1ENR, RCC_APBENR_TIMEN_MAPPING[config->timer_num]);
        tmpreg = READ_BIT(RCC->APB1ENR, RCC_APBENR_TIMEN_MAPPING[config->timer_num]);
    }
    UNUSED(tmpreg);

    /* Configure GPIO Pin */
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = hw_info.pin;
    GPIO_InitStruct.Mode = GPIO_MODE_DEFAULT;
    GPIO_InitStruct.Pull = GPIO_PULL_REG_DEFAULT;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_DEFAULT;
    GPIO_InitStruct.Alternate = TIM_ALTERNATE_FUNC_MAPPING[config->timer_num];
    HAL_GPIO_Init(hw_info.port, &GPIO_InitStruct);

    /* Configure Timer */
    timer_handle[config->timer_num].Instance                 = TIM_MAPPING[config->timer_num];
    timer_handle[config->timer_num].Init.Prescaler           = 0;
    timer_handle[config->timer_num].Init.CounterMode         = PWM_COUNTERMODE_DEFAULT;
    timer_handle[config->timer_num].Init.Period              = 0;
    timer_handle[config->timer_num].Init.ClockDivision       = PWM_TIM_CLOCK_DIV_DEFAULT;
    timer_handle[config->timer_num].Init.AutoReloadPreload   = TIM_AUTORELOAD_PRELOAD_DISABLE;
    TIMER_CHECK(!HAL_TIM_Base_Init(&timer_handle[config->timer_num]), PWM_INIT_ERR_STR, STM_FAIL);

    /* Configure PWM */
    TIMER_CHECK(!HAL_TIM_PWM_Init(&timer_handle[config->timer_num]), PWM_INIT_ERR_STR, STM_FAIL);

    /* Configure Timer clock source */
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    TIMER_CHECK(!HAL_TIM_ConfigClockSource(&timer_handle[config->timer_num], &sClockSourceConfig), PWM_INIT_ERR_STR, STM_FAIL);

    /* Configure Timer in master mode */
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    TIMER_CHECK(!HAL_TIMEx_MasterConfigSynchronization(&timer_handle[config->timer_num], &sMasterConfig), PWM_INIT_ERR_STR, STM_FAIL);

    /* Configure Timer PWM channel */
    TIM_OC_InitTypeDef sConfigOC = {0};
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    TIMER_CHECK(!HAL_TIM_PWM_ConfigChannel(&timer_handle[config->timer_num], &sConfigOC, TIM_CHANNEL_x_MAPPING[config->timer_chnl]), PWM_INIT_ERR_STR, STM_FAIL);

    HAL_TIM_Base_Start(&timer_handle[config->timer_num]);
    return STM_OK;
}

stm_err_t pwm_start(timer_num_t timer_num, timer_chnl_t timer_chnl)
{
    TIMER_CHECK(timer_num < TIMER_NUM_MAX, PWM_START_ERR_STR, STM_ERR_INVALID_ARG);
    TIMER_CHECK(timer_chnl < TIMER_CHNL_MAX, PWM_START_ERR_STR, STM_ERR_INVALID_ARG);

    HAL_TIM_PWM_Start(&timer_handle[timer_num], TIM_CHANNEL_x_MAPPING[timer_chnl]);
    return STM_OK;
}

stm_err_t pwm_stop(timer_num_t timer_num, timer_chnl_t timer_chnl)
{
    TIMER_CHECK(timer_num < TIMER_NUM_MAX, PWM_STOP_ERR_STR, STM_ERR_INVALID_ARG);
    TIMER_CHECK(timer_chnl < TIMER_CHNL_MAX, PWM_STOP_ERR_STR, STM_ERR_INVALID_ARG);

    HAL_TIM_PWM_Stop(&timer_handle[timer_num], TIM_CHANNEL_x_MAPPING[timer_chnl]);
    return STM_OK;
}

stm_err_t pwm_set_frequency(timer_num_t timer_num, timer_chnl_t timer_chnl, uint32_t freq_hz)
{
    TIMER_CHECK(timer_num < TIMER_NUM_MAX, PWM_SET_FREQ_ERR_STR, STM_ERR_INVALID_ARG);
    TIMER_CHECK(timer_chnl < TIMER_CHNL_MAX, PWM_SET_FREQ_ERR_STR, STM_ERR_INVALID_ARG);

    if (freq_hz == 0)
    {
        __HAL_TIM_SET_AUTORELOAD(&timer_handle[timer_num], 0);
        __HAL_TIM_SET_PRESCALER(&timer_handle[timer_num], 0);
        __HAL_TIM_SET_COMPARE(&timer_handle[timer_num], TIM_CHANNEL_x_MAPPING[timer_chnl], 0);

        return STM_OK;
    }

    uint16_t cur_period = __HAL_TIM_GET_AUTORELOAD(&timer_handle[timer_num]);
    uint32_t cur_compare  = __HAL_TIM_GET_COMPARE(&timer_handle[timer_num], TIM_CHANNEL_x_MAPPING[timer_chnl]);
    uint8_t cur_duty = (uint8_t)(cur_compare * 100 / cur_period);

    /* Calculate Timer PWM parameters. When change timer period you also
     * need to update timer compare value to keep duty cycle stable */
    uint32_t apb_freq = APBx_CLOCK_MAPPING[timer_num] * HAL_RCC_GetHCLKFreq();
    uint32_t conduct = (uint32_t) (apb_freq / freq_hz);
    uint16_t timer_prescaler = conduct / TIMER_MAX_RELOAD + 1;
    uint16_t timer_period = (uint16_t)(conduct / (timer_prescaler + 1)) - 1;
    uint32_t timer_compare_value = cur_duty * timer_period / 100;

    /* Configure Timer PWM parameters */
    __HAL_TIM_SET_AUTORELOAD(&timer_handle[timer_num], timer_period);
    __HAL_TIM_SET_PRESCALER(&timer_handle[timer_num], timer_prescaler);
    __HAL_TIM_SET_COMPARE(&timer_handle[timer_num], TIM_CHANNEL_x_MAPPING[timer_chnl], timer_compare_value);
    return STM_OK;
}

stm_err_t pwm_set_params(timer_num_t timer_num, timer_chnl_t timer_chnl, uint32_t freq_hz, uint8_t duty_percent)
{
    TIMER_CHECK(timer_num < TIMER_NUM_MAX, PWM_SET_PARAMS_ERR_STR, STM_ERR_INVALID_ARG);
    TIMER_CHECK(timer_chnl < TIMER_CHNL_MAX, PWM_SET_PARAMS_ERR_STR, STM_ERR_INVALID_ARG);

    if (freq_hz == 0)
    {
        __HAL_TIM_SET_AUTORELOAD(&timer_handle[timer_num], 0);
        __HAL_TIM_SET_PRESCALER(&timer_handle[timer_num], 0);
        __HAL_TIM_SET_COMPARE(&timer_handle[timer_num], TIM_CHANNEL_x_MAPPING[timer_chnl], 0);

        return STM_OK;
    }

    /* Calculate Timer PWM parameters. When change timer period you also
     * need to update timer compare value to keep duty cycle stable */
    uint32_t apb_freq = APBx_CLOCK_MAPPING[timer_num] * HAL_RCC_GetHCLKFreq();
    uint32_t conduct = (uint32_t) (apb_freq / freq_hz);
    uint16_t timer_prescaler = conduct / TIMER_MAX_RELOAD + 1;
    uint16_t timer_period = (uint16_t)(conduct / (timer_prescaler + 1)) - 1;
    uint32_t timer_compare_value = duty_percent * timer_period / 100;

    /* Configure Timer PWM parameters */
    __HAL_TIM_SET_AUTORELOAD(&timer_handle[timer_num], timer_period);
    __HAL_TIM_SET_PRESCALER(&timer_handle[timer_num], timer_prescaler);
    __HAL_TIM_SET_COMPARE(&timer_handle[timer_num], TIM_CHANNEL_x_MAPPING[timer_chnl], timer_compare_value);
    return STM_OK;
}

stm_err_t pwm_set_duty(timer_num_t timer_num, timer_chnl_t timer_chnl, uint8_t duty_percent)
{
    TIMER_CHECK(timer_num < TIMER_NUM_MAX, PWM_SET_DUTYCYCLE_ERR_STR, STM_ERR_INVALID_ARG);
    TIMER_CHECK(timer_chnl < TIMER_CHNL_MAX, PWM_SET_DUTYCYCLE_ERR_STR, STM_ERR_INVALID_ARG);

    /* Calculate PWM compare value */
    uint32_t compare_value;
    compare_value = duty_percent * (timer_handle[timer_num].Instance->ARR) / 100;

    /* Configure PWM compare value */
    __HAL_TIM_SET_COMPARE(&timer_handle[timer_num], TIM_CHANNEL_x_MAPPING[timer_chnl], compare_value);
    return STM_OK;
}

stm_err_t etr_config(etr_cfg_t *config)
{
    /* Check input condition */
    TIMER_CHECK(config, ETR_INIT_ERR_STR, STM_ERR_INVALID_ARG);
    TIMER_CHECK(config->timer_num < TIMER_NUM_MAX, ETR_INIT_ERR_STR, STM_ERR_INVALID_ARG);
    TIMER_CHECK(config->timer_pins_pack < TIMER_PINS_PACK_MAX, ETR_INIT_ERR_STR, STM_ERR_INVALID_ARG);
    TIMER_CHECK(config->counter_mode < TIMER_COUNTER_MODE_MAX, ETR_INIT_ERR_STR, STM_ERR_INVALID_ARG);

    /* Get hardware information */
    tim_hw_info_t hw_info = _tim_etr_get_hw_info(config->timer_num, config->timer_pins_pack);

    /* Enable GPIO clock */
    uint32_t tmpreg = 0x00;
    SET_BIT(RCC->AHB1ENR, hw_info.rcc_ahbenr_gpioen);
    tmpreg = READ_BIT(RCC->AHB1ENR, hw_info.rcc_ahbenr_gpioen);
    UNUSED(tmpreg);

    /* Enable timer clock */
    tmpreg = 0x00;
    if ((config->timer_num == TIMER_NUM_1) || (config->timer_num == TIMER_NUM_8) || (config->timer_num == TIMER_NUM_9) || (config->timer_num == TIMER_NUM_10) || (config->timer_num == TIMER_NUM_11)) {
        SET_BIT(RCC->APB2ENR, RCC_APBENR_TIMEN_MAPPING[config->timer_num]);
        tmpreg = READ_BIT(RCC->APB2ENR, RCC_APBENR_TIMEN_MAPPING[config->timer_num]);
    }
    else {
        SET_BIT(RCC->APB1ENR, RCC_APBENR_TIMEN_MAPPING[config->timer_num]);
        tmpreg = READ_BIT(RCC->APB1ENR, RCC_APBENR_TIMEN_MAPPING[config->timer_num]);
    }
    UNUSED(tmpreg);

    /* Configure GPIO pin */
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = hw_info.pin;
    GPIO_InitStruct.Mode = GPIO_MODE_DEFAULT;
    GPIO_InitStruct.Pull = GPIO_PULL_REG_DEFAULT;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_DEFAULT;
    GPIO_InitStruct.Alternate = TIM_ALTERNATE_FUNC_MAPPING[config->timer_num];
    HAL_GPIO_Init(hw_info.port, &GPIO_InitStruct);

    /* Configure Timer */
    timer_handle[config->timer_num].Instance                 = TIM_MAPPING[config->timer_num];
    timer_handle[config->timer_num].Init.Prescaler           = EXT_CNT_PRES_DEFAULT;
    timer_handle[config->timer_num].Init.CounterMode         = TIMER_COUNTER_MODE_MAPPING[config->counter_mode];
    timer_handle[config->timer_num].Init.Period              = config->max_reload;
    timer_handle[config->timer_num].Init.ClockDivision       = PWM_TIM_CLOCK_DIV_DEFAULT;
    timer_handle[config->timer_num].Init.AutoReloadPreload   = TIM_AUTORELOAD_PRELOAD_DISABLE;
    TIMER_CHECK(!HAL_TIM_Base_Init(&timer_handle[config->timer_num]), ETR_INIT_ERR_STR, STM_FAIL);

    /* Configure Timer clock source */
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_ETRMODE2;
    sClockSourceConfig.ClockPolarity = TIM_CLOCKPOLARITY_NONINVERTED;
    sClockSourceConfig.ClockPrescaler = TIM_CLOCKPRESCALER_DIV1;
    sClockSourceConfig.ClockFilter = 0;
    TIMER_CHECK(!HAL_TIM_ConfigClockSource(&timer_handle[config->timer_num], &sClockSourceConfig), ETR_INIT_ERR_STR, STM_FAIL);

    /* Configure Timer in master mode */
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    TIMER_CHECK(!HAL_TIMEx_MasterConfigSynchronization(&timer_handle[config->timer_num], &sMasterConfig), ETR_INIT_ERR_STR, STM_FAIL);

    return STM_OK;
}

stm_err_t etr_start(timer_num_t timer_num)
{
    TIMER_CHECK(timer_num < TIMER_NUM_MAX, ETR_START_ERR_STR, STM_ERR_INVALID_ARG);

    /* Start timer base */
    HAL_TIM_Base_Start(&timer_handle[timer_num]);
    return STM_OK;
}

stm_err_t etr_stop(timer_num_t timer_num)
{
    TIMER_CHECK(timer_num < TIMER_NUM_MAX, ETR_STOP_ERR_STR, STM_ERR_INVALID_ARG);

    /* Stop time base */
    HAL_TIM_Base_Stop(&timer_handle[timer_num]);
    return STM_OK;
}

stm_err_t etr_get_value(timer_num_t timer_num, uint32_t *value)
{
    TIMER_CHECK(timer_num < TIMER_NUM_MAX, ETR_GET_VALUE_ERR_STR, STM_ERR_INVALID_ARG);

    /* Get counter value */
    *value = __HAL_TIM_GET_COUNTER(&timer_handle[timer_num]);
    return STM_OK;
}

stm_err_t etr_set_value(timer_num_t timer_num, uint32_t value)
{
    TIMER_CHECK(timer_num < TIMER_NUM_MAX, ETR_SET_VALUE_ERR_STR, STM_ERR_INVALID_ARG);

    /* Set counter value */
    __HAL_TIM_SET_COUNTER(&timer_handle[timer_num], value);
    return STM_OK;
}

stm_err_t etr_set_mode(timer_num_t timer_num, timer_counter_mode_t counter_mode)
{
    TIMER_CHECK(timer_num < TIMER_NUM_MAX, ETR_SET_MODE_ERR_STR, STM_ERR_INVALID_ARG);
    TIMER_CHECK(counter_mode < TIMER_COUNTER_MODE_MAX, ETR_SET_MODE_ERR_STR, STM_ERR_INVALID_ARG);

    /* Reconfigure timer init parameters */
    timer_handle[timer_num].Instance                 = TIM_MAPPING[timer_num];
    timer_handle[timer_num].Init.Prescaler           = EXT_CNT_PRES_DEFAULT;
    timer_handle[timer_num].Init.CounterMode         = TIMER_COUNTER_MODE_MAPPING[counter_mode];
    timer_handle[timer_num].Init.Period              = __HAL_TIM_GET_AUTORELOAD(&timer_handle[timer_num]);
    timer_handle[timer_num].Init.ClockDivision       = PWM_TIM_CLOCK_DIV_DEFAULT;
    timer_handle[timer_num].Init.AutoReloadPreload   = TIM_AUTORELOAD_PRELOAD_DISABLE;

    /* Keep last counter value */
    uint32_t last_counter_val = __HAL_TIM_GET_COUNTER(&timer_handle[timer_num]);

    /* Set timer counter mode */
    TIMER_CHECK(!HAL_TIM_Base_Init(&timer_handle[timer_num]), ETR_SET_MODE_ERR_STR, STM_FAIL);

    /* Set timer last counter value */
    __HAL_TIM_SET_COUNTER(&timer_handle[timer_num], last_counter_val);

    return STM_OK;
}







