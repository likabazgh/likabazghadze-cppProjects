/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"

LinkedListPriorityQueue::LinkedListPriorityQueue() {
	top = NULL;
}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	cell* current = top;
	while(current != NULL){
		cell* next = current->next;
		delete current;
		current = next;
	}
}

int LinkedListPriorityQueue::size() {
	if(isEmpty()){
		return 0;
	}
	int count = 1;
	cell* current = top;
	while(current->next != NULL){
		count += 1;
		current = current->next;
	}
	return count;
}

bool LinkedListPriorityQueue::isEmpty() {
	return top == NULL;
}

void LinkedListPriorityQueue::enqueue(string value) {
	
	cell* current = top;
	cell* last = NULL;

	if(isEmpty()){
		top = new cell(value);
		return;
	}

	while(true){
		if(value < current->val){
			insert(value, last);
			return;
		}
		last = current;
		if(current->next == NULL){
			break;
		}
		current = current->next;
	}
	insert(value, current);
}

string LinkedListPriorityQueue::peek() {
	if(isEmpty()){
		error("empty");
	}
	return top->val;
}

string LinkedListPriorityQueue::dequeueMin() {
	if(isEmpty()){
		error("empty");
	}
	string res = top->val;
	cell* next = top->next;
	delete top;
	top = next;
	return res;
}

void LinkedListPriorityQueue::insert(string value, cell* previous){
	cell* newCell = new cell(value);
	if(previous == NULL){
		newCell->next = top;
		top = newCell;
	}
	else{
		newCell->next = previous->next;
		previous->next = newCell;
	}
}

