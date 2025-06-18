/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Combinations problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
using namespace std;

int pascal(int n, int k){
	if(n == 0 || k ==0 || n==k){
		return 1;
	}
	return pascal(n-1, k-1) + pascal(n-1, k);
	
}

int main() {
	int n = getInteger("enter n- ");
	int k = getInteger("enter k- ");
	if(k<n){
		int c = pascal(n, k);
		cout << "c(n,k)= " << c << endl;
	} else {
		cout << "enter valid numbers" << endl;
	}
    return 0;
}
