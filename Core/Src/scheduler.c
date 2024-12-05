/*
 * scheduler.c
 *
 *  Created on: Nov 24, 2024
 *      Author: HOME
 */
#include "scheduler.h"


List list;

void SCH_Init(void) {
	list.head = NULL;
    list.numTask = 0;
}

void SCH_Add_Task(void (*function)(), uint32_t Delay, uint32_t Period){
	sTask * newTask = (sTask *) malloc (sizeof(sTask));
	if (newTask == NULL)
		return;
	newTask->pTask = function;
	newTask->Delay = Delay/10; // scale for TIM2 10ms run
	newTask->Period = Period/10;
	newTask->next = NULL;
	if(list.head == NULL){
		list.head = newTask;
	}
	else{
		sTask * cur = list.head;
		sTask * prev = cur;
		//--------- FINDING LOCATE FOR NEWTASK-----------
		while(cur != NULL && newTask->Delay >= cur->Delay){
			newTask->Delay = newTask->Delay - cur->Delay;
			cur = cur->next;
			prev = cur;
		}
		if(cur == list.head){ // Add To First List
			newTask->next = list.head;
			list.head->Delay = list.head->Delay - newTask->Delay;
			list.head = newTask;
		}
		else if(cur == NULL){ // Add to Last List -- Add After Cur
			prev->next = newTask;
		}
		else{ // Add to Mid list -- Add before Cur
			newTask->next = cur;
			prev->next = newTask;
			cur->Delay = cur->Delay - newTask->Delay;
		}
	}
	list.numTask++;
}

void SCH_Update(void){ // TIM involked every 10ms
	if (list.head == NULL) {
		return;
	}
	list.head->Delay--;
}
void SCH_Dispatch_Task(void){
	if (list.head == NULL) {
		return;
	}
	if(list.head->Delay <= 0){
		list.head->pTask();
		sTask * temp = list.head;
		list.head = list.head->next;
		if(temp->Period > 0){
			SCH_Add_Task(temp->pTask, temp->Period * 10, temp->Period * 10);
		}
		free(temp);
		list.numTask--;
	}
}

uint8_t SCH_Delete_Task(void (*function)()){
	if(list.numTask == 0)
		return 0;
	if(list.numTask == 1){
		sTask * temp = list.head;
		list.head = NULL;
		list.numTask = 0;
		free(temp);
		return 1;
	}
	sTask * temp = list.head;
	sTask * prev = temp;
	while(temp != NULL){
		if(temp->pTask == function){
			if(temp == list.head){ // Delete head
				list.head = list.head->next;
				list.head->Delay = list.head->Delay + temp->Delay;
			}
			else if (temp->next == NULL){ // Delete tail
				prev = NULL;
			}
			else{
				prev = temp->next;
				temp->next->Delay = temp->next->Delay + temp->Delay;
			}
			list.numTask--;
			free(temp);
			return 1;
		}
		prev = temp;
		temp = temp->next;
	}
	return 0;
}
