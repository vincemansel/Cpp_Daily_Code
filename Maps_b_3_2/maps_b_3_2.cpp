//
//  maps_b_3_2.cpp
//  maps_b_3_2
//
//  Created by Vince Mansel on 10/7/11.
//  Copyright 2011 Wave Ocean Software. All rights reserved.
//

#include <iostream>
#include "map.h"
#include "vector.h"
#include "simpio.h"

struct pointT {
    int x, y;
};
struct cityT {
    string name;
    pointT coordinates;
};

string ConvertCoordinates(cityT city);

int main() {

    Vector<cityT> cities; 
    
    Map<string> map;
    
    cityT city;
    city.coordinates.x = 1;
    city.coordinates.y = 2;
    city.name = "San Francisco";
    cities.add(city);
    
    city.coordinates.x = 5;
    city.coordinates.y = 6;
    city.name = "Oakland";    
    cities.add(city);
    
    city.coordinates.x = 3;
    city.coordinates.y = 4;
    city.name = "San Jose";    
    cities.add(city);
    
    for (int i = 0; i < cities.size(); i++) {
        string key = ConvertCoordinates(cities[i]);
        map.put(key,cities[i].name);
    }
    
    Map<string>::Iterator itr = map.iterator();
    
    while (itr.hasNext()) {
        string key = itr.next();
        cout << map[key] << "@" << key << endl;
    }
    
    return 0;
}

/*
 * ConvertCoordinaters transform the two integer value into a "unique" key that
 * can be used of storing map data
 */

string ConvertCoordinates(cityT city) {
    string coords;
    coords = IntegerToString(city.coordinates.x) + ":" + IntegerToString(city.coordinates.y);
    return coords;
}