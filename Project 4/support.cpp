//
//  support.cpp
//  Map
//
//  Created by Anthony on 3/13/17.
//  Copyright © 2017 CS32. All rights reserved.
//

#include "support.h"

geoCoord2::geoCoord2(GeoCoord original){
    m_geoCoord = original;
}

GeoCoord geoCoord2::getGeoCoord2(){
    return m_geoCoord;
}

bool geoCoord2::operator < (const geoCoord2& compare) const{
    if (m_geoCoord.longitude < compare.m_geoCoord.longitude){
        return true;
    }
    if (m_geoCoord.latitude < compare.m_geoCoord.latitude){
        return true;
    }
    return false;
}


bool geoCoord2::operator == (const geoCoord2& compare) const{
    if (m_geoCoord.latitude == compare.m_geoCoord.latitude && m_geoCoord.longitude == compare.m_geoCoord.longitude){
        return true;
    }
    return false;
}

bool geoCoord2::operator > (const geoCoord2& compare) const{
    if (m_geoCoord.longitude > compare.m_geoCoord.longitude){
        return true;
    }
    if (m_geoCoord.latitude > compare.m_geoCoord.latitude){
        return true;
    }
    return false;
}
