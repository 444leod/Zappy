/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** commands
*/

#include "commands.h"

/**
 * @brief The commands
 * @details The string command and its function
*/
const command_t commands[] = {
    {"/create", &create},
    {"/info", &info},
    {"/list", &list},
    {"/login", &login},
    {"/logout", &logout},
    {"/messages", &messages},
    {"/send", &my_send},
    {"/subscribe", &subscribe},
    {"/subscribed", &subscribed},
    {"/unsubscribe", &unsubscribe},
    {"/use", &use},
    {"/user", &user},
    {"/users", &users},
    {NULL, &unknown_command}
};
