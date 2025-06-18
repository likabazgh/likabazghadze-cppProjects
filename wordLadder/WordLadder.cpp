/*
 * File: WordLadder.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Word Ladder problem.
 * [TODO: rewrite the documentation]
 */
#include <iostream>
#include "console.h"
#include "simpio.h"
#include "lexicon.h"
#include "set.h"
#include "vector.h"
#include "queue.h"
using namespace std;

Lexicon dict("EnglishWords.dat");
Lexicon newLexicon(string word);

void ladder(string begining, string ending){

	Set<string> used;
	used += begining;

	Vector<string> vect;
	vect.add(begining);
	Vector<string> curr;

	Queue<Vector<string>> q;
	q.enqueue(vect);

	string result;
	
	while(!q.isEmpty()){
		curr = q.dequeue();
		if(curr[curr.size()-1] == ending){
			for(int i=0; i<curr.size(); i++){
				result += curr[i];
				result += '-';
			}
			cout << "ledder is: " << result.substr(0, result.length()-1) << endl;
			return;
		}
		Vector<string> newvect;
		Lexicon checker = newLexicon(curr[curr.size()-1]);
		foreach(string newword in checker){
			if(!used.contains(newword)){
				used += newword;
				newvect = curr;
				newvect.add(newword);
				q.enqueue(newvect);
			}
		}
	}
	if(q.isEmpty()){
			cout << "not found. " << endl;
	}
}

Lexicon newLexicon(string word){
	Lexicon newLexicon;
	string temp = word;
	for(int i=0; i<temp.length(); i++){
		for(int j=0; j<26; j++){
			temp[i]='a'+j;
			if(dict.contains(temp) && word!=temp){
				newLexicon.add(temp);
			}
		}
		temp = word;
	}
	return newLexicon;
}

int main() {
	while(true){
		string begining = getLine("Enter start word: ");
		string ending = getLine("Enter destination word: ");

		if (begining.length() != ending.length()) {
			cout << "type words with same length. " << endl;

		}
		if(begining=="" || ending==""){
			break;
		}
		if(dict.contains(begining) && dict.contains(ending)){
			ladder(begining,ending);
		} else {
			cout << "type words that exists." <<endl;
		}
	}
    return 0;
} 