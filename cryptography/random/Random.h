/* This file is a part of The Valency Project which is released under the GNU Lesser General Public License v2.1
   Go to https://github.com/thevalencyproject/valency-core/blob/main/LICENSE for further license details.        */

#ifndef RANDOM_H
#define RANDOM_H

#include <random>


class Random {
private:
    int refresh = 0;    // Ensures that seed is different each time (increments each time)

public:
    Random() {}

    // Random Number Generator Function - generates a random number between the inputted minimum and maximum
    size_t getRandomNumber(size_t* minimum, size_t* maximum, size_t* seed);
};

#endif