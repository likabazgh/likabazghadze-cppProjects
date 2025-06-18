/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	top = NULL;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	cell* current = top;
	while (current != NULL) {
        cell* nextCell = current->next;
		delete current;
        current = nextCell;
	}
}

int DoublyLinkedListPriorityQueue::size() {
	int count = 0;
	cell* current = top;
    while (current != NULL) {
		count += 1;
        current = current->next;
	}
	return count;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
	return top == NULL;
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
	if (top == NULL) {
        top = new cell(value);
	}
	else {
        cell* newCell = new cell(value);
        newCell->next = top;
        top->previous = newCell;
		top = newCell;
	}
}

string DoublyLinkedListPriorityQueue::peek() {
	if (isEmpty()){
		error("empty");
	}
	cell* res = findMin();
    return res->val;
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
	if (isEmpty()){
		error("empty");
	}
	cell* min = findMin();
	if (min->next != NULL)
        min->next->previous = min->previous;
	if (min == top) {
        top = min->next;
	}
	else {
        min->previous->next = min->next;
	}
    string result = min->val;
	delete min;
	return result;
}

DoublyLinkedListPriorityQueue::cell *DoublyLinkedListPriorityQueue::findMin() {
	cell* result = top;
    cell* current = top->next;
	while (current != NULL) {
		if (current->val < result->val){
			result = current;
		}
		current = current->next;
	}
	return result;
}

