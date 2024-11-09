/*
 * timer.h
 *
 *  Created on: Nov 9, 2024
 *      Author: HOME
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "main.h"

extern int counter[3];
extern int timer_flag[3];

void setTimer(int, int);
void timer_run();
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *);

#endif /* INC_TIMER_H_ */
