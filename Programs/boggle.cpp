//
//  boggle.cpp
//  Boggle
//
//  Created by Vince Mansel on 10/14/11.
//  Copyright 2011 Wave Ocean Software. All rights reserved.
//
 
#include "genlib.h"
#include "simpio.h"
#include <iostream>
#include "extgraph.h"
#include "grid.h"
#include "random.h"
#include "gboggle.h"
#include "lexicon.h"
#include "map.h"

struct cubeT {
    int num;
    char letter;
};

const int MinLengthWord = 4;

string StandardCubes[16]  = 
{"AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS", "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
 "DISTTY", "EEGHNW", "EEINSU", "EHRTVW", "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"};
 
string BigBoggleCubes[25]  = 
{"AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM", "AEEGMU", "AEGMNN", "AFIRSY", 
"BJKQXZ", "CCNSTW", "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT", "DHHLOR", 
"DHLNOR", "EIIITT", "EMOTTT", "ENSSSU", "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"};

void GiveInstructions()
{
    cout << endl << "The boggle board is a grid onto which I will randomly distribute " 
	 << "cubes. These 6-sided cubes have letters rather than numbers on the faces, " 
	 << "creating a grid of letters on which you try to form words. You go first, " 
	 << "entering all the words you can find that are formed by tracing adjoining " 
	 << "letters. Two letters adjoin if they are next to each other horizontally, " 
	 << "vertically, or diagonally. A letter can only be used once in the word. Words "
	 << "must be at least 4 letters long and can only be counted once. You score points "
	 << "based on word length: a 4-letter word is worth 1 point, 5-letters earn 2 "
	 << "points, and so on. After your puny brain is exhausted, I, the super computer, "
	 << "will find all the remaining words and double or triple your paltry score." << endl;
	
    cout << "\nHit return when you're ready...";
    GetLine();
}

static void Welcome()
{
    cout << "Welcome!  You're about to play an intense game of mind-numbing Boggle. " 
	 << "The good news is that you might improve your vocabulary a bit.  The "
	 << "bad news is that you're probably going to lose miserably to this little "
	 << "dictionary-toting hunk of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

void InitBoard(Grid<cubeT> &board);
void Shake(Grid<cubeT> &board);
void HumanTurn(Grid<cubeT> & board, Lexicon & lex, Map<string> &wordList);
bool OnBoardHuman(Grid<cubeT> & board, string word);
void ComputerTurn(Grid<cubeT> & board, Lexicon & lex, Map<string> &wordList);
void PrintString(string key, string word);

int main()
{
    Randomize();
	SetWindowSize(9, 5);
	InitGraphics();
	Welcome();
	//GiveInstructions();
    
    int numRows = 4;
    int numCols = 4;
    
    Grid<cubeT> board(numRows, numCols);
    Lexicon lex("lexicon.dat");
    Map<string> wordList;
    
    DrawBoard(numRows, numCols);
    InitBoard(board);
    Shake(board);
    
    // TEST CODE
    
    int k = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            board[i][j].letter = IntegerToString(k)[0];
            LabelCube(i, j, IntegerToString(k++)[0]);
            if (k > 9) k = 0;
        }
    }
    
//    board[1][3].letter = 'T';
//    board[0][2].letter = 'A';
//    board[0][1].letter = 'I';
//    board[0][3].letter = 'N';
//    LabelCube(1, 3, 'T');
//    LabelCube(0, 2, 'A');
//    LabelCube(0, 1, 'I');
//    LabelCube(0, 3, 'N');
    
    board[0][0].letter = 'T';
    board[0][1].letter = 'A';
    board[0][2].letter = 'I';
    board[0][3].letter = 'N';
    LabelCube(0, 0, 'T');
    LabelCube(0, 1, 'A');
    LabelCube(0, 2, 'I');
    LabelCube(0, 3, 'N');

    ComputerTurn(board, lex, wordList);
    wordList.mapAll(PrintString);
    
    HumanTurn(board, lex, wordList);
    wordList.mapAll(PrintString);
	return 0;
}

void PrintString(string key, string word) {
    cout << key << endl;
}

void InitBoard(Grid<cubeT> &board) {
    
    int k = 0;
    for (int i = 0; i < board.numRows(); i++) {
        for (int j = 0; j < board.numCols(); j++) {
            board[i][j].num = k++;
        }
    }
}

void Shake(Grid<cubeT> &board) {
    for (int i = 0; i < board.numRows(); i++) {
        for (int j = 0; j < board.numCols(); j++) {
            int randomRow = RandomInteger(i, board.numRows()-1);
            int randomCol = RandomInteger(j, board.numCols()-1);
            int temp = board[i][j].num;
            board[i][j].num = board[randomRow][randomCol].num;
            board[randomRow][randomCol].num = temp;
            temp = RandomInteger(0,5);
            board[i][j].letter = StandardCubes[board[i][j].num][temp];
            LabelCube(i, j, board[i][j].letter);
        }
    }
}

void HumanTurn(Grid<cubeT> &board, Lexicon &lex, Map<string> &wordList) {
    while (true) {
        cout << "Enter a word: ";
        string word = GetLine();
        if (word == "") break;
        word = ConvertToUpperCase(word);
        if (word.length() < MinLengthWord) {
            cout << "Word must have " << MinLengthWord << " or more characters." << endl;
        }
        else if (wordList.containsKey(word)) {
            cout << word + " has already played. Try again..." << endl;
        }
        else if (!lex.containsWord(word)) {
            cout << word + " is not in the lexicon. Try again..." << endl;
        }
        else if (!OnBoardHuman(board, word)) {
            cout << word + " can not be spelled with cubes. Try again..." << endl;
        }
        else {
            wordList.put(word,word);
            RecordWordForPlayer(word, Human);
        }
    }
}

struct pointT {
    int row;
    int col;
    pointT * next;
};

bool OffGrid(Grid<cubeT> & board, int row, int col) {
    return row < 0 || col < 0 || row >= board.numRows() ||
    col >= board.numCols();
}

bool HasVisited(int row, int col, pointT * tracker) {
    
    if (tracker->next != NULL) {
        if (tracker->next->row == row && tracker->next->col == col) {
            return true;
        }
        else {
            return HasVisited(row, col, tracker->next);
        }
    }
    return false;
}

bool HasVisitedComputer(int row, int col, pointT * tracker) {
    
    if (tracker != NULL) {
        if (tracker->row == row && tracker->col == col) {
            cout << "   HVC: r:c=" << row << ":" << col << " already visited." << endl;
            return true;
        }
        else {
            return HasVisitedComputer(row, col, tracker->next);
        }
    }
    cout << "   HVC: r:c=" << row << ":" << col << " not visited." << endl;
    return false;
}


void PrintLinkedList(pointT * list) {
    if (list == NULL) {
        return;
    }
    cout << list->row << ":" << list->col << endl;
    PrintLinkedList(list->next);
}

void ReVisitAndHightlight( pointT * tracker ) {
    if (tracker != NULL) {
        ReVisitAndHightlight(tracker->next);
        HighlightCube(tracker->row, tracker->col, true);
        Pause(0.25);
        HighlightCube(tracker->row, tracker->col, false);
        //Pause(0.25);
    }
}

void RecursiveScan(Grid<cubeT> & board, Lexicon &lex, Map<string> &wordList, string word, int row, int col, pointT * tracker);

void ComputerTurn(Grid<cubeT> &board, Lexicon &lex, Map<string> &wordList) {
    
    for (int i = 0; i < board.numRows(); i++) {
        for (int j = 0; j < board.numCols(); j++) {
            string word;
            word += board[i][j].letter; 
            pointT * tracker = new pointT;
            tracker->row = i;
            tracker->col = j;
            tracker->next = NULL;
            RecursiveScan(board, lex, wordList, word, i, j, tracker);
        }
    }
}

void RecursiveScan(Grid<cubeT> & board, Lexicon &lex, Map<string> &wordList, string word, int row, int col, pointT * tracker) {

    //PrintLinkedList(tracker);
    
    if (word.length() >= MinLengthWord && lex.containsWord(word) && !wordList.containsKey(word)) {  // BASE CASE: SUCCESS
        //PrintLinkedList(tracker);
        ReVisitAndHightlight(tracker);
        wordList.put(word,word);
        RecordWordForPlayer(word, Computer);
        cout << "---------------------- R4: WORD FOUND FOUND:" << word << " r:c=" << row << ":" << col << endl << endl;
    }
    
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (!(dx == 0 && dy == 0) && !OffGrid(board,row+dx,col+dy)) {
                cout << "R1: " << word << " r:c=" << row << ":" << col << " dx:dy=" << dx << ":" << dy << endl;
                if (lex.containsPrefix(word)) { // BASE CASE: FAIL FAST
                    cout << "  >>> TrackerList <<<" << endl;
                    PrintLinkedList(tracker);
                    cout << "Next: r+dx:c+dy=" << row+dx << ":" << col+dy << endl;
                    cout << "***********************" << endl;
                    if (word.length() > 1 && HasVisitedComputer(row+dx, col+dy, tracker)) {// BASE CASE: FAILED
                        cout << " R2: " << word << " r:c=" << row << ":" << col << " dx:dy=" << dx << ":" << dy << endl << endl << endl;
                        return;
                    }
                    else {
                        word += board[row+dx][col+dy].letter;
                        if (lex.containsPrefix(word)) { // BASE CASE: FAIL FAST
                            cout << "  R3: NEW WORD to search:" << word << " r:c=" << row << ":" << col << " dx:dy=" << dx << ":" << dy << endl;
                            
                            pointT * tracker2 = new pointT;
                            tracker2->next = tracker;       // tracker2 is now the listHead point back up the call chain
                            tracker2->row = row+dx;
                            tracker2->col = col+dy;
                            
                            RecursiveScan(board, lex, wordList, word, row+dx, col+dy, tracker2);
                        }
                    }
                }
            }
        }
    } 
}

bool RecursiveOnBoard(Grid<cubeT> & board, string soFar, string rest, int row, int col, pointT * tracker);

bool OnBoardHuman(Grid<cubeT> & board, string word) {
    string soFar;
    
    for (int i = 0; i < board.numRows(); i++) {
        for (int j = 0; j < board.numCols(); j++) {
            if (board[i][j].letter == word[0]) {
                pointT * tracker = new pointT;
                tracker->row = i;
                tracker->col = j;
                tracker->next = NULL;
                
                soFar += word[0];
                
                if (RecursiveOnBoard(board, soFar, word.substr(1), i, j, tracker)) return true;
            }
        }
    }
    return false;
}

bool RecursiveOnBoard(Grid<cubeT> & board, string soFar, string rest, int row, int col, pointT * tracker) {
    
    //PrintLinkedList(tracker);
    if (HasVisited(row, col, tracker)) // BASE CASE: FAILED
        return false;
    
    if (rest.length() == 0) { // BASE CASE: SUCCESS
        //PrintLinkedList(tracker);
        ReVisitAndHightlight(tracker);
        return true;
    }
    
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (!(dx == 0 && dy == 0) && !OffGrid(board,row+dx,col+dy)) {
                if (board[row+dx][col+dy].letter == rest[0]) {
                    pointT * tracker2 = new pointT;
                    tracker2->next = tracker;       // tracker2 is now the listHead point back up the call chain
                    tracker2->row = row+dx;
                    tracker2->col = col+dy;
                    
                    soFar += rest[0];
                    
                    if (RecursiveOnBoard(board, soFar, rest.substr(1), row+dx, col+dy, tracker2))
                        return true;
                }
            }
        }
    } 
    return false;
}



