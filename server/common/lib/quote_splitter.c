/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** quote_splitter
*/

#include "lib.h"
#include "garbage_collector.h"
#include <string.h>
#include <stdbool.h>

/**
 * @brief Count the number of quotes
 * @details count the number of quotes in the given string
 *
 * @param str the string to count the quotes from
 *
 * @return size_t the number of quotes
*/
static size_t count_quotes(char *str)
{
    size_t count = 0;

    for (int i = 0; str[i]; i++) {
        if (str[i] == '\"')
            count++;
    }
    return count;
}

/**
 * @brief Clean empty strings
 * @details clean empty strings from the given array
 *
 * @param db_array the array to clean
 *
 * @return char** the cleaned array
*/
static char **clean_empty_str(char **db_array)
{
    size_t len = 0;

    for (uint16_t i = 0; db_array[i]; i++) {
        if (db_array[i][0] == '\0' || db_array[i][0] == ' ')
            continue;
        db_array[len] = db_array[i];
        len++;
    }
    db_array[len] = NULL;
    return db_array;
}

/**
 * @brief Get the correct array
 * @details get the correct array from the given token
 *      if the current index is even, the token will be surrounded by quotes
 *      otherwise the token will be split by spaces and \t.
 *
 * @param token the token to get the correct array from
 * @param len the length of the token
 *
 * @return char** the correct array
*/
static char **get_correct_array(char *token, size_t len)
{
    char **db_array = NULL;

    if (len % 2 == 0) {
        db_array = my_malloc(sizeof(char **) * 2);
        db_array[0] = supercat(3, "\"", token, "\"");
        db_array[1] = NULL;
    } else
        db_array = str_to_word_array(token, " \t");
    for (uint16_t i = tablen((void **)db_array) - 1; i > 0; i--) {
        if (db_array[i][0] == '\0' || db_array[i][0] == ' ')
            db_array[i] = NULL;
        else
            break;
    }
    return clean_empty_str(db_array);
}

/**
 * @brief Concatenate multiple arrays into one
 * @details concatenate multiple arrays into one
 *
 * @param tab the arrays to concatenate
 *
 * @return char** the concatenated array
*/
static char **concat_db_array_tab(char ***tab)
{
    char **db_array = my_malloc(sizeof(char *) * 1);
    size_t len = 0;
    size_t sub_len = 0;

    db_array[0] = NULL;
    for (int i = 0; tab[i]; i++) {
        len = tablen((void **)db_array);
        sub_len = tablen((void **)tab[i]);
        db_array = my_realloc(db_array, sizeof(char *) * (len + sub_len + 1),
            sizeof(char *) * len);
        for (int j = 0; tab[i][j]; j++) {
            len = tablen((void **)db_array);
            db_array[len] = my_strdup(tab[i][j]);
            db_array[len + 1] = NULL;
        }
    }
    return db_array;
}

/**
 * @brief Split a string with quotes
 * @details split the given string into multiple strings, if quotes are found
 *        the string between the quotes will be considered as one string
 *
 * @param str the string to split
 *
 * @return char** the splitted string
*/
char **quote_split(char *str)
{
    char ***tab = NULL;
    char **sub_strings;
    size_t quote_nbr = count_quotes(str);

    if (quote_nbr % 2 != 0)
        return NULL;
    sub_strings = str_to_word_array(str, "\"");
    tab = my_malloc(sizeof(char *) * (tablen((void **)sub_strings) + 1));
    for (int i = 0; sub_strings[i]; i++) {
        tab[i] = get_correct_array(sub_strings[i], i + 1);
        tab[i + 1] = NULL;
    }
    return concat_db_array_tab(tab);
}
