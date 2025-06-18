/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Consecutive Heads problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "random.h"
using namespace std;

int headCount(){
	int consecutive = 0;
	int count = 0;

	while(true){
		int headNum = randomInteger(0,1);
		count++;
		if(headNum == 1){
			cout << "head" << endl;
			consecutive++;
			if(consecutive == 3){
				break;
			}
		} else {
			consecutive = 0;
			cout << "tail" << endl;
		}
	}
	return count;
}

int main() {
	int count = headCount();
	cout << "it took " << count << " flips to get 3 consecutive heads" << endl;

    return 0;
}
