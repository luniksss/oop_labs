#ifndef ICANVASDRAWABLE_H
#define ICANVASDRAWABLE_H
#include <memory>
#include "ICanvas.h"

class ICanvasDrawable
{
    public:
        virtual ~ICanvasDrawable() = default;
        virtual void Draw(std::shared_ptr<ICanvas> canvas) = 0;
};

#endif // ICANVASDRAWABLE_H