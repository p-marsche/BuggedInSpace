#pragma once

#include "pch.h"

// idk if we need/want this, but i put it in for now

/// Displays a simple window with the message of the occured exception
class ErrorWindow
{
public:
    ErrorWindow(std::string message);
    void showError();

private:
    sf::RenderWindow m_window = sf::RenderWindow();
    std::string m_errorMessage;
};
