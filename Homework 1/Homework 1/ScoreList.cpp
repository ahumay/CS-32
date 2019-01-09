//
//  ScoreList.cpp
//  Homework 1
//
//  Created by Anthony on 1/19/17.
//  Copyright © 2017 CS32. All rights reserved.
//
/*
#include "ScoreList.h"

ScoreList::ScoreList() : scoreList() {
    // Create an empty score list.
}

bool ScoreList::add(unsigned long score){
    if(score >= 0 && score <= 100 && scoreList.size() != DEFAULT_MAX_ITEMS){
        scoreList.insert(score);
        return true;
    }
    return false;
}
// If the score is valid (a value from 0 to 100) and the score list
// has room for it, add it to the score list and return true.
// Otherwise, leave the score list unchanged and return false.

bool ScoreList::remove(unsigned long score){
    int i = -1;
    i = scoreList.find(score);
    scoreList.erase(i);
    if (i == -1){
        return -1;
    }
    return true;
}
// Remove one instance of the specified score from the score list.
// Return true if a score was removed; otherwise false.

int ScoreList::size() const{
    return scoreList.size();
}
// Return the number of scores in the list.

unsigned long ScoreList::minimum() const{
    if (scoreList.empty()){
        return NO_SCORE;
    }
    
    unsigned long min = 0;
    
    for (int i = 0; i < size(); i++){
        unsigned long temp = 0;
        scoreList.get(i, temp);
        if (temp < min){
            min = temp;
        }
    }
    
    return min;
}
// Return the lowest score in the score list.  If the list is
// empty, return NO_SCORE.

unsigned long ScoreList::maximum() const{
    if (scoreList.empty()){
        return NO_SCORE;
    }
    
    unsigned long max = 0;
    
    for (int i = 0; i < size(); i++){
        unsigned long temp = 0;
        scoreList.get(i, temp);
        if (temp >= max){
            max = temp;
        }
    }
    
    return max;
}
// Return the highest score in the score list.  If the list is
// empty, return NO_SCORE.
*/
