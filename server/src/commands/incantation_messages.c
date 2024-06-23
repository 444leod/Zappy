/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** incantation_messages
*/

#include "game.h"
#include "commands.h"
#include "commands_utils.h"
#include "lib.h"

/**
 * @brief Sends the pic message to the graphical clients
 * @param master The player launching the ritual
 * @param others The list of players in the ritual
 */
void send_pic(player_t master, player_list_t others)
{
    char *tmp = NULL;
    char *msg = my_snprintf("pic %d %d %d",
        master->position.x, master->position.y, master->player_number);

    for (player_list_t node = others; node; node = node->next) {
        if (node->player == master)
            continue;
        tmp = my_strdup(msg);
        my_free(msg);
        msg = my_snprintf("%s %d", tmp, node->player->player_number);
        my_free(tmp);
    }
    queue_to_graphical(msg);
}

/**
 * @brief Sends the pie message to the graphical clients
 * @param player The player
 * @param success Whether the ritual succeeded
 */
void send_pie(player_t player, bool success)
{
    char *msg = my_snprintf("pie %d %d %d",
        player->position.x, player->position.y, success);

    queue_to_graphical(msg);
}
