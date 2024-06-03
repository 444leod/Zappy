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
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/wait.h>

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
 * @brief Add the clients to the write and read fd_sets
 * @details add the clients to the write and read fd_sets and update the
 *   max_sd variable, also update the fork status of the clients
 *
 * @param clients the clients to add to the fd_sets
 * @param readfds the read fd_set
 * @param writefds the write fd_set
 * @param max_sd the max_sd variable
*/
static void add_clients_to_set(
    client_t *clients,
    fd_set *readfds,
    fd_set *writefds,
    int *max_sd)
{
    client_t tmp = *clients;

    while (tmp) {
        if (tmp->packet_queue)
            FD_SET(tmp->fd, writefds);
        FD_SET(tmp->fd, readfds);
        if (tmp->fd > *max_sd)
            *max_sd = tmp->fd;
        tmp = tmp->next;
    }
}

/**
 * @brief Add a new client to the list of clients
 * @details add a new client to the list of clients by accepting a connexion
 *
 * @param socketFd the socket file descriptor
*/
static void add_new_client(int socketFd)
{
    int new_socket = 0;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    client_t *clients = get_clients();

    new_socket = accept(socketFd, (struct sockaddr *)&address,
        (socklen_t *)&addrlen);
    if (new_socket < 0)
        my_error("new client: accept failed");
    if (*clients == NULL)
        *clients = create_client(new_socket);
    else
        add_client(create_client(new_socket));
}

/**
 * @brief Wrapper for the select function
 * @details wrapper for the select function, if the select function failed
 *   the program exit, else the function updates the fd_sets each 100ms.
 *
 * @param max_sd the max_sd variable
 * @param readfds the read fd_set
 * @param writefds the write fd_set
 * @param clients the list of clients
*/
static void select_wrapper(int max_sd, fd_set *readfds,
    fd_set *writefds, UNUSED client_t *clients)
{
    struct timeval timeout = {0, 100};
    int activity = 0;

    activity = select(max_sd + 1, readfds, writefds, NULL, &timeout);
    if (activity < 0)
        my_error("select wrapper failed");
}

/**
 * @brief Main Zappy loop
 * @details the main loop of the Zappy server, it accepts new clients and
 *  updates the clients status, also it calls the loop_clients function
 *  to handle the clients commands
 *
 * @param socketFd the socket file descriptor
 * @param server_info the server_info struct
*/
void zappy_loop(int socketFd, server_info_t server_info)
{
    fd_set readfds;
    fd_set writefds;
    int max_sd = 0;
    client_t *clients = NULL;

    while (1) {
        clients = get_clients();
        FD_ZERO(&readfds);
        FD_ZERO(&writefds);
        FD_SET(socketFd, &readfds);
        max_sd = socketFd;
        add_clients_to_set(clients, &readfds, &writefds, &max_sd);
        special_print(&readfds, &writefds);
        select_wrapper(max_sd + 1, &readfds, &writefds, clients);
        if (FD_ISSET(socketFd, &readfds))
            add_new_client(socketFd);
        loop_clients(clients, &readfds, &writefds, server_info);
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
    team_name_t tmp = server_info->team_names;

    DEBUG_PRINT("\nServer info:\n");
    DEBUG_PRINT("\tRunning on port %d\n", server_info->port);
    DEBUG_PRINT("\t%d ", server_info->clientsNb);
    if (server_info->clientsNb == 1)
        DEBUG_PRINT("client per team\n");
    else {
        DEBUG_PRINT("clients per team\n");
    }
    DEBUG_PRINT("\tMap size: %d * %d\n",
        server_info->width, server_info->height);
    DEBUG_PRINT("\tFrequency: %d\n", server_info->freq);
    DEBUG_PRINT("\tTeam names:\n");
    while (tmp) {
        DEBUG_PRINT("\t  - %s\n", tmp->name);
        tmp = tmp->next;
    }
    DEBUG_PRINT("\n");
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
int server(int argc, char *argv[])
{
    int socketFd = -1;
    server_info_t server_info;

    errno = 0;
    DEBUG_PRINT("Zappy server started\n");
    signal(2, handle_sigint);
    check_args(argc, argv);
    server_info = init_server_info(argv);
    socketFd = get_socket();
    prepare_exit(socketFd);
    bind_socket(socketFd, server_info->port);
    print_server_info(server_info);
    listen_socket(socketFd, 1024);
    zappy_loop(socketFd, server_info);
    close(socketFd);
    return 0;
}
