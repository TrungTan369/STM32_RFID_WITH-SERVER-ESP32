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
#define MASTER_INIT 2
#define MASTER_ADDCARD 3
#define MASTER_DELCARD 4

extern int status;
extern uint8_t * data_uart;

void fsm(uint8_t *, uint8_t);

#endif /* INC_FSM_MASTER_C_ */
