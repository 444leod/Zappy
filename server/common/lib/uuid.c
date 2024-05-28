/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** get_uuid_as_string
*/

#include "garbage_collector.h"
#include <stdlib.h>
#include <stdbool.h>
#include <uuid/uuid.h>
#include <stdbool.h>
#include <string.h>

/**
 * @brief Get the uuid as string
 * @details Transform the uuid_t into a string
 * (37 is the size of a uuid string representation + 1 for the null byte)
 *
 * @param uuid the uuid to transform
 *
 * @return the string
*/
char *get_uuid_as_string(uuid_t uuid)
{
    char *str = my_malloc(37);

    uuid_unparse(uuid, str);
    return str;
}

/**
 * @brief Get the uuid from a string
 * @details Transform the string into a uuid_t
 *
 * @param str the string to transform
 * @param uuid the uuid to fill
 *
 * @return void
*/
void get_uuid_from_string(char *str, uuid_t uuid)
{
    uuid_parse(str, uuid);
}

/**
 * @brief Check if a string is a valid uuid
 * @details Check if a string is a valid uuid
 *
 * @param str the string to check
 *
 * @return true if the string is a valid uuid
*/
bool is_uuid_valid(char *str)
{
    uuid_t uuid;

    if (strlen(str) != 36)
        return false;
    if (uuid_parse(str, uuid) == -1)
        return false;
    return true;
}
