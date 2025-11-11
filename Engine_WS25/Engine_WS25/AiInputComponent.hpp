#pragma once

#include "InputComponent.hpp"

#include <SFML/Graphics.hpp>

class AiInputComponent
	: public InputComponent
{
public:
	AiInputComponent();
	~AiInputComponent() = default;
	void SetMoveDirection(sf::Vector2f direction);

private:
};

