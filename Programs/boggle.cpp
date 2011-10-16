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
#include "set.h"

struct cubeT {
    int num;
    char letter;
};

struct pointT {
    int row;
    int col;
    pointT * next;
};

const int MinLengthWord = 4;
const double HighlightSpeedComputer = 0.01;
const double HighlightSpeedHuman = 0.25;

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
//void HumanTurn(Grid<cubeT> & board, Lexicon & lex, Map<string> &wordList);
void HumanTurn(Grid<cubeT> & board, Lexicon & lex, Set<string> &wordSet);
bool OnBoardHuman(Grid<cubeT> & board, string word);
//void ComputerTurn(Grid<cubeT> & board, Lexicon & lex, Map<string> &wordList);
void ComputerTurn(Grid<cubeT> & board, Lexicon & lex, Set<string> &wordSet);
void PrintString(string word);
void PrintString(string key, string word);
//Map<string> DivideLists(Map<string> wordList1, Map<string> wordList2);

pointT * ExtendTracker(pointT *  tracker, int row, int col);
bool RecursiveHuman(Grid<cubeT> & board, string soFar, string rest, int row, int col, pointT * tracker);
void RecursiveComputer(Grid<cubeT> & board, Lexicon &lex, Set<string> &wordSet, string word, int row, int col, pointT * tracker);

int main()
{
    Randomize();
	SetWindowSize(9, 10);
	
	Welcome();
	GiveInstructions();
    
    Lexicon lex("lexicon.dat");
    
    while (true) {
        int numRows;
        int numCols;
        
        while (true) {
            cout << "Which Boggle would you like to play (Big, Little)?: ";
            string line = GetLine();
            line = ConvertToLowerCase(line);
            if (line == "big" || line == "b") {
                numRows = 5;
                numCols = 5;
                break;
            }
            else if (line == "little" || line == "l") {
                numRows = 4;
                numCols = 4;
                break;
            }
            else {
                cout << "Try again... " << endl;
            }
        }
        
        InitGraphics();
        Grid<cubeT> board(numRows, numCols);
        Set<string> wordSet;
        
        DrawBoard(numRows, numCols);
        InitBoard(board);
        Shake(board);
        
        HumanTurn(board, lex, wordSet);   
        
        //    Set<string> wordSet1 = wordSet;
        ComputerTurn(board, lex, wordSet);
        
        //    cout << "Combined List" << endl;
        //    wordSet.mapAll(PrintString);
        //    
        //    cout << endl << "Human List" << endl;
        //    wordSet1.mapAll(PrintString);
        //
        //    wordSet.subtract(wordSet1);
        //    cout << endl << "Computer List" << endl;
        //    wordSet.mapAll(PrintString);
        
        cout << "Would you like to play again? (y,n): ";
        if (GetLine()[0] == 'n') break;
    }
    
	return 0;
}

void PrintString(string word) {
    cout << word << endl;
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

void HumanTurn(Grid<cubeT> &board, Lexicon &lex, Set<string> &wordSet) {
    while (true) {
        cout << "Enter a word: ";
        string word = GetLine();
        if (word == "") {
            cout << "Are you sure? (y or n): ";
            if (GetLine()[0] == 'y') break;
        }
        word = ConvertToUpperCase(word);
        if (word.length() < MinLengthWord) {
            cout << "Word must have " << MinLengthWord << " or more characters." << endl;
        }
        else if (wordSet.contains(word)) {
            cout << word + " has already played. Try again..." << endl;
        }
        else if (!lex.containsWord(word)) {
            cout << word + " is not in the lexicon. Try again..." << endl;
        }
        else if (!OnBoardHuman(board, word)) {
            cout << word + " can not be spelled with cubes. Try again..." << endl;
        }
        else {
            wordSet.add(word);
            RecordWordForPlayer(word, Human);
        }
    }
}

bool OffGrid(Grid<cubeT> & board, int row, int col) {
    return row < 0 || col < 0 || row >= board.numRows() ||
    col >= board.numCols();
}

bool HasVisited(int row, int col, pointT * tracker) {
    
    if (tracker != NULL && tracker->next != NULL) {
        if (tracker->next->row == row && tracker->next->col == col) {
            return true;
        }
        else {
            return HasVisited(row, col, tracker->next);
        }
    }
    return false;
}

void PrintLinkedList(pointT * list) {
    if (list == NULL) {
        return;
    }
    cout << list->row << ":" << list->col << endl;
    PrintLinkedList(list->next);
}

void ReVisitAndHightlight(pointT * tracker, playerT player) {
    double speed = HighlightSpeedComputer;
    if (player == Human) {
        speed = HighlightSpeedHuman;
    }
    if (tracker != NULL) {
        ReVisitAndHightlight(tracker->next, player);
        HighlightCube(tracker->row, tracker->col, true);
        Pause(speed);
        HighlightCube(tracker->row, tracker->col, false);
    }
}

void ComputerTurn(Grid<cubeT> &board, Lexicon &lex, Set<string> &wordSet) {
    
    for (int i = 0; i < board.numRows(); i++) {
        for (int j = 0; j < board.numCols(); j++) {
            string word;
            word += board[i][j].letter; 
            pointT * tracker = ExtendTracker(NULL, i, j);
            RecursiveComputer(board, lex, wordSet, word, i, j, tracker);
        }
    }
}

void RecursiveComputer(Grid<cubeT> & board, Lexicon &lex, Set<string> &wordSet, string word, int row, int col, pointT * tracker) {

    if (word.length() >= MinLengthWord && lex.containsWord(word) && !wordSet.contains(word)) { // BASE CASE: SUCCESS
        wordSet.add(word);
        ReVisitAndHightlight(tracker, Computer);
        RecordWordForPlayer(word, Computer);
        // Don't return yet: allows for search for plurals, compound words and extended words
    }
    
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (!(dx == 0 && dy == 0) && !OffGrid(board,row+dx,col+dy)) {
                string tempWord = word + board[row+dx][col+dy].letter;  // This is key! tempWord does not allow mispellings.
                pointT * tracker2 = ExtendTracker(tracker, row+dx, col+dy);
                if (HasVisited(row+dx, col+dy, tracker2)) // BASE CASE: FAILED
                    continue;
                if (!lex.containsPrefix(tempWord)) // BASE CASE: FAILED
                    continue;
                RecursiveComputer(board, lex, wordSet, tempWord, row+dx, col+dy, tracker2);
            }
        }
    }
}

bool OnBoardHuman(Grid<cubeT> & board, string word) {
    string soFar;
    
    for (int i = 0; i < board.numRows(); i++) {
        for (int j = 0; j < board.numCols(); j++) {
            if (board[i][j].letter == word[0]) {
                pointT * tracker = ExtendTracker(NULL, i, j);
                soFar += word[0];
                if (RecursiveHuman(board, soFar, word.substr(1), i, j, tracker)) return true;
            }
        }
    }
    return false;
}

bool RecursiveHuman(Grid<cubeT> & board, string soFar, string rest, int row, int col, pointT * tracker) {    
    if (HasVisited(row, col, tracker)) // BASE CASE: FAILED
        return false;
    
    if (rest.length() == 0) { // BASE CASE: SUCCESS
        ReVisitAndHightlight(tracker, Human);
        return true;
    }
    
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (!(dx == 0 && dy == 0) && !OffGrid(board,row+dx,col+dy)) {
                if (board[row+dx][col+dy].letter == rest[0]) {
                    pointT * tracker2 = ExtendTracker(tracker, row+dx, col+dy);
                    soFar += rest[0];
                    if (RecursiveHuman(board, soFar, rest.substr(1), row+dx, col+dy, tracker2))
                        return true;
                }
            }
        }
    } 
    return false;
}

pointT * ExtendTracker(pointT *  tracker, int row, int col) {
    pointT * tracker2 = new pointT;
    tracker2->next = tracker;       // tracker2 is now the listHead and points back up the call chain
    tracker2->row = row;
    tracker2->col = col;
    return tracker2;
}

// TODO: Delete these utility functions when wordSet implemented.
Set<string> MapToSet(Map<string> wordList) {
    Map<string>::Iterator itr = wordList.iterator();
    Set<string> wordSet;
    
    while(itr.hasNext())
        wordSet.add(itr.next());
    
    return wordSet;
}

Map<string> SetToMap(Set<string> wordSet1) {
    
    Set<string>::Iterator itr = wordSet1.iterator();
    Map<string> wordList;
    
    while(itr.hasNext()) {
        string word = itr.next();
        wordList.add(word, word);
    }
    
    return wordList; 
}

Map<string> DivideLists(Map<string> wordList1, Map<string> wordList2) {
    Set<string> wordSet1 = MapToSet(wordList1);
    Set<string> wordSet2 = MapToSet(wordList2);
    
    wordSet1.subtract(wordSet2);
    
    return SetToMap(wordSet1);
}

void PrintString(string key, string word) {
    cout << key << endl;
}

void testOnly() {
// TEST CODE

//    int k = 0;
//    for (int i = 0; i < 4; i++) {
//        for (int j = 0; j < 4; j++) {
//            board[i][j].letter = IntegerToString(k)[0];
//            LabelCube(i, j, IntegerToString(k++)[0]);
//            if (k > 9) k = 0;
//        }
//    }

//    board[1][3].letter = 'F';
//    board[0][2].letter = 'O';
//    board[0][1].letter = 'U';
//    board[0][3].letter = 'R';
//    LabelCube(1, 3, 'F');
//    LabelCube(0, 2, 'O');
//    LabelCube(0, 1, 'U');
//    LabelCube(0, 3, 'R');

//    board[0][0].letter = 'F';
//    board[0][1].letter = 'O';
//    board[0][2].letter = 'U';
//    board[0][3].letter = 'R';
//    LabelCube(0, 0, 'F');
//    LabelCube(0, 1, 'O');
//    LabelCube(0, 2, 'U');
//    LabelCube(0, 3, 'R');

//    board[1][1].letter = 'N';
//    board[2][1].letter = 'E';
//    board[3][2].letter = 'A';
//    board[3][3].letter = 'R';
//    board[2][2].letter = 'E';
//    board[1][2].letter = 'S';
//    board[0][3].letter = 'T';

//    LabelCube(1, 1, 'N');
//    LabelCube(2, 1, 'E');
//    LabelCube(3, 2, 'A');
//    LabelCube(3, 3, 'R');
//    LabelCube(2, 2, 'E');
//    LabelCube(1, 2, 'S');
//    LabelCube(0, 3, 'T');
    
}

