#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <memory>

class DebugDraw
{
public:
    static DebugDraw& getInstance();
    void init(sf::RenderWindow* _window);
    void drawLine(sf::Vector2f start, sf::Vector2f end, sf::Color color);
    void drawRectOutline(sf::Vector2f topLeft, int width, int height, sf::Color color);
    void drawRectOutline(sf::IntRect rect, sf::Color color);
    void drawRectangle(sf::Vector2f position, int width, int height, sf::Color color);
    void drawRectangle(sf::IntRect rect, sf::Color color);

private:
    DebugDraw() = default;
    ~DebugDraw() = default;
    DebugDraw(const DebugDraw&) = delete;
    DebugDraw& operator=(DebugDraw const&) = delete;

    sf::RenderWindow* m_window;
};
