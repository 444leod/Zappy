/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Message
*/

#pragma once

#include <vector>
#include <iostream>
#include <cstdint>
#include <ctime>
#include <chrono>

namespace gui {
    typedef struct message_s {
        std::uint32_t senderId;
        std::string message;
        std::string teamName;
        std::chrono::system_clock::time_point time;
    } message_t;
}
