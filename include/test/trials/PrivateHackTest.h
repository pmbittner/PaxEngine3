//
// Created by Paul on 08.05.2017.
//

#ifndef PAXENGINE3_PRIVATEHACKTEST_H
#define PAXENGINE3_PRIVATEHACKTEST_H

#include <iostream>

namespace PAX { namespace TEST {
    class Victim {
        int x = 0;
        long int y = 0;
        bool b = 0;
    public:
        int getX() {return x;}
        long int getY() {return y;}
        bool isB() {return b;}
    };

    bool HackTest() {
        Victim c;

        int *pointerToX = reinterpret_cast<int*>(&c);
        *pointerToX = 3;

        long int *pointerToY = reinterpret_cast<long int*>(pointerToX + 1);
        *pointerToY = 123;

        bool *pointerToB = reinterpret_cast<bool*>(pointerToY + 1);
        *pointerToB = 1;

        std::cout << c.getX() << " / " << c.getY() << " / " << c.isB() << std::endl;
    }
}}

#endif //PAXENGINE3_PRIVATEHACKTEST_H
