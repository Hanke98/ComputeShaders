//
// Created by ljf on 2020/6/30.
//

#include "MathUtils.h"
#include <cstdlib>
#include <random>

float MathUtils::RandomFloat() {
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

float MathUtils::RandomFloat(float lb, float ub) {
    std::default_random_engine generator;
    std::uniform_real_distribution<float>u (lb, ub);
    return u(generator);
}

