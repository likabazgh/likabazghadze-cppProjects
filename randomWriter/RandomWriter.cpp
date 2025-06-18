#include <iostream>
#include "console.h"
#include "simpio.h"
#include <string>
#include <fstream>
#include "vector.h"
#include "map.h"
#include "random.h"
using namespace std;


void getSymbolsFromFile(string fileName, Vector<char> &vect);
string findMaxSeed(int markOrd, Vector<char> &chars, Map<string, Vector<char> > &markovModel);
void saveStrings(int &markOrd, Vector<char> &chars, Map<string, Vector<char> > &markovModel, string &eachStr, 
						   Vector<char> &nextChars, string &maxSeed, int &maxVectorSize, int &i);
void generateText(string maxSeed, Map<string, Vector<char> > &markovModel);
char getRandomSymbol(Vector<char> &v);

int main() {
	string filename = getLine("enter source file: ");
	ifstream stream(filename.c_str());
	while(!stream.is_open()){
		stream.clear();
		cout << "File doesn't exist. try again." << endl;
		filename = getLine("enter source file: ");
		stream.open(filename.c_str());
	}
	int markOrd = getInteger("enter markov order from 1 to 10: "); 
	while(markOrd>10 || markOrd<1){
		cout << "out of range." << endl;
		markOrd = getInteger("enter markov order from 1 to 10: ");
	}
	cout << "File in process..." << endl;

	Vector<char> chars;
	getSymbolsFromFile(filename, chars); // stores symbols from file in char array
	
	Map<string, Vector<char> > markovModel;
	string maxSeed = findMaxSeed(markOrd, chars, markovModel);
	generateText(maxSeed, markovModel);
	
    return (0);
}

void getSymbolsFromFile(string fileName, Vector<char> &vect){ 
	ifstream file(fileName.c_str());
	
	char symbol;
	while(file.get(symbol)){
		vect.add(symbol);
	}

	file.close();
};

string findMaxSeed(int markOrd, Vector<char> &chars, Map<string, Vector<char> > &markovModel){ // returns most common string
	string maxSeed;
    int maxVector = 0;

    for (int i = 0; i <= chars.size() - markOrd; i++) {
        string str(chars.begin() + i, chars.begin() + i + markOrd);
        Vector<char>& nextChars = markovModel[str];

        if (i + markOrd < chars.size()) {
            nextChars.add(chars[i + markOrd]);
        }

        if (nextChars.size() > maxVector) {
            maxVector = nextChars.size();
            maxSeed = str;
        }
    }
    return maxSeed;
};

// this function adds string with its chars array
void saveStrings(int &markOrd, Vector<char> &chars, Map<string, Vector<char> > &markovModel, string &str, 
						   Vector<char> &nextChars, string &maxSeed, int &maxVector, int &i){
	
    if(markovModel.containsKey(str)){
        markovModel.get(str).add(chars[i + markOrd]);
    }
    else{
        Vector<char> newVect; 
        newVect.add(chars[i + markOrd]);
        markovModel.put(str, newVect);
    }
    if(markovModel.get(str).size() > maxVector){
        maxVector = markovModel.get(str).size();
        maxSeed = str;
    }
    str = "";
};

void generateText(string maxSeed, Map<string, Vector<char> > &markovModel) {
    Vector<char> symbols;
	char randSymbol;
	string currStr = maxSeed;
	string result = maxSeed;

	for(int i = 0; i < (2000 - maxSeed.size()); i++){
		symbols = markovModel.get(currStr);
		randSymbol = getRandomSymbol(symbols);
		result += randSymbol;
		
		currStr = currStr.substr(1, currStr.length() - 1) + randSymbol;

		if(!markovModel.containsKey(currStr)){
			break;
		}
	}
	cout << result << endl;
}

char getRandomSymbol(Vector<char> &vect){
	int randomIndex = randomInteger(0, (vect.size() - 1));

	return vect[randomIndex];
};