#include "pch.h"

#include "AssetManager.hpp"

AssetNotFoundException::AssetNotFoundException() { m_text = ""; }
AssetNotFoundException::AssetNotFoundException(std::string message) : m_text(message) {}

const char* AssetNotFoundException::what() const noexcept
{
	return m_text.c_str();
}


AssetManager& AssetManager::getInstance()
{
	static AssetManager assetManager;
	return assetManager;
}

void AssetManager::loadTexture(std::string name, std::string filename)
{
	m_textures.try_emplace(name, std::make_unique<sf::Texture>());
	m_textures[name]->loadFromFile("./Assets/Textures/" + filename); //< somehow make more configurable location. config file/class with consts?
}

void AssetManager::loadSoundBuffer(std::string name, std::string filename)
{
	m_soundBuffers.try_emplace(name, std::make_unique<sf::SoundBuffer>());
	m_soundBuffers[name]->loadFromFile(".Assets/Sounds/" + filename);
}

void AssetManager::loadFont(std::string name, std::string filename)
{
	m_fonts.try_emplace(name,std::make_unique<sf::Font>());
	m_fonts[name]->loadFromFile("./Assets/Fonts/" + filename);
}

void AssetManager::loadMusic(std::string name, std::string filename)
{
	m_music.try_emplace(name, std::make_unique<sf::Music>());
	m_music[name]->openFromFile("./Assets/Music" + filename);
}

void AssetManager::loadImage(std::string name, std::string filename)
{
	m_images.try_emplace(name, std::make_unique<sf::Image>());
	m_images[name]->loadFromFile("./Assets/Images/" + filename);
}

void AssetManager::loadSpriteSheet(std::string name, std::string filename, int tilingX, int tilingY, std::vector<int> numberAnimationFrames)
{
	auto texture(std::make_shared<sf::Texture>());
	texture->loadFromFile("./Assets/SpriteSheets/" + filename);
	m_spriteSheets.try_emplace(name, std::make_unique<SpriteSheet>(texture, tilingX, tilingY, numberAnimationFrames));
}

void AssetManager::replaceTexture(std::string name, std::string filename)
{
	if (auto it = m_textures.find(name) != m_textures.end())
	{
		auto extracted = m_textures.extract(name);
		auto ptr = extracted.mapped().release();
		if (ptr)
		{
			delete ptr;
			ptr = nullptr;
		}
	}
	m_textures.emplace(name, std::make_unique<sf::Texture>());
	m_textures[name]->loadFromFile("./Assets/Textures/" + filename);
}

void AssetManager::replaceSoundBuffer(std::string name, std::string filename)
{
	if (auto it = m_soundBuffers.find(name) != m_soundBuffers.end())
	{
		auto extracted = m_soundBuffers.extract(name);
		auto ptr = extracted.mapped().release();
		if (ptr)
		{
			delete ptr;
			ptr = nullptr;
		}
	}
	m_soundBuffers.emplace(name, std::make_unique<sf::SoundBuffer>());
	m_soundBuffers[name]->loadFromFile("./Assets/Sounds/" + filename);
}

void AssetManager::replaceFont(std::string name, std::string filename)
{
	if (auto it = m_fonts.find(name) != m_fonts.end())
	{
		auto extracted = m_fonts.extract(name);
		auto ptr = extracted.mapped().release();
		if (ptr)
		{
			delete ptr;
			ptr = nullptr;
		}
	}
	m_fonts.emplace(name, std::make_unique<sf::Font>());
	m_fonts[name]->loadFromFile("./Assets/Fonts/" + filename);
}

void AssetManager::replaceMusic(std::string name, std::string filename)
{
	if (auto it = m_music.find(name) != m_music.end())
	{
		auto extracted = m_music.extract(name);
		auto ptr = extracted.mapped().release();
		if (ptr)
		{
			delete ptr;
			ptr = nullptr;
		}
	}
	m_music.emplace(name, std::make_unique<sf::Music>());
	m_music[name]->openFromFile("./Assets/Music" + filename);
}

void AssetManager::replaceImage(std::string name, std::string filename)
{
	if (auto it = m_images.find(name) != m_images.end())
	{
		auto extracted = m_images.extract(name);
		auto ptr = extracted.mapped().release();
		if (ptr)
		{
			delete ptr;
			ptr = nullptr;
		}
	}
	m_images.emplace(name, std::make_unique<sf::Image>());
	m_images[name]->loadFromFile("./Assets/Images/" + filename);
}

void AssetManager::replaceSpriteSheet(std::string name, std::string filename, int tilingX, int tilingY, std::vector<int> numberAnimationFrames)
{
	if (auto it = m_spriteSheets.find(name) != m_spriteSheets.end())
	{
		auto extracted = m_spriteSheets.extract(name);
		auto ptr = extracted.mapped().release();
		if (ptr)
		{
			delete ptr;
			ptr = nullptr;
		}
	}
	auto texture(std::make_shared<sf::Texture>());
	texture->loadFromFile("./Assets/SpriteSheets/" + filename);
	m_spriteSheets.emplace(name, std::make_unique<SpriteSheet>(texture, tilingX, tilingY, numberAnimationFrames));
}


sf::Texture& AssetManager::getTexture(std::string name)
{
	if (m_textures.find(name) != m_textures.end())
		return *m_textures[name];
	else
		throw new AssetNotFoundException("The texture '{name}' could not be found!");
}

sf::SoundBuffer& AssetManager::getSoundBuffer(std::string name)
{
	if (m_soundBuffers.find(name) != m_soundBuffers.end())
		return *m_soundBuffers[name];
	else
		throw new AssetNotFoundException("The sound buffer '{name}' could not be found!");
}

sf::Font& AssetManager::getFont(std::string name)
{
	if (m_fonts.find(name) != m_fonts.end())
		return *m_fonts[name];
	else
		throw new AssetNotFoundException("The font '{name}' could not be found!");
}

sf::Music& AssetManager::getMusic(std::string name)
{
	if (m_music.find(name) != m_music.end())
		return *m_music[name];
	else
		throw new AssetNotFoundException("The music file '{name}' could not be found!");
}

sf::Image& AssetManager::getImage(std::string name)
{
	if (m_images.find(name) != m_images.end())
		return *m_images[name];
	else
		throw new AssetNotFoundException("The image file '{name}' could not be found!");
}

SpriteSheet& AssetManager::getSpriteSheet(std::string name)
{
	if (m_spriteSheets.find(name) != m_spriteSheets.end())
		return *m_spriteSheets[name];
	else
		throw new AssetNotFoundException("The sprite sheet '{name}' could not be found!");
}
