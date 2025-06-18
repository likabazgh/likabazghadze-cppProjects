/*
 * File: Subsequences.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Subsequences problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
using namespace std;

/* Given two strings, returns whether the second string is a
 * subsequence of the first string.
 */

bool isSub(string text, string subsequence, int textInd, int subInd){
	if(subsequence.length() == subInd){
		return true;
	}
	if(text.length() == textInd){
		return false;
	}
	if(text[textInd] == subsequence[subInd]){
		return isSub(text, subsequence, textInd + 1, subInd +  1);
	} else {
		return isSub(text, subsequence, textInd + 1, subInd);
	}
}

bool isSubsequence( string text, string subsequence){
	return isSub(text, subsequence, 0, 0);
}

int main() {
	while(true){
		string text = getLine("enter text: ");
		string subsequence = getLine("enter subsequence: ");
		cout << isSubsequence(text, subsequence) << endl;
	}
    return 0;
}
