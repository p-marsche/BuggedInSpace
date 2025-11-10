#include "pch.h"

#include "VectorUtils.hpp"

void VecUtils::normalizeVector2f(sf::Vector2f& vec)
{
	float vecLength = std::sqrtf(vec.x * vec.x + vec.y * vec.y);
	if (std::abs(vecLength) < 0.05f)
		return;

	vec = { vec.x / vecLength, vec.y / vecLength };
}

sf::Vector2f VecUtils::lerp(sf::Vector2f a, sf::Vector2f b, float t) {
	return a * (1 - t) + b * t;
}