#ifndef __MILALE_H
#define __MILALE_H

#include <stdbool.h>

// Constants
#define MAX_WORD_LEN 5
#define MAX_GUESSES 6
#define NEW_GUESS                                           \
    {                                                       \
        "_____", { ABSENT, ABSENT, ABSENT, ABSENT, ABSENT } \
    }

// Strings
#define EMPTY_LETTER '_'
#define ENTER_WORD "Please enter a 5 letters word:\n"
#define ERR_TOO_SHORT "Word too short, please enter a 5 letters word.\n"
#define ERR_TOO_LONG "Word too long, please enter a 5 letters word.\n"
#define ERR_NOT_FOUND "Word not recognized, please enter a new word.\n"
#define WELCOME "Welcome to Milale-C!\nYou have 6 tries to find the secret 5 letter word.\n\n"
#define WIN_MSG "Congratulations! You've found the secret word in %d/6 guesses."
#define LOSE_MSG "Too bad, noob! Better luck next time I guess...\n"

// Colors
#define COLOR_ABSENT "\033[0m"     // White
#define COLOR_PRESENT "\033[1;33m" // Yellow
#define COLOR_CORRECT "\033[0;32m" // Green

// Types
typedef char Word[MAX_WORD_LEN + 1];

typedef enum state
{
    ABSENT,  // 0
    PRESENT, // 1
    CORRECT  // 2
} State;

typedef struct guess
{
    Word word;
    State states[MAX_WORD_LEN];
} Guess;

Guess make_guess();
bool check_guess(Guess *guess, const Word const secretWord);
bool check_word(const Word const word);
void set_console_color(State state);
void print_letter(char letter, State state);
void print_guess(const Guess const guess);
void print_word(const Word const word);
void print_board(const Guess const guesses[MAX_GUESSES]);

#endif