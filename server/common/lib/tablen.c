/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** tablen
*/

/**
 * @brief Get the length of a table
 * @details Get the length of a table
 *
 * @param tab the table
 *
 * @return the length of the table
*/
int tablen(void **tab)
{
    int i = 0;

    while (tab[i] != (void *)0)
        i++;
    return i;
}
