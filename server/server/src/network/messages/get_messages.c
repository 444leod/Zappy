/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** get_messages
*/

#include "data_structures.h"
#include "linked_lists.h"

/**
 * @brief Get the messages
 * @details Get the messages
 *
 * @return messages_t* the messages
 */
messages_t *get_messages(void)
{
    static messages_t messages = NULL;

    return &messages;
}

/**
 * @brief Get the messages by sender
 * @details Get the messages by sender
 *
 * @param sender_uuid the sender uuid
 *
 * @return messages_t* the messages
 */
messages_t *get_messages_by_sender(uuid_t sender_uuid)
{
    messages_t *messages = get_messages();
    messages_t *new_messages = NULL;
    messages_t tmp = *messages;

    while (tmp) {
        if (uuid_compare(tmp->message->sender_uuid, sender_uuid) == 0)
            add_to_list((void *)tmp->message, (node_t *)new_messages);
        tmp = tmp->next;
    }
    return new_messages;
}

/**
 * @brief Get the messages by receiver
 * @details Get the messages by receiver
 *
 * @param receiver_uuid the receiver uuid
 *
 * @return messages_t* the messages
 */
messages_t *get_messages_by_receiver(uuid_t receiver_uuid)
{
    messages_t *messages = get_messages();
    messages_t *new_messages = NULL;
    messages_t tmp = *messages;

    while (tmp) {
        if (uuid_compare(tmp->message->receiver_uuid, receiver_uuid) == 0)
            add_to_list((void *)tmp->message, (node_t *)new_messages);
        tmp = tmp->next;
    }
    return new_messages;
}

/**
 * @brief Get the messages by sender and receiver
 * @details Get the messages by sender and receiver
 *
 * @param sender_uuid the sender uuid
 * @param receiver_uuid the receiver uuid
 *
 * @return messages_t* the messages
 */
messages_t get_messages_by_sender_and_receiver(uuid_t sender_uuid,
    uuid_t receiver_uuid)
{
    messages_t *messages = get_messages();
    messages_t new_messages = NULL;
    messages_t tmp = (messages ? *messages : NULL);

    while (tmp) {
        if ((uuid_compare(tmp->message->sender_uuid, sender_uuid) == 0 &&
            uuid_compare(tmp->message->receiver_uuid, receiver_uuid) == 0) ||
            (uuid_compare(tmp->message->sender_uuid, receiver_uuid) == 0 &&
            uuid_compare(tmp->message->receiver_uuid, sender_uuid) == 0))
            add_to_list((void *)(tmp->message), (node_t *)(&new_messages));
        tmp = tmp->next;
    }
    return new_messages;
}
