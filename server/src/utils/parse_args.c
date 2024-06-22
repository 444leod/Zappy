/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** parse_args
*/

#include <string.h>
#include "lib.h"
#include "linked_lists.h"
#include "garbage_collector.h"

static int run_while(const char *str, char c)
{
    int i = 0;

    for (; str[i] == c; i++);
    return i;
}

static int run_until(const char *str, char c)
{
    int i = 0;

    for (; str[i] && str[i] != c; i++);
    return (str[i]) ? i : -1;
}

static void *capture_quotes(const char *str, char quote, uint32_t *i)
{
    int end = 0;
    char *capture = NULL;

    (*i)++;
    end = run_until(str, quote);
    if (end < 0) {
        return NULL;
    }
    capture = my_strndup(str, (uint32_t)end);
    *i += end;
    return (void *)capture;
}

static void *capture_word(const char *str, uint32_t *i)
{
    int end = run_until(str, ' ');
    char *capture = NULL;

    if (end < 0)
        end = strlen(str);
    capture = my_strndup(str, (uint32_t)end);
    *i += end;
    return (void *)capture;
}

static node_t get_args_nodes(const char *str)
{
    node_t node = NULL;
    uint32_t len = strlen(str);

    for (uint32_t i = 0; i < len; i++) {
        i += run_while(str + i, ' ');
        if (str[i] == 0)
            break;
        if (str[i] == '\"' || str[i] == '\'')
            add_to_list(capture_quotes(str + i + 1, str[i], &i), &node);
        else
            add_to_list(capture_word(str + i, &i), &node);
    }
    return node;
}

static bool is_valid_args(node_t nodes, uint32_t *out_size)
{
    uint32_t size = 0;

    while (nodes) {
        if (!nodes->data)
            return false;
        nodes = nodes->next;
        size++;
    }
    *out_size = size;
    return true;
}

static void **nodes_to_array(node_t nodes)
{
    void **args = NULL;
    node_t node = nodes;
    node_t next = NULL;
    uint32_t size = 0;

    if (!is_valid_args(node, &size))
        return NULL;
    args = my_malloc(sizeof(void *) * (size + 1));
    for (uint32_t i = 0; i < size; i++) {
        next = node->next;
        args[i] = node->data;
        my_free(node);
        node = next;
    }
    return args;
}

char **parse_command_args(const char *command)
{
    node_t nodes = NULL;

    if (!command)
        return NULL;
    nodes = get_args_nodes(command);
    return (char **)nodes_to_array(nodes);
}
