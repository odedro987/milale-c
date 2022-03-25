#include "milale.h"
#include "data.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char const *argv[])
{
    // Intializes random number generator and a secret word
    time_t t;
    srand((unsigned)time(&t));

    Word secret;
    strcpy(secret, SECRET_WORDS[rand() % SECRET_WORDS_LEN]);

    // Init game variables
    Guess guesses[MAX_GUESSES] = {NEW_GUESS, NEW_GUESS, NEW_GUESS, NEW_GUESS, NEW_GUESS, NEW_GUESS};
    int totalGuesses = 0;
    bool done = false;

    // Game
    printf("%s", WELCOME);

    while (!done && totalGuesses < MAX_GUESSES)
    {
        guesses[totalGuesses] = make_guess();
        bool isCorrect = check_guess(&guesses[totalGuesses], secret);
        print_board(guesses);

        if (isCorrect)
        {
            done = true;
            printf(WIN_MSG, totalGuesses + 1);
        }

        totalGuesses++;
    }

    if (!done)
        printf(LOSE_MSG);

    return 0;
}

void set_console_color(State state)
{
    switch (state)
    {
    case ABSENT:
        printf("%s", COLOR_ABSENT);
        break;
    case PRESENT:
        printf("%s", COLOR_PRESENT);
        break;
    case CORRECT:
        printf("%s", COLOR_CORRECT);
        break;
    default:
        printf("%s", COLOR_ABSENT);
        break;
    }
}

void print_letter(char letter, State state)
{
    set_console_color(state);
    printf("%c", letter);
    set_console_color(ABSENT);
}

void print_guess(const Guess const guess)
{
    Word upper;
    strcpy(upper, guess.word);
    to_uppercase(upper);

    for (int i = 0; i < MAX_WORD_LEN; i++)
    {
        print_letter(upper[i], guess.states[i]);
    }
    printf("\n");
}

void print_word(const Word const word)
{
    Guess wrapper = NEW_GUESS;
    strcpy(wrapper.word, word);
    print_guess(wrapper);
}

void print_board(const Guess const guesses[MAX_GUESSES])
{
    for (int i = 0; i < MAX_GUESSES; i++)
    {
        print_guess(guesses[i]);
    }
}

bool check_word(const Word const word)
{
    for (int i = 0; i < VALID_GUESSES_LEN; i++)
    {
        if (strcmp(word, VALID_GUESSES[i]) == 0)
            return true;
    }

    return false;
}

Guess make_guess()
{
    Guess newGuess = NEW_GUESS;
    bool done = false;
    Word word;

    while (!done)
    {
        printf(ENTER_WORD);
        scanf("%s", word);
        to_lowercase(word);

        int len = strlen(word);
        if (len < MAX_WORD_LEN)
            printf(ERR_TOO_SHORT);
        else if (len > MAX_WORD_LEN)
            printf(ERR_TOO_LONG);
        else if (!check_word(word))
            printf(ERR_NOT_FOUND);
        else
            done = true;
    }

    strcpy(newGuess.word, word);

    return newGuess;
}

bool check_guess(Guess *guess, const Word const secretWord)
{
    int *guessBuckets = get_letter_count(guess->word);
    int *secretBuckets = get_letter_count(secretWord);

    for (int i = 0; i < MAX_WORD_LEN; i++)
    {
        if (guess->word[i] == secretWord[i])
            guess->states[i] = CORRECT;
        else if (is_letter_in_word(guess->word[i], secretWord))
            guess->states[i] = PRESENT;
    }

    for (int i = MAX_WORD_LEN - 1; i >= 0; i--)
    {
        if (guess->states[i] == PRESENT)
        {
            int index = guess->word[i] - 'a';
            if (guessBuckets[index] > secretBuckets[index])
            {
                guessBuckets[index]--;
                guess->states[i] = ABSENT;
            }
        }
    }

    free(guessBuckets);
    free(secretBuckets);

    return strcmp(guess->word, secretWord) == 0;
}
