//
//  maze.cpp
//  Homework 3
//
//  Created by Anthony on 2/10/17.
//  Copyright © 2017 CS32. All rights reserved.
//

//#include <string>
//#include <stack>
//#include <iostream>
//using namespace std;

//bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec){

    Coord current(sr, sc); // set the current coordinate to the first spot

    //If the start location is equal to the ending location, then we've
    //solved the maze, so return true.
    if (current.r() == er && current.c() == ec){
        return true;
    }
    
    //Mark the start location as visted.
    maze[current.r()][current.c()] = '@';
    
    //For each of the four directions,
    //If the location one step in that direction (from the start location) is unvisited,
    //then call pathExists starting from that location (and ending at the same ending location as in the current call).
    // NORTH
    if (maze[current.r() - 1][current.c()] == '.' && maze[current.r() - 1][current.c()] != '@'){
        if (pathExists(maze, nRows - 1, nCols, current.r() - 1, current.c(), er, ec)){ //If that returned true,
            return true; //then return true.
        }
    }
    
    // EAST
    if (maze[current.r()][current.c() + 1] == '.' && maze[current.r()][current.c() + 1] != '@'){
        if (pathExists(maze, nRows, nCols + 1, current.r(), current.c() + 1, er, ec)){
            return true;
        }
    }
    
    // SOUTH
    if (maze[current.r() + 1][current.c()] == '.' && maze[current.r() + 1][current.c()] != '@'){
        if (pathExists(maze, nRows + 1, nCols, current.r() + 1, current.c(), er, ec)){
            return true;
        }
    }
    
    // WEST
    if (maze[current.r()][current.c() - 1] == '.' && maze[current.r()][current.c() - 1] != '@'){
        if (pathExists(maze, nRows, nCols - 1, current.r(), current.c() - 1, er, ec)){
            return true;
        }
    }
    
    return false;

//// WITHOUT CURRENT COORDINATE
//    
//    //If the start location is equal to the ending location, then we've
//    //solved the maze, so return true.
//    if (sr == er && sc == ec){
//        return true;
//    }
//    maze[sr][sc] = '@';     //Upadate the maze of new start coordinates
//
//    //Mark the start location as visted.
//    //    maze[current.r()][current.c()] = '@';
//    
//    //For each of the four directions,
//    //If the location one step in that direction (from the start location) is unvisited,
//    //then call pathExists starting from that location (and ending at the same ending location as in the current call).
//    // NORTH
//    if (sr != 0 && maze[sr - 1][sc] == '.' && maze[sr - 1][sc] != '@'){
//        if (pathExists(maze, nRows - 1, nCols, sr - 1, sc, er, ec)){ //If that returned true,
//            return true; //then return true.
//        }
//    }
//    
//    // EAST
//    if (sc != nCols && maze[sr][sc + 1] == '.' && maze[sr][sc + 1] != '@'){
//        if (pathExists(maze, nRows, nCols + 1, sr, sc + 1, er, ec)){
//            return true;
//        }
//    }
//    
//    // SOUTH
//    if (sr != nRows && maze[sr + 1][sc] == '.' && maze[sr + 1][sc] != '@'){
//        if (pathExists(maze, nRows + 1, nCols, sr + 1, sc, er, ec)){
//            return true;
//        }
//    }
//    
//    // WEST
//    if (sc != 0 && maze[sr][sc - 1] == '.' && maze[sr][sc - 1] != '@'){
//        if (pathExists(maze, nRows, nCols - 1, sr, sc - 1, er, ec)){
//            return true;
//        }
//    }
//
//
//    return false; //Return false.
}
