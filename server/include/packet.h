/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** packet
*/

#pragma once

    #include <uuid/uuid.h>
    #include <stdbool.h>

typedef struct packet_s {
    char *buffer;
} packet_t;

    #define PACKET_SIZE sizeof(struct packet_s)

typedef struct packet_queue_s {
    packet_t *packet;
    struct packet_queue_s *next;
} *packet_queue_t;

void add_packet_to_queue(packet_queue_t *queue, packet_t *packet);
packet_t *pop_packet_from_queue(packet_queue_t *queue);
void free_packet_queue(packet_queue_t *queue);

void send_packet(int fd, packet_t *packet);
packet_t *build_packet(char *buffer);
