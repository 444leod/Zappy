/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** dump_teams
*/

#include "linked_lists.h"
#include "data_structures.h"
#include "magic_number.h"
#include <fcntl.h>
#include <unistd.h>

/**
 * @brief Dump the teams in a file
 * @details Dump the teams in a file
*/
void dump_teams(void)
{
    teams_t *teams = get_teams();
    teams_t tmp = *teams;
    int fd = open(SAVE_FOLDER".teams", O_CREAT | O_WRONLY | O_TRUNC, 0666);

    if (fd == -1)
        return;
    write_magic_number(fd);
    while (tmp) {
        write(fd, tmp->team, sizeof(struct team_s));
        tmp = tmp->next;
    }
}
