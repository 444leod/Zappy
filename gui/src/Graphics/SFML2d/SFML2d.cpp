/*
** EPITECH PROJECT, 2024
** SFML.cpp
** File description:
** SFML.cpp
*/

#include "../../../include/Graphics/ILibrary.hpp"
#include "../../../include/Graphics/SharedLibraryType.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <deque>
#include <memory>

class SFML2dTexture : public gui::ITexture {
public:
    SFML2dTexture() = default;
    virtual ~SFML2dTexture() = default;

    void load(
        const gui::TextureSpecification& spec,
        const std::shared_ptr<sf::Texture>& texture,
        std::optional<gui::Rect<uint32_t>> rect
    )
    {
        this->_spec = spec;
        this->_texture = texture;

        if (rect.has_value()) {
            this->_rect = sf::IntRect(
                rect.value().x,
                rect.value().y,
                rect.value().width,
                rect.value().height
            );
        } else {
            this->_rect = sf::IntRect(
                0,
                0,
                texture->getSize().x,
                texture->getSize().y
            );
        }
    }

    virtual const gui::TextureSpecification& specification() const { return this->_spec; }
    const std::shared_ptr<sf::Texture>& raw() const { return this->_texture; }
    const sf::IntRect subrect() const { return this->_rect; }

private:
    std::shared_ptr<sf::Texture> _texture;
    sf::IntRect _rect;
    gui::TextureSpecification _spec;
};

class SFML2dTextureManager : public gui::ITextureManager {
public:
    SFML2dTextureManager() = default;
    virtual ~SFML2dTextureManager() = default;

    virtual bool load(const std::string& name, const gui::TextureSpecification& specification, unsigned int width = 1, unsigned int height = 1)
    {
        auto texture = std::make_shared<SFML2dTexture>();

        if (std::holds_alternative<gui::TextureImage>(specification.graphical)) {
            auto image = std::get<gui::TextureImage>(specification.graphical);

            if (this->_cache.find(image.path) != this->_cache.end()) {
                texture->load(specification, this->_cache[image.path], image.subrect);
                this->_textures[name] = texture;
                return true;
            }

            auto sftex = std::make_shared<sf::Texture>();
            if (!sftex->loadFromFile(image.path))
                return false;

            this->_cache[image.path] = sftex;
            texture->load(specification, sftex, image.subrect);
            this->_textures[name] = texture;
            return true;
        }

        auto color = std::get<gui::Color>(specification.graphical);
        auto img = sf::Image{};
        img.create(width, height, sf::Color(color.red, color.green, color.blue, color.alpha));
        auto sftex = std::make_shared<sf::Texture>();
        if (!sftex->loadFromImage(img))
            return false;
        texture->load(specification, sftex, std::nullopt);
        this->_textures[name] = texture;
        return true;
    }

    virtual std::shared_ptr<gui::ITexture> get(const std::string& name)
    {
        if (this->_textures.find(name) == this->_textures.end())
            return nullptr;
        return this->_textures.at(name);
    }

    virtual std::map<std::string, gui::TextureSpecification> dump() const
    {
        auto specs = std::map<std::string, gui::TextureSpecification>{};

        for (const auto& [name, texture] : this->_textures)
            specs[name] = texture->specification();

        return specs;
    }

private:
    std::map<std::string, std::shared_ptr<sf::Texture>> _cache;
    std::map<std::string, std::shared_ptr<SFML2dTexture>> _textures;
};

class SFML2dFont : public gui::IFont {
public:
    SFML2dFont() = default;
    virtual ~SFML2dFont() = default;

    bool init(const gui::FontSpecification& spec)
    {
        this->_spec = spec;
        if (!this->_font.loadFromFile(spec.path))
            return false;
        this->_color =  sf::Color(spec.color.red, spec.color.green, spec.color.blue, spec.color.alpha);
        this->_size = spec.size;
        return true;
    }

    virtual const gui::FontSpecification& specification() const { return this->_spec; }
    const sf::Color& color() const { return this->_color; }
    std::size_t size() const { return this->_size; }
    const sf::Font& font() const { return this->_font; }

private:
    sf::Color _color = {};
    std::size_t _size = 0;
    sf::Font _font = {};
    gui::FontSpecification _spec = {};
};

class SFML2dFontManager : public gui::IFontManager {
public:
    SFML2dFontManager() = default;
    virtual ~SFML2dFontManager() = default;

    virtual bool load(const std::string& name, const gui::FontSpecification& spec)
    {
        auto attribute = std::make_shared<SFML2dFont>();

        if (!attribute->init(spec))
            return false;
        this->_fonts[name] = attribute;
        return true;
    }

    virtual std::shared_ptr<gui::IFont> get(const std::string &name)
    {
        if (this->_fonts.find(name) == this->_fonts.end())
            return nullptr;
        return this->_fonts.at(name);
    }

    virtual std::map<std::string, gui::FontSpecification> dump() const
    {
        auto specs = std::map<std::string, gui::FontSpecification>{};

        for (const auto& [name, font] : this->_fonts)
            specs[name] = font->specification();

        return specs;
    }

private:
    std::map<std::string, std::shared_ptr<SFML2dFont>> _fonts;
};

class SFML2dSound : public gui::ISound {
public:
    SFML2dSound() = default;
    virtual ~SFML2dSound() = default;

    bool init(const gui::SoundSpecification& spec)
    {
        this->_spec = spec;
        if (!_buffer.loadFromFile(spec.path)) {
            const int sampleRate = 44100;

            std::vector<sf::Int16> samples(sampleRate);
            for (size_t i = 0; i < samples.size(); ++i) {
                samples[i] = 0;
            }

            _buffer.loadFromSamples(&samples[0], samples.size(), 1, sampleRate);
        }
        return true;
    }

    void setBuffer(void)
    {
        _sound.setBuffer(_buffer);
    }

    virtual void play() { _sound.play(); }
    virtual void stop() { this->_sound.stop(); }
    virtual sf::Sound::Status getStatus() const { return this->_sound.getStatus(); }
    virtual void setVolume(float volume) { this->_sound.setVolume(volume); }

    virtual const gui::SoundSpecification& specification() const { return this->_spec; }
    const sf::Sound& sound() const { return this->_sound; }

private:
    sf::Sound _sound = {};
    sf::SoundBuffer _buffer = {};
    gui::SoundSpecification _spec = {};
};

class SFML2dSoundManager : public gui::ISoundManager {
public:
    SFML2dSoundManager() = default;
    virtual ~SFML2dSoundManager() = default;

    virtual bool load(const std::string& name, const gui::SoundSpecification& spec)
    {
        auto sound = std::make_shared<SFML2dSound>();

        if (!sound->init(spec))
            return false;

        this->_sounds[name] = sound;
        this->_sounds[name]->setBuffer();
        return true;
    }

    virtual std::shared_ptr<gui::ISound> get(const std::string &name)
    {
        return this->_sounds.at(name);
    }

    virtual std::map<std::string, gui::SoundSpecification> dump() const
    {
        auto specs = std::map<std::string, gui::SoundSpecification>{};

        for (auto& [name, sound] : this->_sounds) {
            specs[name] = sound->specification();
        }

        return specs;
    }

    virtual void play(const std::string& name, const float volume)
    {
        this->_sounds.at(name)->setVolume(volume);
        this->_sounds.at(name)->play();
    }

    virtual void stop(const std::string& name)
    {
        this->_sounds.at(name)->stop();
    }

    virtual bool isPlaying(const std::string& name)
    {
        return this->_sounds.at(name)->getStatus() == sf::Sound::Playing;
    }

private:
    std::map<std::string, std::shared_ptr<SFML2dSound>> _sounds;
};

class SFML2dMusic : public gui::IMusic {
public:
    SFML2dMusic() = default;
    virtual ~SFML2dMusic() = default;

    bool init(const gui::MusicSpecification& spec)
    {
        this->_spec = spec;
        if (!this->_music.openFromFile(spec.path))
            return false;

        this->_music.setLoop(spec.loop);
        if (spec.startOffset != -1)
            this->_music.setPlayingOffset(sf::seconds(spec.startOffset));
        if (spec.isPlaying)
            this->_music.play();
        return true;
    }

    virtual void play() {
        this->_music.play();
    }
    virtual void stop() { this->_music.stop(); }
    virtual void setVolume(float volume) { this->_music.setVolume(volume); }
    virtual sf::Music::Status getStatus() const { return this->_music.getStatus(); }

    virtual const gui::MusicSpecification& specification() const { return this->_spec; }
    const sf::Music& music() const { return this->_music; }

private:
    sf::Music _music = {};
    gui::MusicSpecification _spec = {};
};

class SFML2dMusicManager : public gui::IMusicManager {
public:
    SFML2dMusicManager() = default;
    virtual ~SFML2dMusicManager() = default;

    virtual bool load(const std::string& name, const gui::MusicSpecification& spec)
    {
        auto music = std::make_shared<SFML2dMusic>();

        if (!music->init(spec))
            return false;

        this->_musics[name] = music;
        return true;
    }

    virtual std::shared_ptr<gui::IMusic> get(const std::string &name)
    {
        return this->_musics.at(name);
    }

    virtual std::map<std::string, gui::MusicSpecification> dump() const
    {
        auto specs = std::map<std::string, gui::MusicSpecification>{};

        for (auto& [name, music] : this->_musics) {
            gui::MusicSpecification spec = music->specification();
            spec.isPlaying = music->getStatus() == sf::Music::Playing;
            if (spec.isPlaying)
                spec.startOffset = music->music().getPlayingOffset().asSeconds();

            specs[name] = spec;
        }

        return specs;
    }

    virtual void play(const std::string& name, const float volume)
    {
        this->_musics.at(name)->setVolume(volume);
        this->_musics.at(name)->play();
    }

    virtual void stop(const std::string& name)
    {
        this->_musics.at(name)->stop();
    }

    virtual bool isPlaying(const std::string& name)
    {
        return this->_musics.at(name)->getStatus() == sf::Music::Playing;
    }

private:
    std::map<std::string, std::shared_ptr<SFML2dMusic>> _musics;
};

class SFML2dDisplay : public gui::IDisplay {
public:
    SFML2dDisplay()
    {
        this->_tileSize = 16;
        this->_width = 80;
        this->_height = 60;
        this->_framerate = 0;
        this->_title = "GUI Application";

        sf::VideoMode mode;
        mode.width = this->_width * this->_tileSize;
        mode.height = this->_height * this->_tileSize;
        mode.bitsPerPixel = 32;
        this->_window.create(mode, this->_title, sf::Style::Titlebar | sf::Style::Close);
        this->_window.setKeyRepeatEnabled(false);
    }

    virtual ~SFML2dDisplay() = default;

    virtual void setTitle(const std::string& title)
    {
        this->_title = title;
        this->_window.setTitle(title);
    }

    virtual void setFramerate(uint32_t framerate)
    {
        this->_framerate = framerate;
        this->_window.setFramerateLimit(framerate);
    }

    virtual void setTileSize(std::size_t size)
    {
        this->_tileSize = size;
        this->_resizeWindow();
    }

    virtual void setWidth(std::size_t width)
    {
        this->_width = width;
        this->_resizeWindow();
    }

    virtual void setHeight(std::size_t height)
    {
        this->_height = height;
        this->_resizeWindow();
    }

    virtual std::string title() const
    {
        return this->_title;
    }

    virtual uint32_t framerate() const
    {
        return this->_framerate;
    }

    virtual std::size_t tileSize() const
    {
        return this->_tileSize;
    }

    virtual std::size_t width() const
    {
        return this->_width;
    }

    virtual std::size_t height() const
    {
        return this->_height;
    }

    static gui::KeyCode MapSFML2dKey(sf::Keyboard::Key key)
    {
        if (key < 26) return static_cast<gui::KeyCode>(key);
        if (key == sf::Keyboard::Up) return gui::KeyCode::UP;
        if (key == sf::Keyboard::Down) return gui::KeyCode::DOWN;
        if (key == sf::Keyboard::Left) return gui::KeyCode::LEFT;
        if (key == sf::Keyboard::Right) return gui::KeyCode::RIGHT;
        if (key == sf::Keyboard::Space) return gui::KeyCode::SPACE;
        if (key == sf::Keyboard::Enter) return gui::KeyCode::ENTER;
        if (key == sf::Keyboard::Escape) return gui::KeyCode::ESCAPE;
        if (key == sf::Keyboard::Tab) return gui::KeyCode::TAB;
        if (key == sf::Keyboard::BackSpace) return gui::KeyCode::DELETE;
        return gui::KeyCode::UNKNOWN;
    }

    static sf::Keyboard::Key MapGuiKey(gui::KeyCode key)
    {
        if (static_cast<uint64_t>(key) < 26) return static_cast<sf::Keyboard::Key>(key);
        if (key == gui::KeyCode::UP) return sf::Keyboard::Up;
        if (key == gui::KeyCode::DOWN) return sf::Keyboard::Down;
        if (key == gui::KeyCode::LEFT) return sf::Keyboard::Left;
        if (key == gui::KeyCode::RIGHT) return sf::Keyboard::Right;
        if (key == gui::KeyCode::SPACE) return sf::Keyboard::Space;
        if (key == gui::KeyCode::ENTER) return sf::Keyboard::Enter;
        if (key == gui::KeyCode::ESCAPE) return sf::Keyboard::Escape;
        return sf::Keyboard::Unknown;
    }

    static gui::MouseButton MapSFML2dMouseButton(sf::Mouse::Button button)
    {
        if (button == sf::Mouse::Left) return gui::MouseButton::LEFT;
        if (button == sf::Mouse::Right) return gui::MouseButton::RIGHT;
        if (button == sf::Mouse::Middle) return gui::MouseButton::MIDDLE;
        return gui::MouseButton::UNKNOWN;
    }

    static sf::Mouse::Button MapGuiMouseButton(gui::MouseButton button)
    {
        if (button == gui::MouseButton::LEFT) return sf::Mouse::Left;
        if (button == gui::MouseButton::RIGHT) return sf::Mouse::Right;
        if (button == gui::MouseButton::MIDDLE) return sf::Mouse::Middle;
        return sf::Mouse::ButtonCount;
    }

    virtual void update([[maybe_unused]] float deltaTime)
    {
        sf::Event event;
        gui::Event e;

        while (this->_window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                this->_window.close();
                break;
            case sf::Event::KeyPressed:
                e.type = gui::EventType::KEY_PRESSED;
                e.key.code = SFML2dDisplay::MapSFML2dKey(event.key.code);
                e.key.shift = event.key.shift;
                this->_events.push_back(std::move(e));
                break;
            case sf::Event::MouseButtonPressed:
                e.type = gui::EventType::MOUSE_BUTTON_PRESSED;
                e.mouse.button = SFML2dDisplay::MapSFML2dMouseButton(event.mouseButton.button);
                e.mouse.x = event.mouseButton.x / this->_tileSize;
                e.mouse.y = event.mouseButton.y / this->_tileSize;
                this->_events.push_back(std::move(e));
                break;
            default:
                break;
            }
        }
    }

    virtual bool pollEvent(gui::Event& event)
    {
        if (this->_events.empty())
            return false;

        event = this->_events.front();
        this->_events.pop_front();
        return true;
    }

    virtual void close()
    {
        this->_window.close();
    }

    virtual bool opened() const
    {
        return this->_window.isOpen();
    }

    virtual void clear(gui::Color color)
    {
        this->_window.clear(sf::Color{color.red, color.green, color.blue, color.alpha});
    }

    virtual void draw(std::shared_ptr<gui::ITexture> texture, float x, float y, float scale)
    {
        if (texture == nullptr)
            return;

        auto sprite = sf::Sprite{};
        auto tex = std::dynamic_pointer_cast<SFML2dTexture>(texture);

        sprite.setTexture(*tex->raw().get());
        sprite.setTextureRect(tex->subrect());
        sprite.setPosition(x * this->_tileSize, y * this->_tileSize);
        sprite.setScale(scale, scale);
        this->_window.draw(sprite);
    }

    virtual void print(const std::string& string, std::shared_ptr<gui::IFont> font, float x, float y)
    {
        if (font == nullptr)
            return;

        auto attr = std::dynamic_pointer_cast<SFML2dFont>(font);
        auto text = sf::Text(sf::String(string), attr->font(), attr->size());
        text.setFillColor(attr->color());
        text.setPosition(x * this->_tileSize, y * this->_tileSize);
        this->_window.draw(text);
    }

    virtual gui::Rect<float> measure(const std::string& string, std::shared_ptr<gui::IFont> font, float x, float y)
    {
        if (font == nullptr)
            return gui::Rect<float> { 0.f, 0.f, 0.f, 0.f };

        auto attr = std::dynamic_pointer_cast<SFML2dFont>(font);
        auto text = sf::Text(sf::String(string), attr->font(), attr->size());
        text.setFillColor(attr->color());
        text.setPosition(x, y);
        auto bounds = text.getLocalBounds();
        return {bounds.left, bounds.top, bounds.width / this->_tileSize, bounds.height / this->_tileSize};
    }

    virtual void flush()
    {
        this->_window.display();
    }

private:
    virtual void _resizeWindow()
    {
        sf::Vector2u size;
        size.x = this->_width * this->_tileSize;
        size.y = this->_height * this->_tileSize;

        this->_window.setSize(size);
        this->_window.setView(sf::View(sf::FloatRect(0, 0, size.x, size.y)));
    }

private:
    sf::RenderWindow _window;

    std::string _title;
    uint32_t _framerate;
    std::size_t _width;
    std::size_t _height;
    std::size_t _tileSize;
    std::deque<gui::Event> _events;
};

class SFML2dLibrary : public gui::ILibrary {
public:
    SFML2dLibrary() = default;
    virtual ~SFML2dLibrary() = default;

    virtual gui::IDisplay& display() { return this->_display; }
    virtual gui::ITextureManager& textures() { return this->_textures; }
    virtual gui::IFontManager& fonts() { return this->_fonts; }
    virtual gui::ISoundManager& sounds() { return this->_sounds; }
    virtual gui::IMusicManager& musics() { return this->_musics; }

private:
    SFML2dDisplay _display;
    SFML2dTextureManager _textures;
    SFML2dFontManager _fonts;
    SFML2dSoundManager _sounds;
    SFML2dMusicManager _musics;
};

extern "C" gui::ILibrary *entrypoint()
{
    return new SFML2dLibrary;
}

extern "C" gui::SharedLibraryType type()
{
    return gui::SharedLibraryType::LIBRARY;
}

extern "C" const char *name()
{
    return "SFML2d";
}
