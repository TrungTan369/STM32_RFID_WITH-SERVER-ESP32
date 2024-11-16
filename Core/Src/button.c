/*
 * button.c
 *
 *  Created on: Nov 16, 2024
 *      Author: HOME
 */
#include "button.h"

int buttonFlag[2] = {0,0};
void getKeyinput(){
	//-----PROCESS BUTTON 1------------
	if((timer_flag[2] == 1) && (HAL_GPIO_ReadPin(BUTTON1_GPIO_Port, BUTTON1_Pin) == 0)){

		buttonFlag[0] = 1;
		setTimer(2, 300);
	}
	// ----PROCESS BUTTON 2-----------
	if((timer_flag[2] == 1) && (HAL_GPIO_ReadPin(BUTTON2_GPIO_Port, BUTTON2_Pin) == 0)){

		buttonFlag[1] = 1;
		setTimer(2, 300);
	}
}
int isButtonPress(int i){
	if(buttonFlag[i] == 1){
		buttonFlag[i] = 0;
		return 1;
	}
	return 0;
}


