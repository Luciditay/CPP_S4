#include <iostream>
#include <random>
#include "hangman.hpp"

int main()
{
    std::vector<std::string> allWords = {"cattle", "coding", "cinema", "melenchon", "nupes"};
    launch_game(allWords);
    // std::cout << wordToUnderscore(allWords[0]) << std::endl;
}