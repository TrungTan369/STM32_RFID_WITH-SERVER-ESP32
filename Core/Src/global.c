/*
 * global.c
 *
 *  Created on: Nov 16, 2024
 *      Author: HOME
 */

#include "global.h"

const uint8_t master[4] = {243, 25, 142, 19};
uint8_t ** data = NULL;
uint8_t numCard = 0;



uint8_t check_Card(uint8_t * readCard){
	if(readCard[0] == master[0] && readCard[1] == master[1] && readCard[2] == master[2] && readCard[3] == master[3]){
		return 2; // MASTERCARD
	}
	if (search_Card(readCard) >= 0){
		return 1; // NORMAL CARD
	}
	return 0; // CARD not exist
}

void add_Card(uint8_t * readCard){
	data = (uint8_t **)realloc(data, (numCard + 1) * sizeof(uint8_t *));
	data[numCard] = (uint8_t *)malloc(4 * sizeof(int));
	data[numCard][0] = readCard[0];
	data[numCard][1] = readCard[1];
	data[numCard][2] = readCard[2];
	data[numCard][3] = readCard[3];
	numCard++;
}

int8_t search_Card(uint8_t *readCard){
	for(int i = 0; i < numCard; i++){
		if(data[i][0] == readCard[0] && data[i][1] == readCard[1] && data[i][2] == readCard[2] && data[i][3] == readCard[3] ){
			return i;
		}
	}
	return -1; // can't searched
}
void delete_Card(uint8_t * readCard){
	if(numCard <= 0)
		return;
	int index = search_Card(readCard);
	if(index == -1){
		return;
	}
	free(data[index]);
	for (int i = index; i < numCard - 1; i++) {
	    data[i] = data[i + 1];
	}
	data = (uint8_t **)realloc(data, numCard * sizeof(uint8_t *));
	numCard--;

}
