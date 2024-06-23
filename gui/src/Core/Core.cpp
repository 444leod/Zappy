/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Core
*/

#include "GraphicalLibraryLoader.hpp"
#include "GameData.hpp"
#include "ILibrary.hpp"
#include "Client.hpp"
#include "../display/scenes/SceneManager.hpp"
#include "CommandHandler.hpp"
#include "ArgumentParser.hpp"
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

            void run(std::string host, std::uint16_t port)
            {
                auto libSwitch = false;
                auto before = std::chrono::high_resolution_clock::now();

                _serverCli = std::make_shared<ntw::Client>(host, port);
                _sceneManager = std::make_shared<gui::SceneManager>(_gameData, _serverCli);
                _sceneManager->initialize(*_curLib);
                _serverCli->connectToServer();

                gui::CommandHandler commandHandler(_serverCli, _gameData);

                while (this->_curLib->display().opened()) {

                    this->handleNetwork(commandHandler);

                    if (gui::CommandHandler::isLoaded) {
                        commandHandler.handleCommandsQueue();
                        gui::CommandHandler::isLoaded = false;
                    }

                    gui::Event event = {};
                    auto now = std::chrono::high_resolution_clock::now();
                    float deltaTime = std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(now - before).count() / 1000.0;
                    before = now;

                    this->_curLib->display().update(deltaTime);
                    if (libSwitch) {
                        this->switchGraphicLib();
                        libSwitch = false;
                        continue;
                    }
                    while (_curLib->display().pollEvent(event)) {
                        switch (event.type) {
                            case gui::EventType::MOUSE_BUTTON_PRESSED:
                                _sceneManager->onMouseButtonPressed(*_curLib, event.mouse.button, event.mouse.x, event.mouse.y);
                                break;
                            case gui::EventType::KEY_PRESSED:
                                _sceneManager->onKeyPressed(*_curLib, event.key.code, event.key.shift);
                                break;
                            case gui::EventType::KEY_DOWN:
                                _sceneManager->onKeyDown(*_curLib, event.key.code);
                                break;
                        }
                    }

                    _sceneManager->update(*_curLib, deltaTime);
                    _sceneManager->draw(*_curLib);
                }
            }

            void handleNetwork(gui::CommandHandler& commandHandler)
            {
                try {
                    _serverCli->receive();
                    if (_serverCli->hasRequests()) {
                        _serverCli->sendRequests(std::chrono::milliseconds(10));
                    }

                    while (_serverCli->hasResponses()) {
                        auto response = _serverCli->popResponse();
                        commandHandler.handleCommand(response);
                    }
                } catch (const ntw::Client::ClientTimeoutException& e) {
                    std::cerr << e.what() << std::endl;
                } catch (const std::invalid_argument& e) {
                    std::cerr << e.what() << std::endl;
                }
            }

        private:
            std::shared_ptr<gui::GameData> _gameData = std::make_shared<gui::GameData>();
            std::shared_ptr<gui::SceneManager> _sceneManager = nullptr;
            std::shared_ptr<ntw::Client> _serverCli = nullptr;
            std::shared_ptr<gui::ILibrary> _curLib = nullptr;
            std::shared_ptr<LibraryObject> _libHandler = nullptr;
            LibraryLoader _loader;
    };
}

int main(int ac, char **av)
{
    try {
        auto args = gui::ArgumentParser(ac, av);
        gui::Core().run(args.host(), args.port());
    }
    catch (const std::invalid_argument &e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
        return 84;
    } catch (const gui::ntw::Client::ClientTimeoutException& e) {
        std::cerr << "ClientTimeoutException: " << e.what() << std::endl;
        return 84;
    } catch (const gui::ntw::Client::ClientNotConnectedException& e) {
        std::cerr << "ClientNotConnectedException: " << e.what() << std::endl;
        return 84;
    } catch (const gui::ntw::Client::ClientException& e) {
        std::cerr << "ClientException: " << e.what() << std::endl;
        return 84;
    } catch (const gui::CoreException& e) {
        std::cerr << "CoreException: " << e.what() << std::endl;
        return 84;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 84;
    }
    return 0;
}
