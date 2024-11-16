/*
 * global.c
 *
 *  Created on: Nov 16, 2024
 *      Author: HOME
 */

#include "global.h"

const uint8_t master[4] = {227, 182, 182, 015};

uint8_t numCard = 0;
uint8_t *data[4];

uint8_t Check_master(const uint8_t* master, uint8_t* readCard){
	if(readCard[0] == master[0] && readCard[1] == master[1] && readCard[2] == master[2] && readCard[3] == master[3]){
		HAL_GPIO_WritePin(LED_DEBUG_GPIO_Port, LED_DEBUG_Pin, 1);
		return 1;
	}
	return 0;
}
void readCard(){

}
void addCard(uint8_t readCard[]){
	data[numCard] = (uint8_t*)malloc(4 * sizeof(uint8_t));
	data[numCard][0] = readCard[0];
	data[numCard][1] = readCard[1];
	data[numCard][2] = readCard[2];
	data[numCard][3] = readCard[3];
	numCard++;
}
uint8_t delCard(uint8_t readCard){
	if(numCard <= 0){
		return 0;
	}
	free(data[numCard]);
	numCard--;
	return 1;
}
