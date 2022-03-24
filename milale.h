#ifndef __MILALE_H
#define __MILALE_H

#include <stdbool.h>

// Constants
#define MAX_WORD_LEN 5
#define MAX_GUESSES 6

// Strings
#define EMPTY_LETTER '_'
#define ENTER_WORD "Please enter a 5 letters word:"
#define ERR_TOO_SHORT "Word too short, please enter a 5 letters word."
#define ERR_TOO_LONG "Word too long, please enter a 5 letters word."
#define ERR_NOT_FOUND "Word not recognized, please enter a new word."

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
bool check_guess(Guess *guess);
bool check_word(Word word);
void set_console_color(State state);
void print_letter(char letter, State state);
void print_guess(Guess guess);
void print_board(Guess guesses[MAX_GUESSES]);

#endif