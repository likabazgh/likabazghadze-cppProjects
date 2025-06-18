/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"

VectorPriorityQueue::VectorPriorityQueue() {
}

VectorPriorityQueue::~VectorPriorityQueue() {
}

int VectorPriorityQueue::size() {
	return vect.size();
}

bool VectorPriorityQueue::isEmpty() {
	
	return size()==0;
}

void VectorPriorityQueue::enqueue(string value) {
	vect.add(value);
}

string VectorPriorityQueue::peek() {
	if(isEmpty()){
		cout << "queue is empty" << endl;
	}
	int ind = index();
	return vect[ind];
}

string VectorPriorityQueue::dequeueMin() {
	if(isEmpty()){
		cout << "queue is empty" << endl;
	}
	int ind = index();
	string top = vect[ind];
	vect.remove(ind);
	return top;
}

int VectorPriorityQueue::index() {
	string top = vect[0];
	int ind = 0;
	for (int i = 1; i < vect.size(); i++) {
		if (vect[i] <= top) {
			top = vect[i];
			ind = i;
		}
	}
	return ind;
}



