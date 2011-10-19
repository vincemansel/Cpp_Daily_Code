//
//  findMax.cpp
//  findMax
//
//  Created by Vince Mansel on 10/19/11.
//  Copyright (c) 2011 Wave Ocean Software. All rights reserved.
//

#include <iostream>
#include "simpio.h"
#include "vector.h"
#include "cmpFn.h"

struct Car {
    string name;
    int weight;
    int numAirbags;
};

int SafestCar(Car one, Car two) {
	if (one.numAirbags == two.numAirbags) {
        if (one.weight == two.weight) return 0;
        if (one.weight < two.weight) return -1;
    }
	else if (one.numAirbags < two.numAirbags) return -1;
	return 1;
}

template <typename Type>
Type FindMax(Vector<Type> &v, int (cmpFn)(Type, Type) = OperatorCmp);

int main() {
    
    
    Vector<Car> cars;
    
    Car car;
    car.name = "BMW";
    car.weight = 4500;
    car.numAirbags = 5;
    cars.add(car);
    
    car.name = "Audi";
    car.weight = 4000;
    car.numAirbags = 5;
    cars.add(car);
    
    car.name = "Benz";
    car.weight = 5000;
    car.numAirbags = 5;
    cars.add(car);
    
    Car max = FindMax(cars,SafestCar);
    
    cout << max.name << endl;
    
    
    return 0;
}

template <typename Type>
Type FindMax(Vector<Type> &v, int (cmpFn)(Type, Type)) {
    Type max = v[0];
    
    for (int i = 1; i < v.size(); i++) {
        if (cmpFn(max,v[i]) == -1)
            max = v[i];
    }    
    
    return max;
}

