/*
 * timer.c
 *
 *  Created on: Dec 5, 2024
 *      Author: HOME
 */

#include "timer.h"


int counter[3] = {0, 0, 0};
int timer_flag[3] = {0, 0, 1};// FLAG[2] = 1 TO READY READ BUTTON
									// FLAG[4] = 1 TO READY READ CARD
void setTimer(int timer, int duration){
	counter[timer] = duration / 10;
	timer_flag[timer] = 0;
}
void timer_run(){
	for(int i = 0; i < 3; i++){
		if(counter[i] > 0){
			counter[i]--;
			if(counter[i] <= 0)
				timer_flag[i] = 1;
		}
	}
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * htim){ // 10ms each time run
	getKeyinput();
	timer_run();
}
