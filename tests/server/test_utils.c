/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** sample
*/

#include <unistd.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "garbage_collector.h"
#include "server_info.h"
#include "lib.h"
#include "zappy.h"
#include "packet.h"

void assert_packet_queue(packet_queue_t packetQueue, uint32_t packets_number, ...)
{
    va_list args;

    va_start(args, packets_number);
    for (uint32_t i = 0; i < packets_number; i++) {
        cr_assert_not_null(packetQueue);
        cr_assert_not_null(packetQueue->packet);
        cr_assert_not_null(packetQueue->packet->buffer);
        cr_assert_str_eq(packetQueue->packet->buffer, va_arg(args, char *));
        packetQueue = packetQueue->next;
    }
    va_end(args);
    cr_assert_null(packetQueue);
}

server_info_t get_server_info()
{
    return init_server_info((const char *[]){"./zappy_server", "-p", "4242", "-f", "1", "-c", "10", "-x", "10", "-y", "10", "-n", "teamName", "team2", NULL});
}

client_t test_create_client(uint32_t id)
{
    client_t client = create_client(id);

    client->packetQueue = NULL;
    return client;
}

void init(void) {
    cr_redirect_stdout();
    cr_redirect_stderr();
}

void verify_gc(gc_node_t *list, uint32_t size, ...)
{
    cr_assert_not_null(list);

    if (size == 0) {
        cr_assert_null(*list);
        return;
    } else
        cr_assert_not_null(*list);

    va_list ap;
    va_start(ap, size);

    gc_node_t tmp = *list;
    gc_node_t first;

    for (uint32_t i = 0; i < size; i++) {
        if (i == 0)
            first = tmp;
        cr_assert_not_null(tmp);
        cr_assert_eq(tmp->data, va_arg(ap, void *));
        tmp = tmp->next;
    }
    cr_assert_eq(tmp, first);
    va_end(ap);
}

void assert_stdout_eq_str(char *str)
{
    fflush(stdout);
    cr_assert_stdout_eq_str(str);
}

/**
 * A boolean assertion example.
 * You can simply check equalities this way.
*/
Test(example_suite, assert_example_one) {
    cr_assert(0 == 0);
}

/**
 * A typed assertion example.
 * If you don't want to write `==`,
 * then you can call `..._eq`.
*/
Test(example_suite, assert_eq_example) {
    cr_assert_eq(0, 0);
}

/**
 * An assertion example based on program output.
 * Uses `.init` to setup the redirection of standard outputs.
*/
Test(example_suite, stdout_example, .init=init) {
    write(1, "Hello!", 6);
    cr_assert_stdout_eq_str("Hello!");
}
