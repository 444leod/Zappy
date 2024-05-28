/*
** EPITECH PROJECT, 2024
** myreplies
** File description:
** get_replies
*/

#include "data_structures.h"
#include "linked_lists.h"

/**
 * @brief Get the replies
 * @details Get the replies
 *
 * @return replies_t* the replies
 */
replies_t *get_replies(void)
{
    static replies_t replies = NULL;

    return &replies;
}

/**
 * @brief Get the replies of a certain creator
 * @details Get the replies of a certain creator, based on the creator uuid
 *
 * @param creator_uuid the creator uuid
 *
 * @return replies_t* the replies linked list
 */
replies_t *get_replies_by_creator(uuid_t creator_uuid)
{
    replies_t *replies = get_replies();
    replies_t tmp = *replies;
    replies_t *new_replies = NULL;

    while (tmp) {
        if (uuid_compare(tmp->reply->creator_uuid, creator_uuid) == 0)
            add_to_list((void *)tmp->reply, (node_t *)new_replies);
        tmp = tmp->next;
    }
    return new_replies;
}

/**
 * @brief Get the replies of a certain thread
 * @details Get the replies of a certain thread, based on the thread uuid
 *
 * @param thread_uuid the thread uuid
 *
 * @return replies_t* the replies linked list
 */
replies_t get_replies_by_thread(uuid_t thread_uuid)
{
    replies_t *replies = get_replies();
    replies_t tmp = *replies;
    replies_t new_replies = NULL;

    while (tmp) {
        if (uuid_compare(tmp->reply->thread_uuid, thread_uuid) == 0)
            add_to_list((void *)tmp->reply, (node_t *)&new_replies);
        tmp = tmp->next;
    }
    return new_replies;
}
