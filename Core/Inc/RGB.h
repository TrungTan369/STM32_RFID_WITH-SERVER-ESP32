/*
 * RBG.H
 *
 *  Created on: Nov 9, 2024
 *      Author: HOME
 */

#ifndef INC_RGB_H_
#define INC_RGB_H_

#include "main.h"
#define RED 1
#define GREEN 2
#define BLUE 3
#define YELLOW 4
#define PURPLE 5
#define WHITE 6
TIM_HandleTypeDef htim3;
DMA_HandleTypeDef hdma_tim3_ch4_up;

extern int blue;
extern int green;
extern int red;
extern int status;
extern int increasing;
extern int decreasing;

void rgb(int, int, int);
void all_led();
#endif /* INC_RGB_H_ */
