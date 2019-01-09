//
//  support.hpp
//  Map
//
//  Created by Anthony on 3/13/17.
//  Copyright © 2017 CS32. All rights reserved.
//

#ifndef support_h
#define support_h

#include "provided.h"

class geoCoord2{ // will be a simple class that basically extends geo coord with overloaded operators
public:
    geoCoord2(GeoCoord a); // simply need the geoCoord
    geoCoord2(){} // constructor
    ~geoCoord2(){} // destructor 
    GeoCoord getGeoCoord2(); // get m_realCoord
    bool operator > (const geoCoord2& other) const;
    bool operator < (const geoCoord2& other) const;
    bool operator == (const geoCoord2& other) const;
    GeoCoord m_geoCoord;
private:
};

#endif /* support_h */
