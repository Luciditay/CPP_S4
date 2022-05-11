#include <iostream>
#include <random>

static constexpr int MaxRange = 200;

void play_the_game();

int rand(int min, int max);
int pick_random_number();

int getNumberfromuser();

bool InputHigherThanNumber(int input, int number);
bool InputLowerThanNumber(int input, int number);
bool InputEqualNumber(int input, int number);
