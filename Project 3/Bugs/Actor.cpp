#include "Actor.h"
//#include "StudentWorld.h"
//#include <cmath>
#include "Compiler.h"

/*
 
 										GRAPH OBJECT
 										ACTOR
 			ENERGY											pebbles   water pool    poison
 food     pheromones   anthills	 active
                                 ants    baby grasshoppers
                                         adult grasshoppers
 
 */

//ACTOR
//Actor::Actor(int imgID, int x, int y, StudentWorld * studentWorld, Direction dir, int depth) : GraphObject(imgID, x, y){
//    m_world = studentWorld; // every object should know what world it's in
//    m_isMoveable = true; // all objects are auto created to move
//    m_isAlive = true; // all objects are auto created to be alive
//    m_isBiteable = false; // all objects are auto created to NOT be biteable
//    m_isEdible = false; // all objects are auto created to NOT be edible
//    m_isStunnable = false; // for the pools of water
//    m_canDamage = false; // all objects are auto created to NOT be capapble of damaging
//    m_checked = false;
//}

void Actor::doSomething(){}

// GETTERS AND SETTERS
bool Actor::getCanDamage(){ // asks if this can be damaged
    fuck = true;
    return m_canDamage;
}

void Actor::setCanDamage(bool b){
    m_canDamage = b;
}

bool Actor::getChecked(){ // will let the init know that it's this actor has already done something this tick
    return m_checked;
}

bool Actor::setChecked(bool v){ // indicates checked
    m_checked = v;
    return true;
}

bool Actor::getAlive(){ // asks if it is alive
    return m_isAlive;
}

bool Actor::getEdible(){ // asks can this be eaten
    return m_isEdible;
}

StudentWorld * Actor::getWorld(){
    return m_world;
}

void Actor::setIsAlive(bool b){ // used by active
    m_isAlive = b;
}

void Actor::setEdible(bool b){
    m_isEdible = b;
}

bool Actor::getMovable(){ // asks is it a pebble
    return m_isMoveable;
}

void Actor::setMovable(bool v){ // used by pebble
    m_isMoveable = v;
}

bool Actor::getStunablePoisonable(){ // asks can this be stunned
    return m_isStunnable;
}

void Actor::setStunablePoisonable(bool b){
    m_isStunnable = b;
}

bool Actor::getBiteable(){ // asks if this can be bitten
    return m_isBiteable;
}

void Actor::setBiteable(bool b){
	m_isBiteable = b;
}

// ENERGY
Energy::Energy(int imgID, int x, int y, StudentWorld * studentWorld, Direction dir, int depth) : Actor(imgID, x, y, studentWorld){
}

void Energy::setEnergy(int num){ // changes the hitpoints for an actor
    m_energy = num;
}

int Energy::getEnergy(){ // returns hit points (energy)
    return m_energy;
}

void Energy::resetEnergy(){ // changes energy to zero
    m_energy = 0;
}

bool Energy::checkHitPoints(){ // checks if there's any hit points
    if (getEnergy() <= 0){
        setIsAlive(false); // must set its status to dead
        return false; // must immediately return
    }
    return true;
}

bool Energy::eat(int amt){
    if (getWorld() -> getFood(getX(), getY()) != nullptr){ // if there is food at the x, y
        Food * foo = dynamic_cast<Food *>(getWorld() -> getFood(getX(), getY())); // turn it into food
        if (foo != nullptr && foo -> getEnergy() > amt){ // if the food has enough energy
//            std::cerr << "Food is about to get eaten and is at : " << foo -> getEnergy() << std::endl;
            foo -> setEnergy(foo -> getEnergy() - amt); // take the energy from food
            setEnergy(getEnergy() + amt);
//            std::cerr << "Food eaten and now energy : " << foo -> getEnergy() << std::endl;
            return true;
        } else if (foo != nullptr && foo -> getEnergy() > 0 && foo -> getEnergy() <= amt){ // otherwise
//            std::cerr << "Food dies" << std::endl;
            setEnergy(getEnergy() + foo -> getEnergy()); // get all the food's energy
            foo -> setEnergy(0);
            foo -> setIsAlive(false); // set it to dead
            return true;
        }
    }
    return false;
}

// FOOD
Food::Food(int imgID, int x, int y, StudentWorld * studentWorld, Direction dir, int depth) : Energy(imgID, x, y, studentWorld){
    setEnergy(6000); // starts off with 1600
    setEdible(true); // it is edible
}

void Food::doSomething(){
    if (getEnergy() <= 0){
//        std::cerr << "Food died" << std::endl;
        setIsAlive(false);
    }
}

// PHEROMONE
Pheromone::Pheromone(int colony, int imgID, int x, int y, StudentWorld * studentWorld, Direction dir, int depth) : Energy(imgID, x, y, studentWorld){
    setEnergy(256); //All new Pheromone objects must have a strength of 256 units
    // will automatically not be stunnable or edible or bitable
    m_pheromoneColNum = colony; // make sure it knows it's colony
}

void Pheromone::doSomething(){
    setEnergy(getEnergy() - 1); //They decrease their strength by 1 unit
    if (checkHitPoints() == false){ //If their strength reaches zero units, then they must set their status to dead
        return;
    }
}

int Pheromone::getColonyNum(){ // corresponds to anthill and ant
    return m_pheromoneColNum;
}

// ANT HILL
Anthill::Anthill(int colonyNum, Compiler * comp, int imgID, int x, int y, StudentWorld * studentWorld, Direction dir, int depth) : Energy(imgID, x, y, studentWorld){
    setEnergy(8999); //new AntHill objects must have a starting hit points of 8,999 units
    m_colNum = colonyNum;
    m_compPtr = comp;
}

void Anthill::doSomething(){
    setEnergy(getEnergy() - 1); //decreases its (queen’s) hit points by 1 unit
    
    if (checkHitPoints() == false){ // the anthill’s (queen’s) hit points reaches zero units, then
        return; // must immediately return
    }
    
    // eat
    if (eat(10000)){ // if there's food and it eats
        return; // immediately return
    }
    
    // produce ants
    if (getEnergy() >= 2000){ // checks to see if it has enough energy - at least 2,000 hit points - to produce a
        getWorld() -> addAnts(getColonyNum(), 1); // asks StudentWorld to increase the count of the total number of ants that this colony has produced
        Actor * temp = new Ant(getX(), getY(), getColonyNum(), m_compPtr, IID_ANT_TYPE0 + getColonyNum(), getX(), getY(), getWorld()); // new ant of the same colony number to its square in the simulation
        getWorld() -> add(getX(), getY(), temp); // adds it
        setEnergy(getEnergy() - 1500); // it reduces its own hit points by 1,500
    }
}

int Anthill::getColonyNum(){ // corresponds to ant and pheromone
    return m_colNum;
}

Anthill::~Anthill(){
    delete m_compPtr;
}

// ACTIVE
Active::Active(int imgID, int x, int y, StudentWorld * studentWorld, Direction dir, int depth) : Energy(imgID, x, y, studentWorld){
    setMovable(true);
    setBiteable(true);
    setDrowning(false); // not drowning
    setCanDamage(true);
}

void Active::setSleepStunned(int sleep){
    m_isSleepStunned = sleep;
}

int Active::getSleepStunned(){
    return m_isSleepStunned;
}

void Active::setRandomDir(){ // used by ants and baby and adult grasshoppers
    int i = randInt(0, 3); // get a random integer from 0 to 3
    if (i == 0) { // depending on what it is set it to a corresponding direction
        setDirection(up);
    } else if (i == 1) {
        setDirection(down);
    } else if (i == 2) {
        setDirection(right);
    } else if (i == 3) {
        setDirection(left);
    }
}

void Active::diedSoAddFood(int amt){ // when an active actor dies
    if (getWorld() -> getFood(getX(), getY()) == nullptr){ // if there's no food where it died
        Food * foo = new Food(IID_FOOD, getX(), getY(), getWorld()); // create a new food item
        foo -> setEnergy(amt); // will be 100 vs 1600
        getWorld() -> add(getX(), getY(), foo);
//        std::cerr << "Something died and was made into food" << std::endl;
        return;
    } else { // otherwise
        Food * q = dynamic_cast<Food *>(getWorld() -> getFood(getX(), getY()));
        q -> setEnergy(getEnergy() + amt); // add it to the existing food
//        std::cerr << "Something died and was added to existing food" << std::endl;
        return;
    }
}

bool Active::move(){
    if (getDirection() == up){ // depending on the direction
        if ((getWorld() -> isRock(getX(), getY() + 1))){ // if the spot towards the move is a rock
            return false;
        }
        setDrowning(false); // should become un-drowning
        moveTo(getX(), getY() + 1); // otherwise, move the object
        return true;
    } else if (getDirection() == left){
        if ((getWorld() -> isRock(getX() - 1, getY()))){
            return false;
        }
        setDrowning(false); // should become un-drowning
        moveTo(getX() - 1, getY());
        return true;
    } else if (getDirection() == right){
        if ((getWorld() -> isRock(getX() + 1, getY()))){
            return false;
        }
        setDrowning(false); // should become un-drowning
        moveTo(getX() + 1, getY());
        return true;
    } else if (getDirection() == down){
        if ((getWorld() -> isRock(getX(), getY() - 1))){
            return false;
        }
        setDrowning(false); // should become un-drowning
        moveTo(getX(), getY() - 1);
    }
    return true;
}

bool Active::beginContinue(){
    setEnergy(getEnergy() - 1); // decrement the energy
    
    if (checkHitPoints() == false){ // must check to see if its hit points have reached zero
        diedSoAddFood(100); // add food to the square
        return false; // end of tick
    }
    
    if (getSleepStunned() > 0){ // if it's sleeping
        setSleepStunned(getSleepStunned() - 1); // decrement how much it's slept
        return false; // end of tick
    }
    
    return true;
}

bool Active::getDrowning(){
    return m_isDrowning;
}

void Active::setDrowning(bool set){
    m_isDrowning = set;
}

bool Active::bite(int dmg){
    Ant * a = dynamic_cast<Ant *>(this); // need to know if current object an ant
    Actor * r; // get a random insect
    if (a == nullptr){ // if it's not an ant
        r = getWorld() -> getRandomInsect(getX(), getY(), this); // get a random insect
    } else {
        r = getWorld() -> getRandomInsect(getX(), getY(), this, a -> getColonyNum()); // if it's an ant, get a random insect not from their colony
    }
    
    if (r != nullptr && r -> getAlive()){ // if the random insect is alive
//        std::cerr << "Biting" << std::endl;
        Active * randInsect = dynamic_cast<Active *>(r);
        if (randInsect != nullptr){
            randInsect -> setEnergy(randInsect -> getEnergy() - dmg);
            if (randInsect -> checkHitPoints() == false){ // if the insect died
                diedSoAddFood(100); // it died so add food
                return true;
            }
            
            Ant * n = dynamic_cast<Ant *>(randInsect); // if it's an ant
            if (n != nullptr){
                n -> setBitten(true); // it needs to remember it has been bitten
            }
            
            AdultGrasshopper * bittenHopper = dynamic_cast<AdultGrasshopper *>(randInsect);
            
            if (bittenHopper == nullptr){ // if it's a baby grasshopper
                return true; // we don't need to do anything else
            }
            
            if (bittenHopper != nullptr){
                int rand = randInt(1, 2);
                if (rand == 1){
                    bittenHopper -> bite(50); // the bitten grasshopper has the opportunity to bite back
                }
            }
        }
        return true;
    }
    return false;
}

// ANT
Ant::Ant(int xColony, int yColony, int antColonyNum, Compiler * comp, int imgID, int x, int y, StudentWorld * studentWorld, Direction, int depth) : Active(imgID, x, y, studentWorld){
    setEnergy(1500); // Has 1,500 hit points.
    setRandomDir(); // starts of random direction
    setBitten(false);
    m_justBlocked = false;
    setCanDamage(true); // ants can do damage
    setSleepStunned(0); // start off in non sleep stunned state
    m_antColonyNum = antColonyNum;
    m_compPtr = comp;
    m_holdFood = 0;
    m_xColony = xColony;
    m_yColony = yColony;
    m_lastNumber = 0; //Has a last random number value of 0
    ic = 0; // start at the beginning of the vector
    setStunablePoisonable(true); // can be stunned/poisoned
}

void Ant::setBlocked(bool block){
    m_justBlocked = block;
}

bool Ant::eat(int amt){
    if (m_holdFood > 0){ // if it is holding food
        if (m_holdFood >= 100){ // and if the food is more than 100
            setEnergy(getEnergy() + 100); // the ant eats 100
            m_holdFood = m_holdFood - 100;
            return true;
        } else if (m_holdFood < 100){ // otherwise
            setEnergy(getEnergy() + m_holdFood); // the ant eats whatevers left
            m_holdFood = 0; // sets to zero
            return true;
        }
    }
    return false;
}

bool Ant::runCommand(Compiler::Command& c){
    std::string error;
    
//    if (!m_compPtr -> compile(m_compPtr -> getColonyName(), error)){
//        std::cerr << "error: " << error << std::endl;
//        return false; // there was an error!
//    }
    
    int cnt = 0; // count to keep track of number of instructions executed in this round
    bool noFlag = true; // must note that the function modifies certain aspects
    while (noFlag){ // while there's no flag
        cnt++; // increment the count
        
        if (m_compPtr -> getCommand(ic, c) == false){
            return false; // error - no such instruction!
        }
        
        switch (c.opcode){
            // commands with no operands
            case Compiler::emitPheromone:{
//                std::cerr << "Emit pheromone " << getEnergy() << std::endl;
                int IID;
                if (getColonyNum() == 0){ // depending on the colony, set a specific pheromone
                    IID = IID_PHEROMONE_TYPE0;
                } else if (getColonyNum() == 1){
                    IID = IID_PHEROMONE_TYPE1;
                } else if (getColonyNum() == 2){
                    IID = IID_PHEROMONE_TYPE2;
                } else if (getColonyNum() == 3){
                    IID = IID_PHEROMONE_TYPE3;
                }
                addPheromone(IID); // add this pheromone to the studentWorld
                noFlag = false; // set the flag
                ++ic;
                break;
            }
            case Compiler::faceRandomDirection:
//                std::cerr << "Face new dir" << std::endl;
                setRandomDir(); // use the function already written
                noFlag = false;
                ++ic;
                break;
            case Compiler::rotateClockwise:
                if (getDirection() == right){ // depending on the current direction, set a new one
                    setDirection(down);
                } else if (getDirection() == down){
                    setDirection(left);
                } else if (getDirection() == left){
                    setDirection(up);
                } else if (getDirection() == up){
                    setDirection(right);
                }
                ++ic;
                noFlag = false; // set the flag
                break;
            case Compiler::rotateCounterClockwise:
                if (getDirection() == right){ // depending on the current direction, set a new one
                    setDirection(up);
                } else if (getDirection() == down){
                    setDirection(right);
                } else if (getDirection() == left){
                    setDirection(down);
                } else if (getDirection() == up){
                    setDirection(left);
                }
                ++ic;
                noFlag = false; // set the flag
                break;
            case Compiler::moveForward:{
//                std::cerr << "Move forward " << getEnergy() << std::endl;
                if (move()){ // if it moves
//                    std::cerr << "I WAS NOT BlOCKED" << std::endl;
                    m_justBitten = false; // note that it wasn't bitten or blocked
                    m_justBlocked = false;
                } else {
//                    std::cerr << "I WAS BlOCKED" << std::endl;
                    m_justBlocked = true; // otherwise it was blocked
                }
                ++ic; // advance to next instruction
                noFlag = false;
                break;
            }
            case Compiler::bite:
                bite(15); // An ant bite does 15 points of damage to the enemy.
                noFlag = false; // set the flag
                ++ic;
                break;
            case Compiler::pickupFood:{
//                std::cerr << "pickupFood, energy before: " << getEnergy() << std::endl;
                int currentEnergy = getEnergy(); // remember this value
                if (m_holdFood <= 1400){ // may only hold a total of 1800 units of food
                    Energy::eat(400); //  try to pick up 400 units of food at a time from its current location
                } else {
                    Energy::eat(1800 - m_holdFood); // hold up to 1800 units
                }
                m_holdFood += (getEnergy() - currentEnergy); // how much gained is how much more energy was gained
                setEnergy(currentEnergy); // ensure the ant's energy hasn't changed
                noFlag = false; // set the flag
                ++ic;
//                std::cerr << "pickupFood, energy after: " << getEnergy() << std::endl;
                break;
            }
            case Compiler::dropFood:{
                diedSoAddFood(m_holdFood); // ants will drop all the food they are holding
                m_holdFood = 0; // adjust accordingly
                ++ic;
                noFlag = false; // set the flag
                break;
            }
            case Compiler::eatFood:
//                std::cerr << "Ant eats, energy before : " << getEnergy() << std::endl;
                eat(100); // call the ant's eat method
//                std::cerr << "Ant eats, energy after : " << getEnergy() << std::endl;
                ++ic;
                noFlag = false; // set the flag
                break;
                
            // more complex commands with operands
            case Compiler::goto_command:{
//                std::cerr << " ... go to " << std::endl;
                ic = stoi(c.operand1); // convert the operand to an int
                break;
            }
            case Compiler::generateRandomNumber:
//                std::cerr << "Generate rand num " << std::endl;
                if (stoi(c.operand1) == 0){ // if the num was 0
                    m_lastNumber = 0;
                    ++ic; // advance to next instruction
                    break;
                }
                m_lastNumber = randInt(0, stoi(c.operand1) - 1); // zero to n - 1
                ++ic; // advance to next instruction
                break;
            case Compiler::if_command:
//                std::cerr << "If " << std::endl;
                int operand2Int = stoi(c.operand2); // convert the operand to an int
                switch (stoi(c.operand1)){
                    case Compiler::Condition::last_random_number_was_zero:
                        if (m_lastNumber == 0){ // if the last rand num was 0
//                            std::cerr << "Last random number was zero : " << std::endl;
                            ic = operand2Int;
                            break;
                        }
                        ++ic;
                        break;
                    case Compiler::Condition::i_am_carrying_food:
                        if (m_holdFood > 0){ // if it's holding food
                            ic = operand2Int;
                            return true;
                        }
                        ++ic;
                        break;
                    case Compiler::Condition::i_am_hungry:
//                        std::cerr << "I am hungry : " << std::endl;
                        if (getEnergy() <= 25){ // if hitpoints are less than 25 the ant is hungry
                            ic = operand2Int;
                            break;
                        }
                        ++ic;
                        break;
                    case Compiler::Condition::i_am_standing_with_an_enemy:{
                        Actor * rand = getWorld() -> getRandomInsect(getX(), getY(), this, getColonyNum()); // get a random insect that's not the current ant
                        if (rand != nullptr){
                            ic = operand2Int; // go to the operand 2 instruction
                            break;
                        }
                        ++ic;
                        break;
                    }
                    case Compiler::Condition::i_am_standing_on_food:{
                        Actor * foodObj = getWorld() -> getFood(getX(), getY()); //get a actor food obj
                        Food * foodCast = dynamic_cast<Food*>(foodObj); // cast it to food
                        if (foodCast != nullptr){ // if it exists
//                            std::cerr << "I am standing on food " << std::endl;
                            ic = operand2Int; // execute instruction
                            break;
                        }
//                        std::cerr << "I am NOT standing on food " << std::endl;
                        ++ic;
                        break;
                    }
                    case Compiler::Condition::i_am_standing_on_my_anthill:
                        if((getX() == m_xColony) && (getY() == m_yColony)){ // if the home colony coordinates match the current coordinates
                            ic = operand2Int; // execute instruction
                        }
                        ++ic;
                        break;
                    case Compiler::Condition::i_smell_pheromone_in_front_of_me:{
//                        std::cerr << "Checking for my own pheromone" << std::endl;
                        bool checkedPher = getWorld() -> isPheromone(this); //If there is a pheromone with a strength of at least 1 in the square in front of where the ant is facing
                        if (checkedPher == true){
                            ic = operand2Int; // go to the operand 2 instruction
                            break;
                        }
                        ++ic;
                        break;
                    }
                    case Compiler::Condition::i_smell_danger_in_front_of_me:{
                        bool checkedDanger = getWorld() -> findDangerous(this); // if there's danger
                        if (checkedDanger == true){
//                            std::cerr << "I smell danger " << std::endl;
                            ic = operand2Int; // go to the operand 2 instruction
                            break;
                        }
                        ++ic;
                        break;
                    }
                    case Compiler::Condition::i_was_blocked_from_moving:
                        if (m_justBlocked == true){ // if the ant was just blocked
//                            std::cerr << "I was just blocked" << std::endl;
                            ic = operand2Int; // execute instruction
                            break;
                        }
                        ++ic;
                        break;
                    case Compiler::Condition::i_was_bit:
                        if (m_justBitten == true){ // if the ant was just bit
                            ic = operand2Int; // execute instruction
                            break;
                        }
                        ++ic;
                        break;
                }
                break;
        }
        if (cnt >= 10){ // if it has executed more than 10 instructions
//            std::cerr << "Returned false at 10 count " << std::endl;
            noFlag = false; // don't run anymore
        }
    }
    return true;
}

void Ant::doSomething(){
    // dies or is sleeping
    if (beginContinue() == false){ // if the actor is dead or stunned
//        std::cerr << "Ant died or is stunned" << std::endl;
        return; // end of tick
    }
    
    Compiler::Command c; // get the command
    
    if (runCommand(c) == false){ // run the command
        setIsAlive(false); // if it failed, it's dead
//        diedSoAddFood(100); // the ant has died and will be destroyed next tick
    }
}

void Ant::setBitten(bool bit){
    m_justBitten = bit;
}

int Ant::getColonyNum(){
    return m_antColonyNum;
}

void Ant::addPheromone(int IID){
    if (getWorld() -> getPheromone(this) != nullptr){ // if a pheromone is found
        Pheromone * pher = dynamic_cast<Pheromone*>(getWorld() -> getPheromone(this));
        pher -> setEnergy(pher -> getEnergy() + 256); // increase it's energy by 256
        if (pher -> getEnergy() > 768){ // don't let it get too much energy though
            pher -> setEnergy(768);
        }
    } else { // if there's no existing pheromone
        Pheromone * pher = new Pheromone(getColonyNum(), IID, getX(), getY(), getWorld()); // add a brand new one
        getWorld() -> add(getX(), getY(), pher); // put it in the world
    }
}


// BABY GRASSHOPPER
BabyGrasshopper::BabyGrasshopper(int imgID, int x, int y, StudentWorld * studentWorld, Direction dir, int depth) : Active(IID_BABY_GRASSHOPPER, x, y, studentWorld){
    setMoveDist(randInt(2, 10)); // give it a random dist
    setSleepStunned(0); // should not start off sleeping or stunned
    setEnergy(500); // must start off with 500 hit points
    setRandomDir(); // give it a random dir
    setStunablePoisonable(true); // can be stunned/poisoned
}

void BabyGrasshopper::setMoveDist(int move){
    m_moveDist = move;
}

int BabyGrasshopper::getMoveDist(){
    return m_moveDist;
}

void BabyGrasshopper::doSomething(){
//    std::cerr << "Baby grasshopper, energy : " << getEnergy() << std::endl;
    
    // dies or is sleeping
    if (beginContinue() == false){ // if the actor is dead or stunned
//        std::cerr << "Begin continue was false" << std::endl;
        return; // end of tick
    }
    
    // evolves
    if (getEnergy() >= 1600){
//        std::cerr << "Evolves" << std::endl;
        AdultGrasshopper * G = new AdultGrasshopper(IID_ADULT_GRASSHOPPER, getX(), getY(), getWorld());
        getWorld() -> add(getX(), getY(), G); // add the adult
        setIsAlive(false); // kill it
        diedSoAddFood(100); // add food
        return;
    }
    
    // eat
    if (eat(200) && randInt(1, 2) == 1){
//        std::cerr << "Eats" << std::endl;
        setSleepStunned(2);
        return;
    }
    
    if (getMoveDist() <= 0){ // if the moveDist is zero
//        std::cerr << "Move distance was zero" << std::endl;
        setMoveDist(randInt(2, 10)); // give it a new dist
        setRandomDir(); // give it a new dir
    }
    
    // move
    setMoveDist(getMoveDist() - 1);
    if (move() == false){ // if it doesn't move
//        std::cerr << "Couldn't or didn't move" << std::endl;
        setMoveDist(0); // move dist equals zero
    } else {
//        std::cerr << "Did move : x : " << getX() << " y " << getY() << std::endl;
    }
    
    setSleepStunned(2);
}

// ADULT GRASSHOPPER
AdultGrasshopper::AdultGrasshopper(int imgID, int x, int y, StudentWorld * studentWorld, Direction dir, int depth) : BabyGrasshopper(IID_ADULT_GRASSHOPPER, x, y, studentWorld){
    resetEnergy(); setEnergy(1600); // reset the energy (which might have a value from the baby grasshopper), and then set it to 1600
    setSleepStunned(0); // should not start off sleeping or stunned
    setMoveDist(randInt(2, 10)); // give it a random dist
    setRandomDir(); // give it a random dir
    setCanDamage(true); // adults can do damage
    setStunablePoisonable(false); // cannot be stunned/poisoned
}

void AdultGrasshopper::doSomething(){
//    std::cerr << "Adult grasshopper, energy : " << getEnergy() << std::endl;

    // dies or is sleeping
    if (beginContinue() == false){ // if the actor is dead or stunned
        return; // end of tick
    }

    //one in three chance that the adult grasshopper will try to bite another insect
    int rand = randInt(1, 3); // 1 in 3
    if (rand == 1){
        //If the adult grasshopper does decide to bite an enemy during the tick (⅓ chance), and there are one or more enemies
        //The adult grasshopper will randomly choose one of the enemies and bite them, doing 50 hit points of damage
        if (bite(50)){ // if the bite is successfull
            setSleepStunned(2); // make it sleep
            return;
        }
    	// otherwise continue as normal
    }
    
    //there is a one in ten chance that the adult grasshopper will decide to jump to another square
    rand = randInt(1, 10); // 1 in 10
    int radius; double angle; // random radian angle and radius will be given to this
    int xCoor; int yCoor; // random x and y
    
    if (rand == 1){ // just need a random number out of 10
        bool foundEmpty = false, wentToEmpty = false;
        
        for (int x = 0; x < 11; x++){ // run through the possible 10 x around current
            for (int y = 0; y < 11; y++){ // run through the possible 10 y around current
                if (sqrt(x*x + y*y) <= 10 && (getWorld() -> isRock(getX() + x, getY() + y) == false)){
                    foundEmpty = true;
                }
            }
        }
        if (foundEmpty){
            while (wentToEmpty == false){
                radius = randInt(1, 10); // within 10
                angle = randInt(1, 360) * (M_PI / 180); // random radian angle
                xCoor = radius * cos(angle); // x coordinate
                yCoor = radius * sin(angle); // y coordinate
                    if (getWorld() -> isRock(getX() + xCoor, getY() + yCoor)){ // if it's a rock or no distance has been added
                        continue; // keep looking for an open space
                    } else { // otherwise
                        wentToEmpty = true; // exit the while loop
                        moveTo(getX() + xCoor, getY() + yCoor); // move the object
//                        std::cerr << "Adult grasshopper coordinates : " << getX() << " Y : " << getY() << std::endl;
                        setSleepStunned(2); // should sleep and return (step 13)
                        return;
                    }
            }
    	}
    }

    // eat food
    if (eat(200)){
        int rand = randInt(1, 2); // if the adult grasshopper did eat, then there is a 50% chance it will want to rest immediately
        if (rand == 1){
        	setSleepStunned(2);
        }
        return;
    }
    
    //see if the adult grasshopper has finished walking
    if (getMoveDist() <= 0){
        setRandomDir();
        setMoveDist(randInt(2, 10)); // give it a random dist
    }
    
    //The adult grasshopper attempts to move one square in its currently facing direction
    if (move() == false){
        setMoveDist(0); // move dist equals zero
        setSleepStunned(2);
        return;
    }
    
    //Otherwise, the adult grasshopper decreases its desired distance to walk in the current direction by one.
    setMoveDist(getMoveDist() - 1);
    setSleepStunned(2);
}

// PEBBLE
Pebble::Pebble(int imgID, int x, int y, StudentWorld * studentWorld, Direction dir, int depth) : Actor(IID_ROCK, x, y, studentWorld,  dir, depth){
    setMovable(false); // this is only for pebbles
}

void Pebble::doSomething(){} // must do something b/c inheriting from pure virtual class

// WATER POOL
WaterPool::WaterPool(int imgID, int x, int y, StudentWorld * studentWorld, Direction dir, int depth) : Actor(IID_WATER_POOL, x, y, studentWorld,  dir, depth){
    setCanDamage(true); // poison can do damage
}

void WaterPool::doSomething(){
    getWorld() -> stunActors(getX(), getY()); // let the world's function stun pertinent actors
    return;
}

void WaterPool::reverseWater(){ // will reverse when the actor is stunned while sleeping
    bool didStun = false;
    for (int x = 0; x < VIEW_WIDTH; x++){
        for (int y = 0; y < VIEW_HEIGHT; y++){
//            std::cerr << "Object just got stunned by water" << std::endl;
            if (didStun == true){ // if it was stunned
                return; // return
            }
        }
    }
}

// POISON
Poison::Poison(int imgID, int x, int y, StudentWorld * studentWorld, Direction dir, int depth) : Actor(IID_POISON, x, y, studentWorld,  dir, depth){
    setCanDamage(true); // poison can do damage
}

void Poison::doSomething(){
    getWorld() -> poisonActors(getX(), getY()); // let the world's function poison pertinent actors
}


