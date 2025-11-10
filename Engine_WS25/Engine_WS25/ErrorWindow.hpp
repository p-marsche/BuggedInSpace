#pragma once

// idk if we need/want this, but i put it in for now

/// <summary>
/// Displays a simple window with the message of the occured exception
/// </summary>
class ErrorWindow
{
public:
    ErrorWindow(std::string message);
    void showError();

private:
    sf::RenderWindow m_window = sf::RenderWindow();
    std::string m_errorMessage;
};
