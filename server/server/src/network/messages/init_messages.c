/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** init_messages
*/

#include "data_structures.h"
#include "linked_lists.h"
#include "logging_server.h"
#include "debug.h"
#include "garbage_collector.h"
#include "magic_number.h"
#include "clientllist.h"
#include "lib.h"
#include "macros.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

static void print_initialized_message(UNUSED message_t *message)
{
    DEBUG_PRINT("Message loaded: (from %s to %s) \"%s\"(%s)\n",
        get_user_by_uuid(message->sender_uuid)->username,
        get_user_by_uuid(message->receiver_uuid)->username,
        message->body, get_uuid_as_string(message->uuid));
}

/**
 * @brief Read the messages from the save file
 * @details Read the messages from the save file
 *
 * @param fd the file descriptor
*/
void read_messages(int fd)
{
    message_t *new_message;
    int rd = 0;

    while (1) {
        new_message = my_malloc(sizeof(message_t));
        rd = read(fd, new_message, sizeof(message_t));
        if (rd <= 0 || rd != sizeof(message_t)) {
            my_free(new_message);
            break;
        }
        if (get_user_by_uuid(new_message->sender_uuid) == NULL ||
            get_user_by_uuid(new_message->receiver_uuid) == NULL) {
            printf("Cannot find user with uuid %s\n",
                get_uuid_as_string(new_message->sender_uuid));
            my_free(new_message);
            continue;
        }
        print_initialized_message(new_message);
        add_to_list((void *)new_message, (node_t *)get_messages());
    }
}

/**
 * @brief Init the messages linked list
 * @details Init the messages linked list using the .save/.messages file
*/
void init_messages(void)
{
    messages_t *messages = get_messages();
    int fd = open(SAVE_FOLDER".messages", O_RDONLY);

    *messages = NULL;
    DEBUG_PRINT("Init messages\n");
    if (fd == -1) {
        printf("messages: No save file\n");
        return;
    }
    if (!is_magic_number_valid(fd)) {
        printf("messages: Invalid magic number\n");
        close(fd);
        return;
    }
    read_messages(fd);
    close(fd);
}
