#include "Random.h"


size_t Random::getRandomNumber(size_t* minimum, size_t* maximum, size_t* seed) {
    // Add refresh onto the seed to ensure randomness
    std::mt19937 Random(*seed + refresh);
    std::uniform_real_distribution<size_t> gen(*minimum, *maximum);
    
    refresh++;
    return gen(Random);
}