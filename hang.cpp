#include <iostream>
#include <cstring>
#include <ctime>
#include <cstdlib>

using namespace std;

// Node to represent a character in the secret word
struct Node {
    char data;
    Node* next;

    Node(char ch) : data(ch), next(nullptr) {}
};

class HangmanGame {
private:
    Node* secretWord;
    char* guessedLetters;
    int attemptsLeft;

public:
    HangmanGame() : secretWord(nullptr), guessedLetters(nullptr), attemptsLeft(6) {
        initializeWord();
        guessedLetters = new char[26];
        memset(guessedLetters, 0, sizeof(char) * 26);
    }

    ~HangmanGame() {
        while (secretWord) {
            Node* temp = secretWord;
            secretWord = secretWord->next;
            delete temp;
        }
        delete[] guessedLetters;
    }

    void initializeWord() {
        const char* words[] = {"programming", "hangman", "algorithm", "cplusplus", "developer", "learning"};
        srand(time(nullptr));
        const char* selectedWord = words[rand() % (sizeof(words) / sizeof(words[0]))];

        for (int i = 0; i < strlen(selectedWord); ++i) {
            insertCharacter(selectedWord[i]);
        }
    }

    void insertCharacter(char ch) {
        Node* newNode = new Node(ch);
        newNode->next = secretWord;
        secretWord = newNode;
    }

    void displayWord() {
        Node* current = secretWord;
        while (current) {
            if (isGuessed(current->data)) {
                cout << current->data << " ";
            } else {
                cout << "_ ";
            }
            current = current->next;
        }
        cout << endl;
    }

    bool isGuessed(char ch) {
        for (int i = 0; i < strlen(guessedLetters); ++i) {
            if (guessedLetters[i] == ch) {
                return true;
            }
        }
        return false;
    }

    void displayGuessedLetters() {
        cout << "Guessed Letters: ";
        for (int i = 0; i < strlen(guessedLetters); ++i) {
            cout << guessedLetters[i] << " ";
        }
        cout << endl;
    }

    void makeGuess() {
        char guess;
        cout << "Enter your guess: ";
        cin >> guess;

        if (isGuessed(guess)) {
            cout << "You've already guessed that letter. Try again.\n";
            return;
        }

        guessedLetters[strlen(guessedLetters)] = guess;

        if (!checkGuess(guess)) {
            attemptsLeft--;
            cout << "Incorrect guess. Attempts left: " << attemptsLeft << endl;
        }

        displayWord();
        displayGuessedLetters();
    }

    bool checkGuess(char guess) {
        Node* current = secretWord;
        bool correctGuess = false;

        while (current) {
            if (current->data == guess) {
                correctGuess = true;
            }
            current = current->next;
        }

        return correctGuess;
    }

    bool isGameOver() {
        if (attemptsLeft == 0) {
            cout << "Game over! You've run out of attempts. The word was: ";
            displayWord();
            return true;
        }

        Node* current = secretWord;
        while (current) {
            if (!isGuessed(current->data)) {
                return false;
            }
            current = current->next;
        }

        cout << "Congratulations! You've guessed the word: ";
        displayWord();
        return true;
    }

    void playGame() {
        cout << "Welcome to Hangman!\n";
        displayWord();

        while (!isGameOver()) {
            makeGuess();
        }
    }
};

int main() {
    HangmanGame game;
    game.playGame();

    return 0;
}
