#ifndef __UTILS_H
#define __UTILS_H

#include "milale.h"

void to_uppercase(Word word);
void to_lowercase(Word word);
bool is_letter_in_word(char letter, const Word word);
int *get_letter_count(const Word word);
Word *get_words_from_file(char *filename, int *length);

#endif