/* This file is a part of The Valency Project which is released under the GNU Lesser General Public License v2.1
   Go to https://github.com/thevalencyproject/valency-core/blob/main/LICENSE for further license details.        */

#include "Random.h"


size_t Random::getRandomNumber(size_t* minimum, size_t* maximum, size_t* seed) {
    // Add refresh onto the seed to ensure randomness
    std::mt19937 Random(*seed + refresh);
    std::uniform_real_distribution<size_t> gen(*minimum, *maximum);
    
    refresh++;
    return gen(Random);
}