/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Color
*/

#pragma once

#include <cstdint>

namespace gui {
    /**
     * @brief Represents a color
     */
    struct Color {
        uint8_t red;
        uint8_t green;
        uint8_t blue;
        uint8_t alpha;
    };
}
