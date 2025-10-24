#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <memory>

class DebugDraw
{
public:
    static DebugDraw& GetInstance();
    void Init(sf::RenderWindow* _window);
    void DrawLine(sf::Vector2f start, sf::Vector2f end, sf::Color color);
    void DrawRectOutline(sf::Vector2f topLeft, int width, int height, sf::Color color);
    void DrawRectOutline(sf::IntRect rect, sf::Color color);
    void DrawRectangle(sf::Vector2f position, int width, int height, sf::Color color);
    void DrawRectangle(sf::IntRect rect, sf::Color color);

private:
    DebugDraw() = default;
    ~DebugDraw() = default;
    DebugDraw(const DebugDraw& rhv) = delete;
    DebugDraw& operator=(DebugDraw const&) = delete;

    sf::RenderWindow* m_window;
};

