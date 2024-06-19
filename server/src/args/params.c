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
    param_t flag_node;
    param_t flag_content;

    while (tmp) {
        if (strcmp(tmp->informations->content, flag) == 0 &&
            tmp->informations->handled == false) {
            flag_node = tmp;
            break;
        }
        tmp = tmp->next;
    }
    if (flag_node == NULL)
        display_help(supercat(2, flag, " is missing\n"));
    flag_node->informations->handled = true;
    flag_content = flag_node->next;
    return flag_content;
}
