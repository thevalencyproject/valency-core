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