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

sf::Vector2f VecUtils::rotate(sf::Vector2f vec, float degrees)
{
	// absolutely not correct, but close enough for this usecase I'd say
    float rad = degrees * 3.1415f / 180.f;

    float c = std::cos(rad);
    float s = std::sin(rad);

    return { vec.x * c - vec.y * s, vec.x * s + vec.y * c };
}

sf::Vector2f VecUtils::clamp(sf::Vector2f vec, float maxLength)
{
	float lengthSquare = vec.x * vec.x + vec.y * vec.y;
	if (lengthSquare <= (maxLength * maxLength))
		return vec;

	float currLength = std::sqrtf(lengthSquare);
	float newScale = maxLength / currLength;

	return sf::Vector2f(vec.x * newScale, vec.y * newScale);
}