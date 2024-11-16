/*
 * fsm_normal.h
 *
 *  Created on: Nov 16, 2024
 *      Author: HOME
 */

#include "global.h"

#define init 0
#define MASTER 1
#define READCARD 2
#define WAITCARD 3

int status = init;

void normal();
