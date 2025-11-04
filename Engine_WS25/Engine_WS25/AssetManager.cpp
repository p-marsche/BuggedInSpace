#include "AssetManager.h"

AssetNotFoundException::AssetNotFoundException() { m_text = ""; }
AssetNotFoundException::AssetNotFoundException(std::string message) : m_text(message) {}

const char* AssetNotFoundException::what() const noexcept
{
	std::string output = "An asset could not be found: " + m_text;
	return output.c_str();
}


AssetManager& AssetManager::instance()
{
	static AssetManager assetManager;
	return assetManager;
}

void AssetManager::loadTexture(std::string name, std::string filename)
{
	m_textures.insert({ name, std::make_unique<sf::Texture>() });
	m_textures[name]->loadFromFile("./Assets/Textures/" + filename); //< somehow make more configurable location. config file/class with consts?
}

void AssetManager::loadSoundBuffer(std::string name, std::string filename)
{
	m_soundBuffers.insert({ name, std::make_unique<sf::SoundBuffer>() });
	m_soundBuffers[name]->loadFromFile(".Assets/Sounds/" + filename);
}

void AssetManager::loadFont(std::string name, std::string filename)
{
	m_fonts.insert({ name,std::make_unique<sf::Font>() });
	m_fonts[name]->loadFromFile("./Assets/Fonts/" + filename);
}

void AssetManager::loadMusic(std::string name, std::string filename)
{
	m_music.insert({ name, std::make_unique<sf::Music>() });
	m_music[name]->openFromFile("./Assets/Music" + filename);
}

void AssetManager::loadSpriteSheet(std::string name, std::string filename, int tilingX, int tilingY, std::vector<int> numberAnimationFrames)
{
	auto texture(std::make_shared<sf::Texture>());
	texture->loadFromFile("./Assets/SpriteSheets/" + filename);
	m_spriteSheets.insert({ name, std::make_unique<SpriteSheet>(texture, tilingX, tilingY, numberAnimationFrames) });
}

void AssetManager::loadImage(std::string name, std::string filename)
{
	m_images.insert({ name, std::make_unique<sf::Image>() });
	m_images[name]->loadFromFile("./Assets/Images/" + filename);
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