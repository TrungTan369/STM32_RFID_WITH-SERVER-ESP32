/*
 * global.h
 *
 *  Created on: Nov 16, 2024
 *      Author: HOME
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"
#include <stdlib.h>
#include "string.h"
#include "timer.h"
#include "button.h"
#include "RGB.h"
#include "i2c-lcd.h"
#include "RFID_SPI.h"
#include "uart_ESP.h"

extern UART_HandleTypeDef huart1;
extern const uint8_t master[4];
extern uint8_t ** data;


uint8_t check_Card(uint8_t * );
uint8_t delete_Card(uint8_t *);
int8_t search_Card(uint8_t *);
uint8_t num_Card();
void add_Card(uint8_t *);
#endif /* INC_GLOBAL_H_ */
