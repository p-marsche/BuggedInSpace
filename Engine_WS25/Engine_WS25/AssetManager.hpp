#pragma once

#include "SpriteSheet.hpp"

class AssetNotFoundException : std::exception
{
public:
    AssetNotFoundException();
    AssetNotFoundException(std::string message);

    const char* what() const noexcept override;

private:
    std::string m_text;
};

class AssetManager
{
public:
    static AssetManager& getInstance();

    AssetManager(const AssetManager&) = delete;
    AssetManager& operator =(const AssetManager&) = delete;

    // if using duplicate key does nothing
    void loadTexture(std::string name, std::string filename);
    void loadSoundBuffer(std::string name, std::string filename);
    void loadFont(std::string name, std::string filename);
    void loadMusic(std::string name, std::string filename);
    void loadImage(std::string name, std::string filename);
    void loadSpriteSheet(std::string name, std::string filename, int tilingX, int tilingY, std::vector<int> numberAnimationFrames);

    // explicit replace functions
    void replaceTexture(std::string name, std::string filename);
    void replaceSoundBuffer(std::string name, std::string filename);
    void replaceFont(std::string name, std::string filename);
    void replaceMusic(std::string name, std::string filename);
    void replaceImage(std::string name, std::string filename);
    void replaceSpriteSheet(std::string name, std::string filename, int tilingX, int tilingY, std::vector<int> numberAnimationFrames);

    sf::Texture& getTexture(std::string name);
    sf::SoundBuffer& getSoundBuffer(std::string name);
    sf::Font& getFont(std::string name);
    sf::Music& getMusic(std::string name);
    sf::Image& getImage(std::string name);
    SpriteSheet& getSpriteSheet(std::string name);

private:
    std::unordered_map<std::string, std::unique_ptr<sf::Texture>> m_textures;
    std::unordered_map<std::string, std::unique_ptr<sf::SoundBuffer>> m_soundBuffers;
    std::unordered_map<std::string, std::unique_ptr<sf::Font>> m_fonts;
    std::unordered_map<std::string, std::unique_ptr<sf::Music>> m_music;
    std::unordered_map<std::string, std::unique_ptr<sf::Image>> m_images;
    std::unordered_map<std::string, std::unique_ptr<SpriteSheet>> m_spriteSheets;

    AssetManager() {}
    ~AssetManager() {}
};
