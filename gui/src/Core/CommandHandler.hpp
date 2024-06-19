/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** CommandHandler
*/

#pragma once

#include "Client.hpp"
#include "GameData.hpp"
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
#include "Pbc.hpp"
#include "Enw.hpp"
#include "Mct.hpp"
#include "Ebo.hpp"
#include "Pfk.hpp"
#include "Sgt.hpp"
#include "Sst.hpp"
#include "Smg.hpp"
#include "Suc.hpp"
#include "Sbp.hpp"
#include <functional>
#include <unordered_map>

namespace gui {
    class CommandHandler {
        public:
            CommandHandler(std::shared_ptr<ntw::Client> client, std::shared_ptr<GameData> gameData) : _client(client), _gameData(gameData) {}
            ~CommandHandler() = default;

            /**
             * @brief The handleCommand function is used to handle the command given by the server
             * @param command The command given by the server
             */
            void handleCommand(std::string& command);

        private:
            std::shared_ptr<ntw::Client> _client;
            std::shared_ptr<GameData> _gameData;
            std::unordered_map<std::string, std::shared_ptr<ICommand>> _responseHandlers = {
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
                {"pgt", std::make_shared<Pgt>()},
                {"pbc", std::make_shared<Pbc>()},
                {"enw", std::make_shared<Enw>()},
                {"mct", std::make_shared<Mct>()},
                {"ebo", std::make_shared<Ebo>()},
                {"pfk", std::make_shared<Pfk>()},
                {"sgt", std::make_shared<Sgt>()},
                {"sst", std::make_shared<Sst>()},
                {"smg", std::make_shared<Smg>()},
                {"suc", std::make_shared<Suc>()},
                {"sbp", std::make_shared<Sbp>()}
            };
    };
}
