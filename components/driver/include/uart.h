#ifndef _UART_H_
#define _UART_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stdlib.h"
#include "stdint.h"

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_uart.h"
#include "stm32f4xx_hal_dma.h"


/* Table below shows all possible pins for each uart
 *
 *  U(S)ARTx | Pins pack 1 | Pins pack 2 | Pins pack 3 |  APB  |
 *           |  TX    RX   |  TX    RX   |  TX    RX   |       |
 *--------------------------------------------------------------
 *  USART1   |  PA9   PA10 |  PB6   PB7  |  -     -    |   2   |
 *  USART2   |  PA2   PA3  |  PD5   PD6  |  -     -    |   1   |
 *  USART3   |  PB10  PB11 |  PC10  PC11 |  PD8   PD9  |   1   |
 *  USART4   |  PA0   PA1  |  PC10  PC11 |  -     -    |   1   |
 *  USART5   |  PC12  PD2  |  -     -    |  -     -    |   1   |
 *  USART6   |  PC6   PC7  |  PG14  PG9  |  -     -    |   2   |
 *  USART7   |  PE8   PE7  |  PF7   PF6  |  -     -    |   1   |
 *  USART8   |  PE1   PE0  |  -     -    |  -     -    |   1   |
 */

/*
 * UART Status Typedef.
 */
typedef enum {
    UART_ERROR = -1,    /*!< UART error */
    UART_READY,         /*!< UART ready*/
    UART_READING,       /*!< UART reading */
    UART_WRITING        /*!< UART writing */
} uart_status_t;

/*
 * UART Num Select Typedef.
 */
typedef enum {
    UART_NUM_1 = 0,     /*!< UART Num 1 selected */
    UART_NUM_2,         /*!< UART Num 2 selected */
    UART_NUM_3,         /*!< UART Num 3 selected */
    UART_NUM_4,         /*!< UART Num 4 selected */
    UART_NUM_5,         /*!< UART Num 5 selected */
    UART_NUM_6,         /*!< UART Num 6 selected */
    UART_NUM_MAX
} uart_num_t;

/*
 * UART Pins Pack Select Typedef.
 */
typedef enum {
    UART_PINS_PACK_1 = 0,   /*!< UART Pins Pack 1 selected */
    UART_PINS_PACK_2,       /*!< UART Pins Pack 2 selected */
    UART_PINS_PACK_3,       /*!< UART Pins Pack 3 selected */
    UART_PINS_PACK_MAX
} uart_pins_pack_t;

/*
 * UART Configuration Typedef.
 */
typedef struct {
    uart_num_t         uart_num;            /*!< UART Num */
    uart_pins_pack_t   uart_pins_pack;      /*!< UART Pins Pack */
    uint32_t           baudrate;            /*!< UART Baudrate */
} uart_config_t;

/*
 * @brief   Initialize UART.
 * @param   config Struct pointer.
 * @return
 *      - UART handle structure: Success.
 *      - 0: Fail.
 */
int uart_init(uart_config_t *config);

/*
 * @brief   UART write bytes.
 * @param   handle UART handle structure.
 * @param   data Data transmit pointer.
 * @param   length Data length.
 * @param   timeout_ms Time out in microsecond.
 * @return
 *      - 0: Success.
 *      - (-1): Fail.
 */
int uart_write_bytes(uart_num_t uart_num, uint8_t *data, uint16_t length, uint32_t timeout_ms);

/*
 * @brief   UART read bytes.
 * @param   handle UART handle structure.
 * @param   buf Data receive pointer.
 * @param   length Data length.
 * @param   timeout_ms Time out in microsecond.
 * @return
 *      - 0: Success.
 *      - (-1): Fail.
 */
int uart_read_bytes(uart_num_t uart_num, uint8_t *buf, uint16_t length, uint32_t timeout_ms);


#ifdef __cplusplus
}
#endif

#endif /* _UART_H_ */
