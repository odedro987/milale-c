#include "utils.h"
#include <stdlib.h>

void to_uppercase(Word word)
{
    for (int i = 0; i < MAX_WORD_LEN; i++)
    {
        if (word[i] >= 'a' && word[i] <= 'z')
            word[i] -= 32;
    }
}

void to_lowercase(Word word)
{
    for (int i = 0; i < MAX_WORD_LEN; i++)
    {
        if (word[i] >= 'A' && word[i] <= 'Z')
            word[i] += 32;
    }
}

bool is_letter_in_word(char letter, const Word word)
{
    for (int i = 0; i < MAX_WORD_LEN; i++)
    {
        if (word[i] == letter)
            return true;
    }

    return false;
}

int *get_letter_count(const Word word)
{
    int *buckets = (int *)malloc(26 * sizeof(int));
    for (int i = 0; i < 26; i++)
    {
        buckets[i] = 0;
    }

    for (int i = 0; i < MAX_WORD_LEN; i++)
    {
        buckets[word[i] - 'a']++;
    }

    return buckets;
}