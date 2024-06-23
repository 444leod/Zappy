/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Rect
*/

#pragma once

namespace gui {
    /**
     * @brief Represents a rectangle
     */
    template<typename T>
    struct Rect {
        T x;
        T y;
        T width;
        T height;
    };
}
