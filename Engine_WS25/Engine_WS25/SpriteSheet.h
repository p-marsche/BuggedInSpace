#pragma once
#include <memory>
#include <vector>

// predecleration for used classes
namespace sf {
	class Texture;
}

struct SpriteSheet
{
	std::shared_ptr<sf::Texture> sheetTexture;
	const int TILING_X;
	const int TILING_Y;
	const std::vector<int> numberAnimationFrames;

	SpriteSheet(std::shared_ptr<sf::Texture> texture, int x, int y, std::vector<int> numberAnimationFrames)
		: sheetTexture(texture)
		, TILING_X(x)
		, TILING_Y(y)
		, numberAnimationFrames(numberAnimationFrames)
	{ }
};