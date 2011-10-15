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
void HumanTurn(Grid<cubeT> & board, Lexicon & lex);
bool OnBoard(Grid<cubeT> & board, string word);
void ComputerTurn(Grid<cubeT> & board, Lexicon & lex);

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
    
    DrawBoard(numRows, numCols);
    InitBoard(board);
    Shake(board);
    
    // TEST CODE
//    board[0][0].letter = 'D';
//    board[0][1].letter = 'E';
//    board[0][2].letter = 'A';
//    board[0][3].letter = 'R';
//    LabelCube(0, 0, 'D');
//    LabelCube(0, 1, 'E');
//    LabelCube(0, 2, 'A');
//    LabelCube(0, 3, 'R');

    HumanTurn(board, lex);
    ComputerTurn(board, lex);
       
	return 0;
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

void HumanTurn(Grid<cubeT> &board, Lexicon &lex) {
    Map<int> wordList;
    while (true) {
        cout << "Enter a word: ";
        string word = GetLine();
        if (word == "") break;
        word = ConvertToUpperCase(word);
        if (word.length() < 4) {
            cout << "Word must have 4 or more characters." << endl;
        }
        else if (wordList.containsKey(word)) {
            cout << word + " has already played. Try again..." << endl;
        }
        else if (!lex.containsWord(word)) {
            cout << word + " is not in the lexicon. Try again..." << endl;
        }
        else if (!OnBoard(board, word)) {
            cout << word + " can not be spelled with cubes. Try again..." << endl;
        }
        else {
            wordList.put(word,1);
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

bool RecursiveOnBoard(Grid<cubeT> & board, string soFar, string rest, int row, int col, pointT * tracker);

bool OnBoard(Grid<cubeT> & board, string word) {
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


void ReVisitAndHightlight( pointT * tracker ) {
    if (tracker != NULL) {
        
        HighlightCube(tracker->row, tracker->col, true);
        Pause(1.0);
        HighlightCube(tracker->row, tracker->col, false);
        ReVisitAndHightlight(tracker->next);
    }
}

bool RecursiveOnBoard(Grid<cubeT> & board, string soFar, string rest, int row, int col, pointT * tracker) {
    
    if (HasVisited(row, col, tracker)) return false;
    
    if (rest.length() == 0) {
        ReVisitAndHightlight(tracker);
        return true;
    }
    
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (!(dx == 0 && dy == 0) && !OffGrid(board,row+dx,col+dy)) {
                if (board[row+dx][col+dy].letter == rest[0]) {
                    pointT * tracker2 = new pointT;
                    tracker2->next = tracker;       // tracker2 is now the listHead point back up the call chain
                    tracker2->row = row;
                    tracker2->col = col;
                    
                    soFar += rest[0];
                    
                    if (RecursiveOnBoard(board, soFar, rest.substr(1), row+dx, col+dy, tracker2))
                        return true;
                }
            }
        }
    } 
    
    return false;
}

void ComputerTurn(Grid<cubeT> &board, Lexicon &lex) {
    
}

