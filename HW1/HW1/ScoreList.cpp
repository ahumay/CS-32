



#include "ScoreList.h"
#include <limits>


ScoreList::ScoreList() : m_scoreListSequence()
{
}// Create an empty score list.


bool ScoreList::add(unsigned long score)
{
    if (score > 100 || m_scoreListSequence.size() == DEFAULT_MAX_ITEMS)
        return false;
    m_scoreListSequence.insert(score);
    return true;
}
    // If the score is valid (a value from 0 to 100) and the score list
    // has room for it, add it to the score list and return true.
    // Otherwise, leave the score list unchanged and return false.


bool ScoreList::remove(unsigned long score)
{
    int a = m_scoreListSequence.find(score);
    if (a == -1)
        return false;
    m_scoreListSequence.erase(a);
    return true;
}
    // Remove one instance of the specified score from the score list.
    // Return true if a score was removed; otherwise false.
    
int ScoreList::size() const
{
    return m_scoreListSequence.size();
}// Return the number of scores in the list.
    
unsigned long ScoreList::minimum() const
{
    if (m_scoreListSequence.empty())
        return NO_SCORE;
    unsigned long a = 100;
    unsigned long b;
    for (int k = 0; k < m_scoreListSequence.size(); k++)
    {
        m_scoreListSequence.get(k, b);
        if (b < a)
            a = b;
    }
    return a;
}
    // Return the lowest score in the score list.  If the list is
    // empty, return NO_SCORE.
    
unsigned long ScoreList::maximum() const
{
    if (m_scoreListSequence.empty())
        return NO_SCORE;
    unsigned long a = 0;
    unsigned long b;
    for (int k = 0; k < m_scoreListSequence.size(); k++)
    {
        m_scoreListSequence.get(k, b);
        if (b > a)
            a = b;
    }
    return a;
}
    // Return the highest score in the score list.  If the list is
    // empty, return NO_SCORE.
    



