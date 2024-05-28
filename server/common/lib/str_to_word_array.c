/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** str_to_word_array
*/

#include <stdlib.h>
#include <string.h>
#include "lib.h"
#include "garbage_collector.h"

/**
 * @brief Count the number of words in a string
 * @details Count the number of words in a string using a delimiter
 *
 * @param str the string to count
 * @param delim the delimiters
 *
 * @return the number of words
*/
static size_t count_words(char *str, char *delim)
{
    size_t count = 0;
    char *start = str;
    char *end;

    end = strpbrk(start, delim);
    while (end != NULL) {
        count++;
        start = end + 1;
        end = strpbrk(start, delim);
    }
    count++;
    return count;
}

/**
 * @brief Split a string into an array of words
 * @details Split a string into an array of words using a delimiter
 *
 * @param str the string to split
 * @param delim the delimiters
 *
 * @return the array of words
*/
char **str_to_word_array(char *str, char *delim)
{
    char **array = my_malloc(sizeof(char *) * (count_words(str, delim) + 1));
    int i = 0;
    char *start = str;
    char *end;

    end = strpbrk(start, delim);
    while (end != NULL) {
        array[i] = my_strndup(start, end - start);
        i++;
        start = end + 1;
        end = strpbrk(start, delim);
    }
    array[i] = my_strdup(start);
    i++;
    array[i] = NULL;
    return array;
}
