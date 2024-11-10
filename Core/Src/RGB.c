/*
 * RGB.c
 *
 *  Created on: Nov 10, 2024
 *      Author: xjkpr
 */
#include "RGB.h"

void rgb(int red, int green, int blue){
__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 100-red);
__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 100-green);
__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 100-blue);
}
