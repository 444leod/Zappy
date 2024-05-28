/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** get_threads
*/

#include "data_structures.h"
#include "linked_lists.h"

/**
 * @brief Get the threads
 * @details Get the threads
 *
 * @return threads_t* the threads
 */
threads_t *get_threads(void)
{
    static threads_t threads = NULL;

    return &threads;
}

/**
 * @brief Get the threads by creator
 * @details Get the threads by creator
 *
 * @param creator_uuid the creator uuid
 *
 * @return threads_t the threads linked list
 */
threads_t get_threads_by_creator(uuid_t creator_uuid)
{
    threads_t *threads = get_threads();
    threads_t new_threads = NULL;
    threads_t tmp = *threads;

    while (tmp) {
        if (uuid_compare(tmp->thread->creator_uuid, creator_uuid) == 0)
            add_to_list((void *)tmp->thread, (node_t *)&new_threads);
        tmp = tmp->next;
    }
    return new_threads;
}

/**
 * @brief Get the threads by channel
 * @details Get the threads by channel
 *
 * @param channel_uuid the channel uuid
 *
 * @return threads_t the threads linked list
 */
threads_t get_threads_by_channel(uuid_t channel_uuid)
{
    threads_t *threads = get_threads();
    threads_t new_threads = NULL;
    threads_t tmp = *threads;

    while (tmp) {
        if (uuid_compare(tmp->thread->channel_uuid, channel_uuid) == 0)
            add_to_list((void *)tmp->thread, (node_t *)&new_threads);
        tmp = tmp->next;
    }
    return new_threads;
}
