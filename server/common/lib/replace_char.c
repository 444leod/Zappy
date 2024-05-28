/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** replace_char
*/

/**
 * @brief Replace a character in a string
 * @details Replace a character in a string
 *
 * @param str the string to modify
 * @param find the character to find
 * @param replace the character to replace
 *
 * @return the modified string
*/
char *replace_char(char *str, char find, char replace)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == find) {
            str[i] = replace;
        }
    }
    return str;
}
