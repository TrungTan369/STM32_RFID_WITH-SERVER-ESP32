/*
 * button.c
 *
 *  Created on: Nov 16, 2024
 *      Author: HOME
 */
#include "button.h"

int count  = 0;
int buttonFlag[2] = {0,0};
void getKeyinput(){
	if (count > 0) count--;
	//-----PROCESS BUTTON 1------------
	if((count == 0) && (HAL_GPIO_ReadPin(BUTTON1_GPIO_Port, BUTTON1_Pin) == 0)){
		buttonFlag[0] = 1;
		count = 10;
	}
	// ----PROCESS BUTTON 2-----------
	if((count == 0) && (HAL_GPIO_ReadPin(BUTTON2_GPIO_Port, BUTTON2_Pin) == 0)){
		buttonFlag[1] = 1;
		count = 10;
	}
}
int isButtonPress(int i){
	if(buttonFlag[i] == 1){
		buttonFlag[i] = 0;
		return 1;
	}
	return 0;
}


