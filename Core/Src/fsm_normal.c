/*
 * fsm_normal.c
 *
 *  Created on: Nov 16, 2024
 *      Author: HOME
 */

#include "fsm_normal.h"

void normal(){

	if(Check_master(master, readCard)){
		lcd_clear_display();
		status = MASTER_INIT;
	}
}
