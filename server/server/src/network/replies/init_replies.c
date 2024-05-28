/*
** EPITECH PROJECT, 2024
** myreplies
** File description:
** init_replies
*/

#include "data_structures.h"
#include "linked_lists.h"
#include "logging_server.h"
#include "debug.h"
#include "garbage_collector.h"
#include "magic_number.h"
#include "lib.h"
#include "macros.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

static void print_initialized_reply(UNUSED reply_t *reply)
{
    DEBUG_PRINT("Reply loaded: \"%s\" (%s)\n",
        reply->body, get_uuid_as_string(reply->uuid));
}

/**
 * @brief Read the replies from the save file
 * @details Read the replies from the save file
 *
 * @param fd the file descriptor
*/
void read_replies(int fd)
{
    reply_t *new_reply;
    int rd = 0;

    while (1) {
        new_reply = my_malloc(sizeof(reply_t));
        rd = read(fd, new_reply, sizeof(reply_t));
        if (rd <= 0 || rd != sizeof(reply_t)) {
            my_free(new_reply);
            break;
        }
        if (get_thread_by_uuid(new_reply->thread_uuid) == NULL) {
            printf("Thread with uuid %s not found\n",
                get_uuid_as_string(new_reply->thread_uuid));
            my_free(new_reply);
            continue;
        }
        print_initialized_reply(new_reply);
        add_to_list((void *)new_reply, (node_t *)get_replies());
    }
}

/**
 * @brief Init the replies linked list
 * @details Init the replies linked list using the .save/.replies file
*/
void init_replies(void)
{
    replies_t *replies = get_replies();
    int fd = open(SAVE_FOLDER".replies", O_RDONLY);

    *replies = NULL;
    DEBUG_PRINT("Init replies\n");
    if (fd == -1) {
        printf("replies: No save file\n");
        return;
    }
    if (!is_magic_number_valid(fd)) {
        printf("replies: Invalid magic number\n");
        close(fd);
        return;
    }
    read_replies(fd);
    close(fd);
}
