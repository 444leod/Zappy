/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** GameDataManager
*/

#pragma once

#include "GameData.hpp"
#include "Client.hpp"
#include <sstream>
#include <functional>
#include <unordered_map>
#include "ACommand.hpp"
#include "Msz.hpp"
#include "Bct.hpp"
#include "Tna.hpp"
#include "Pex.hpp"
#include "Seg.hpp"
#include "Pnw.hpp"
#include "Ppo.hpp"
#include "Plv.hpp"
#include "Pin.hpp"
#include "Pic.hpp"
#include "Pie.hpp"
#include "Pdi.hpp"
#include "Edi.hpp"
#include "Pdr.hpp"
#include "Pgt.hpp"

namespace gui {
    class GameDataManager {
        public:
            GameDataManager(std::uint32_t port) : _port(port), _client(port) { _client.connectToServer(); }
            ~GameDataManager() = default;

            void handleRequests();

        private:
            std::vector<std::string> _requests;
            std::uint32_t _port;
            GameData _gameData;
            ntw::Client _client;
            std::unordered_map<std::string, std::shared_ptr<ACommand>> _responseHandlers = {
                {"msz", std::make_shared<Msz>()},
                {"bct", std::make_shared<Bct>()},
                {"tna", std::make_shared<Tna>()},
                {"pex", std::make_shared<Pex>()},
                {"seg", std::make_shared<Seg>()},
                {"pnw", std::make_shared<Pnw>()},
                {"ppo", std::make_shared<Ppo>()},
                {"plv", std::make_shared<Plv>()},
                {"pin", std::make_shared<Pin>()},
                {"pic", std::make_shared<Pic>()},
                {"pie", std::make_shared<Pie>()},
                {"pdi", std::make_shared<Pdi>()},
                {"edi", std::make_shared<Edi>()},
                {"pdr", std::make_shared<Pdr>()},
                {"pgt", std::make_shared<Pgt>()}
            };
    };
}
