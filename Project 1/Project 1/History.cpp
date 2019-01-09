

#include "History.h"
#include <iostream>
using namespace std;

History::History(int nRows, int nCols)
{
    for (int k = 1; k <= nRows; k++)
    {
        for (int i = 1; i <= nCols; i++)
        {
            ratPoisons[k][i] = '.';//set each position to start at 0 rats poisoned aka '.'
        }
    }
    
    m_rows = nRows;//set the history size to the same as the corresponding arena
    m_cols = nCols;
}

bool History::record(int r, int c)
{
    if (r <= 0 || r > m_rows || c <= 0 || c > m_cols)//check if the position whose history is requested is a valid postion in the arena
    {
        return false;
    }
    
    if (ratPoisons[r][c] >= 'A')//check if position has poisoned one or more rats
    {
        if (ratPoisons[r][c] == 'Z')//if it has poisoned 25 or more rats then return true and print 'Z'
        {
            return true;
        }
        else
        {
            ratPoisons[r][c]++;//if position has poisoned one or more rats then increment letter
        	return true;
        }
    }
    else
    {
    	ratPoisons[r][c] = 'A';//if no rats have been poisoned on this position yet then set symbol to 'A'
    	return true;
    }
}

void History::display() const
{
    clearScreen();
    for (int k = 1; k <= m_rows; k++)
    {
        for (int i = 1; i <= m_cols; i++)
        {
            cout << ratPoisons[k][i];//go through each position in arena and print out character representing amount of rats that have been poisoned there
        }
        cout << endl;
    }
    for (int k = 1; k <= m_rows; k++)
    {
        for (int i = 1; i <= m_cols; i++)
        {
        }
    }
    cout << endl;
}

