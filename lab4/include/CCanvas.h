#pragma once
#include "../src/Interface/ICanvas.h"
#include <SFML/Graphics.hpp>
#include <memory>

class CCanvas : public ICanvas
{
public:
    explicit CCanvas(sf::RenderWindow& window) : m_window(window) {}

    void DrawLine(CPoint from, CPoint to, uint32_t outlineColor) override;
    void DrawCircle(CPoint center, double radius, uint32_t outlineColor, uint32_t fillColor) override;

private:
    sf::RenderWindow& m_window;
    static sf::Color Uint32ToSFMLColor(uint32_t color);
};