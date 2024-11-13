/*
 * uart.h
 *
 *  Created on: Nov 10, 2024
 *      Author: HOME
 */

#ifndef INC_ESP32_UART_H_
#define INC_ESP32_UART_H_

#include "main.h"
#include "string.h"
#include "stm32f0xx_hal.h"

extern UART_HandleTypeDef huart1;

void UARTsend(char* );

#endif /* INC_ESP32_UART_H_ */
