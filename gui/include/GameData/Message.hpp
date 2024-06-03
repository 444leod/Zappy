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

namespace gui {
    struct Message {
        std::uint32_t id;
        std::string message;
        std::string teamName;
        std::time_t time;
    };
}
