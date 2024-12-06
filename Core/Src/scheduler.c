/*
 * scheduler.c
 *
 *  Created on: Nov 19, 2024
 *      Author: HOME
 */
#include "scheduler.h"

List list;

void SCH_Init(void) {
	list.head = NULL;
	list.tail = NULL;
    list.numTask = 0;
}

void SCH_Add_Task(void (*function)(), uint32_t Delay, uint32_t Period){
	if(SCH_Is_Task_Exist(function) == 1)
		return;
	sTask * newTask = (sTask *) malloc (sizeof(sTask));
	if (newTask == NULL)
		return;

	newTask->pTask = function;
	newTask->Delay = Delay/10; // scale for TIM2 10ms run
	newTask->Period = Period/10;
	newTask->runMe = 0;
	newTask->next = NULL;
	newTask->prev = NULL;

	if(list.head == NULL){
		list.head = newTask;
		list.tail = newTask;
	}
	else{
		newTask->prev = list.tail;
		list.tail->next = newTask;
		list.tail = newTask;
	}
	list.numTask++;
}

void SCH_Update(void){
	sTask * temp = list.head;
	while(temp != NULL){
		if(temp->Delay > 0){
			temp->Delay --;
		}
		else{
			temp->runMe++;
			temp->Delay = temp->Period;
		}
		temp = temp->next;
	}
}
void SCH_Dispatch_Task(void){
	sTask * temp = list.head;
	while(temp != NULL){
		if(temp->runMe > 0){
			temp->runMe --;
			temp->pTask();
			if(temp->Period == 0){
				SCH_Delete_Task(temp->pTask);
			}
		}
		temp = temp ->next;
	}
}

uint8_t SCH_Delete_Task(void (*function)()){
	if(list.numTask == 0)
		return 0;
	sTask * temp = list.head;
	while(temp != NULL){
		if(temp->pTask == function){
			if(temp == list.head){ // delete head
				temp->next->prev = NULL;
				list.head = temp->next;
			}
			else if (temp == list.tail){ //delete tail
				temp->prev->next = NULL;
				list.tail = temp->prev;
			}
			else{
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
			}
			list.numTask--;
			free(temp);
			return 1;
		}
		temp = temp->next;
	}
	return 0;
}
uint8_t SCH_Is_Task_Exist(void (*function)()){
	if(list.numTask == 0) return 0;
	sTask * temp = list.head;
	while(temp != NULL){
		if(temp->pTask == function)
			return 1;
		temp = temp->next;
	}
	return 0;
}
