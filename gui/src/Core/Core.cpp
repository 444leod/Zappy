/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Core
*/

#include "GraphicalLibraryLoader.hpp"
#include "../GameDisplay/GameDisplay.hpp"
#include "GameData.hpp"
#include "ILibrary.hpp"
#include "GameDataManager.hpp"
#include "ArgumentChecking.hpp"
#include "Client.hpp"
#include "GameDataManager.hpp"
#include <cstring>
#include <iostream>
#include <vector>

namespace gui {

    class CoreException : public std::exception
    {
        public:
            CoreException(const std::string& msg) : _msg(msg) {}
            ~CoreException() = default;
            virtual const char *what() const noexcept { return _msg.c_str(); }
        private:
            std::string _msg;
    };

    class Core
    {
        public:
            Core() : _loader(LibraryLoader("./gui/lib"))
            {
                std::string path = "./gui/lib/zappy_sfml2d.so";

                if (!this->_loader.contains(path, gui::SharedLibraryType::LIBRARY))
                    throw CoreException("File " + path + " is not a valid graphical library.");
                this->_libHandler = this->_loader.load(path);
                if (!this->_libHandler)
                    throw CoreException("Could not open " + path + ".");
                this->_curLib = this->_libHandler->get<gui::ILibrary>();
                if (this->_curLib == nullptr)
                    throw CoreException("Object failed to load library");
                this->_gameDisplay.initialize(*_curLib);
            }

            ~Core() {}

            void switchGraphicLib()
            {
                std::string title = this->_curLib->display().title();
                uint32_t framerate = this->_curLib->display().framerate();
                std::size_t width = this->_curLib->display().width();
                std::size_t height = this->_curLib->display().height();

                auto textures = this->_curLib->textures().dump();
                auto fonts = this->_curLib->fonts().dump();
                auto sounds = this->_curLib->sounds().dump();
                auto musics = this->_curLib->musics().dump();

                this->_libHandler.reset();
                this->_curLib.reset();
                this->_curLib = this->_libHandler->get<gui::ILibrary>();
                if (this->_curLib == nullptr)
                    throw CoreException("Object failed to load library");

                this->_curLib->display().setTitle(title);
                this->_curLib->display().setFramerate(framerate);
                this->_curLib->display().setWidth(width);
                this->_curLib->display().setHeight(height);

                for (const auto& texture : textures)
                    this->_curLib->textures().load(texture.first, texture.second);

                for (const auto& font : fonts)
                    this->_curLib->fonts().load(font.first, font.second);

                for (const auto& sound : sounds)
                    this->_curLib->sounds().load(sound.first, sound.second);

                for (const auto& music : musics)
                    this->_curLib->musics().load(music.first, music.second);
            }

            void run(std::uint32_t port)
            {
                auto libSwitch = false;
                auto before = std::chrono::high_resolution_clock::now();
                gui::GameDataManager gameDataManager(port);

                while (this->_curLib->display().opened()) {
//                    gameDataManager.handleRequests();
                    gui::Event event = {};
                    auto now = std::chrono::high_resolution_clock::now();
                    float deltaTime = std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(now - before).count() / 1000.0;
                    before = now;

                    if (libSwitch) {
                        this->switchGraphicLib();
                        libSwitch = false;
                        continue;
                    }
                    while (_curLib->display().pollEvent(event)) {
                        if (event.key.code == gui::KeyCode::J || event.key.code == gui::KeyCode::L)
                            libSwitch = true;
                    }

                    this->_curLib->display().update(deltaTime);
                    this->_gameDisplay.draw(*_curLib, _gameData);
                }
            }

        private:
            GameData _gameData;
            GameDisplay _gameDisplay;
            std::shared_ptr<gui::ILibrary> _curLib = nullptr;
            std::shared_ptr<LibraryObject> _libHandler = nullptr;
            LibraryLoader _loader;
    };
}

int main(int ac, char **av)
{
    try {
        std::shared_ptr<gui::ArgumentChecking> argCheck = std::make_shared<gui::ArgumentChecking>();
        argCheck->checkArgs(ac, av);
        std::uint32_t port = std::atoi(av[2]);
        gui::Core core;
        core.run(port);
    }
    catch (const std::invalid_argument &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    } catch (const gui::ntw::Client::ClientTimeoutException& e) {
        std::cerr << e.what() << std::endl;
        return 84;
    } catch (const gui::ntw::Client::ClientNotConnectedException& e) {
        std::cerr << e.what() << std::endl;
        return 84;
    } catch (const gui::ntw::Client::ClientException& e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
