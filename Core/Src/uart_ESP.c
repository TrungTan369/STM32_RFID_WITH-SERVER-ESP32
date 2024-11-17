/*
 * uart_ESP.c
 *
 *  Created on: Nov 17, 2024
 *      Author: HOME
 */
#include "uart_ESP.h"

void sendDataToESP32(char *data) {
    HAL_UART_Transmit(&huart1, (uint8_t *)data, strlen(data), HAL_MAX_DELAY); // Gửi dữ liệu qua UART
}
