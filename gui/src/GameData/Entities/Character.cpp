/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Character
*/

#include "Character.hpp"

void gui::Character::updateEvolutionStatus(UNUSED Vector2u position, UNUSED std::uint32_t level, bool result)
{
    if (result) {
        increasePlayerLevel();
        _incantationResult = true;
    } else
        _incantationResult = false;
}
