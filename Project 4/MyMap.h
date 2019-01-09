//
//  MyMap.hpp
//  Projct 4
//
//  Created by Anthony on 3/8/17.
//  Copyright © 2017 CS32. All rights reserved.
//

// TODO: erase directions in navigator, loadMapData in Navigator just comes from file path

#ifndef MyMap_h
#define MyMap_h

// MyMap.h

// Skeleton for the MyMap class template.  You must implement the first six
// member functions.

template<typename KeyType, typename ValueType>
class MyMap
{
public:
    // CONSTRUCTOR
    MyMap(){
        m_root = nullptr;
        m_numItems = 0;
    }
    
    // DESTRUCTOR
    ~MyMap(){
        clear();
    }
    
    void clear(){
        freeTree(m_root); // will recursively delete all
        m_root = nullptr; // in case clear is called not from the destructor
        m_numItems = 0; // in case clear is called not from the destructor
    }
    
    int size() const{
        return m_numItems;
    }
    
    //	The	associate	method	associates	one	item	(key)	with	another	(value).
    //	If	no	association	currently	exists	with	that	key,	this	method	inserts
    //	a	new	association	into	the	tree	with	that	key/value	pair.		If	there	is
    //	already	an	association	with	that	key	in	the	tree,	then	the	item
    //	associated	with	that	key	is	replaced	by	the	second	parameter	(value).
    //	Thus,	the	tree	contains	no	duplicate	keys.
    void associate(const KeyType& key, const ValueType& value);
    
    //	If	no	association	exists	with	the	given	key,	return	nullptr;	otherwise,
    //	return	a	pointer	to	the	value	associated	with	that	key.		This	pointer	can	be
    //	used	to	examine	that	value,	and	if	the	map	is	allowed	to	be	modified,	to
    //	modify	that	value	directly	within	the	map (the	second	overload	enables
    //	this).		Using	a	little	C++	magic,	we	have	implemented	it	in	terms	of	the
    //	first	overload,	which	you	must	implement.
    
    // for a map that can't be modified, return a pointer to const ValueType
    const ValueType* find(const KeyType& key) const;
    
    // for a modifiable map, return a pointer to modifiable ValueType
    ValueType* find(const KeyType& key)
    {
        return const_cast<ValueType*>(const_cast<const MyMap*>(this)->find(key));
    }
    
    // C++11 syntax for preventing copying and assignment
    MyMap(const MyMap&) = delete;
    MyMap& operator=(const MyMap&) = delete;
    
private:
    struct Node {
        KeyType m_first; // for the key
        ValueType m_second; // for the value
        Node * m_left = nullptr; // default is set to nullptr
        Node * m_right = nullptr;
    };
    
    void freeTree(Node * cur){// design based off Nachenburg's lecture 12 page 50
        if (cur == nullptr){
            return;
        }
        freeTree(cur -> m_left);
        freeTree(cur -> m_right);
        delete cur;
    }
    
//    queue<Node *> m_data;
    Node * m_root;
    int m_numItems; // will be two times the number of items in the base layer
};

// IMPLEMENTATIONS
class Node;
template<typename KeyType, typename ValueType>
const ValueType* MyMap<KeyType, ValueType>::find(const KeyType& key) const{
    Node * temp = m_root;
    while (temp != nullptr){ // we search through the tree
        if (temp -> m_first == key){ // if it's equal
            break; // break out of the loop
        } else if (temp -> m_first > key){ // if the key is less
            temp = temp -> m_left; // go left and keep looking
            continue;
        } else if (temp -> m_first < key){ // otherwise
            temp = temp -> m_right; // go right
            continue;
        } else {
            return nullptr; // and if it gets here it's not in the tree
        }
	}
    if (temp != nullptr){ // as long as it's not nullpur
        return &(temp -> m_second); // return a reference the ValueType
    } else {
        return nullptr;
    }
}

template<typename KeyType, typename ValueType>
void MyMap<KeyType, ValueType>::associate(const KeyType& key, const ValueType& value){
    if (m_root == nullptr){ // if the 
        m_root = new Node;
        m_root -> m_first = key;
        m_root -> m_second = value;
        m_root -> m_left = nullptr;
        m_root -> m_right = nullptr;
        m_numItems++;
    } else {
        Node * current = m_root;
        while (m_numItems != 1000000000000){ // infinite loop
            if (current -> m_first == key){ // if it already exists
                current -> m_second = value; // override it with the second one
                return;
            }
            if (current -> m_first > key){
                if (current -> m_left == nullptr){
                    current -> m_left = new Node;
                    current -> m_left -> m_first = key;
                    current -> m_left -> m_second = value;
                    current -> m_left -> m_left = nullptr;
                    current -> m_left -> m_right = nullptr;
                    m_numItems++;
                    break;
                } else {
                    current = current -> m_left;
                }
            } else {
                if (current -> m_right == nullptr){
                    current -> m_right = new Node;
                    current -> m_right -> m_first = key;
                    current -> m_right -> m_second = value;
                    current -> m_right -> m_left = nullptr;
                    current -> m_right -> m_right = nullptr;
                    m_numItems++;
                    break;
                } else {
                    current = current -> m_right;
                }
            }
        } // end of while
    }
}


#endif /* MyMap_h */

