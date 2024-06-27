/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** zappy
*/

#include "zappy.h"
#include "clients.h"
#include "lib.h"
#include "macros.h"
#include "garbage_collector.h"
#include "debug.h"
#include "select_wrapper.h"
#include "commands_utils.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <stdlib.h>

/**
 * @brief callback for SIGINT
 * @details exit the program by calling my_exit to free all the memory
 *     and correctly close the socket and the clients sockets.
*/
static void handle_sigint(UNUSED int sig)
{
    my_exit(0);
}

/**
 * @brief Add a new client to the list of clients
 * @details add a new client to the list of clients by accepting a connexion
 *
 * @param socket_fd the socket file descriptor
*/
static void add_new_client(int socket_fd)
{
    int new_socket = 0;
    struct sockaddr_in address;
    unsigned int addrlen = sizeof(address);

    new_socket = accept(socket_fd, (struct sockaddr *)&address, &addrlen);
    if (new_socket < 0)
        my_error("new client: accept failed");
    add_client(create_client(new_socket));
    DEBUG_PRINT("[DEBUG] New client connected: %d\n", new_socket);
}

/**
 * @brief End the game
 * @details End the game by printing result and sending winner team to
 *  graphical clients
 *
 * @param last_team the last team standing
*/
static void end_game(const team_t last_team)
{
    client_list_t clients = *get_clients();

    if (last_team == NULL) {
        printf("Tie !\n");
    } else {
        printf("Team \"%s\" won!\n", get_escaped_string(last_team->name));
    }
    queue_to_graphical(get_game_end_string(last_team));
    while (clients) {
        clients->client->end = true;
        clients = clients->next;
    }
}

static void check_level_8(client_list_t clients, server_info_t server_info)
{
    player_t player = NULL;

    while (clients) {
        player = clients->client->player;
        if (player && player->level == 8) {
            end_game(player->team);
            server_info->end = true;
            return;
        }
        clients = clients->next;
    }
}

/**
 * @brief Check if the game is ended (if there is only 1 team left)
 * @details Check if the game is ended, if so, end it.
 *
 * @param server_info the server informations.
 */
static void check_game_end(const server_info_t server_info)
{
    team_list_t teams = server_info->teams;
    team_t remaining_team = NULL;

    check_level_8(get_clients_by_type(AI), server_info);
    while (teams) {
        if (get_list_size((node_t)teams->team->players) == 0 &&
            teams->team->remaining_slots == 0) {
            teams = teams->next;
            continue;
        }
        if (remaining_team != NULL)
            return;
        remaining_team = teams->team;
        teams = teams->next;
    }
    end_game(remaining_team);
}

/**
 * @brief Initialize the select_data struct
 * @details initialize the select_data struct with the read and write fd_sets
 *  and the max_sd variable
 *
 * @return the select_data struct
*/
static select_data_t init_select_data(void)
{
    select_data_t select_data;

    select_data.readfds = my_malloc(sizeof(fd_set));
    select_data.writefds = my_malloc(sizeof(fd_set));
    select_data.max_sd = 0;
    FD_ZERO(select_data.readfds);
    FD_ZERO(select_data.writefds);
    return select_data;
}

static void check_possible_deconnexion(server_info_t server_info,
    client_list_t clients)
{
    if (server_info->end && clients == NULL)
        my_exit(0);
}

/**
 * @brief Main Zappy loop
 * @details the main loop of the Zappy server, it accepts new clients and
 *  updates the clients status, also it calls the loop_clients function
 *  to handle the clients commands
 *
 * @param socket_fd the socket file descriptor
 * @param server_info the server_info struct
*/
void zappy_loop(int socket_fd, server_info_t server_info)
{
    select_data_t select_data = init_select_data();
    client_list_t clients = NULL;

    while (1) {
        refill_map(server_info);
        clients = (*get_clients());
        FD_ZERO(select_data.readfds);
        FD_ZERO(select_data.writefds);
        FD_SET(socket_fd, select_data.readfds);
        select_data.max_sd = socket_fd;
        select_wrapper(&select_data, clients, server_info);
        if (FD_ISSET(socket_fd, select_data.readfds))
            add_new_client(socket_fd);
        loop_clients(clients, select_data.readfds,
            select_data.writefds, server_info);
        DEBUG_PRINT("Executed all actions.\n");
        if (!server_info->end)
            check_game_end(server_info);
        check_possible_deconnexion(server_info, clients);
    }
}

/**
 * @brief Print the server info
 * @details print the server info to the standard output in debug mode
 *
 * @param server_info the server_info struct
*/
static void print_server_info(server_info_t server_info)
{
    team_list_t teams = server_info->teams;

    DEBUG_PRINT("\n[ --------------- DEBUG --------------- ]\nServer info:\n");
    DEBUG_PRINT("\tRunning on port %d\n", server_info->port);
    DEBUG_PRINT("\t%d ", server_info->clients_nb);
    if (server_info->clients_nb == 1)
        DEBUG_PRINT("client per team\n");
    else {
        DEBUG_PRINT("clients per team\n");
    }
    DEBUG_PRINT("\tMap size: %d * %d\n",
        server_info->width, server_info->height);
    DEBUG_PRINT("\tFrequency: %d\n", server_info->freq);
    DEBUG_PRINT("\tTeam names:\n");
    while (teams) {
        DEBUG_PRINT("\t  - %s\n", teams->team->name);
        teams = teams->next;
    }
    DEBUG_PRINT("\n[ --------------- DEBUG --------------- ]\n");
}

/**
 * @brief Main Zappy function
 * @details the main function of the Zappy server,
 *  it initializes the server_info struct and the socket,
 *  then it calls the zappy_loop function
 *  to start the server
 *
 * @param argc the number of arguments
 * @param argv the arguments of the program
 *
 * @return 0 if the program exited correctly
*/
int server(const int argc, const char *argv[])
{
    int socket_fd = -1;
    server_info_t server_info;

    errno = 0;
    srand(time(NULL));
    DEBUG_PRINT("Zappy server started\n");
    signal(2, handle_sigint);
    check_args(argc, argv);
    server_info = init_server_info(argv);
    socket_fd = get_socket();
    prepare_exit(socket_fd);
    bind_socket(socket_fd, server_info->port);
    print_server_info(server_info);
    listen_socket(socket_fd, 1024);
    zappy_loop(socket_fd, server_info);
    my_exit(0);
    return 0;
}
