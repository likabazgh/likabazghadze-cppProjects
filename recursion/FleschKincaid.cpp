#include <iostream>
#include "console.h"
#include <fstream>
#include "simpio.h"
#include "tokenscanner.h"
#include "filelib.h"
using namespace std;

const double C0 = -15.59;
const double C1 = 0.39;
const double C2 = 11.8;

bool isWord(string token){
	if(isalpha(token[0])){
		return true;
	}
	return false;
}

bool isSentence(string token){
	if(token == "." || token == "?" || token == "!"){
		return true;
	}
	return false;
}

int isSyllable(string token){
	int numSyllable = 0;
	int n = token.length();
	
	bool isSyllablePrev = false;
	bool isSyllable = false;

	for(int i=0; i<n; i++){
		if(token[i] == 'a' || token[i] == 'e' || token[i] == 'i' || token[i] == 'o' || token[i] == 'u' || token[i] == 'y' || 
			token[i] == 'A' || token[i] == 'E' || token[i] == 'I' || token[i] == 'O' || token[i] == 'U' || token[i] == 'Y'){
			isSyllable = true;
			if(!((token[i] == 'e' || token[i] == 'E') && i == n-1)){
				numSyllable++;
				if(isSyllablePrev && isSyllable){
					numSyllable--;
				}	
			}
		}
		isSyllablePrev = isSyllable;
		isSyllable = false;
	}
	if(numSyllable == 0){
		numSyllable++;
	}
	return numSyllable;
}

double grade(int words, int sentences, int syllables){
	double result = C0 + C1*(words*1.0/sentences) + C2*(syllables*1.0/words);
	return result;
}

double calculate(ifstream &input){
	TokenScanner scanner(input);
	scanner.ignoreWhitespace();
	scanner.addWordCharacters("'");

	int words = 0;
	int sentences = 0;
	int syllables  = 0;

	while(scanner.hasMoreTokens()){
		string token = scanner.nextToken();
		if(isSentence(token)){
			sentences++;
		} else if(isWord(token)){
			words++;
			syllables += isSyllable(token);
		}
	}
	
	if(words == 0){
		words += 1;
	}
	if(sentences ==0){
		sentences += 1;
	}

	cout << "word " << words << endl;
	cout << "sentences " << sentences << endl;
	cout << "syllables " << syllables << endl; 

	double calc = grade(words, sentences, syllables);
	return calc;
}


int main() {
	string fileName = getLine("enter file name: ");
	ifstream file;
	file.open(fileName.c_str());

	while(!file.is_open()){
		file.clear();
		fileName = getLine("enter existing file name: ");
		file.open(fileName.c_str());
	}

	double calc = calculate(file);

	file.close();

	cout << calc << endl;
    return 0;
}