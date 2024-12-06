/*
 * fsm_master.c
 *
 *  Created on: Nov 16, 2024
 *      Author: HOME
 */

#include "fsm.h"

int status = INIT;
uint8_t * data_uart ;
void fsm(uint8_t * readCard, uint8_t status_read){
	switch (status) {
		case INIT:
			lcd_clear_display();
			lcd_goto_XY(1, 0);
			lcd_send_string("PUT ON YOUR CARD");
			lcd_goto_XY(0, 0);
			lcd_send_string("TO CONTROL LED");
			status = WAITCARD;
		case WAITCARD:
			if( status_read == MI_OK && cardProcessed == 0 ){
				if(check_Card(readCard) == 2){ // MASTER CARD
					sendDataToESP32("MASTER LOGGIN\r\n");
					setTimer(0, 3000);
					rgb(60, 60, 60); // PINK
					lcd_clear_display();
					lcd_goto_XY(1, 0);
					lcd_send_string("1. ADD - DELETE");
					lcd_goto_XY(0, 0);
					lcd_send_string("2. OTHER");
					status = MASTER_MENU_1;
					break;
				}
				if( check_Card(readCard) == 1){ // NORMAL CARD
					sendDataToESP32("TURN LED\r\n");
					setTimer(0, 3000);
					rgb(0, 100, 0);
					break;
				}
				if (check_Card(readCard) == 0) {
					lcd_clear_display();
					lcd_goto_XY(1, 0);
					lcd_send_string("CARD NOT EXIST");
					HAL_Delay(1000);
					status = INIT;
				}
			}
			break;
		case MASTER_MENU_1:
				if(isButtonPress(0) == 1){
					lcd_clear_display();
					lcd_goto_XY(1, 0);
					lcd_send_string("1. ADD CARD");
					lcd_goto_XY(0, 0);
					lcd_send_string("2. DELETE CARD");
					status = MASTER_MENU_2;
				}
				if(isButtonPress(1) == 1){
					lcd_clear_display();
					lcd_goto_XY(1, 0);
					lcd_send_string("1. CARD COUNT");
					lcd_goto_XY(0, 0);
					lcd_send_string("2. EXIT");
					status = MASTER_MENU_3;
				}
				break;
		case MASTER_MENU_2:
				if(isButtonPress(0) == 1){
					lcd_clear_display();
					lcd_goto_XY(1, 0);
					lcd_send_string("SET CLOSER CARD");
					status = MASTER_ADDCARD;
				}
				if(isButtonPress(1) == 1){
					lcd_clear_display();
					lcd_goto_XY(1, 0);
					lcd_send_string("SET CLOSER CARD");
					status = MASTER_DELCARD;
				}
				break;
			case MASTER_MENU_3:
				if(isButtonPress(0) == 1){
					lcd_clear_display();
					lcd_goto_XY(1, 0);
					lcd_send_string("NUMBER OF CARDS");
					lcd_goto_XY(0, 0);
					lcd_send_int(numCard);
					HAL_Delay(1000);
					status = INIT;
				}
				if(isButtonPress(1) == 1){
					status = INIT;
				}
				break;
		case MASTER_ADDCARD:
			if(status_read == MI_OK){
				if(check_Card(readCard) == 1){
					lcd_goto_XY(0, 0);
					lcd_send_string("CARD EXISTED");
				}
				else {
					add_Card(readCard);
					lcd_goto_XY(0, 0);
					lcd_send_string("ADDED CARD");
					sendDataToESP32("ADDED CARD\r\n");
					setTimer(3, 2000);
				}
				HAL_Delay(1000);
				status = INIT;
			}
			break;
		case MASTER_DELCARD:
			if(num_Card() == 0){
				lcd_goto_XY(0, 0);
				lcd_send_string(" LIST CARD EMPTY");
				HAL_Delay(1000);
				status = INIT;
				break;
			}
			if(status_read == MI_OK){
				if( delete_Card(readCard) == 0){
					lcd_goto_XY(0, 0);
					lcd_send_string("CARD NOT EXIST");
				}
				else {
					lcd_goto_XY(0, 0);
					lcd_send_string("DELETED CARD");
					sendDataToESP32("DELETED CARD\r\n");
				}
				HAL_Delay(1000);
				status = INIT;
				break;
			}
			break;
		default:
			break;
	}

	if(timer_flag[0] == 1){ // sang trong 3 s
		rgb(100, 0, 0); // RED
	}
}
