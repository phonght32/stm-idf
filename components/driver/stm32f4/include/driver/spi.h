// MIT License

// Copyright (c) 2020 phonght32

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

#ifndef _DRIVER_SPI_H_
#define _DRIVER_SPI_H_

/* Table below shows all possible pins for each SPI.
 *
 *  SPIx   |    Pins pack 1    |    Pins pack 2    |    Pins pack 3    |  APB  |
 *         |  MOSI  MISO  SCK  |  MOSI  MISO  SCK  |  MOSI  MISO  SCK  |       |
 *------------------------------------------------------------------------------
 *  SPI1   |  PA7   PA10  PA5  |  PB5   PB4   PB3  |  -     -     -    |   2   |
 *  SPI2   |  PC3   PA3   PB10 |  PB15  PB14  PB13 |  PI3   PI2   PI0  |   1   |
 *  SPI3   |  PB5   PB11  PB3  |  PC12  PC11  PC10 |  -     -     -    |   1   |
 *  SPI4   |  PE6   PA1   PE2  |  PE14  PE13  PE12 |  -     -     -    |   2   |
 *  SPI5   |  PF9   PD2   PF7  |  PF11  PH7   PH6  |  -     -     -    |   2   |
 *  SPI6   |  PG14  PC7   PG13 |  -     -     -    |  -     -     -    |   2   |
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "stm_err.h"

typedef enum {
	SPI_NUM_1 = 0,								/*!< SPI num 1 */
	SPI_NUM_2,									/*!< SPI num 2 */
	SPI_NUM_3,									/*!< SPI num 3 */
	SPI_NUM_4,									/*!< SPI num 4 */
	SPI_NUM_5,									/*!< SPI num 5 */ 
	SPI_NUM_6,									/*!< SPI num 6 */ 
	SPI_NUM_MAX
} spi_num_t;

typedef enum {
	SPI_PINS_PACK_1 = 0,						/*!< SPI pins pack 1 */ 
	SPI_PINS_PACK_2,							/*!< SPI pins pack 2 */ 
	SPI_PINS_PACK_3,							/*!< SPI pins pack 3 */ 
	SPI_PINS_PACK_MAX
} spi_pins_pack_t;

typedef struct {
	spi_num_t 			spi_num;				/*!< SPI num */ 
	spi_pins_pack_t 	spi_pins_pack;			/*!< SPI pins pack*/ 
} spi_cfg_t;

/*
 * @brief   Initialize SPI.
 * @param   config Struct pointer.
 * @return
 *      - STM_OK:       Success.
 *      - Others:       Fail.
 */
stm_err_t spi_config(spi_cfg_t *config);

/*
 * @brief   SPI write bytes.
 * @param   spi_num SPI num.
 * @param   data Data transmit pointer.
 * @param   length Data length.
 * @param   timeout_ms Time out in microsecond.
 * @return
 *      - STM_OK:       Success.
 *      - Others:       Fail.
 */
stm_err_t spi_write_bytes(spi_num_t spi_num, uint8_t *data, uint16_t length, uint32_t timeout_ms);

/*
 * @brief   SPI.
 * @param   spi_num SPI num.
 * @param   buf Data receive pointer.
 * @param   length Data length.
 * @param   timeout_ms Time out in microsecond.
 * @return
 *      - STM_OK:       Success.
 *      - Others:       Fail.
 */
stm_err_t spi_read_bytes(spi_num_t spi_num, uint8_t *buf, uint16_t length, uint32_t timeout_ms);

#ifdef __cplusplus
}
#endif

#endif /* _DRIVER_SPI_H_ */