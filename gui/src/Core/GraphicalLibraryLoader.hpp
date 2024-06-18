/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** GraphicalLibraryLoader
*/

#pragma once

#include "../../include/Graphics/SharedLibraryType.hpp"
#include <dlfcn.h>
#include <iostream>
#include <vector>
#include <filesystem>

namespace gui {

    class LibraryObject {
            public:
            LibraryObject(const std::string& path);
            ~LibraryObject();

            template<typename T>
            std::shared_ptr<T> get()
            {
                auto h = reinterpret_cast<T *(*)()>(dlsym(_handle, "entrypoint"));
                return std::shared_ptr<T>(h());
            }

            bool loaded() const { return this->_loaded; }
            const std::string& path() const { return this->_path; }
            const std::string& name() const { return this->_name; }
            gui::SharedLibraryType type() const { return this->_type; }

        private:
            bool _loaded = false;
            std::string _path = "";
            std::string _name = "";
            gui::SharedLibraryType _type = gui::SharedLibraryType::LIBRARY;
            void *_handle = nullptr;
    };

    class LibraryLoader {
        public:
            LibraryLoader(const std::string &path);
            ~LibraryLoader();
            const std::vector<std::shared_ptr<LibraryObject>> &libs() const { return this->_libs; }
            bool contains(const std::string &lib, gui::SharedLibraryType type) const;
            bool contains(const std::string &lib) const;
            bool contains(gui::SharedLibraryType type) const;
            std::shared_ptr<LibraryObject> nextLib();
            std::shared_ptr<LibraryObject> load(const std::string &path, gui::SharedLibraryType type = gui::SharedLibraryType::LIBRARY);

        private:
            bool path_cmp(const std::string &a, const std::string& b) const;

            int _gameIndex = -1;
            int _libIndex = -1;
            std::vector<std::shared_ptr<LibraryObject>> _libs = {};
    };
}
