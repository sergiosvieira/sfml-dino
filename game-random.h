#ifndef GAMERANDOM_H
#define GAMERANDOM_H

#include <random>

static std::random_device rd;
static std::mt19937 mt(rd());
static std::uniform_real_distribution<double> urd(0., 3.);
static std::uniform_real_distribution<double> nor(0., 1.);

#endif // GAMERANDOM_H
