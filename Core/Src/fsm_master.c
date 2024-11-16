/*
 * fsm_master.c
 *
 *  Created on: Nov 16, 2024
 *      Author: HOME
 */

#include "fsm_master.h"


void fsm_master(){
	switch (status) {
		case MASTER_INIT:
			lcd_goto_XY(1, 0);
			lcd_send_string("1. ADD CARD");
			lcd_goto_XY(0, 0);
			lcd_send_string("2. DELETE CARD");
			if(isButtonPress(0) == 1){
				lcd_clear_display();
				lcd_goto_XY(1, 0);
				lcd_send_string("PLEASE SET CLOSER CARD");
				status = MASTER_ADDCARD;
			}
			if(isButtonPress(1) == 1){
				lcd_clear_display();
				lcd_goto_XY(1, 0);
				lcd_send_string("PLEASE SET CLOSER CARD");
				status = MASTER_DELCARD;
			}
			break;
		case MASTER_ADDCARD:
			if(status_read){
				addCard(readCard);
				lcd_goto_XY(1, 0);
				lcd_send_string("ADDED CARD");
				HAL_Delay(1000);
				lcd_clear_display();
				status = WAITCARD;
			}
			break;
		case MASTER_DELCARD:
			if(status_read){
				addCard(readCard);
				lcd_goto_XY(1, 0);
				lcd_send_string("DELETED CARD");
				HAL_Delay(1000);
				lcd_clear_display();
				status = WAITCARD;
			}
			break;
		default:
			return;
	}

}
