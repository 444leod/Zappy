/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** connect_to_socket
*/

#include "lib.h"
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

/**
 * @brief Connect client socket to server
 *
 * @param sockfd the client socket
 * @param ip the server ip
*/
void connect_to_server(int sockfd, char *ip, int port)
{
    struct sockaddr_in servaddr;

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(ip);
    servaddr.sin_port = htons(port);
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0)
        my_error("Connection with the server failed");
}
