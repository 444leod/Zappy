/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Character
*/

#include "Character.hpp"

void gui::Character::updateEvolutionStatus(bool result)
{
    if (result)
        _incantationResult = true;
    else
        _incantationResult = false;
}
