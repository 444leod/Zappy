/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ebo
*/

#include "commands.h"
#include "lib.h"
#include "zappy.h"

/**
 * @brief Get the egg player connexion string
 *
 * @param egg the egg
 * @return char* the string
 */
char *get_egg_player_connexion_string(const egg_t egg)
{
    return my_snprintf("ebo %d", egg->number);
}
