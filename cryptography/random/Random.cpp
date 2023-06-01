#include "Random.h"


int Random::getRandomNumber(int* minimum, int* maximum, int* seed) {
    // Add refresh onto the seed to ensure randomness
    std::mt19937 Random(*seed + refresh);
    std::uniform_int_distribution<int> gen(*minimum, *maximum);

    refresh++;
    return gen(Random);
}