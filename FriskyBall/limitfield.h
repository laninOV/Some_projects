#ifndef LIMITFIELD_H
#define LIMITFIELD_H
#include "point.h"

    // Структура limitfield представляет прямоугольник, стороны которого параллельны осям координат.
struct limitfield{
    limitfield() = default;

    limitfield(float x, float y, float width, float height)
        :origin(x, y), size(width, height)
    {
    }

    // позиция левого верхнего угла
    Point origin;
    // размеры окна (ширина, высота)
    Point size;

    float leftEdge() const {
        return origin.getPointX();
    }
    float rightEdge() const{
        return origin.getPointX() + size.getPointX();
    }
    float topEdge() const {
        return origin.getPointY();
    }
    float bottomEdge() const{
        return origin.getPointY() + size.getPointY();
    }
};
#endif // LIMITFIELD_H
