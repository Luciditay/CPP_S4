#include "hangman.hpp"

static constexpr int LIVES = 5;

std::string wordToUnderscore(std::string& word)
{
    std::string word_underscored = word;
    for (unsigned int i = 0; i < word.size(); i++) {
        word_underscored[i] = '_';
    }
    return word_underscored;
}

char getLetterFromUser()
{
    char lettre = 'a';
    std::cout << "Entrez une lettre" << std::endl;
    std::cin >> lettre;
    return lettre;
}

Hangman::Hangman(int lives, const std::vector<std::string>& possibleWords)
    : m_lives(lives), m_wordToGuess(pick_random_words(possibleWords))
{
    m_wordForUser = wordToUnderscore(m_wordToGuess);
}

int rand(int min, int max)
{
    static std::default_random_engine  generator{std::random_device{}()};
    std::uniform_int_distribution<int> distribution{min, max};
    return distribution(generator);
}

std::string pick_random_words(const std::vector<std::string>& possibleWords)
{
    if (!possibleWords.empty()) {
        unsigned int wordId = rand(0, possibleWords.size() - 1);
        return possibleWords.at(wordId);
    }
    std::cout << "L'ensemble des mots possible est vide ! Arrêt du programme." << std::endl;
    exit(EXIT_FAILURE);
}

int Hangman::letterInWordToGuess(char lettre)
{
    int letterCount = 0;
    for (unsigned int i = 0; i < m_wordToGuess.length(); i++) {
        if (lettre == m_wordToGuess.at(i)) {
            m_wordForUser[i] = lettre;
            letterCount++;
        }
    }
    return letterCount;
}

bool Hangman::letterAlreadyGuesssed(char lettre)
{
    for (auto i : m_alreadyGuessedLetters) {
        if (lettre == i) {
            return true;
        }
    }
    return false;
    ;
}

bool Hangman::player_is_alive()
{
    return (m_lives > 0);
}

void Hangman::removeOneLife()
{
    m_lives--;
}

bool Hangman::player_has_won()
{
    return (m_guessedLetters == m_wordToGuess.length());
}

void Hangman::play_game()
{
    std::cout << "Here is the word still to guess : " << m_wordForUser << std::endl;
    while (player_is_alive() && !player_has_won()) {
        std::cout << "You have " << m_lives << " lifes" << std::endl;
        std::cout << m_wordForUser << std::endl;
        m_userInput = getLetterFromUser();
        while (letterAlreadyGuesssed(m_userInput)) {
            std::cout << "You already picked up the letter " << m_userInput << ". Choose another one please." << std::endl;
            std::cout << m_wordForUser << std::endl;
            m_userInput = getLetterFromUser();
        }
        if (letterInWordToGuess(m_userInput)) {
            m_guessedLetters += letterInWordToGuess(m_userInput);
            std::cout << "Correct !" << std::endl;
        }
        else {
            removeOneLife();
            std::cout << "Wrong !" << std::endl;
        }
        m_alreadyGuessedLetters.push_back(m_userInput);
    }

    if (player_has_won()) {
        std::cout << "You win ! You succesfully guessed " << m_wordToGuess << std::endl;
    }
    else {
        std::cout << "You lost ! The word to guess was " << m_wordToGuess << std::endl;
    }
}

void launch_game(const std::vector<std::string>& possibleWords)
{
    Hangman hangman(LIVES, possibleWords);
    std::cout << "Welcome to Hangman !" << std::endl;
    hangman.play_game();
}