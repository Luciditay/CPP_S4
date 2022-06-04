#include "menu.hpp"
#include "guessNumber.hpp"
#include "hangman.hpp"

void showMenu()
{
    std::cout << "What do you want to do ?" << std::endl;
    std::cout << "1 <-- Play Guess the Number" << std::endl;
    std::cout << "2 <-- Play Hangman" << std::endl;
    std::cout << "q <-- Quit the menu" << std::endl;
}

void chooseGame()
{
    bool quit = false;
    while (!quit) {
        showMenu();
        char command = getLetterFromUser();

        switch (command) {
        case '1':
            play_guess_number();
            quit = true;
            break;

        case '2':
            launch_game();
            quit = true;
            break;

        case 'q':
            quit = true;
            break;

        default:
            std::cout << "I don't know that command." << std::endl;
            break;
        }
    }
}