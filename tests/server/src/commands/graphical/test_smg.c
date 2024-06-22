/*
** EPITECH PROJECT, 2024
** Untitled (Workspace)
** File description:
** test_smg
*/

#include "source_header.h"
#include "commands.h"

Test(smg_suite, send_empty_message)
{
    client_t clientA = test_create_client(0);
    client_t clientB = test_create_client(1);

    clientA->type = GRAPHICAL;
    clientB->type = GRAPHICAL;

    smg("hehehe haw");

    assert_packet_queue(clientA->packet_queue, 1, "smg hehehe haw");
    assert_packet_queue(clientB->packet_queue, 1, "smg hehehe haw");
}
