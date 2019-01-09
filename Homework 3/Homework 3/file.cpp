//
//  main.cpp
//  Homework 3
//
//  Created by Anthony on 2/9/17.
//  Copyright © 2017 CS32. All rights reserved.
//

//#include <iostream>
//#include <string>
//using namespace std;

//Your declarations and implementations would go here
class File{
public:
    File(string name);
    virtual ~File();
    virtual void open() const = 0;
    string name() const;
    virtual void redisplay() const;
private:
    string m_name;
};

class TextMsg : public File{
public:
    TextMsg(string name) : File(name){};
    ~TextMsg();
    void open() const;
};

class Video : public File{
public:
    Video(string name, int size);
    ~Video();
    void open() const;
    void redisplay() const;
private:
    int m_size;
};

class Picture : public File{
public:
    Picture(string name) : File(name){};
    ~Picture();
    void open() const;
};

// FILE
File::File(string name){
    m_name = name;
}

File::~File(){
}

void File::open() const{
}

string File::name() const{
    return m_name;
}

void File::redisplay() const{
    cout << "refresh the screen";
}

// TEXT MSG
TextMsg::~TextMsg(){
    cout << "Destroying " << name() << ", a text message" << endl;;
}

void TextMsg::open() const{
    cout << "open text message";
}

// VIDEO
Video::Video(string name, int size) : File(name){
    m_size = size;
}

void Video::open() const{
    cout << "play " << m_size << " second video";
}

Video::~Video(){
    cout << "Destroying " << name() << ", a video" << endl;
}

void Video::redisplay() const{
    cout << "replay video";
}

// PICTURE
void Picture::open() const{
    cout << "show picture";
}

Picture::~Picture(){
    cout << "Destroying the picture " << name() << endl;
}

// DON'T TOUCH
void openAndRedisplay(const File* f){
    cout << f->name() << ": ";
    f->open();
    cout << endl << "Redisplay: ";
    f->redisplay();
    cout << endl;
}

//int main(){
////    File * f = new File("name"); not supposed to compile
//    
//    File * files[4];
//    files[0] = new TextMsg("fromFred.txt");
//    // Videos have a name and running time
//    files[1] = new Video("goblin.mpg", 3780);
//    files[2] = new Picture("kitten.jpg");
//    files[3] = new Picture("baby.jpg");
//    
//    for (int k = 0; k < 4; k++)
//        openAndRedisplay(files[k]);
//    
//    // Clean up the files before exiting
//    cout << "Cleaning up." << endl;
//    for (int k = 0; k < 4; k++)
//        delete files[k];
//}

//Output produced:
//
//fromFred.txt: open text message
//Redisplay: refresh the screen
//goblin.mpg: play 3780 second video
//Redisplay: replay video
//kitten.jpg: show picture
//Redisplay: refresh the screen
//baby.jpg: show picture
//Redisplay: refresh the screen
//Cleaning up.
//Destroying fromFred.txt, a text message
//Destroying goblin.mpg, a video
//Destroying the picture kitten.jpg
//Destroying the picture baby.jpg
//Decide which function(s) should be pure virtual, which should be non-pure virtual, and which could be non-virtual. Experiment to see what output is produced if you mistakenly make a function non-virtual when it should be virtual instead.

