/*
 * fsm_master.c
 *
 *  Created on: Nov 16, 2024
 *      Author: HOME
 */

#ifndef INC_FSM_MASTER_C_
#define INC_FSM_MASTER_C_

#include "global.h"

#define INIT 0
#define WAITCARD 1
#define MASTER_MENU_1 2
#define MASTER_MENU_2 3
#define MASTER_MENU_3 4
#define MASTER_ADDCARD 5
#define MASTER_DELCARD 6
#define STATUS_DELAY 7
extern int status;
extern uint8_t * data_uart;

void fsm(uint8_t *, uint8_t);
void RESET_RFID();
void STATUS_INIT();
#endif /* INC_FSM_MASTER_C_ */
