//
//  moment.cpp
//  firstAttempt
//
//  Created by артем on 21.04.16.
//  Copyright © 2016 артем. All rights reserved.
//
#include "../include/moments.h"

void Moment::setTime(int dayImp, int monthImp, int yearImp) {
    day = dayImp;
    month = monthImp;
    year = yearImp;
}

void Moment::printInfo() {
    std::cout<< "Day - "<< day<< std::endl
    << "Month - "<< month<< std::endl
    << "Year - "<< year<< std::endl;
}