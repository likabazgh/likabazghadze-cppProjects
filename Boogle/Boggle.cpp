/*
 * File: Boggle.cpp
 * ----------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the main starter file for Assignment #4, Boggle.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
using namespace std;

/* Constants */
const int maxSize=4;

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;

const string STANDARD_CUBES[16]  = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25]  = {
    "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
    "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
    "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
    "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
    "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

const int ROWS = 4;
const int COLS = 4;
const int CUBE_SIDES = 6;
const int MIN_WORD = 4;


/* Function prototypes */
void welcome();
void giveInstructions();
void setUp(Grid<char>& board);
void generateCombination(Vector<string>& cubes);
void swapCubes(Vector<string>& cubes);
void swapElements(Vector<string>& cubes, int num1, int num2);
void randomRoll(Grid<char>& board, Vector<string>& cubes);
void searchForWords(Lexicon& lex, Grid<char>& board, Set<string>& foundWords, Player human);
bool isValidWord(string word, Lexicon& lex, Grid<char>& board, Set<string>& foundWords);
bool isWordOnBoard(string word, Grid<char>& board);
void fillGridWithBools(Grid<bool>& board, bool b);
bool recursiveWordIsOnBoard(string word, Grid<char>& board, Grid<bool>& usedLetters, int row, int col);
void highlight(Grid<bool>& usedLetters);
void deHighlight();
void generateWords(Grid<char>& board, Lexicon& lex, Set<string>& foundWords, Player computer);
void recFindWords(Grid<char>& board, Lexicon& lex, Set<string>& foundWords,
	Grid<bool>& usedLetters, int row, int col, string soFar, Player computer);

/* Main program */

int main(){
	GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
	initGBoggle(gw);

	welcome();
	giveInstructions();

	Player human = HUMAN;
	Player computer = COMPUTER;

	Grid<char> board(ROWS, COLS);
	drawBoard(ROWS, COLS);

	while (true){   // for player to start over if they want to
		gw.repaint();
		setUp(board);

		Lexicon lex("EnglishWords.dat");
		Set<string> foundWords;

		searchForWords(lex, board, foundWords, human);

		generateWords(board, lex, foundWords, computer);

		string str = getLine("do you want to play again?");
		while(true){
			if(str == "no") {
				break;
			}
		}
	}
	return 0;
};


/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */




void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit return when you're ready...";
    getLine();
}

// [TODO: Fill in the rest of the code]

//generates the board
void setUp(Grid<char>& board){  
	Vector<string> cubes;
	generateCombination(cubes);

	swapCubes(cubes); 
	randomRoll(board, cubes);
}
//asks player if they want to generate the board or play on auto generated board
void generateCombination(Vector<string>& cubes){
	cout << endl << "Do you want to set up your own letters?";

	string answer = getLine("-Answer here: ");
	if(answer == "yes"){
		cout << "Enter 16 string to fill up the board" << endl;
		for (int i = 0; i < ROWS * COLS; i++){  // player enters strings
			cubes.add(toUpperCase(getLine("Enter the string: ")));
		}
	}
	if(answer == "no"){
		for(int i=0; i< ROWS * COLS; i++){  // computer generates strings on each cube
			cubes.add(STANDARD_CUBES[i]);
		}
	}
}
// random vector swap
void swapCubes(Vector<string>& cubes){
	int rand;

	string str;
	for (int i = 0; i < cubes.size(); i++){
		rand = randomInteger(i, cubes.size() - 1);
		
		str = cubes[i];
		cubes[i] = cubes[rand];
		cubes[rand] = str;
	}
}
// cube's roll randomly
void randomRoll(Grid<char>& board, Vector<string>& cubes){
	string cube;
	char front;
	for (int i = 0; i < board.nRows; i++){
		for (int j = 0; j < board.nCols; j++){
			cube = cubes[i * board.nCols + j];
			front = cube[randomInteger(0, CUBE_SIDES - 1)];
			board[i][j] = front;
			labelCube(i, j, front);
		}
	}
}
// player enters the word and this function checks if its valid or not
void searchForWords(Lexicon& lex, Grid<char>& board, Set<string>& foundWords, Player human){
	string word;
	while (true){
		word = getLine("Enter word: ");
		if (word == "") break;
		word = toUpperCase(word);

		if (isValidWord(word, lex, board, foundWords)){ 
			foundWords.add(word); 
			recordWordForPlayer(word, human);
			deHighlight(); 
		}
		else{
			cout << "not possible" << endl;
		}
	}
}

bool isValidWord(string word, Lexicon& lex, Grid<char>& board, Set<string>& foundWords){
	if (word.size() < MIN_WORD || !lex.contains(word) || foundWords.contains(word)){
		return false;
	}
	if (isWordOnBoard(word, board)){
		return true;
	}
	return false;
}
// this checks if entered word is on board
bool isWordOnBoard(string word, Grid<char>& board){
    Grid<bool> usedLetters(ROWS, COLS);
	fillGridWithBools(usedLetters, false);

    for (int i = 0; i < board.nRows; i++) {
        for (int j = 0; j < board.nCols; j++) {
            if (board[i][j] == toupper(word[0]) && recursiveWordIsOnBoard(word, board, usedLetters, i, j)) {
                highlight(usedLetters);
                return true;
            }
        }
    }

    return false;
}


bool recursiveWordIsOnBoard(string word, Grid<char>& board, Grid<bool>& usedLetters, int row, int col){
    if (word.empty()) {
        return true;
    }

    for (int i = row - 1; i <= row + 1; i++) {
        for (int j = col - 1; j <= col + 1; j++) {
            if (board.inBounds(i, j) && !usedLetters[i][j] && toupper(word[0]) == board[i][j]) {
                usedLetters[i][j] = true;
            
                if (recursiveWordIsOnBoard(word.substr(1), board, usedLetters, i, j)) {
                    return true;
                }
                usedLetters[i][j] = false;
            }
        }
    }
    return false;
}
//visualization
void highlight(Grid<bool>& usedLetters){
	for (int i = 0; i < usedLetters.nRows; i++){
		for (int j = 0; j < usedLetters.nCols; j++){
			highlightCube(i, j, usedLetters[i][j]);
		}
	}
}

void deHighlight(){
	for (int i = 0; i < ROWS; i++){
		for (int j = 0; j < COLS; j++){
			highlightCube(i, j, false);
		}
	}
}
// computer generates words on board
void generateWords(Grid<char>& board, Lexicon& lex, Set<string>& foundWords, Player computer) {
    Grid<bool> usedLetters(ROWS, COLS);
	fillGridWithBools(usedLetters, false);

    string empty = "";

    for (int i = 0; i < board.nRows; i++) {
        for (int j = 0; j < board.nCols; j++) {
            usedLetters[i][j] = true;
            empty = tolower(board[i][j]);
            recFindWords(board, lex, foundWords, usedLetters, i, j, empty, computer);
            usedLetters[i][j] = false;
            empty = "";
        }
    }
}

void recFindWords(Grid<char>& board, Lexicon& lex, Set<string>& foundWords, Grid<bool>& usedLetters,
                  int row, int col, string soFar, Player computer) {
    if (soFar.size() >= MIN_WORD && lex.contains(soFar) && !foundWords.contains(soFar)) {
        foundWords.add(soFar);
        recordWordForPlayer(soFar, computer);
    }

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int newRow = row + i;
            int newCol = col + j;

            if (board.inBounds(newRow, newCol) && !usedLetters[newRow][newCol] && lex.containsPrefix(soFar + board[newRow][newCol])) {
                usedLetters[newRow][newCol] = true;
                recFindWords(board, lex, foundWords, usedLetters, newRow, newCol, soFar + board[newRow][newCol], computer);
                usedLetters[newRow][newCol] = false;
            }
        }
    }
}

void fillGridWithBools(Grid<bool>& board, bool b){
	for (int i = 0; i < board.nRows; i++){
		for (int j = 0; j < board.nCols; j++){
			board[i][j] = b;
		}
	}
}