/*
 * File: life.cpp
 * --------------
 * Your name and comments go here!
 */
 
#include "genlib.h"
#include "extgraph.h"
#include "simpio.h"
#include "strutils.h"
#include "random.h"
#include "grid.h"
#include "lifeGraphics.h"
#include "vector.h"

#include <iostream>
#include <fstream>

const bool TEST_MODE = true;
const bool TEST_RANDOM= false;
const int TEST_SPEED = 4;
const int TEST_SIM = 0;
//const string TEST_FILE = "simplebar";
const string TEST_FILE = "Snowflake";

const int MAX_ROW = 70;
const int MAX_COL = 90;

struct gridSizeT {
    int row;
    int col;
};

struct gridLifeT {
    gridSizeT size;
    Grid<int> lifeGrid;
};

void Welcome();
bool AskForFile();
bool AskForYesOrNo(string messageOut);

gridLifeT GridStart(bool isGetFile);
gridLifeT GetGridFromFile(ifstream &in1);
void DrawGrid(gridLifeT &gridLife);
void UpdateGrid(gridLifeT &gridLife);
void GetOneRow(string line, Grid<int> &theGrid, int currentRow);
gridLifeT GenerateRandomGrid();
int GetSimSpeed();
int GetSimMode();
void RunLifeSim(int simSpeed, int simMode, gridLifeT &gridLife);

int main()
{
	SetWindowTitle("Life!");
	InitGraphics();
	Welcome();
    while (true) {
        gridLifeT gridLife = GridStart(AskForFile());
        if (TEST_MODE) {
            RunLifeSim(TEST_SPEED, TEST_SIM, gridLife);
        }
        else {
            RunLifeSim(GetSimSpeed(), GetSimMode(), gridLife);
        }
        bool anotherGame = AskForYesOrNo("Would you like to run another simulation? ");
        if (!anotherGame) {
            if (!TEST_MODE) break;
        }
    }
	return 0;
}

void Welcome()
{
	SetPointSize(48);
	MovePen(GetWindowWidth()/2-TextStringWidth("Welcome To Life!")/2,GetWindowHeight()/2);
	DrawTextString("Welcome To Life!");
	UpdateDisplay();
	cout << "Welcome to the game of Life, a simulation of the lifecycle of a bacteria colony." << endl;
	cout << "Cells live and die by the following rules:" << endl;
	cout << "\tA cell with 1 or fewer neighbors dies of loneliness" << endl;
	cout << "\tLocations with 2 neighbors remain stable" << endl;
	cout << "\tLocations with 3 neighbors will spontaneously create life" << endl;
	cout << "\tLocations with 4 or more neighbors die of overcrowding" << endl;
	cout << "In the animation, new cells are dark and lighten as they age." << endl;
	cout << "Hit RETURN when ready: ";
	//GetLine();
}

bool AskForFile() {
    cout << "You can start your colony from random cells or read from a prepared file." << endl;
    return AskForYesOrNo("Do you have a starting file in mind? ");
}

bool AskForYesOrNo(string messageOut) {
    bool result = false;
    while (true) {
        cout << messageOut;
        string line;
        if (!TEST_MODE)
            line = ConvertToLowerCase(GetLine());
        else {
            if (TEST_RANDOM) {
                line = "no";
                cout << "TEST_MODE: Answer is no" << endl;
            }
            else {
                line = "yes";
                cout << "TEST_MODE: Answer is yes" << endl;
            }
        }
        if (line[0] == 'y') {
            result = true;
            break;
        }
        else if (line[0] == 'n') {
            break;
        }
        else {
            cout << "Please answer yes or no." << endl;
        }
    }
    
    return result;
}

gridLifeT GridStart(bool isGetFile) {
    gridLifeT gridLife;
    
    if (isGetFile) {
        while (true) {
            cout << "Please enter the filename: ";
            string filename;
            if (!TEST_MODE)
                filename = GetLine();
            else {
                filename = TEST_FILE;
                cout << "TEST_MODE: filename is " <<  TEST_FILE << endl;
            }
            ifstream in1;
            in1.open(filename.c_str());
            if (in1.fail()) {
                cout << "Unable to open the file named " << filename << ".  Please try again." << endl;
                in1.clear();
            }
            else {
                gridLife = GetGridFromFile(in1);
                DrawGrid(gridLife);
                in1.close();
                break;
            }
        }
    }
    else {
        gridLife = GenerateRandomGrid();
        DrawGrid(gridLife);
    }
    return gridLife;
}

gridLifeT GetGridFromFile(ifstream &in1) {
    gridLifeT gridLife;
    Grid<int> theGrid;
    gridSizeT gridSize;
    bool gotRow = false;
    int currentRow = 0;
    
    //cout << "Got a good file name" << endl;
    
    while (true) {
        string line;
        getline(in1,line);
        if (in1.fail()) {
            break;
        }
        if (line[0] == 'X' || line[0] == '-')  { // Parse for Grid
            GetOneRow(line, theGrid, currentRow);
            currentRow += 1;
        }
        else if (line[0] == '#') { // Ignore comments
            
        }
        else { // Assume well-formed file (no error checking)
            int param = StringToInteger(line);
            if (gotRow) {
                gridSize.col = param;
                theGrid.resize(gridSize.row, gridSize.col);
            }
            else {
                gridSize.row = param;
                gotRow = true;
            }
        }
    }
    
    gridLife.lifeGrid = theGrid;
    gridLife.size = gridSize;
    return gridLife;
}

void GetOneRow(string line, Grid<int> &theGrid, int currentRow) {
    int numCols = theGrid.numCols();
    
    for (int i = 0; i < numCols; i++) {
        int age = 0;
        if (line[i] == 'X') {
            age = 1;
        }
        theGrid[currentRow][i] = age;
    }
}

void DrawGrid(gridLifeT &gridLife) {
    InitLifeGraphics(gridLife.size.row, gridLife.size.col);
    for (int i = 0; i < gridLife.size.row; i++)
        for (int j = 0; j < gridLife.size.col; j++)
            DrawCellAt(i, j, gridLife.lifeGrid.getAt(i,j));
    UpdateDisplay();
}

void UpdateGrid(gridLifeT &gridLife) {
    gridLifeT gridLife2 = gridLife;
}

gridLifeT GenerateRandomGrid() {
    gridLifeT gridLife;
    gridSizeT gridSize;
    
    cout << "Random Grid Generation." << endl;
    
    gridSize.row = MAX_ROW;
    gridSize.col = MAX_COL;
    gridLife.size = gridSize;
    gridLife.lifeGrid.resize(MAX_ROW, MAX_COL);
    
    for (int i = 0; i < gridLife.size.row; i++) {
        for (int j = 0; j < gridLife.size.col; j++)
            gridLife.lifeGrid[i][j] = RandomInteger(0, 12);
    }
    
    return gridLife;
}

void PrintString(string message) {
    cout << "    " << message << endl;
}

int isMatch(char choice, Vector<char> userChoice) {
    int feedback = -1;
    for (int i = 0; i < userChoice.size(); i++) {
        if (choice == userChoice[i]) {
            feedback = i;
            break;
        }
    }
    return feedback;
}

/*
 * This is a generic choice request function.
 * Returns the user feedback  as an integer (0 to N-1) for N elements,
 * regardless if the choice is alpha or numeric.
 */

int AskForChoice(string messageOut, Vector<string> choices) {
    int userFeedback = 0;
    Vector<char> userChoice;
    cout << endl;
    cout << messageOut << endl;
    choices.mapAll(PrintString);
    
    for (int i = 0; i < choices.size(); i++) { // Generate the choices to compare against user input,
                                                // which is the first character of the choices string
        userChoice.add(choices[i][0]);
        //cout << "AskForChoice: " << choices[i][0] << endl;
    }
    bool isInt = false;
    
    if (isdigit(userChoice[0])) {
        isInt = true;
    }

    while (true) {
        cout << "Your choice: ";
        if (isInt) {
            userFeedback = GetInteger();
            int comp1 = userChoice[0] - '0';
            int comp2 = userChoice[userChoice.size()-1] - '0';
            if (userFeedback < comp1 || userFeedback > comp2) {
                cout << "Acceptable answers are " << comp1 << " to " << comp2 << "!" << endl;
            }
            else {
                break;
            }
        }
        else {
            //cout << "Stub for Alpha choices..." << endl;
            string feedback = GetLine();
            feedback = ConvertToUpperCase(feedback);
            if ((userFeedback = isMatch(feedback[0], userChoice)) == -1) {
                cout << "Acceptable answers are ";
                for (int i = 0; i < userChoice.size() - 1; i++)
                    cout << userChoice[i] << ", ";
                cout << " or " << userChoice[userChoice.size()-1];
                cout << "!" << endl;
            }
            else {
                break;
            }
        }
    }
    
    return userFeedback;
}

int GetSimSpeed() {
    //cout << "Stub for GetSimSpeed()" << endl;
    string messageOut = "You choose how fast to run the simulation.";
	Vector<string> choices;
    choices.add("1 = Ludicrous Speed!");
	choices.add("2 = Ow, my eyes hurt. Kick it back a notch.");
	choices.add("3 = That \"tortoise\" setting on your lawn mower.");
	choices.add("4 = PowerPoint mode");
    return AskForChoice(messageOut, choices);
}

int GetSimMode() {
    //cout << "Stub for GetSimMode()" << endl;
    string messageOut = "You choose how cells on the edges will count their neighbors.";
    Vector<string> choices;
	choices.add("P = Plateau Mode (cells on edges just have fewer neighbors)");
	choices.add("D = Donut Mode (cells on edges wrap around to find neighbors)");
	choices.add("M = Mirror Mode (cells on edge reflect back to find neighbors)");
    return AskForChoice(messageOut, choices);
}

void PrintCell(int point) {
    cout << point;
}

void RunLifeSim(int simSpeed, int simMode, gridLifeT &gridLife) {
    cout << "Stub for RunLifeSim(" << simSpeed << ", " << simMode << ", GRID= " << gridLife.size.row << ":" << gridLife.size.col << ")" << endl;
    cout << endl;
    
    //Click and hold the mouse button on the graphics window to end the simulation.
    
    //RETURN to continue (or "quit" to end simulation): 
    
}


void RunLifeSim2(int simSpeed, int simMode, gridLifeT &gridLife) {
    cout << "Stub for RunLifeSim(" << simSpeed << ", " << simMode << ", GRID= " << gridLife.size.row << ":" << gridLife.size.col << ")" << endl;
    //gridLife.lifeGrid.mapAll(PrintCell);
    cout << endl;
    for (int i = 0; i < gridLife.size.row; i++) {
        for (int j = 0; j < gridLife.size.col; j++)
            cout << gridLife.lifeGrid[i][j];
        cout << endl;
    }
    
    //InitLifeGraphics(gridLife.size.row, gridLife.size.col);
    
}



