#ifndef ISOLIDSHAPE_H
#define ISOLIDSHAPE_H
#include "IShape.h"

class ISolidShape : public IShape
{
public:
    virtual uint32_t GetFillColor() const = 0;
};

#endif //ISOLIDSHAPE_H