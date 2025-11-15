#pragma once

namespace VecUtils
{
	void normalizeVector2f(sf::Vector2f& vec);
	sf::Vector2f lerp(sf::Vector2f a, sf::Vector2f b, float t);
	sf::Vector2f rotate(sf::Vector2f vec, float degrees);
	sf::Vector2f clamp(sf::Vector2f, float maxLength);
};
