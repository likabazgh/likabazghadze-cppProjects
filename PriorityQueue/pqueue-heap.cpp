/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include "error.h"

HeapPriorityQueue::HeapPriorityQueue() {
	elements = CAPACITY;
	arr = new string[elements];
	length = 0;
}

HeapPriorityQueue::~HeapPriorityQueue() {
	delete[] arr;
}

int HeapPriorityQueue::size() {
	return length;
}

bool HeapPriorityQueue::isEmpty() {
	return length == 0;
}

void HeapPriorityQueue::enqueue(string value) {
	if(isEmpty()){
		arr = new string[1];
		arr[0] = value;
		elements = 1;
	}
	if(length == elements){
		expandArr();
	}
	arr[length] = value;
	length++;
	bubbleUp(length);
}

string HeapPriorityQueue::peek() {
	if(isEmpty()){
		error("empty");
	}
	return arr[0];
}

string HeapPriorityQueue::dequeueMin() {
	string res = peek();

	arr[0] = arr[length - 1];
	arr[length - 1] = res;
    length--;
    bubbleDown(length);
    
    return res;
}

void HeapPriorityQueue::expandArr(){
	elements = elements * 2;
	string* newArr = new string[elements];

	for(int i=0; i<length; i++){
		newArr[i] = arr[i];
	}
	delete[] arr;
}

void HeapPriorityQueue::bubbleUp(int index) {
    string newValue = arr[elements - 1];
    int valueIndex = elements - 1;
    int parentIndex = (valueIndex - 1) / 2;

    while (valueIndex > 0 && newValue < arr[parentIndex]) {
        arr[valueIndex] = arr[parentIndex];
        valueIndex = parentIndex;
        parentIndex = (valueIndex - 1) / 2;
    }

    arr[valueIndex] = newValue;
}

void HeapPriorityQueue::bubbleDown(int index) {
    int startIndex = 0;
    while (startIndex * 2 + 1 < length) {
        int childIndex = startIndex * 2 + 1;
        if (childIndex + 1 < length && arr[childIndex + 1] < arr[childIndex]) {
            childIndex++;
        }
        if (arr[startIndex] <= arr[childIndex]) {
            break;
        }
        string tmp = arr[startIndex];
        arr[startIndex] = arr[childIndex];
        arr[childIndex] = tmp;
        startIndex = childIndex;
    }
}