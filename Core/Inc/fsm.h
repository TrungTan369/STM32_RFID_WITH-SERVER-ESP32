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
#define CARD_NOT_EXSIT 7
#define CARD_EXISTED 8

extern uint8_t cardProcessed;

void fsm();
void state_INIT();
void state_WAITCARD();
void state_MASTER_INIT();
void state_MASTER_ADDCARD();
void state_MASTER_DELCARD();
void state_CARD_NOT_EXSIT();
void state_CARD_EXSITED();
#endif /* INC_FSM_MASTER_C_ */
