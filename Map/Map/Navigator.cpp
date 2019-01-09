//
//  Navigator.cpp
//  Map
//
//  Created by Anthony on 3/10/17.
//  Copyright © 2017 CS32. All rights reserved.
//

#include "provided.h"
#include <string>
#include <vector>
#include "MyMap.h"
#include <queue>
#include "support.h"
#include <iostream>
using namespace std;

class NavigatorImpl{
public:
    NavigatorImpl();
    ~NavigatorImpl();
    bool loadMapData(string mapFile);
    NavResult navigate(string start, string end, vector<NavSegment>& directions) const;
private:
    SegmentMapper m_segMapObj; // every Navigator will have a segment mapper
    AttractionMapper m_attractMapObj; // and attraction mapper
    
    string findStreet(geoCoord2 g1, geoCoord2 g2) const{
        vector<StreetSegment> segments1 = m_segMapObj.getSegments(g1.m_geoCoord); // get all interacting street segments
        vector<StreetSegment> segments2 = m_segMapObj.getSegments(g2.m_geoCoord); // get all interacting street segments
        for (int i = 0; i < segments1.size(); i++){ // run through them
            for (int j = 0; j < segments2.size(); j++){
                if (segments1[i].streetName == segments2[j].streetName) // if any of them match
                    return segments1[i].streetName; // return which one
            }
        }
        return "name not found for street";
    }
    
    string findDir(const geoCoord2 g1, const geoCoord2 g2) const {
        GeoSegment line = GeoSegment(g1.m_geoCoord, g2.m_geoCoord); // make a line
        double ang = angleOfLine(line); // find it's angle
        
        if (ang >= 0 && ang <= 22.5){ // depending on what the angle is
            return "east"; // it's direction will change
        }
        if (ang > 22.5 && ang <= 67.5){
            return "northeast";
        }
        if (ang > 67.5 && ang <= 112.5){
            return "north";
        }
        if (ang > 112.5 && ang <= 157.5){
            return "northwest";
        }
        if (ang > 157.5 && ang <= 202.5){
            return "west";
        }
        if (ang > 202.5 && ang <= 247.5){
            return "southwest";
        }
        if (ang > 247.5 && ang <= 292.5){
            return "south";
        }
        if (ang > 292.5 && ang <= 337.5){
            return "southeast";
        }
        if (ang > 337.5 && ang <= 360){
            return "east";
        }
        return "";
    }
    
    bool isTurn(geoCoord2 g1, geoCoord2 g2, geoCoord2 g3) const{
        if (findStreet(g1, g2) != findStreet(g2, g3)){ // if the next street is not the same
            return true; // then the next direction is a turn
        }
        return false;
    }
    
    string getTurnDir(geoCoord2 g1, geoCoord2 g2, geoCoord2 g3) const{
        GeoSegment line1(g1.m_geoCoord, g2.m_geoCoord); // create the current segment
        GeoSegment line2(g2.m_geoCoord, g3.m_geoCoord); // create the new street seg
        double ang = angleBetween2Lines(line1, line2); // get their angle

        if ((ang >= 180 && ang <= 360)){ // A turn of 180 degrees or more indicates a right turn.
            return "right";
        }
        if ((ang >= 0 && ang < 180)){ // A turn of less than 180 degrees from one segment onto another indicates a left turn
            return "left";
        }
        return "";
    }
};

NavigatorImpl::NavigatorImpl()
{
}

NavigatorImpl::~NavigatorImpl()
{
}

bool NavigatorImpl::loadMapData(string mapFile){
    MapLoader ml;
    bool loadedFile = ml.load(mapFile); // creates a vector of the street segments
    if (!loadedFile){ // if it fails
        return false; // return so
    }
    bool dir = false;
    m_segMapObj.init(ml); // create a tree of vectors of coordinates of segments
    m_attractMapObj.init(ml); // create a tree of attractions mapped with their geocoordinates
    return true;
}

NavResult NavigatorImpl::navigate(string start, string end, vector<NavSegment> &directions) const{
    geoCoord2 startGeoCoord; // this will be our start
    geoCoord2 endGeoCoord; // this will be our end
    bool created; // this will help us navigate what is pushed on
    bool telling; // used for additional info
    
    MyMap<geoCoord2,geoCoord2> m_map; // this will hold our routes in concentric cirlces
    queue<geoCoord2> m_queue; // this will hold all the possible paths as we solve
    
    m_attractMapObj.getGeoCoord(start, startGeoCoord.m_geoCoord); // load up the geoCoord of the starting loc
    m_attractMapObj.getGeoCoord(end, endGeoCoord.m_geoCoord); // load up the geoCoord of the ending loc
    
    vector<StreetSegment> startingV = m_segMapObj.getSegments(startGeoCoord.m_geoCoord); // get the street segments of the starting loc
    vector<StreetSegment> endingV = m_segMapObj.getSegments(endGeoCoord.m_geoCoord); // get the street segments of the ending loc
    if (startingV.size() == 0 || endingV.size() == 0){ // if either has no street segments
        if (startingV.size() == 0){ // return the appropriate error
            return NAV_BAD_SOURCE;
        }
        if (endingV.size() == 0){
            return NAV_BAD_DESTINATION;
        }
    }
    
    for (int i = 0 ; i < startingV.size(); i++){ // run through the starting street segments
        m_map.associate(startingV[i].segment.start, startGeoCoord); // associate them with the starting and ending geoCoords
        m_queue.push(startingV[i].segment.start); // push it onto potential search locs
        m_map.associate(startingV[i].segment.end, startGeoCoord);
        m_queue.push(startingV[i].segment.end);
    }
    
    int k = startingV.size();
    while (k != 0){ // run through the starting street segments
        if (k == endingV.size()){ // find index of best locs
            telling = true; // is telling information
        }
    }
    
    bool isRoute = false; // we'll use this to find out if there's a route
    while (isRoute == false || m_queue.empty() == false){
        if (m_queue.empty() == true){ // in case nothing has been found yet there is nothing left in the queue
            return NAV_NO_ROUTE;
        }
        
        geoCoord2 inspectedCoord = m_queue.front();
        m_queue.pop();
        
        for (int i = 0; i < endingV.size(); i++){ // let's run through and see if we found a route
            if ((inspectedCoord.m_geoCoord.latitude == endingV[i].segment.end.latitude && inspectedCoord.m_geoCoord.longitude == endingV[i].segment.end.longitude)){ // if there is a match
                m_map.associate(endGeoCoord, inspectedCoord); //
                isRoute = true;
                continue;
            }
            if ((inspectedCoord.m_geoCoord.latitude == endingV[i].segment.start.latitude && inspectedCoord.m_geoCoord.longitude == endingV[i].segment.start.longitude)){ // if there is a match with it's front
                m_map.associate(endGeoCoord, inspectedCoord);
                isRoute = true;
                continue;
            }
        }
        
        vector<StreetSegment> curSegments = m_segMapObj.getSegments(inspectedCoord.m_geoCoord);
        for (int i = 0; i < curSegments.size(); i++){ // let's run through the current spot's segments
            if (m_map.find(curSegments[i].segment.start) == nullptr){ // if it's not already in the map
                m_map.associate(curSegments[i].segment.start, inspectedCoord); // add it
                m_queue.push(curSegments[i].segment.start); // make sure we check it later
            }
            if (m_map.find(curSegments[i].segment.end) == nullptr){
                m_map.associate(curSegments[i].segment.end, inspectedCoord);
                m_queue.push(curSegments[i].segment.end);
            }
        }
    } // end of while loop
    
    vector<geoCoord2> solved; // if we've made it here, there is a path
    geoCoord2 geoIterator = endGeoCoord; // we need to add the path backwards
    while (!(geoIterator.m_geoCoord.longitude == startGeoCoord.m_geoCoord.longitude && geoIterator.m_geoCoord.latitude == startGeoCoord.m_geoCoord.latitude)){ // while we haven't reached the start
        const geoCoord2 * value = m_map.find(geoIterator); // find the current geoCoord
        solved.push_back(*value); // add it to the list
        geoIterator = *value;
    }
    
    solved[0] = endGeoCoord;
    
    int queueSize = solved.size() - 1;
    for (int i = queueSize; i > 0; i--){ // we need to add backwards
        NavSegment navSeg = NavSegment(findDir(solved[i].m_geoCoord, solved[i - 1].m_geoCoord), findStreet(solved[i].m_geoCoord, solved[i - 1].m_geoCoord), distanceEarthMiles(solved[i].m_geoCoord, solved[i - 1].m_geoCoord), GeoSegment(solved[i].m_geoCoord, solved[i - 1].m_geoCoord)); // get all the necessary functions
        directions.push_back(navSeg); // add it to the directions
        
        if (i >= 2 && isTurn(solved[i], solved[i - 1], solved[i - 2])){ // if the next direction is a turn
            NavSegment turnNavSeg = NavSegment(getTurnDir(solved[i], solved[i - 1], solved[i - 2]), findStreet(solved[i - 1], solved[i - 2])); // get the specific turn directions
            directions.push_back(turnNavSeg); // add it to the directions
        }
    }
    
    return NAV_SUCCESS;
    
}

//******************** Navigator functions ************************************

// These functions simply delegate to NavigatorImpl's functions.
// You probably don't want to change any of this code.

Navigator::Navigator()
{
    m_impl = new NavigatorImpl;
}

Navigator::~Navigator()
{
    delete m_impl;
}

bool Navigator::loadMapData(string mapFile)
{
    return m_impl->loadMapData(mapFile);
}

NavResult Navigator::navigate(string start, string end, vector<NavSegment>& directions) const
{
    return m_impl->navigate(start, end, directions);
}
