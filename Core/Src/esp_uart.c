/*
 * uart.c
 *
 *  Created on: Nov 10, 2024
 *      Author: HOME
 */


#include "esp_uart.h"

UART_HandleTypeDef huart1;

void UARTsend(char* data) {
  HAL_UART_Transmit(&huart1, (uint8_t*)data, strlen(data), HAL_MAX_DELAY); // Gửi dữ liệu tới ESP32
}
