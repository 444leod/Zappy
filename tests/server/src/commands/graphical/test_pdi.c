/*
** EPITECH PROJECT, 2024
** Untitled (Workspace)
** File description:
** test_pdi
*/

#include "source_header.h"
#include "commands.h"
#include "commands_utils.h"

Test(pdi, player_death_to_graphical)
{
    client_t client1 = test_create_client(0);
    client_t client2 = test_create_client(0);
    client_t client3 = test_create_client(0);

    struct player_s player = {
        .player_number = 0
    };

    client1->type = GRAPHICAL;
    client2->type = GRAPHICAL;
    client3->type = GRAPHICAL;

    queue_to_graphical(get_player_death_string(&player));

    assert_packet_queue(client1->packet_queue, 1, "pdi 0");
    assert_packet_queue(client2->packet_queue, 1, "pdi 0");
    assert_packet_queue(client3->packet_queue, 1, "pdi 0");
}
