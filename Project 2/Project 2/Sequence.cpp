//
//  Sequence.cpp
//  Project 2
//
//  Created by Anthony on 1/25/17.
//  Copyright © 2017 CS32. All rights reserved.
//

#include "Sequence.h"

int Sequence::size() const{
    return m_size;
}

bool Sequence::empty() const{
    return size() == 0;
}

Sequence::Sequence(){
    m_size = 0; // start off the list as of size 0
    head = nullptr; // make the new
}

Sequence::~Sequence(){ //When a Sequence is destroyed, the nodes in the linked list must be deallocated.
    Node * p = head;
    while (p != nullptr){
        Node * n = p; // create a temporary pointer that points to the next item
        p = p -> m_next; // delete the current item
        delete n; // set the counting pointer equal to the next item
    }
    delete p; // delete the last item
}

Sequence::Sequence(const Sequence& copy){ //When a brand new Sequence is created as a copy of an existing Sequence, enough new nodes must be allocated to hold a duplicate of the original list.
    //initializing the size
    m_size = copy.size(); // make the size equal to the copy's
    
    bool secondToLast = false; // bool can be used to track when the loop is almost done
    if (copy.empty()){ // if the sequence is empty
        head = nullptr;
    } else {
        Node * p = copy.head; // this will run through the copy
        Node * n = new Node; // this will run through our new sequence
        head = n;
        int i = copy.size(); // since the size will be changing we should remember it here
        while(i != 0 && p -> m_next != nullptr){ // as long as there are still nodes
            if (head == n){ // if it's the first node, ensure it knows going back isn't allowed
                n -> m_backwards = nullptr;
            }
            Node * x = new Node; // create a duplicate node for the new sequence, this will be the next node in the sequence and not the current one
            x -> m_backwards = n; // the duplicate node should connect to the current node
            n -> m_data = p -> m_data; // copy the data over to the current node
            n -> m_next = x; // our new sequence should connect the current node with the next
            n = n -> m_next; // increment both node pointers
            p = p -> m_next;
            i--;
            if (p == nullptr){
                secondToLast = true;
            }
        }
        n -> m_data = p -> m_data; // the last node needs to be set
        n -> m_next = nullptr;
    }
}

Sequence& Sequence::operator=(const Sequence& other){ //When an existing Sequence (the left-hand side) is assigned the value of another Sequence (the right-hand side), the result must be that the left-hand side object is a duplicate of the right-hand side object, with no memory leak of list nodes (i.e. no list node from the old value of the left-hand side should be still allocated yet inaccessible).
    while (!empty()){ // empty the sequence
        erase(0);
    }
    
    if (this != &other){ // check for aliasing
        Sequence test(other); // put the right side of the operator in a temporary variable
        swap(test); // swap the copy of the right hand side with the left hand side
    	// it will get deleted as it is a local copy
    }
    return *this;
}
bool Sequence::insert(int pos, const ItemType& value){
    if (pos < 0 || pos > size()){
        return false;
    }
    
    // IF LIST IS EMPTY
    if (pos == 0 && empty()){
        Node * added = new Node; // make a new node and give it the current node's next
        added -> m_next = nullptr; // in this case is null in both ways
        added -> m_backwards = nullptr;
        added -> m_data = value;
        head = added; // make it the head
        m_size++;
        return true;
    }
    // IF INSERTING AT 0
    if (pos == 0){
        Node * added = new Node; // make a new node and give it the current node's next
        Node * n = head; // make it the head
        added -> m_backwards = nullptr;
        added -> m_next = n; // addition
        added -> m_data = value;
        n -> m_backwards = added;
        head = added;
        m_size++;
        return true;
    }

    // IF INSERTING AT THE END OF THE SEQUENCE
    else if (pos == size()){
        //finding the last node
        Node * n = head;
        while (n -> m_next != nullptr){ // find the end of the sequence
            n = n -> m_next;
        }
        Node * added = new Node;
        added -> m_backwards = n;
        n -> m_next = added;
        added -> m_data= value;
        added -> m_next = nullptr; // there is no next for the last node
        m_size++;
        return true;
    }

    // IF INSERTING SOMEWHERE ELSE IN THE SEQUENCE, INCLUDING THE SECOND TO LAST POS
    Node* n = head;
    int count = 0;
    while (n -> m_next != nullptr) // loop through the nodes
    {
        count++; // count is 1
        n = n -> m_next; // p is in pos 1
        if (count == pos){
            break;
        }
    }
    Node * added = new Node;
    added -> m_backwards = n -> m_backwards;
    added -> m_next = n;
    added -> m_data = value;
    n -> m_backwards -> m_next = added; // connect the new node both ways
    n -> m_backwards = added;
    m_size++;
    return true;
}

int Sequence::insert(const ItemType& value){
    // IF LIST IS EMPTY
    if (empty()){
        insert(0, value);
        return 0;
    }
    
    // INSERT IT IN THE FRONT OF THE LIST
    if (head -> m_data >= value && size() > 0){ // if the head node is bigger
        insert(0, value);
        return 0;
    }
    
    // INSERT IT SOMEWHERE IN LIST
    Node * n = head; // the counter node points to the first node
    for (int i = 0; i < size(); i++){
        if (n -> m_data >= value){ // if the node is bigger
            insert(i, value);
            return i;
        }
        if (n  -> m_next != nullptr){ // if the counter is not the
            n = n -> m_next;
        } else {
            break;
        }
    }
    
    // INSERT IT INTO THE LAST POSITION
    insert(size(), value);
    return size() - 1;
    
    return -1;
}

bool Sequence::erase(int pos){
    if (pos < 0  ||  pos >= size() || head == nullptr){
        return false;
    }
    
    // FIRST AND ONLY POSITION
    if (size() == 1 && pos == 0){
        delete head;
        head = nullptr;
        m_size--;
        return true;
    }
    
    // FIRST POSITION
    if (pos == 0){
        Node * n = head; // point to the first element in the list
        head = n -> m_next;
        delete n;
//        head -> m_backwards = nullptr;
        m_size--;
        return true;
    }
    
    // LAST POSITION
    if (pos == size() - 1){
        Node * n = head; // point to the first element in the list
        while (n -> m_next != nullptr){ // loop until the end
            n = n -> m_next;
        }
        Node * del = n;
        n -> m_backwards -> m_next = del -> m_next;
        delete del;
        m_size--;
        return true;
    }

    // SOMEWHERE ELSE
    Node * n = head; // point to the first element in the list
    int i = 0;
    while (n -> m_next != nullptr){
        if (i == pos){
            break;
        }
        n = n -> m_next;
        i++;
    }
    Node * del = n;
    n -> m_backwards -> m_next = del -> m_next;
    n -> m_next -> m_backwards = del -> m_backwards;
    delete del;
    m_size--;
    return true;
}

int Sequence::remove(const ItemType& value){
    if (empty()){ // if it's empty, can't do anything
        return 0;
    }
    
    int count = 0; // counting variable
    int i = 0; // looping variable
    Node * n = head;
    while (n != nullptr){ // loop through
        if (n -> m_data == value){ // when the value is the one desired
            if (n != nullptr){
                n = n -> m_next; // if it's not the nullptr move it onwards
            } else {
                break;
            }
            erase(i); // erase the wanted located
            i--; // index is not correctly updated as one was just erased
            count++;
        } else {
            if (n != nullptr){
                n = n -> m_next; // if it's not the nullptr move it onwards
            } else {
                break;
            }
        }
        i++;
    }
    return count;
}

bool Sequence::get(int pos, ItemType& value) const{
    if (pos < 0 || pos >= size()){
        return false;
    }
    Node * n = head; // point to the first element in the list
    for (int i = 0; i <= size() - 1; i++){ // loop through all nodes
        if (i == pos){ // when the desired pos is found
            value = n -> m_data; // input the data
            return true;
        }
        if (n != nullptr){
            n = n -> m_next;
        } else {
            return false;
        }
    }
    return true;
}

bool Sequence::set(int pos, const ItemType& value){
    if (pos < 0  ||  pos >= size()){
        return false;
    }
    Node * n = head; // point to the first element in the list
    for (int i = 0; i <= size() - 1; i++){ // loop through all nodes
        if (i == pos){
            n -> m_data = value; // set the data at the requested pos to value
            return true;
        }
        if (n != nullptr){
            n = n -> m_next;
        } else {
            return false;
        }
    }
    return true;
}

int Sequence::find(const ItemType& value) const{
    Node * n = head; // point to the first element in the list
    for (int i = 0; i <= size() - 1; i++){ // loop through indexes
        if (n -> m_data == value){ // if the data matches the desired value
            return i;
        }
        if (n != nullptr){
            n = n -> m_next;
        } else {
            return -1;
        }
    }
    return -1;
}

void Sequence::swap(Sequence& other){
    // swap their heads
    Node * temp = other.head;
    other.head = head;
    head = temp;
    
    // swap sizes
    int tempSize = m_size;
    m_size = other.m_size;
    other.m_size = tempSize;
}

int subsequence(const Sequence& seq1, const Sequence& seq2){
    if (seq1.empty() || seq2.empty() || seq2.size() > seq1.size()){ // if either are empty or the second sequence is bigger than the first,
        return -1;
    }
    
    int foundAt = -1;
    ItemType firstSeq2; // find the first item of the sequence 2
    seq2.get(0, firstSeq2);
    int length = 0;
    ItemType temp; // for swapping
    ItemType value1;
    ItemType value2;
    
    for (int i = 0; i <= seq1.size() - 1; i++){ // use <= so the
        seq1.get(i, value1);
        foundAt = -1; // reset where it is found
        if (value1 == firstSeq2){ // if there is potential
            for (int j = 0; j <= seq2.size() - 1; j++){ // see if they match
                seq1.get(i + j, value1); // i + j as that is where the potential was found
                seq2.get(j, value2);
                if (value2 == value1){ // if they match
                    length++; // increase the length of the potential match
                    foundAt = i; // it's correct so far
                } else { // start over
                    length = 0;
                    break;
                }
            }
            if (length == seq2.size()){ // if the counter is equal to seq 2,
                return foundAt;
            }
            else { // otherwise, if it somehow made it to this point, start over
                length = 0;
            }
        }
    }
    return -1; // if it gets to this point, the search has failed
}

// SUBSEQUENCE FIRST IMPLEMENTATION FAILS IN MATCH BUT NOT IMMEDIATE CASE
//    for (int i = 0; i <= seq1.size() - 1; i++){
//        foundAt = -1; // reset foundAt
//
//        if (seq1.find(firstSeq2) != -1){ // if there is a potential match
//            foundAt = seq1.find(firstSeq2); // set foundAt
//
//            for (int j = 0; j <= seq2.size() - 1; j++){ // go through seq 2
//                ItemType item;
//                seq2.get(j, item);
//                if (seq1.find(firstSeq2) != -1 && seq1.find(firstSeq2) == foundAt + j){
//                    if (j - foundAt == seq2.size() - 1){ // if the length of the sequence is the length of what has been found
//                        return foundAt;
//                    }
//                    continue;
//                } else {
//                    break;
//                }
//            }
//        }
//    }

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result){
    Sequence extra(result); // have to duplicate the sequence in case of aliasing
    while (!extra.empty()){ // empty the duplicate so we can proceed confident that the sequence is what we want it to be
        extra.erase(0);
    }
    
    if (seq1.empty()){ // if sequence 1 is empty, the result will be sequence 2
        extra = seq2;
        result = extra;
        return;
    } else if (seq2.empty()){ // vice versa
        extra = seq1;
        result = extra;
        return;
    }
    
    if (seq1.size() >= seq2.size()){ // if sequence 1 is larger or same size
        ItemType x; // these temp variables will copy items from seq 1 & 2 to result
        ItemType y;
        int seq_1 = 0; // this will count how far we are into seq 1
        int seq_2 = 0; // this will count how far we are into seq 2
        int count = 0; // this will count how far we are into the result
        while (seq_1 != seq1.size()){ // while sequence 1 is not empty
            if (seq_1 != seq1.size()){
                seq1.get(seq_1, x);
                extra.insert(count, x);
                seq_1++;
                count++;
            }
            
            if (seq_2 != seq2.size()){
                seq2.get(seq_2, y);
                extra.insert(count, y);
                seq_2++;
                count++;
            }
        }
    } else { // if sequence 2 is larger
        ItemType x; // these temp variables will copy items from seq 1 & 2 to result
        ItemType y;
        int seq_1 = 0; // this will count how far we are into seq 1
        int seq_2 = 0; // this will count how far we are into seq 2
        int count = 0; // this will count how far we are into the result
        while (seq_2 != seq2.size()){ // while sequence 2 is not empty
            if (seq_1 != seq1.size()){
                seq1.get(seq_1, x);
                extra.insert(count, x);
                seq_1++;
                count++;
            }
            
            if (seq_2 != seq2.size()){
                seq2.get(seq_2, y);
                extra.insert(count, y);
                seq_2++;
                count++;
            }
        }
    }
    result = extra; // done to avoid aliasing
}
