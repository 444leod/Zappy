/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** magic_number
*/

#include "magic_number.h"
#include <stdbool.h>
#include <unistd.h>

/**
 * @brief Check if the magic number is valid
 * @details Read the file descriptor and check if the magic number is valid
 * It should be sent before the packets and written before saves files.
 *
 * @param fd the file descriptor
 *
 * @return true if the magic number is valid, false otherwise
*/
bool is_magic_number_valid(int fd)
{
    unsigned int magic_number = 0;

    if (read(fd, &magic_number, sizeof(magic_number)) == -1)
        return false;
    return (magic_number == MAGIC_NUMBER);
}

/**
 * @brief Write the magic number
 * @details Write the magic number to the file descriptor
 *
 * @param fd the file descriptor
*/
void write_magic_number(int fd)
{
    unsigned int magic_number = MAGIC_NUMBER;

    write(fd, &magic_number, sizeof(magic_number));
}
