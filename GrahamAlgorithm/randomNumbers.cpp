#include "randomNumbers.h"
#include <random>
#define min 0.0
#define max 100.0
#define precision 2
float randomFloat() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);

    float randomNum = dis(gen);
    randomNum = roundf(randomNum * pow(10, precision)) / pow(10, precision);
    return randomNum;
}