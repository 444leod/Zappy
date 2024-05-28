/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** create_team
*/

#include "data_structures.h"
#include "garbage_collector.h"
#include "linked_lists.h"
#include "logging_server.h"
#include "lib.h"
#include <string.h>

/**
 * @brief Create a team object
 * @details Create a team object
 *
 * @param name the name of the team
 * @param description the description of the team
 *
 * @return team_t* the team
 */
team_t *create_team(char *name, char *description, uuid_t creator_uuid)
{
    team_t *team = my_malloc(sizeof(struct team_s));

    memcpy(team->name, name, strlen(name));
    memcpy(team->description, description, strlen(description));
    memcpy(team->creator_uuid, creator_uuid, sizeof(uuid_t));
    uuid_generate(team->uuid);
    add_to_list((void *)team, (node_t *)get_teams());
    server_event_team_created(
        get_uuid_as_string(team->uuid),
        team->name,
        get_uuid_as_string(creator_uuid));
    return team;
}
