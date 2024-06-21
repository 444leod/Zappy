/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** smg
*/

#include "commands.h"
#include "commands_utils.h"
#include "lib.h"
#include "zappy.h"

/**
 * @brief Sends a mesage to the graphical clients
 */
void smg(const char *message)
{
    queue_to_graphical(my_snprintf("smg %s", message));
}
