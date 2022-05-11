#include "guessNumber.hpp"

int rand(int min, int max)
{
    static std::default_random_engine  generator{std::random_device{}()};
    std::uniform_int_distribution<int> distribution{min, max};
    return distribution(generator);
}

int pick_random_number()
{
    return rand(0, MaxRange);
}

int getNumberfromuser()
{
    int input = 0;
    std::cout << "Pick a number" << std::endl;
    std::cin >> input;
    return input;
}

bool InputHigherThanNumber(int input, int number)
{
    return (input > number);
}

bool InputLowerThanNumber(int input, int number)
{
    return (input < number);
}

bool InputEqualNumber(int input, int number)
{
    return (input == number);
}

void play_the_game()
{
    std::cout << "Let's play Guess-The-Number the game !" << std::endl;
    std::cout << "The number to guess in between 0 and " << MaxRange << std::endl;
    int  userInput     = getNumberfromuser();
    int  numberToGuess = pick_random_number();
    bool finished      = false;
    while (!finished) {
        if (InputEqualNumber(userInput, numberToGuess)) {
            finished = true;
            std::cout << "You won !" << std::endl;
        }
        else if (InputHigherThanNumber(userInput, numberToGuess)) {
            std::cout << "Smaller" << std::endl;
            userInput = getNumberfromuser();
        }
        else {
            std::cout << "Higher" << std::endl;
            userInput = getNumberfromuser();
        }
    }
}