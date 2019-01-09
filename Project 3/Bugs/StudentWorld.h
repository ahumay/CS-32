#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp
class Actor;

class StudentWorld : public GameWorld
{
public:
    // DESTRUCTOR
    ~StudentWorld();

    // CONSTRUCTOR
    StudentWorld(std::string assetDir) : GameWorld(assetDir) {}
    
    // DISPLAY
    int getWinner(); // will calculate the winner

    std::string setText(); // will set text
    
    std::string format(int ticks, int * numbers, std::string * names, int winner, int active);
    	
    // INITALIZATION
    void addObjectToSimulation(Actor * act);

    virtual int init();
    
    virtual int move();

    virtual void cleanUp();
    
    // ADDING AND FINDING
    bool isRock(int x, int y); // check for a rock, make sure it's const
    
    void add(int x, int y, Actor * a); // add the actor to the x, y
    
    Actor * getFood(int x, int y);
    
    Actor * getRandomInsect(int x, int y, Actor * act, int colony = 999);
    
    void addAnts(int colony, int add); // used for adding ants to a particular colony
    
    int getNumberofAnts(int colony); // used for updating display text
    
    void addObjectToSimulation(int colonyNum, Compiler * com);
    
    Actor * getPheromone(Ant * a);
    
    void stunActors(int x, int y); // will stun actors
    
    void poisonActors(int x, int y); // will poison actors
    
    bool findDangerous(Ant * a);

    bool isPheromone(Ant * a);
    
private:
//    std::vector<Actor*> m_ActorList;
    std::vector<Actor *> m_ActorList [VIEW_WIDTH][VIEW_HEIGHT]; // 2D array of vectors of pointers to actors
    int ticks = 2000; // ticks start at 2000
    // for anthill to keep track of the number of ants each colony has:
    int m_coordinatesX[4], m_coordinatesY[4]; // x and y coordinates
    bool alreadyAteTracker; // will help keep track of recent moves
    bool alreadyPoisonedTracker; // will help keep track of recent moves
    bool alreadyStunnedTracker; // will help keep track of recent moves
    bool alreadySleptTracker; // will help keep track of recent moves
    int m_antHillNum[4]; // the total number of ants stored in an array
    std::string m_antHillNames[4]; // the names of the anthills stored in an array
    std::vector<std::string> m_fileNames; // to hold the names
    int m_winningAnt; // index of winning ant
    int m_active = 0;
};

#endif // STUDENTWORLD_H_
