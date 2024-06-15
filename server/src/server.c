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
 * @brief Add a new client to the list of clients
 * @details add a new client to the list of clients by accepting a connexion
 *
 * @param socketFd the socket file descriptor
*/
static void add_new_client(int socketFd)
{
    int new_socket = 0;
    struct sockaddr_in address;
    unsigned int addrlen = sizeof(address);

    new_socket = accept(socketFd, (struct sockaddr *)&address, &addrlen);
    if (new_socket < 0)
        my_error("new client: accept failed");
    add_client(create_client(new_socket));
    DEBUG_PRINT("New client connected: %d\n", new_socket);
}

/**
 * @brief Main Zappy loop
 * @details the main loop of the Zappy server, it accepts new clients and
 *  updates the clients status, also it calls the loop_clients function
 *  to handle the clients commands
 *
 * @param socketFd the socket file descriptor
 * @param serverInfo the serverInfo struct
*/
void zappy_loop(int socketFd, server_info_t serverInfo)
{
    fd_set readfds;
    fd_set writefds;
    int max_sd = 0;
    client_list_t clients = NULL;

    while (1) {
        clients = (*get_clients());
        FD_ZERO(&readfds);
        FD_ZERO(&writefds);
        FD_SET(socketFd, &readfds);
        max_sd = socketFd;
        select_wrapper(&max_sd, &readfds, &writefds, clients);
        if (FD_ISSET(socketFd, &readfds))
            add_new_client(socketFd);
        loop_clients(clients, &readfds, &writefds, serverInfo);
        DEBUG_PRINT("Executed all actions.\n");
    }
}

/**
 * @brief Print the server info
 * @details print the server info to the standard output in debug mode
 *
 * @param serverInfo the serverInfo struct
*/
static void print_server_info(server_info_t serverInfo)
{
    team_list_t teams = serverInfo->teams;

    DEBUG_PRINT("\nServer info:\n");
    DEBUG_PRINT("\tRunning on port %d\n", serverInfo->port);
    DEBUG_PRINT("\t%d ", serverInfo->clientsNb);
    if (serverInfo->clientsNb == 1)
        DEBUG_PRINT("client per team\n");
    else {
        DEBUG_PRINT("clients per team\n");
    }
    DEBUG_PRINT("\tMap size: %d * %d\n",
        serverInfo->width, serverInfo->height);
    DEBUG_PRINT("\tFrequency: %d\n", serverInfo->freq);
    DEBUG_PRINT("\tTeam names:\n");
    while (teams) {
        DEBUG_PRINT("\t  - %s\n", teams->team->name);
        teams = teams->next;
    }
    DEBUG_PRINT("\n");
}

/**
 * @brief Main Zappy function
 * @details the main function of the Zappy server,
 *  it initializes the serverInfo struct and the socket,
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
    int socketFd = -1;
    server_info_t serverInfo;

    errno = 0;
    DEBUG_PRINT("Zappy server started\n");
    signal(2, handle_sigint);
    check_args(argc, argv);
    serverInfo = init_server_info(argv);
    socketFd = get_socket();
    prepare_exit(socketFd);
    bind_socket(socketFd, serverInfo->port);
    print_server_info(serverInfo);
    listen_socket(socketFd, 1024);
    zappy_loop(socketFd, serverInfo);
    close(socketFd);
    return 0;
}
