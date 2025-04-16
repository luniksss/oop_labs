#ifndef CCANVAS_H
#define CCANVAS_H
#include <memory>
#include "../src/Interface/ICanvas.h"

class CCanvas : public ICanvas
{
public:
    // Простые указатели
    // Не нужно зависеть от RenderWindow а от RenderTarget
    CCanvas(std::shared_ptr<sf::RenderTarget> window) : m_window(std::move(window)) {};
    void DrawLine(CPoint from, CPoint to, uint32_t lineColor) override;
    void FillPolygon(std::vector<CPoint>, uint32_t lineColor, uint32_t fillColor) override;
    void DrawCircle(CPoint center, double radius, uint32_t lineColor) override;
    void FillCircle(CPoint center, double radius, uint32_t fillColor) override;
private:
    std::shared_ptr<sf::RenderTarget> m_window;
};

#endif //CCANVAS_H