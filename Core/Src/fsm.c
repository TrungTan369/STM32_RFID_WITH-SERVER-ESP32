/*
 * fsm_master.c
 *
 *  Created on: Nov 16, 2024
 *      Author: HOME
 */

#include "fsm.h"

int status = INIT;

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
			if(status_read != MI_OK){
				break;
			}
			if(check_Card(readCard) == 2){ // MASTER CARD
				setTimer(0, 3000);
				rgb(0, 100, 0); // GREEN
				status = MASTER_INIT;
				lcd_clear_display();
				lcd_goto_XY(1, 0);
				lcd_send_string("1. ADD CARD");
				lcd_goto_XY(0, 0);
				lcd_send_string("2. DELETE CARD");
				break;
			}
			if( check_Card(readCard) == 1){ // NORMAL CARD
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
			break;
		case MASTER_INIT:
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
		case MASTER_ADDCARD:
			if(status_read == MI_OK){
				if(check_Card(readCard) == 1){
					lcd_goto_XY(0, 0);
					lcd_send_string("CARD EXISTED");
					HAL_Delay(1000);
					status = INIT;
					break;
				}
				add_Card(readCard);
				lcd_goto_XY(0, 0);
				lcd_send_string("ADDED CARD");
				HAL_Delay(1000);
				status = INIT;
			}
			break;
		case MASTER_DELCARD:
			if(status_read == MI_OK){
				delete_Card(readCard);
				lcd_goto_XY(0, 0);
				lcd_send_string("DELETED CARD");
				HAL_Delay(1000);
				status = INIT;
			}
			break;
		default:
			break;
	}

	if(timer_flag[0] == 1){ // sang trong 3 s
		rgb(100, 0, 0); // RED
	}
}
