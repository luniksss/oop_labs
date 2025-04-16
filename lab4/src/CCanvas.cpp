#include "../include/CCanvas.h"

sf::Color CCanvas::Uint32ToSFMLColor(uint32_t color)
{
    return {
        static_cast<sf::Uint8>((color >> 16) & 0xFF),  // R
        static_cast<sf::Uint8>((color >> 8) & 0xFF),   // G
        static_cast<sf::Uint8>(color & 0xFF),          // B
        255                                            // A
    };
}

void CCanvas::DrawLine(CPoint from, CPoint to, uint32_t outlineColor)
{
    sf::Vertex line[] = {
        {sf::Vector2f(static_cast<float>(from.m_x), static_cast<float>(from.m_y)), Uint32ToSFMLColor(outlineColor)},
        {sf::Vector2f(static_cast<float>(to.m_x), static_cast<float>(to.m_y)), Uint32ToSFMLColor(outlineColor)}
    };
    m_window.draw(line, 2, sf::Lines);
}

void CCanvas::DrawCircle(CPoint center, double radius, uint32_t outlineColor, uint32_t fillColor)
{
    sf::CircleShape circle(static_cast<float>(radius));
    circle.setPosition(static_cast<float>(center.m_x), static_cast<float>(center.m_y));
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineColor(sf::Color(outlineColor));
    circle.setOutlineThickness(2);

    m_window.draw(circle);
}
