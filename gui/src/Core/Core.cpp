/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Core
*/

#include "GraphicalLibraryLoader.hpp"
#include "GameData.hpp"
#include "GameDisplay.hpp"
#include "ILibrary.hpp"
#include <iostream>
#include <vector>
#include <fstream>

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
            Core(bool tty) : _loader(LibraryLoader("./lib", tty))
            {
                std::string path = "./lib/zappy_sfml2d.so";

                if (!this->_loader.contains(path, gui::SharedLibraryType::LIBRARY))
                    throw CoreException("File " + path + " is not a valid graphical library.");
                this->_lib_handler = this->_loader.load(path);
                if (!this->_lib_handler)
                    throw CoreException("Could not open " + path + ".");
                this->_cur_lib = this->_lib_handler->get<gui::ILibrary>();
            }

            ~Core() {}

            void switch_graphic_lib()
            {
                std::string title = this->_cur_lib->display().title();
                uint32_t framerate = this->_cur_lib->display().framerate();
                std::size_t tileSize = this->_cur_lib->display().tileSize();
                std::size_t width = this->_cur_lib->display().width();
                std::size_t height = this->_cur_lib->display().height();

                auto textures = this->_cur_lib->textures().dump();
                auto fonts = this->_cur_lib->fonts().dump();
                auto sounds = this->_cur_lib->sounds().dump();
                auto musics = this->_cur_lib->musics().dump();

                this->_lib_handler.reset();
                this->_cur_lib.reset();
                this->_cur_lib = this->_lib_handler->get<gui::ILibrary>();
                if (this->_cur_lib == nullptr)
                    throw CoreException("Object failed to load library");

                this->_cur_lib->display().setTitle(title);
                this->_cur_lib->display().setFramerate(framerate);
                this->_cur_lib->display().setTileSize(tileSize);
                this->_cur_lib->display().setWidth(width);
                this->_cur_lib->display().setHeight(height);

                for (const auto& texture : textures)
                    this->_cur_lib->textures().load(texture.first, texture.second, 0, 0);

                for (const auto& font : fonts)
                    this->_cur_lib->fonts().load(font.first, font.second);

                for (const auto& sound : sounds)
                    this->_cur_lib->sounds().load(sound.first, sound.second);

                for (const auto& music : musics)
                    this->_cur_lib->musics().load(music.first, music.second);
            }

            void run()
            {
                auto lib_switch = false;
                auto before = std::chrono::high_resolution_clock::now();

                _gameDisplay.initialize(*_cur_lib, _gameData);
                while (this->_cur_lib->display().opened()) {
                    gui::Event event = {};
                    auto now = std::chrono::high_resolution_clock::now();
                    float deltaTime = std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(now - before).count() / 1000.0;
                    before = now;

                    if (lib_switch) {
                        this->switch_graphic_lib();
                        lib_switch = false;
                        continue;
                    }

                    this->_cur_lib->display().update(deltaTime);

                    while (_cur_lib->display().pollEvent(event)) {
                        // Event handling
                    }
                    _gameDisplay.draw(*_cur_lib, _gameData);
                }
            }

        private:
            GameData _gameData;
            GameDisplay _gameDisplay;
            std::shared_ptr<gui::ILibrary> _cur_lib = nullptr;
            std::shared_ptr<LibraryObject> _lib_handler = nullptr;
            LibraryLoader _loader;
    };
}

int main(int ac, char **av, char **env)
{
    bool tty = true;

    for (int i = 0; env[i]; i++) {
        if (std::string(env[i]).find("DISPLAY") != 0)
            continue;
        tty = false;
        break;
    }

    try {
        gui::Core core(tty);
        core.run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}