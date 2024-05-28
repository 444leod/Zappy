/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** packet
*/

#pragma once

    #include <uuid/uuid.h>
    #include <stdbool.h>

#define MAX_NAME_LENGTH 32
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_BODY_LENGTH 512
typedef char username_t[MAX_NAME_LENGTH + 1];
typedef char title_t[MAX_NAME_LENGTH + 1];
typedef char description_t[MAX_DESCRIPTION_LENGTH + 1];
typedef char body_t[MAX_BODY_LENGTH + 1];

enum PACKET_TYPE {
    NONE,
    ERROR,
    USER_INFORMATION,
    THREAD,
    TEAM,
    REPLY,
    CHANNEL,
    MESSAGE
};

typedef struct packet_s {
    int code;
    bool is_global;
    int packet_type;
    char packet_body[4096];
} packet_t;

typedef struct packet_queue_s {
    packet_t *packet;
    struct packet_queue_s *next;
} *packet_queue_t;

typedef struct user_information_s {
    uuid_t user_uuid;
    username_t username;
    bool is_logged;
} user_information_t;

typedef struct thread_s {
    uuid_t uuid;
    uuid_t creator_uuid;
    time_t timestamp;
    title_t title;
    body_t body;
    uuid_t channel_uuid;
} thread_t;

typedef struct team_s {
    uuid_t uuid;
    title_t name;
    description_t description;
    uuid_t creator_uuid;
} team_t;

typedef struct reply_s {
    uuid_t uuid;
    uuid_t thread_uuid;
    uuid_t team_uuid;
    uuid_t creator_uuid;
    body_t body;
    time_t timestamp;
} reply_t;

typedef struct channel_s {
    uuid_t uuid;
    char name[MAX_NAME_LENGTH + 1];
    char description[MAX_DESCRIPTION_LENGTH + 1];
    uuid_t team_uuid;
} channel_t;

typedef struct message_s {
    uuid_t uuid;
    uuid_t sender_uuid;
    uuid_t receiver_uuid;
    time_t timestamp;
    body_t body;
} message_t;

    #define PACKET_SIZE sizeof(struct packet_s)
    #define USER_INFORMATION_SIZE sizeof(struct user_information_s)
    #define THREAD_SIZE sizeof(struct thread_s)
    #define TEAM_SIZE sizeof(struct team_s)
    #define REPLY_SIZE sizeof(struct reply_s)
    #define CHANNEL_SIZE sizeof(struct channel_s)
    #define MESSAGE_SIZE sizeof(struct message_s)

void add_packet_to_queue(packet_queue_t *queue, packet_t *packet);
packet_t *pop_packet_from_queue(packet_queue_t *queue);
void free_packet_queue(packet_queue_t *queue);

void send_packet(int fd, packet_t *packet);

packet_t *build_packet(int code, char *buffer);
packet_t *build_custom_packet(int code, char *buffer, int packet_type);
packet_t *build_userinfo_packet(int code, username_t username, uuid_t uuid,
    bool is_logged);
packet_t *build_team_packet(int code, team_t *team);
packet_t *build_thread_packet(int code, thread_t *thread);
packet_t *build_reply_packet(int code, reply_t *reply);
packet_t *build_channel_packet(int code, channel_t *channel);
packet_t *build_message_packet(int code, message_t *message);
packet_t *build_error_packet(int code, char *buffer);

packet_t *read_packet(int fd);
user_information_t *get_userinfo_from_packet(packet_t *packet);
thread_t *get_thread_from_packet(packet_t *packet);
team_t *get_team_from_packet(packet_t *packet);
reply_t *get_reply_from_packet(packet_t *packet);
channel_t *get_channel_from_packet(packet_t *packet);
message_t *get_message_from_packet(packet_t *packet);
