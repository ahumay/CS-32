//
//  MapLoader.cpp
//  Map
//
//  Created by Anthony on 3/10/17.
//  Copyright © 2017 CS32. All rights reserved.
//

#include "provided.h"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

class MapLoaderImpl
{
public:
    MapLoaderImpl();
    ~MapLoaderImpl();
    bool load(string mapFile);
    size_t getNumSegments() const;
    bool getSegment(size_t segNum, StreetSegment& seg) const;
private:
    int m_numSegments;
    int m_numAttractions;
    vector<StreetSegment> m_segments;
};

MapLoaderImpl::MapLoaderImpl()
{
    m_numSegments = 0; // will keep track of segments
	m_numAttractions = 0; // will keep track of attractions
}

MapLoaderImpl::~MapLoaderImpl()
{
}

bool MapLoaderImpl::load(string mapFile)
{
    ifstream infile(mapFile);
    if (!infile){ // if the creation of the ifstream format failed
        cerr << "Error while loading data file." << endl; // make not of it
        return false;
    }
    string str = "";
    while (getline(infile, str)){ // while there are lines in the file to get
        StreetSegment seg; // this will be the street segment we add
        seg.streetName = str; // give it it's name
        
        string yCoor1; // in the file, the start point's y coord comes first
        string xCoor1; // then x

        getline(infile, yCoor1, ',');
        
        char format;
        infile.get(format); // the format may not always have a space in between
        if (format != ' '){ // if it doesn;t
            getline(infile, xCoor1, ' '); // this is the xCoor1
            xCoor1 = format + xCoor1;
        } else { // if it doesn't
            getline(infile, xCoor1, ' '); // this is just a garbage value
        }
        
        string yCoor2; // then the y and x of the end point
        getline(infile, yCoor2, ',');
        
        string xCoor2;
        getline(infile, xCoor2, '\n');
        
        GeoCoord start = GeoCoord(yCoor1, xCoor1); // get the start and end points
        GeoCoord end = GeoCoord(yCoor2, xCoor2);
        GeoSegment geoSeg = GeoSegment(start, end); // create a geosegment
        seg.segment = geoSeg; // add the geosegment to the street segment

        getline(infile, str); // get the number of attractions
        int numAttractions = stoi(str);
        for (int i = 0; i < numAttractions; i++){
            Attraction newAttract; // we will add this attraction
            
            string attractName;
            getline(infile, attractName, '|'); // get the name
            
            string attractY;
            getline(infile, attractY, ','); // get the latitude
            
            string attractX;
            char format2;
            infile.get(format2); // same as for the normal coordinates
            if(format2 != ' '){ // if it doesn't have a space
                getline(infile, attractX, '\n'); // then it's the coordinate
                attractX = format2 + attractX;
            } else { // if it does
                getline(infile, attractX, '\n'); // then it's not
            }
            
            newAttract.name = attractName; // give it a name
            GeoCoord G = GeoCoord(attractY, attractX);  // add the geo coord
            newAttract.geocoordinates = G;
            seg.attractions.push_back(newAttract); // add it to the vector
            m_numAttractions++; // increment
        }
        m_segments.push_back(seg); // add the street segment
        m_numSegments++;
    }
    
    return true;
}

size_t MapLoaderImpl::getNumSegments() const
{
    return m_numSegments;
}

bool MapLoaderImpl::getSegment(size_t segNum, StreetSegment &seg) const
{
    if (segNum < 0 || segNum >= m_segments.size()){ // if the passed in segNum is bad access
        return false;
    }
    
    seg = m_segments[segNum];
    return true;
}

//******************** MapLoader functions ************************************

// These functions simply delegate to MapLoaderImpl's functions.
// You probably don't want to change any of this code.

MapLoader::MapLoader()
{
    m_impl = new MapLoaderImpl;
}

MapLoader::~MapLoader()
{
    delete m_impl;
}

bool MapLoader::load(string mapFile)
{
    return m_impl->load(mapFile);
}

size_t MapLoader::getNumSegments() const
{
    return m_impl->getNumSegments();
}

bool MapLoader::getSegment(size_t segNum, StreetSegment& seg) const
{
    return m_impl->getSegment(segNum, seg);
}
