//
//  main.cpp
//  Map
//
//  Created by Anthony on 3/10/17.
//  Copyright © 2017 CS32. All rights reserved.
//

#include <iostream>
#include "MyMap.h"
#include "provided.h"
using namespace std;

void foo()
{
    MyMap<string,double> nameToGPA; // maps student name to GPA
    // add new items to the binary search tree-based map
    nameToGPA.associate("Carey", 3.5); // Carey has a 3.5 GPA
    nameToGPA.associate("David", 3.99); // David beat Carey
    nameToGPA.associate("Abe", 3.2); // Abe has a 3.2 GPA
    
    double* davidsGPA = nameToGPA.find("David");
    double* careys = nameToGPA.find("Carey");
    if (davidsGPA != nullptr)
        *davidsGPA = 1.5; // after a re-grade of David’s exam
    
    nameToGPA.associate("Carey", 4.0); // Carey deserves a 4.0
    // replaces old 3.5 GPA
    double* lindasGPA = nameToGPA.find("Linda");
    if (lindasGPA == nullptr)
        cout << "Linda is not in the roster!" << endl;
    else
        cout << "Linda’s GPA is: " << *lindasGPA << endl;
    cout << "Carey GPA is: " << *careys << endl;
    cout << "David GPA is: " << *davidsGPA << endl;
}

//void example(const MapLoader& ml)
//{
//    AttractionMapper am;
//    am.init(ml); // let our object build its internal data structures
//    // by iterating thru all segments from the MapLoader object
//    GeoCoord fillMe;
//    string attraction = "The Coffee Bean & Tea Leaf";
//    bool found = am.getGeoCoord(attraction, fillMe);
//    if ( ! found)
//    {
//        cout << "No geolocation found for " << attraction << endl;
//        return;
//    }
//    cout << "The location of " << attraction << " is " << fillMe.latitude << ", " << fillMe.longitude << endl;
//}

void example(const MapLoader& ml)
{
    SegmentMapper sm;
    sm.init(ml); // let our object build its internal data structures
    // by iterating thru all segments from the MapLoader object
    GeoCoord lookMeUp("34.0572000", "-118.4417620");
    std::vector<StreetSegment> vecOfAssociatedSegs(sm.getSegments(lookMeUp));
    if (vecOfAssociatedSegs.empty())
    {
        cout << "Error - no segments found matching this coordinate\n";
        return;
    }
    cout << "Here are all the segments associated with your coordinate:" << endl;
    for (auto s: vecOfAssociatedSegs)
    {
        cout << "Segment’s street: " << s.streetName << endl;
        cout << "Segment’s start lat/long: " << s.segment.start.latitudeText << ", " <<
        s.segment.start.longitudeText << endl;
        cout << "Segment’s end lat/long: " << s.segment.end.latitudeText << ", " <<
        s.segment.end.longitudeText << endl;
        cout << "This segment has " << s.attractions.size() <<
        " attractions on it." << endl;
    }
}

int main(int argc, const char * argv[]) {
//    foo();
//    MapLoader ml;
//    ml.load("/Users/Humay/Desktop/Map/mapdata.txt");
//    example(ml);
    Navigator nav;
    nav.loadMapData("/Users/Humay/Desktop/Map/mapdata.txt");
    vector<NavSegment> directions;
    nav.navigate("Westwood Sporting Goods", "Easton Softball Stadium", directions);
//    nav.navigate("1061 Broxton Avenue", "Headlines!" , directions);
//    nav.navigate("Eros Statue", "Hamleys Toy Store", directions);

    cerr << "Navigation dir size : " << directions.size() << endl;
    for (int k = 0; k < directions.size(); k++){
        if (directions[k].m_command == 1){
            cout << "Turn " << directions[k].m_direction << " on to " << directions[k].m_streetName << endl << endl;
        } else
            cout << "Proceed " << directions[k].m_direction << " on " << directions[k].m_streetName << " for " << directions[k].m_distance << " miles" << endl << endl;
                    cout << "The direction is: " << directions[k].m_direction << " on " << directions[k].m_streetName << " for " << directions[k].m_distance << endl << endl;
    }

}
