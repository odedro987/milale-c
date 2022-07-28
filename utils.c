#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

Word *get_words_from_file(char *filename, int *length)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    long read;

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("%s could not be opened", filename);
        exit(1);
    }

    int size = 1024;
    int count = 0;
    Word *words = (Word *)malloc(size * sizeof(Word));

    while ((read = getline(&line, &len, fp)) != -1)
    {
        if (count >= size)
        {
            size *= 2;
            words = (Word *)realloc(words, size * sizeof(Word));
            if (words == NULL)
            {
                printf("Failed reallocating memory");
                exit(1);
            }
        }
        strncpy(words[count], line, sizeof(Word) - 1);
        words[count][sizeof(Word) - 1] = '\0';
        count++;
    }

    words = (Word *)realloc(words, count * sizeof(Word));
    *length = count;

    fclose(fp);
    if (line)
        free(line);

    return words;
}