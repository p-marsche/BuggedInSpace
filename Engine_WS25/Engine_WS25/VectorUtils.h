#pragma once

#include "SFML/Graphics.hpp"
#include <math.h>

namespace VecUtils
{
	static void NormalizeVector2f(sf::Vector2f& vec)
	{
		float vecLength = std::sqrtf(vec.x * vec.x + vec.y * vec.y);
		if (std::abs(vecLength) < 0.05f)
			return;

		vec = { vec.x / vecLength, vec.y / vecLength };
	}
};

