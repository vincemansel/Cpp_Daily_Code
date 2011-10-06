//
//  mazeSolve.cpp
//  mazeGenSolve
//
//  Created by Vince Mansel on 10/5/11.
//  Copyright 2011 Wave Ocean Networks. All rights reserved.
//

#include <iostream>
#include "mazeSolve.h"

#include "simpio.h"
#include "queue.h"
#include "stack.h"

typedef Stack<pointT>  PathStackT;
typedef Queue<PathStackT> PathKeeperT;

bool IsSame(pointT goal, pointT current);
Vector<pointT> GetNeighbors(pointT current);
bool isAccessible(Maze &maze, pointT neighbor, pointT current, pointT previous);

void PrintPoint(pointT current) {
    cout << "Point:" << current.row << ":" << current.col << endl;
}

void PrintPath(PathStackT path) {
    cout << "Current Path" << endl;
    while (!path.isEmpty()) {
        PrintPoint(path.pop());
    }
}

void MarkPath(Maze &maze, PathStackT path) {
    //maze.draw();
    //cout << "Current Path" << endl;
    while (!path.isEmpty()) {
        maze.drawMark(path.pop(), "Red");
    }
}

void Solve(Maze &maze, GridOfCells &cells) {
    
    cout << "Solve: IN" << endl;
    
    PathKeeperT store;
    PathStackT paths;
    
    pointT previous;
    pointT current;
    pointT goal;
    
    previous.row = 0,
    previous.col = 0;
    
    current.row = 0,
    current.col = 0;
    
    goal.row = cells.numRows()-1;
    goal.col = cells.numCols()-1;
    
    paths.push(current);
    store.enqueue(paths);
    
    PathStackT currentPath;
    
    while (true) {
        
        //cout << " WHILE: TOP" << endl;
        if (store.isEmpty()) {
            cout << "Store is Empty" << endl;
            cout << "Previous current path:" << endl;
            //PrintPath(currentPath);
            break;
        }
        PathStackT path = store.dequeue();
        //PrintPath(path);
        currentPath = path;
        //MarkPath(maze, currentPath);
        current = path.pop();
        
        //PrintPoint(current);
        //PrintPoint(goal);
        
        if (IsSame(goal, current)) {
            cout << "Reached Goal" << endl;
            MarkPath(maze, currentPath);
            break;
        }
        
        if (!path.isEmpty()) {
            previous = path.pop();
        }
        
        Vector<pointT> neighborList = GetNeighbors(current);
        for (int i = 0; i < neighborList.size(); i++) {
            pointT neighbor = neighborList[i];
            //cout << "  FOR NEIGHBORS: " ;
            //PrintPoint(neighbor);
            if (isAccessible(maze, neighbor, current, previous)) {
                PathStackT newPath = currentPath;
                newPath.push(neighbor);
                store.enqueue(newPath);
                //cout << "   ENQUEUE: ";
                //PrintPath(newPath);
                //MarkPath(newPath);
            }
        }
        //cout << " WHILE: BOTTOM" << endl;
        //sleep(1);
        //GetLine();
    }
    
    cout << "Solve: OUT" << endl;
}

bool IsSame(pointT goal, pointT current) {
    bool result = false;
    
    if (goal.row == current.row && goal.col == current.col) {
        result = true;
    }
    return result;
}

Vector<pointT> GetNeighbors(pointT current) {
    Vector<pointT> neighborList;
    pointT next;
    
    next.row = current.row;
    next.col = current.col-1;
    neighborList.add(next);
    
    next.col = current.col+1;
    neighborList.add(next);

    next.row = current.row-1;
    next.col = current.col;
    neighborList.add(next);

    next.row = current.row+1;
    neighborList.add(next);
    
    return neighborList;
}

bool isAccessible(Maze &maze, pointT neighbor, pointT current, pointT previous) {
    bool result = false;
    
    if (maze.pointInBounds(neighbor) && !maze.isWall(current,neighbor) && !IsSame(previous, neighbor)) {
        result = true;
    }
    return result;
}


