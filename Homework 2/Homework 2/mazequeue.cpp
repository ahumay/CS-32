////
////  mazequeue.cpp
////  Homework 2
////
////  Created by Anthony on 2/3/17.
////  Copyright © 2017 CS32. All rights reserved.
////
//
//#include <queue>
//#include <string>
//#include <iostream>
//using namespace std;
//
//bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);
//
////
int main()
{
    queue<Coord> coordQueue;    // declare a queue of Coords
    
    Coord a(5,6);
    coordQueue.push(a);            // enqueue item at back of queue
    coordQueue.push(Coord(3,4));   // enqueue item at back of queue
    ...
    Coord b = coordQueue.front();  // look at front item
    coordQueue.pop();              // remove the front item from queue
    if (coordQueue.empty())        // Is the queue empty?
        cout << "empty!" << endl;
    cout << coordQueue.size() << endl;  // number of elements
}

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
    // Return true if there is a path from (sr,sc) to (er,ec)
    // through the maze; return false otherwise
    queue<Coord> possible;
    
    maze[sr][sc] = '@'; // the first coordinate is occupied
    Coord current(sr, sc); // set the current coordinate to the first spot
    possible.push(current);
    
    while (!possible.empty()){
        current = possible.front();
        cerr << "Row: " << possible.front().r() << " | Column: " << possible.front().c() << endl;
        possible.pop();
        
        if (current.r() == er && current.c() == ec){
            return true;
        }
        //        If the current (r,c) coordinate is equal to the ending coordinate,
        //        then we've solved the maze so return true!
        
        if (maze[current.r() - 1][current.c()] == '.' && maze[current.r() - 1][current.c()] != '@'){
            Coord added(current.r() - 1, current.c());
            maze[current.r() - 1][current.c()] = '@';
            possible.push(added);
        }
        //        If you can move NORTH and haven't encountered that cell yet,
        //        then push the coordinate (r-1,c) onto the stack and update
        //        maze[r-1][c] to indicate the algorithm has encountered it.
        
        if (maze[current.r()][current.c() + 1] == '.' && maze[current.r()][current.c() + 1] != '@'){
            Coord added(current.r(), current.c() + 1);
            maze[current.r()][current.c() + 1] = '@';
            possible.push(added);
        }
        //        If you can move EAST and haven't encountered that cell yet,
        //        then push the coordinate (r,c+1) onto the stack and update
        //        maze[r][c+1] to indicate the algorithm has encountered it.
        
        if (maze[current.r() + 1][current.c()] == '.' && maze[current.r() + 1][current.c()] != '@'){
            Coord added(current.r() + 1, current.c());
            maze[current.r() + 1][current.c()] = '@';
            possible.push(added);
        }
        //        If you can move SOUTH and haven't encountered that cell yet,
        //        then push the coordinate (r+1,c) onto the stack and update
        //        maze[r+1][c] to indicate the algorithm has encountered it.
        
        if (maze[current.r()][current.c() - 1] == '.' && maze[current.r()][current.c() - 1] != '@'){
            Coord added(current.r(), current.c() - 1);
            maze[current.r()][current.c() - 1] = '@';
            possible.push(added);
        }
        //        If you can move WEST and haven't encountered that cell yet,
        //        then push the coordinate (r,c-1) onto the stack and update
        //        maze[r][c-1] to indicate the algorithm has encountered it.
    }
    
    return false; //There was no solution, so return false
}

int main()
{
    string maze[10] = {
        "XXXXXXXXXX",
        "X........X",
        "XX.X.XXXXX",
        "X..X.X...X",
        "X..X...X.X",
        "XXXX.XXX.X",
        "X.X....XXX",
        "X..XX.XX.X",
        "X...X....X",
        "XXXXXXXXXX"
    };
    
    if (pathExists(maze, 10,10, 6,4, 1,1))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}
