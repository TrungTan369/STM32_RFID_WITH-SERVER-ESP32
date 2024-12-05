/*
 * RGB.C
 *
 *  Created on: Nov 9, 2024
 *      Author: HOME
 */


#include "RGB.h"

int blue = 0;
int green = 0;
int red = 0;
int status_led =1;
int increasing = 1;
int decreasing = 0;

void rgb(int red, int green, int blue){
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 100 - blue);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 110 - green);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 120 - red);
}
void RGB_RED(){
	rgb(100, 0, 0); // RED
}
void RGB_PURPLE(){
	rgb(100, 0, 100);
}
void RGB_GREEN(){
	rgb(0, 100, 0);
}
void all_led(){
	switch(status_led){
	  case RED:
		  if(increasing){
			  red++;
		  }
		  if(red>=100){
			  increasing--;
			  decreasing++;
		  }
		  if(decreasing){
			  red--;
		  }
		  if(red<0) {
			  status_led++;
			  red=0;
			  increasing++;
			  decreasing--;
		  }
		  break;
	  case GREEN:
		  if(increasing){
		  	  green++;
		 	  }
		  if(green>=100){
			  increasing--;
			  decreasing++;
		  }
		  if(decreasing){
			  green--;
		  }
		  if(green<0) {
			  status_led++;
			  green=0;
			  increasing++;
			  decreasing--;
		  }
		  		  break;
	  case BLUE:
		  if(increasing){
		  	  blue++;
		 	  }
		  if(blue>=100){
			  increasing--;
			  decreasing++;
		  }
		  if(decreasing){
			  blue--;
		  }
		  if(blue<0) {
			  status_led++;
			  blue=0;
			  increasing++;
			  decreasing--;
		  }
		  break;
	  case YELLOW:
		  if(increasing){
			  red++;
			  green=red*1.25;

		 	  }
		  if(green>=100){
			  increasing--;
			  decreasing++;
		  }
		  if(decreasing){
			  red--;
			  green=red*1.25;

		  }
		  if(red<0) {
			  status_led++;
			  green=0;
			  red=0;
			  increasing++;
			  decreasing--;
		  }
		  break;
	  case PURPLE:
		  if(increasing){
			  red++;
			  blue=red*1.25;
		 	  }
		  if(blue>=100){
			  increasing--;
			  decreasing++;
		  }
		  if(decreasing){
			  red--;
			  blue=red*1.25;
		  }
		  if(blue<0) {
			  status_led++;
			  blue=0;
			  red=0;
			  increasing++;
			  decreasing--;
		  }
		  break;
	  case WHITE:
		  if(increasing){
			  red++;
			  blue=red*1.4;
		  	  green=red*1.5;
		 	  }
		  if(blue>=100){
			  increasing--;
			  decreasing++;
		  }
		  if(decreasing){
			  red--;
			  blue=red*1.4;
			  green=red*1.5;
		  }
		  if(blue<0) {
			  status_led = 1;
			  blue=0;
			  red=0;
			  green=0;
			  increasing++;
			  decreasing--;
		  }
		  break;
	  default:
		  break;
	  }
	 rgb(red,green,blue);
	 HAL_Delay(50);
}
