#include "StudentWorld.h"
#include "Field.h"
#include <string>
#include <sstream>
#include <iomanip>
#include "Compiler.h"
using namespace std;

// DESTRUCTOR
StudentWorld::~StudentWorld(){
    cleanUp(); // cleanUp and destructor might do the same thing (in which case the destructor could just call cleanup()
}

// DISPLAY
int StudentWorld::getWinner(){
    int max = -1;
    if (ticks >= 1995 && max != -1){ // the game should go for longer than 2000 before determining a winner
        return max;
    }
    int value = 0;
    for (int i = 0; i < m_active; i++){ // loop through the array
        if (value < m_antHillNum[i] && m_antHillNum[i] > 5){ // get the maximum number of ants of all anthills
            value = m_antHillNum[i]; 
            max = i;
        }
    }
    return max;
}

string StudentWorld::format(int ticks, int * numbers, string * names, int winner, int active){
    ostringstream ostring;
    ostring << "Ticks"; // display the ticks
    ostring << setw(5) << ticks; // set the precision
    ostring << " -  ";
    for (int i = 0; i < active; i++){ // run through the current number of active anthills
        string antHillName = "";
        antHillName = antHillName + names[i]; // get the name
        
        if (i == winner){ // if it's the winner
            antHillName = "*" + antHillName; // designate it
        }
        
        string numberOfAnts;
        if (numbers[i] < 10){ 
            numberOfAnts = "0" + to_string(numbers[i]); // get the number of ants it has
        } else {
            numberOfAnts = to_string(numbers[i]);
        }
        
        antHillName = antHillName + ": " + numberOfAnts; // add the : space
        
        if (i != active - 1){ // if it's not the last
            ostring << antHillName << "  "; // add a space
        } else {
            ostring << antHillName; // just print the last name
        }
    }
    return ostring.str(); // return the string we've built
}

// PROVIDED
GameWorld * createStudentWorld(string assetDir){
    return new StudentWorld(assetDir);
}

// INITIALIZING AND OTHER
void StudentWorld::addObjectToSimulation(int colonyNum, Compiler * com){
    m_ActorList[m_coordinatesY[colonyNum]][m_coordinatesX[colonyNum]].push_back(new Anthill(colonyNum, com, IID_ANT_HILL, m_coordinatesX[colonyNum], m_coordinatesY[colonyNum], this));
    // push a new anthill onto the simulation
}

int StudentWorld::init(){
    string name = getFieldFilename(); // get the name
    Field fld; // make a new field
    string issues = ""; // be able to capture issues
    Field::LoadResult loaded = fld.loadField(name, issues); // load the field
    
    if (loaded == Field::load_fail_file_not_found || loaded == Field::load_fail_bad_format){ // if it didn't load
        return GWSTATUS_LEVEL_ERROR; // error
    } else {
        for (int x = 0; x < VIEW_WIDTH; x++){ // run through all the elements
            for (int y = 0; y < VIEW_HEIGHT; y++){
                Field::FieldItem item = fld.getContentsOf(x, y); // get the ID
                switch (item){
                    // whatever it is, add it to it's appropriate location and pass it the student world
                    case Field::food:
//                        if (x == 0 && y == 0){
//                            std::cerr << "Adding food at x:" << x << " and y:" << y << std::endl;
//                        }
                        m_ActorList[y][x].push_back(new Food(IID_FOOD, x, y, this));
                        break;
                    case Field::rock:
                        //                        if (x == 0 && y == 0){
                        //                            std::cerr << "Adding rock at x:" << x << " and y:" << y << std::endl;
                        //                        }
                        m_ActorList[y][x].push_back(new Pebble(IID_ROCK, x, y, this));
                        break;
                    case Field::grasshopper:
                        //                        if (x == 0 && y == 0){
                        //                            std::cerr << "Adding grasshopper at x:" << x << " and y:" << y << std::endl;
                        //                        }
                        m_ActorList[y][x].push_back(new BabyGrasshopper(IID_BABY_GRASSHOPPER, x, y, this));
                        break;
                    case Field::poison:
//                        if (x == 0 && y == 0){
//                            std::cerr << "Adding poison at x:" << x << " and y:" << y << std::endl;
//                        }
                        m_ActorList[y][x].push_back(new Poison(IID_POISON, x, y, this));
                        break;
                    case Field::water:
                        //                        if (x == 0 && y == 0){
                        //                            std::cerr << "Adding water at x:" << x << " and y:" << y << std::endl;
                        //                        }
                        m_ActorList[y][x].push_back(new WaterPool(IID_WATER_POOL, x, y, this));
                        break;
                    case Field::anthill0:
                        m_coordinatesX[0] = x; // add the anthills coordinates to an array
                        m_coordinatesY[0] = y; // will be used later
                        m_active++;
                        break;
                    case Field::anthill1:
                        m_coordinatesX[1] = x;
                        m_coordinatesY[1] = y;
                        m_active++;
                        break;
                    case Field::anthill2:
                        m_coordinatesX[2] = x;
                        m_coordinatesY[2] = y;
                        m_active++;
                        break;
                    case Field::anthill3:
                        m_coordinatesX[3] = x;
                        m_coordinatesY[3] = y;
                        m_active++;
                        break;
                }
            }
        }
    }
//    std::cerr << "Actorlist at 0, 0 SIZE :" << m_ActorList[0][0].size() << std::endl;

    Compiler * compilerForEntrant0, * compilerForEntrant1, * compilerForEntrant2, * compilerForEntrant3;
    Anthill * ah0, * ah1, * ah2, * ah3;
    m_fileNames = getFilenamesOfAntPrograms(); // get the file names
//    std::cerr << "m_fileNames SIZE" << m_fileNames.size() << std::endl;
    std::string error; // be able to get the errors
    for (int i = 0; i < m_active; i++){
        
        Compiler * comp = new Compiler; // create a new compiler
        
        if (!comp -> compile(m_fileNames[i], error) ){
            setError(m_fileNames[i] + " " + error);
            return GWSTATUS_LEVEL_ERROR;
        }
        
//        std::cerr << "For loop before adding SIZE at 0, 0:" << m_ActorList[0][0].size() << " and i is " << i << std::endl;
        addObjectToSimulation(i, comp); // add a new anthill
//        std::cerr << "For loop after adding SIZE at 0, 0:" << m_ActorList[0][0].size() << " and i is " << i << std::endl;
        
        m_antHillNames[i] = comp -> getColonyName(); // add the name of the anthill
    }
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move(){
    //During each tick, it must ask your baby grasshoppers and pebbles to do something.
//    std::cerr << std::endl;
//    std::cerr << "NEW TICK - " << getCurrentTicks() << std::endl;
//    std::cerr << std::endl;
    for (int x = 0; x < VIEW_WIDTH; x++){ // run through the simulation
        for (int y = 0; y < VIEW_HEIGHT; y++){
            for (int k = 0; k < m_ActorList[x][y].size(); k++){ // go through the data struct
                if (!m_ActorList[x][y][k] -> getChecked()){ // if it hasn't been checked
                    m_ActorList[x][y][k] -> setChecked(true); // now it has been checked

                    int oldX = m_ActorList[x][y][k] -> getX(); // save these values
                    int oldY = m_ActorList[x][y][k] -> getY();
                    
                    m_ActorList[x][y][k] -> doSomething(); // make every actor do something
                    
                    int newX = m_ActorList[x][y][k] -> getX(); // get the new values
                    int newY = m_ActorList[x][y][k] -> getY();
                    
                    if (oldY != newY || oldX != newX){ // compare the values
                        Actor * temp = m_ActorList[x][y][k]; // place the actor at it's new location
                        m_ActorList[x][y].erase(m_ActorList[x][y].begin() + k);
                        m_ActorList[newY][newX].push_back(temp);
                        k--; // decrement k so the for loop stays in order
                    }
                }
            }
        }
    }
    
    // DELETE DEAD
    for (int x = 0; x < VIEW_WIDTH; x++){
        for (int y = 0; y < VIEW_HEIGHT; y++){
            for (int k = 0; k < m_ActorList[x][y].size(); k++){
                if (m_ActorList[x][y][k] -> getAlive() == false){
                    delete m_ActorList[x][y][k];
                    m_ActorList[x][y].erase(m_ActorList[x][y].begin() + k);
                }
            }
        }
    }
    
    // SET FALSE
    for (int x = 0; x < VIEW_WIDTH; x++){
        for (int y = 0; y < VIEW_HEIGHT; y++){
            for (int k = 0; k < m_ActorList[x][y].size(); k++){
                m_ActorList[x][y][k] -> setChecked(false); // set all actors back to not being checked
            }
        }
    }

    
    ticks--; // decrement ticks
    
    m_winningAnt = getWinner(); // get the winning ant
    
    setGameStatText(format(ticks, m_antHillNum, m_antHillNames, m_winningAnt, m_active));
    
    if (ticks == 0){ // if the game is over
        if (m_winningAnt == -1){
            return GWSTATUS_NO_WINNER; // there is no winner
        }
        setWinner(m_antHillNames[m_winningAnt]);
        return GWSTATUS_PLAYER_WON;
    }
    
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp(){
    for (int y = 0; y < VIEW_WIDTH; y++){ // run through the actors
        for (int x = 0; x < VIEW_HEIGHT; x++){
            while (!m_ActorList[y][x].empty()){
                delete m_ActorList[y][x].back(); // delete the actors
                m_ActorList[y][x].pop_back(); // delete the pointers
            }
        }
    }
}

// ADDING AND FINDING
void StudentWorld::add(int x, int y, Actor * a){ // added
    m_ActorList[y][x].push_back(a);
}

bool StudentWorld::isRock(int x, int y){
    if (x >= VIEW_WIDTH || x <= 0 || y >= VIEW_HEIGHT || y <= 0){ // if it's out of bounds
//        std::cerr << "isRock returned TRUE b/c out of bounds" << std::endl;
        return true;
    }
    
    for (int i = 0; i < m_ActorList[y][x].size(); i++){
        if (m_ActorList[y][x][i] != nullptr){ // if it's accessible
            if (!m_ActorList[y][x][i] -> getMovable()){ // and it's a pebble
//                std::cerr << "isRock returned TRUE" << std::endl;
                return true;
            }
        }
    }
//    std::cerr << "isRock returned FALSE" << std::endl;
    return false;
}

Actor * StudentWorld::getFood(int x, int y){
    for (int i = 0; i < m_ActorList[y][x].size(); i++){ // run through the actors
        if (m_ActorList[y][x][i] -> getEdible()){ // if it's edible
            return m_ActorList[y][x][i]; // return it
        }
    }
    return nullptr;
}

Actor * StudentWorld::getRandomInsect(int x, int y, Actor * act, int colony){
    std::vector<Actor*> v; // create a vector of the insects
    for (int i = 0; i < m_ActorList[y][x].size(); i++){
        if (m_ActorList[y][x][i] != nullptr){ // if it exists
            if (m_ActorList[y][x][i] -> getBiteable() && m_ActorList[y][x][i] != act){ // if it's biteable and not the current actor
                Ant * randomInsect = dynamic_cast<Ant *>(m_ActorList[y][x][i]);
                if (randomInsect == nullptr){ // if it's a different insect
                    v.push_back(m_ActorList[y][x][i]); // add it
                } else if(!(randomInsect -> getColonyNum() == colony)){ // if it's an ant not from the same colony
                        v.push_back(m_ActorList[y][x][i]); // add it
                }
            }
        }
    }
    if (v.size() == 0){
        return nullptr;
    }
    int rand = randInt(0, v.size() - 1); // size - 1 stays in bounds
    return v[rand]; // random insect
}

void StudentWorld::addAnts(int colony, int add){
    if (colony == 0){ // add total ants to appropriate colony
        m_antHillNum[0] += add;
    } else if (colony == 1){
        m_antHillNum[1] += add;
    } else if (colony == 2){
        m_antHillNum[2] += add;
    } else if (colony == 3){
        m_antHillNum[3] += add;
    }
}

int StudentWorld::getNumberofAnts(int colony){
    if (colony == 0){ // get total ants from appropriate colony
        return m_antHillNum[0];
    } else if (colony == 1){
        return m_antHillNum[1];
    } else if (colony == 2){
        return m_antHillNum[2];
    } else if (colony == 3){
        return m_antHillNum[3];
    }
    return -1;
}

Actor * StudentWorld::getPheromone(Ant * antHome){
    for (int i = 0; i < m_ActorList[antHome -> getY()][antHome -> getX()].size(); i++){ // run through actors at the ants loc
        if (m_ActorList[antHome -> getY()][antHome -> getX()][i] != nullptr){
            Pheromone * r = dynamic_cast<Pheromone *>(m_ActorList[antHome -> getY()][antHome -> getX()][i]); // cast the actor to a pheromone
            if (r != nullptr && r -> getColonyNum() == antHome -> getColonyNum()){ // if it's colony is equal to the ant's colony
                return m_ActorList[antHome -> getY()][antHome -> getX()][i]; // return it
            }
        }
    }
    return nullptr;
}

void StudentWorld::stunActors(int x, int y){
    for (int i = 0; i < m_ActorList[y][x].size(); i++){
        if (m_ActorList[y][x][i] -> getStunablePoisonable()){ // if it's stunnable
//            std::cerr << "Stun something at X: " << x << ", Y : " << y << std::endl;
            Active * act = dynamic_cast<Active *>(m_ActorList[y][x][i]); // get the actor
            if (act != nullptr){
                if (!(act -> getDrowning())){ // if it's not already in water
                    act -> setSleepStunned((act -> getSleepStunned()) + 2); // stun it
                    act -> setDrowning(true);
//                    std::cerr << "was setSleepStunned : " << act -> getSleepStunned() << std::endl;
                }
            }
        }
    }
}

// similar but different from stun
void StudentWorld::poisonActors(int x, int y){
    for (int i = 0; i < m_ActorList[y][x].size(); i++){
        if (m_ActorList[y][x][i] -> getStunablePoisonable() == true){ // if it's stunnable
            Active * act = dynamic_cast<Active *>(m_ActorList[y][x][i]); // cast it
//            std::cerr << "Poison, energy before: " << act -> getEnergy() << std::endl;
            if (act != nullptr){
                act -> setEnergy(act -> getEnergy() - 150);
//                std::cerr << "Poison, energy after: " << act -> getEnergy() << std::endl;
                if (act -> checkHitPoints() == false){ // if it's dead
                    act -> diedSoAddFood(100); // add 100 to the square
                    act -> setIsAlive(false); // and set it to dead
                }
            }
        }
    }
}

bool StudentWorld::findDangerous(Ant * a){
    vector<Actor *> dangerousInsects; // get a vector of the position above or below it
    if (a -> getDirection() == Active::Direction::up){ // get the direction
        dangerousInsects = m_ActorList[a -> getY() - 1][a -> getX()]; // get the vector
    } else if (a -> getDirection() == Active::Direction::down){
        dangerousInsects = m_ActorList[a -> getY() + 1][a -> getX()];
    } else if (a -> getDirection() == Active::Direction::left){
        dangerousInsects = m_ActorList[a -> getY()][a -> getX() - 1];
    } else if (a -> getDirection() == Active::Direction::right){
        dangerousInsects = m_ActorList[a -> getY()][a -> getX() + 1];
    }
    
    for (int i = 0; i < dangerousInsects.size(); i++){ // run through the vector
    	if (dangerousInsects[i] -> getCanDamage() == true){ // if it can damage
//            std::cerr << "Should find something " << std::endl;
            return true;
        }
    }
    return false;
}

bool StudentWorld::isPheromone(Ant * a){
    vector<Actor*> pheroVect; // get a vector of the position above or below it
    if (a -> getDirection() == Active::Direction::up){ // get the direction
        pheroVect = m_ActorList[a -> getY() - 1][a -> getX()]; // get the vector
    } else if (a -> getDirection() == Active::Direction::down){
        pheroVect = m_ActorList[a -> getY() + 1][a -> getX()];
    } else if (a -> getDirection() == Active::Direction::left){
        pheroVect = m_ActorList[a -> getY()][a -> getX() - 1];
    } else if (a -> getDirection() == Active::Direction::right){
        pheroVect = m_ActorList[a -> getY()][a -> getX() + 1];
    }
    
    for (int i = 0; i < pheroVect.size(); i++){ // run through the vector
        Pheromone * p = dynamic_cast<Pheromone *>(pheroVect[i]);
        if (p != nullptr && p -> getColonyNum() == a -> getColonyNum()){ // if it's a pheromone and of the ant's colony
//            std::cerr << "Should get pheromone " << std::endl;
            return true;
        }
    }
    return false;
}
