/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** exit
*/

#include "source_header.h"
#include <sys/wait.h>
#include "zappy.h"

Test(client, create) {
    client_t c = create_client(0);
    cr_expect(c != NULL);
    cr_assert(c->clientNumber == 0);
}
