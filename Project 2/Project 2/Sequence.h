//
//  Sequence.hpp
//  Project 2
//
//  Created by Anthony on 1/25/17.
//  Copyright © 2017 CS32. All rights reserved.
//

#ifndef Sequence_h
#define Sequence_h

#include <string>
typedef std::string ItemType;
//typedef unsigned long ItemType;

class Sequence
{
public:
    Sequence();
    ~Sequence();
    Sequence(const Sequence& copy);
    Sequence& operator=(const Sequence& copy);
    bool empty() const;
    int size() const;
    bool insert(int pos, const ItemType& value);
    int insert(const ItemType& value);
    bool erase(int pos);
    int remove(const ItemType& value);
    bool get(int pos, ItemType& value) const;
    bool set(int pos, const ItemType& value);
    int find(const ItemType& value) const;
    void swap(Sequence& other);
private:
    struct Node{
        ItemType m_data; // the value of the node
        Node * m_next; // what the node is pointing at
        Node * m_backwards; // where the node came from
    };
    
    int m_size; // number of items in the sequence
    Node * head; // a pointer pointing to the first Node in the sequence
};

int subsequence(const Sequence& seq1, const Sequence& seq2); // non-member functions

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result); // non-member

#endif /* Sequence_h */
