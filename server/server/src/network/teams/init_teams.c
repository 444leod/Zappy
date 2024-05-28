/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** init_teams
*/

#include "data_structures.h"
#include "linked_lists.h"
#include "logging_server.h"
#include "debug.h"
#include "garbage_collector.h"
#include "magic_number.h"
#include "lib.h"
#include "macros.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

static void print_initialized_team(UNUSED team_t *team)
{
    DEBUG_PRINT("Team loaded: \"%s\" (%s)\n",
        team->name, get_uuid_as_string(team->uuid));
}

/**
 * @brief Read the teams from the save file
 * @details Read the teams from the save file
 *
 * @param fd the file descriptor
*/
void read_teams(int fd)
{
    team_t *new_team;
    int rd = 0;

    while (1) {
        new_team = my_malloc(sizeof(team_t));
        rd = read(fd, new_team, sizeof(team_t));
        if (rd <= 0 || rd != sizeof(team_t)) {
            my_free(new_team);
            break;
        }
        print_initialized_team(new_team);
        add_to_list((void *)new_team, (node_t *)get_teams());
    }
}

/**
 * @brief Init the teams linked list
 * @details Init the teams linked list using the .save/.teams file
*/
void init_teams(void)
{
    teams_t *teams = get_teams();
    int fd = open(SAVE_FOLDER".teams", O_RDONLY);

    *teams = NULL;
    DEBUG_PRINT("Init teams\n");
    if (fd == -1) {
        printf("teams: No save file\n");
        return;
    }
    if (!is_magic_number_valid(fd)) {
        printf("teams: Invalid magic number\n");
        close(fd);
        return;
    }
    read_teams(fd);
    close(fd);
}
