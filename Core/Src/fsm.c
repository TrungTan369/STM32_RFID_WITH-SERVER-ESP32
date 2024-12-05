/*
 * fsm_master.c
 *
 *  Created on: Nov 16, 2024
 *      Author: HOME
 */

#include "fsm.h"

int status = INIT;
void fsm(){
	switch (status){
		case INIT:
			lcd_clear_display();
			lcd_goto_XY(1, 0);
			lcd_send_string("PUT ON YOUR CARD");
			lcd_goto_XY(0, 0);
			lcd_send_string("TO CONTROL LED");
			status = WAITCARD;
		case WAITCARD:
			if( status_read == MI_OK && cardProcessed == 0 ){
				// ---------MASTER CARD ----------------
				if(check_Card(readCard) == 2){
					sendDataToESP32("MASTER LOGGIN\r\n");
					RGB_PURPLE();
					SCH_Add_Task(RGB_RED, 3000, 0);
					//state_MASTER_INIT();
					lcd_clear_display();
					lcd_goto_XY(1, 0);
					lcd_send_string("1. ADD - DELETE");
					lcd_goto_XY(0, 0);
					lcd_send_string("2. OTHER");
					status = MASTER_MENU_1;
				}
				// ------ NORMAL CARD ------------
				else if( check_Card(readCard) == 1){
					sendDataToESP32("TURN LED\r\n");
					RGB_GREEN();
					SCH_Add_Task(RGB_RED, 3000, 0);
				}
				else {//if (check_Card(readCard) == 0)
					//state_CARD_NOT_EXSIT();
					lcd_clear_display();
					lcd_goto_XY(1, 0);
					lcd_send_string("CARD NOT EXIST");
					lcd_goto_XY(0, 0);
					lcd_send_string("TRY AGAIN");
					SCH_Add_Task(state_INIT, 1000, 0);
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
				lcd_send_string("1. NUMBER OF CARDS");
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
				lcd_send_int(numCard);
				SCH_Add_Task(state_INIT, 1000, 0);
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
				}
				SCH_Add_Task(state_INIT, 1000, 0);
			}
			break;
		case MASTER_DELCARD:
			if(num_Card() == 0){
				lcd_goto_XY(0, 0);
				lcd_send_string(" LIST CARD EMPTY");
				SCH_Add_Task(state_INIT, 1000, 0);
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
				SCH_Add_Task(state_INIT, 1000, 0);
			}
			break;
		default:
			break;
	}
}

void state_INIT(){
	status = INIT;
}
void state_WAITCARD(){
	status = WAITCARD;
	lcd_clear_display();
	lcd_goto_XY(1, 0);
	lcd_send_string("PUT ON YOUR CARD");
	lcd_goto_XY(0, 0);
	lcd_send_string("TO CONTROL LED");
}
void state_MASTER_INIT(){
	status = MASTER_MENU_1;
	lcd_clear_display();
	lcd_goto_XY(1, 0);
	lcd_send_string("1. ADD CARD");
	lcd_goto_XY(0, 0);
	lcd_send_string("2. DELETE CARD");
}
void state_MASTER_ADDCARD();
void state_MASTER_DELCARD();
void state_CARD_NOT_EXSIT(){
	status = CARD_NOT_EXSIT;
	lcd_clear_display();
	lcd_goto_XY(1, 0);
	lcd_send_string("CARD NOT EXIST");
	lcd_goto_XY(0, 0);
	lcd_send_string("TRY AGAIN");
}
void state_CARD_EXSITED(){
	status = CARD_EXISTED;
	lcd_clear_display();
	lcd_goto_XY(1, 0);
	lcd_send_string("CARD_EXISTED");
	lcd_goto_XY(0, 0);
	lcd_send_string("TRY AGAIN");
}
