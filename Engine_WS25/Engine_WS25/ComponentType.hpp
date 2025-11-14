#pragma once

enum class ComponentType
{
	FIRST,
	Health = FIRST,
	Physics,
	PlayerInput,
	Render,
	Status,
	Transform,
	LAST
	// FIRST and LAST here for iteration only
};