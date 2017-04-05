//
//  Sober.hpp
//  SoberMagic
//
//  Created by Graham Eger on 4/5/17.
//  Copyright © 2017 Graham Eger. All rights reserved.
//

#ifndef Sober_hpp
#define Sober_hpp

#include <iostream>

// A class that represents a potential sober monitor
class Sober
{
public:
    // Overload the operator for sorting and priority queues, only compares the points
    bool operator()(const Sober a, const Sober b) const;
    
    // Overload prefix increment operator
    void operator++();
    
    // a custom constructor that takes a string as the name and a size_t as points
    Sober(std::string in_name, size_t in_points);

    // Getter for points and name, we should never set. Only increment by 1
    size_t getPoints() const;
    std::string getName() const;
    
private:
    std::string name;
    size_t points;
};

#endif /* Sober_hpp */
