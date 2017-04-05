//
//  Sober.cpp
//  SoberMagic
//
//  Created by Graham Eger on 4/5/17.
//  Copyright © 2017 Graham Eger. All rights reserved.
//

#include "Sober.hpp"

bool Sober::operator()(const Sober a, const Sober b) const {
    return a.points < b.points;
}

void Sober::operator++() {
    points++;
}

Sober::Sober(std::string in_name, size_t in_points) {
    name = in_name;
    points = in_points;
}

size_t Sober::getPoints() const {
    return points;
}

std::string Sober::getName() const {
    return name;
}
