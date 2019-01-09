#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "Compiler.h"

/*
 
                       			 GRAPH OBJECT
                            		ACTOR
			ENERGY											pebbles    water pool    poison
 food     pheromones   anthills	 active
                                 ants    baby grasshoppers
                                         adult grasshoppers
 
 */

class StudentWorld;

class Actor : public GraphObject { // It must be derived from our GraphObject class
    int numma;
public:
//    Actor(int imgID, int x, int y, StudentWorld * studentWorld, Direction dir = right, int depth = 1);
    virtual void doSomething() = 0; // pure virtual
    bool getChecked(); // will let the init know that it's this actor has already done something this tick
    bool setChecked(bool v); // indicates checked
    bool getMovable(); // asks is it a pebble
    void setMovable(bool v); // used by pebble
    bool getAlive(); // asks if it is alive
    void setIsAlive(bool b); // used by active
    bool getEdible(); // asks can this be eaten
    void setEdible(bool b);
    bool getStunablePoisonable(); // asks can this be stunned
    void setStunablePoisonable(bool b);
    bool getBiteable(); // asks if this can be bitten
    void setBiteable(bool b);
    bool getCanDamage(); // asks if this can be damaged
    void setCanDamage(bool b);
    StudentWorld * getWorld(); // can't change the student world
private:
    StudentWorld * m_world;
    bool m_checked; // will be used to check every actor every tick
    bool m_isMoveable; // for pebbles
    bool m_isAlive; // to check if actor is alive
    bool m_isBiteable; // to check if actor is biteable
    bool m_isEdible; // to check if actor is edible
    bool m_isStunnable; // for the pools of water
    bool m_canDamage; // to check if actor can damage
    bool m_willMove; // precautionary for movement
    bool fuck;
};

// ENERGY SIDE
class Energy : public Actor {
public:
    Energy(int imgID, int x, int y, StudentWorld * studentWorld, Direction dir = right, int depth = 1);
    virtual void setEnergy(int num); // set the hit points
    virtual int getEnergy(); // get the hit points
    virtual void resetEnergy(); // set the hitpoints to zero
    virtual bool eat(int amt); // active actors and anthills all eat
    bool checkHitPoints(); // is it dead
private:
    int m_energy = 0;
};

class Anthill : public Energy {
public:
    Anthill(int colonyNum, Compiler * comp, int imgID, int x, int y, StudentWorld * studentWorld, Direction dir = right, int depth = 2);
    void doSomething();
    int getColonyNum(); // returns colony number
    ~Anthill(); // need to delete the compiler objects
private:
    int m_colNum;
    Compiler * m_compPtr;
};

class Pheromone : public Energy {
public:
    Pheromone(int colony, int imgID, int x, int y, StudentWorld * studentWorld, Direction dir = right, int depth = 2); // A Pheromone object must start out with a depth of 2.
    void doSomething();
    int getColonyNum(); // returns colony number
private:
    int m_pheromoneColNum;
};

class Food : public Energy {
public:
    Food(int imgID, int x, int y, StudentWorld * studentWorld, Direction dir = right, int depth = 1);
    void doSomething();
private:
};

class Active : public Energy {
public:
    Active(int imgID, int x, int y, StudentWorld * studentWorld, Direction dir = right, int depth = 1);
    void setRandomDir();
    void setSleepStunned(int sleep);
    int getSleepStunned();
    bool move(); // all actives move in a similar way
    void diedSoAddFood(int amt); // all active actors become food when they die
    bool beginContinue(); // all active actors must be checked the same way
    bool getDrowning();
    void setDrowning(bool set);
    bool bite(int dmg);
private:
    int m_isSleepStunned;
    bool m_isDrowning;
};

class Ant : public Active {
public:
    Ant(int xColony, int yColony, int antColonyNum, Compiler * comp, int imgID, int x, int y, StudentWorld * studentWorld, Direction dir = right, int depth = 1);
    void doSomething();
    int getColonyNum(); // returns colony number
    virtual bool eat(int amt); // the ant's own eat function, as it only eats from it's own food
    void setBitten(bool bit);
    void setBlocked(bool block);
    bool getBitten();
    bool getBlocked();
    void addPheromone(int IID = -1); // adds a pheromone, but it is optional for IID
    bool runCommand(Compiler::Command& c); // runs the command for the ant
private:
    int m_antColonyNum;
    int m_holdFood; // how much food it's holding
    int ic; // instruction counter
    Compiler * m_compPtr; // will be passed in from it's anthill
    bool m_justBitten;
    bool m_justBlocked;
    int m_xColony; // its colony coordinates
    int m_yColony;
    int m_lastNumber; // for last random number
};

class BabyGrasshopper : public Active { // has a move distance
public:
    BabyGrasshopper(int imgID, int x, int y, StudentWorld * studentWorld, Direction dir = right, int depth = 1);
    void doSomething();
    void setMoveDist(int move); // sets the distance the baby moves
    int getMoveDist(); // gets the distance the baby moves
private:
    int m_moveDist;
};

class AdultGrasshopper : public BabyGrasshopper { // inherits basic functionality
public:
    AdultGrasshopper(int imgID, int x, int y, StudentWorld * studentWorld, Direction dir = right, int depth = 1);
    void doSomething();
private:
};

// NON ENERGY SIDE
class Pebble : public Actor {
public:
    Pebble(int imgID, int x, int y, StudentWorld * studentWorld, Direction dir = right, int depth = 1);
    void doSomething();
};

class WaterPool : public Actor { // have a depth of 2
public:
    WaterPool(int imgID, int x, int y, StudentWorld * studentWorld, Direction dir = right, int depth = 2);
    void doSomething();
    void reverseWater(); // if the actor was stunned but is also asleep
};

class Poison : public Actor { // similar to water
public:
    Poison(int imgID, int x, int y, StudentWorld * studentWorld, Direction dir = right, int depth = 1);
    void doSomething();
};

#endif // ACTOR_H_
