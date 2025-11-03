#pragma once
#include "IComponent.h"
class InputComponent :
    public IComponent
{
public:
    InputComponent(int playerNumber);
    ~InputComponent() = default;

private:
};

