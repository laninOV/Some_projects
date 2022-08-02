#ifndef LIMITFIELD_H
#define LIMITFIELD_H
#include "QVector2D"

// Структура limitfield представляет прямоугольник, стороны которого параллельны осям координат.
struct limitfield{
    limitfield() = default;

    limitfield(float x, float y, float width, float height)
        :origin(x, y), size(width, height)
    {
    }

    // позиция левого верхнего угла
    QVector2D origin;
    // размеры окна (ширина, высота)
    QVector2D size;

    float leftEdge() const {
        return origin.x();
    }
    float rightEdge() const{
        return origin.x() + size.x();
    }
    float topEdge() const {
        return origin.y();
    }
    float bottomEdge() const{
        return origin.y() + size.y();
    }

};



#endif // LIMITFIELD_H
