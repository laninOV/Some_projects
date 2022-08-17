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
        return origin.pointX;
    }
    float rightEdge() const{
        return origin.pointX + size.pointX;
    }
    float topEdge() const {
        return origin.pointY;
    }
    float bottomEdge() const{
        return origin.pointY + size.pointY;
    }
};
#endif // LIMITFIELD_H
