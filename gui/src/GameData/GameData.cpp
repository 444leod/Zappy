/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** GameData
*/

#include "GameData.hpp"
#include <algorithm>

namespace gui {
    void GameData::addPlayer(std::shared_ptr<Character> player)
    {
        this->_players.push_back(player);
        this->_map.getTileContentByCoordinates(player->position()).addEntity(player);
    }

    void GameData::removePlayer(std::uint32_t playerId)
    {
        auto it = std::find_if(this->_players.begin(), this->_players.end(),
            [playerId](const auto& player){ return player->id() == playerId; });

        if (it != this->_players.end()) {
            this->_map.removeEntityFromTile((*it)->position(), playerId);
            this->_players.erase(it);
        }
    }

    void GameData::addEgg(std::shared_ptr<Egg> egg)
    {
        this->_eggs.push_back(egg);
        this->_map.getTileContentByCoordinates(egg->position()).addEntity(egg);
    }

    void GameData::removeEgg(std::uint32_t eggId)
    {
        auto it = std::find_if(this->_eggs.begin(), this->_eggs.end(),
            [eggId](const auto& egg){ return egg->id() == eggId; });

        if (it != this->_eggs.end()) {
            this->_map.removeEntityFromTile((*it)->position(), eggId);
            this->_eggs.erase(it);
        }
    }
}
