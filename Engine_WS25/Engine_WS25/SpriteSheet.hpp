#pragma once

#include "pch.h"

// predecleration for used classes
namespace sf {
	class Texture;
}

struct SpriteSheet
{
public:
	std::shared_ptr<sf::Texture> m_sheetTexture;
	const int TILING_X;
	const int TILING_Y;
	const std::vector<int> m_numberAnimationFrames;

	SpriteSheet(const std::shared_ptr<sf::Texture> texture, int x, int y, const std::vector<int>& numberAnimationFrames)
		: m_sheetTexture(texture)
		, TILING_X(x)
		, TILING_Y(y)
		, m_numberAnimationFrames(numberAnimationFrames)
	{ }
};
