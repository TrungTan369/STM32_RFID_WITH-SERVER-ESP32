/*
 * RGB.C
 *
 *  Created on: Nov 9, 2024
 *      Author: HOME
 */


#include "RGB.h"

void rgb(int red, int green, int blue){
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 100 - blue);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 110 - green);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 120 - red);
}
