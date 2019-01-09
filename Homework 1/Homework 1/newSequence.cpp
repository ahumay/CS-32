//
//  newSequence.cpp
//  Homework 1
//
//  Created by Anthony on 1/19/17.
//  Copyright © 2017 CS32. All rights reserved.
//
/*
#include "newSequence.h"
#include <cstdlib> // for the exit

Sequence::Sequence(int x){
    if (x < 0){
        exit(1);
    } else {
        m_limit = x;
        m_sequence = new ItemType[m_limit];
        m_length = 0;
    }
}

Sequence::Sequence(){
    m_length = 0;
    m_sequence = new ItemType[m_limit];
}

Sequence::Sequence(const Sequence& copy){
    m_limit = copy.m_limit;
    m_length = copy.m_length;
    m_sequence = new ItemType[m_limit];
    for (int i = 0; i < m_length; i++){
        m_sequence[i] = copy.m_sequence[i];
    }
}

Sequence::~Sequence(){
    delete [] m_sequence;
}

Sequence& Sequence::operator = (const Sequence& z){
    
    if (this != &z){
        delete [] m_sequence;
        Sequence temp(z);
        swap(temp);
    }
    return * this;
}

bool Sequence::empty() const{
    if (m_length == 0){
        return true;
    }
    return false;
}

int Sequence::size() const{
    return m_length;
}

bool Sequence::insert(int pos, const ItemType& value){
    if (pos < 0 || pos > m_limit - 1 || pos > size()){ // is pos valid
        return false;
    }
    
    if (size() >= m_limit){ // is there room
        return false;
    } else {
        m_length++; // increment
    }
    
    if (pos == size()){
        m_sequence[pos] = value;
        return true;
    }
    
    for (int j = size() - 1; j > pos; j--){
        m_sequence[j] = m_sequence[j - 1];
    }
    m_sequence[pos] = value;
    return true;
}
// Insert value into the sequence so that it becomes the item at
// position pos.  The original item at position pos and those that
// follow it end up at positions one higher than they were at before.
// Return true if 0 <= pos <= size() and the value could be
// inserted.  (It might not be, if the sequence has a fixed capacity,
// (e.g., because it's implemented using a fixed-size array) and is
// full.)  Otherwise, leave the sequence unchanged and return false.
// Notice that if pos is equal to size(), the value is inserted at the
// end.

int Sequence::insert(const ItemType& value){
    int p = size();
    m_length++;
    
    if (size() >= m_limit || size() < 0){ // is there room
        return -1;
    }
    
    for (int i = 0; i < size(); i++){
        if (value <= m_sequence[i]){
            p = i;
            break;
        }
    }
    
    for (int j = size() - 1; j > p; j--){
        m_sequence[j] = m_sequence[j - 1];
    }
    m_sequence[p] = value;
    
    return p;
}
// Let p be the smallest integer such that value <= the item at
// position p in the sequence; if no such item exists (i.e.,
// value > all items in the sequence), let p be size().  Insert
// value into the sequence so that it becomes the item at position
// p.  The original item at position p and those that follow it end
// up at positions one higher than before.  Return p if the value
// was actually inserted.  Return -1 if the value was not inserted
// (perhaps because the sequence has a fixed capacity and is full).

bool Sequence::erase(int pos){
    if (pos >= 0 && pos < size()){
        for (int i = pos; i < size() - 1; i++){
            m_sequence[i] = m_sequence[i + 1];
        }
        m_length--;
        return true;
    } else {
        return false;
    }
}
// If 0 <= pos < size(), remove the item at position pos from
// the sequence (so that all items that followed this item end up at
// positions one lower than they were at before), and return true.
// Otherwise, leave the sequence unchanged and return false.

int Sequence::remove(const ItemType& value){
    int removed = 0;
    for (int i = 0; i < size(); i++){
        if (m_sequence[i] == value){
            erase(i);
            removed++;
        }
    }
    return removed;
}
// Erase all items from the sequence that == value.  Return the
// number of items removed (which will be 0 if no item == value).

bool Sequence::get(int pos, ItemType& value) const{
    if (pos < size() && pos >= 0){
        value = m_sequence[pos];
        return true;
    } else {
        return false;
    }
}
// If 0 <= pos < size(), copy into value the item at position pos
// in the sequence and return true.  Otherwise, leave value unchanged
// and return false.
// #1

bool Sequence::set(int pos, const ItemType& value){
    if (pos < size() && pos >= 0){
        m_sequence[pos] = value;
        return true;
    } else {
        return false;
    }
    
}
// If 0 <= pos < size(), replace the item at position pos in the
// sequence with value and return true.  Otherwise, leave the sequence
// unchanged and return false.

int Sequence::find(const ItemType& value) const{
    int p = -1;
    
    for (int i = 0; i < size(); i++){
        if (m_sequence[i] == value){
            p = i;
        }
    }
    return p;
}
// Let p be the smallest integer such that value == the item at
// position p in the sequence; if no such item exists, let p be -1.
// Return p.
// #1

void Sequence::swap(Sequence& other){
    int size1 = m_length;
    m_length = other.m_length;
    other.m_length = size1;
    
    int size2 = m_limit;
    m_limit = other.m_limit;
    other.m_limit = size2;
    
    ItemType * temp;
    temp = m_sequence;
    m_sequence = other.m_sequence;
    other.m_sequence = temp;
}
// Exchange the contents of this sequence with the other one.
*/
