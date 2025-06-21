#include "UserController.h"

#include <random>
std::random_device rd;
std::mt19937 gen(rd());
int UserController::random(int low, int high)
{
    std::uniform_int_distribution<> dist(low, high);
    return dist(gen);
}
