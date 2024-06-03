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

namespace gui {
    struct Message {
        std::uint32_t id;
        std::string message;
        std::string teamName;
        std::uint32_t time;
    };
}
