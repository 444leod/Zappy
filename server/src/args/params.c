/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** params
*/

#include "zappy.h"
#include "params.h"
#include "lib.h"

/**
 * @brief Get the next parameters list node after the given flag
 * @details Get the next parameters list node after the given flag and set the
 * flag as handled
 *
 * @param flag the flag to search
 * @param params the parameters list
 *
 * @return the next parameters list node after the given flag
 */
param_t get_param(const char *flag, param_t params)
{
    param_t tmp = params;
    param_t flagNode;
    param_t flagContent;

    while (tmp) {
        if (strcmp(tmp->informations->content, flag) == 0 &&
            tmp->informations->handled == false) {
            flagNode = tmp;
            break;
        }
        tmp = tmp->next;
    }
    if (flagNode == NULL)
        display_help(supercat(2, flag, " is missing\n"));
    flagNode->informations->handled = true;
    flagContent = flagNode->next;
    return flagContent;
}
