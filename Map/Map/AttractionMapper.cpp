//
//  AttractionMapper.cpp
//  Map
//
//  Created by Anthony on 3/10/17.
//  Copyright © 2017 CS32. All rights reserved.
//

#include "provided.h"
#include <string>
#include "MyMap.h"
using namespace std;

class AttractionMapperImpl
{
public:
    AttractionMapperImpl();
    ~AttractionMapperImpl();
    void init(const MapLoader& ml);
    bool getGeoCoord(string attraction, GeoCoord& gc) const;
private:
    MyMap<string, GeoCoord> m_attractionMap;
};

AttractionMapperImpl::AttractionMapperImpl()
{
}

AttractionMapperImpl::~AttractionMapperImpl()
{
}

void AttractionMapperImpl::init(const MapLoader& ml){
    int size = ml.getNumSegments();
    for (int i = 0; i < size; i++){
        StreetSegment temp;
        bool foundAt = false;
        ml.getSegment(i, temp); // get each segment
        if (temp.attractions.size() != 0){ // only add this segment to the map if it has attractions
            for (int j = 0; j < temp.attractions.size(); j++){
                string str = "";
                foundAt = true;
                for (int k = 0; k < temp.attractions[j].name.size(); k++){ // make everything lowercase
                    str += tolower(temp.attractions[j].name[k]);
                }
        		m_attractionMap.associate(str, temp.attractions[j].geocoordinates); // add this 
            }
        }
    }
}

bool AttractionMapperImpl::getGeoCoord(string attraction, GeoCoord& gc) const{
    string str = "";
    for (int k = 0; k < attraction.size(); k++){ // make everything lowercase
        str += tolower(attraction[k]);
    }
    if (m_attractionMap.find(str) != nullptr){ // the attraction may not be in the map
    	gc = *m_attractionMap.find(str);
    	return true;
    }
    return false;
}

//******************** AttractionMapper functions *****************************

// These functions simply delegate to AttractionMapperImpl's functions.
// You probably don't want to change any of this code.

AttractionMapper::AttractionMapper()
{
    m_impl = new AttractionMapperImpl;
}

AttractionMapper::~AttractionMapper()
{
    delete m_impl;
}

void AttractionMapper::init(const MapLoader& ml)
{
    m_impl->init(ml);
}

bool AttractionMapper::getGeoCoord(string attraction, GeoCoord& gc) const
{
    return m_impl->getGeoCoord(attraction, gc);
}
