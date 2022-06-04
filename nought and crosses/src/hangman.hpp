#include <iostream>
#include <random>

std::string wordToUnderscore(std::string& word);

std::string pick_random_words();

char getLetterFromUser();

class Hangman

{
private:
    int               m_lives;
    char              m_userInput;
    std::string       m_wordToGuess;
    std::string       m_wordForUser;
    unsigned int      m_guessedLetters = 0;
    std::vector<char> m_alreadyGuessedLetters;

public:
    explicit Hangman(int lives);

    int letterInWordToGuess(char lettre);

    bool player_is_alive();
    void removeOneLife();

    bool player_has_won();

    bool letterAlreadyGuesssed(char lettre);

    void play_game();

    bool endGame();
};

void launch_game();