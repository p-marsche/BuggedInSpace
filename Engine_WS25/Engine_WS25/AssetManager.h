#pragma once
#include <exception>
#include <string>
#include <map>
#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "SpriteSheet.h"

// predeclarations for used classes
namespace sf
{
    class Texture;
    class SoundBuffer;
    class Music;
    class Font;
    class Image;
}
struct SpriteSheet;

class AssetNotFoundException : std::exception
{
private:
    std::string m_text;

public:
    AssetNotFoundException();
    AssetNotFoundException(std::string message);

    const char* what() const noexcept override;
};

class AssetManager
{
private:
    std::map<std::string, std::unique_ptr<sf::Texture>> m_textures = std::map<std::string, std::unique_ptr<sf::Texture>>();
    std::map<std::string, std::unique_ptr<sf::SoundBuffer>> m_soundBuffers = std::map<std::string, std::unique_ptr<sf::SoundBuffer>>();
    std::map<std::string, std::unique_ptr<sf::Font>> m_fonts = std::map<std::string, std::unique_ptr<sf::Font>>();
    std::map<std::string, std::unique_ptr<sf::Music>> m_music = std::map<std::string, std::unique_ptr<sf::Music>>();
    std::map<std::string, std::unique_ptr<sf::Image>> m_images = std::map<std::string, std::unique_ptr<sf::Image>>();
    std::map<std::string, std::unique_ptr<SpriteSheet>> m_spriteSheets = std::map<std::string, std::unique_ptr<SpriteSheet>>();

    AssetManager() {}
    ~AssetManager() {}

public:
    static AssetManager& instance();

    AssetManager(const AssetManager&) = delete;
    AssetManager& operator = (const AssetManager&) = delete;

    void loadTexture(std::string name, std::string filename);
    void loadSoundBuffer(std::string name, std::string filename);
    void loadFont(std::string name, std::string filename);
    void loadMusic(std::string name, std::string filename);
    void loadImage(std::string name, std::string filename);
    void loadSpriteSheet(std::string name, std::string filename, int tilingX, int tilingY, std::vector<int> numberAnimationFrames);

    sf::Texture& getTexture(std::string name);
    sf::SoundBuffer& getSoundBuffer(std::string name);
    sf::Font& getFont(std::string name);
    sf::Music& getMusic(std::string name);
    sf::Image& getImage(std::string name);
    SpriteSheet& getSpriteSheet(std::string name);
};