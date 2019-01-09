//
//  SegmentMapper.cpp
//  Map
//
//  Created by Anthony on 3/10/17.
//  Copyright © 2017 CS32. All rights reserved.
//

#include "provided.h"
#include "MyMap.h"
#include <vector>
using namespace std;

class SegmentMapperImpl
{
public:
    SegmentMapperImpl();
    ~SegmentMapperImpl();
    void init(const MapLoader& ml);
    vector<StreetSegment> getSegments(const GeoCoord& gc) const;
private:
    MyMap<string, vector<StreetSegment>> m_segmentMapper; // will be a string of the coordinates
};

SegmentMapperImpl::SegmentMapperImpl()
{
}

SegmentMapperImpl::~SegmentMapperImpl()
{
}

void SegmentMapperImpl::init(const MapLoader& ml){
    int size = ml.getNumSegments();
    for (int i = 0; i < size; i++){
        StreetSegment temp;
        ml.getSegment(i, temp); // get each segment
        string geoCoordText1 = temp.segment.start.latitudeText + temp.segment.start.longitudeText;
        string geoCoordText2 = temp.segment.end.latitudeText + temp.segment.end.longitudeText;

        // start coordinates
        vector<StreetSegment> v;
        if (m_segmentMapper.find(geoCoordText1) != nullptr){ // if it's not the first item
        	v = *(m_segmentMapper.find(geoCoordText1));
            v.push_back(temp);
            m_segmentMapper.associate(geoCoordText1, v);
        } else { // if it is the first item
            v.push_back(temp);
            m_segmentMapper.associate(geoCoordText1, v);
        }

        // end coordinates
        vector<StreetSegment> v2;
        if (m_segmentMapper.find(geoCoordText2) != nullptr){ // if it's not the first item
            v2 = *(m_segmentMapper.find(geoCoordText2));
            v2.push_back(temp);
            m_segmentMapper.associate(geoCoordText2, v2);
        } else { // if it is the first item
            v2.push_back(temp);
            m_segmentMapper.associate(geoCoordText2, v2);
        }
        
        // attractions
        vector<StreetSegment> vt;
        for (int j = 0; j < temp.attractions.size(); j++){
            string geoCoordText3 = temp.attractions[j].geocoordinates.latitudeText + temp.attractions[j].geocoordinates.longitudeText;
            vector<StreetSegment> v3;
            if (m_segmentMapper.find(geoCoordText3) != nullptr){ // if it's not the first item
                v3 = *m_segmentMapper.find(geoCoordText3);
                v3.push_back(temp);
                m_segmentMapper.associate(geoCoordText3, v3);
            } else { // if it is the first item
                v3.push_back(temp);
                m_segmentMapper.associate(geoCoordText3, v3);
            }
        }
    }
}

vector<StreetSegment> SegmentMapperImpl::getSegments(const GeoCoord& gc) const{
    string s = gc.latitudeText + gc.longitudeText;
    vector<StreetSegment> streets;
    if (m_segmentMapper.find(s) != nullptr){ // as long as it's not a nullptr
        return *(m_segmentMapper.find(s)); // it's fine to return (the dereferenced version)
	}
    vector<StreetSegment> garbage; // otherwise it is a nullptr and we should return an empty vector
    return garbage;
}

//******************** SegmentMapper functions ********************************

// These functions simply delegate to SegmentMapperImpl's functions.
// You probably don't want to change any of this code.

SegmentMapper::SegmentMapper()
{
    m_impl = new SegmentMapperImpl;
}

SegmentMapper::~SegmentMapper()
{
    delete m_impl;
}

void SegmentMapper::init(const MapLoader& ml)
{
    m_impl->init(ml);
}

vector<StreetSegment> SegmentMapper::getSegments(const GeoCoord& gc) const
{
    return m_impl->getSegments(gc);
}
