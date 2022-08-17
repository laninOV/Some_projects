#include "geometryball.h"

GeometryBall::GeometryBall(float size)
    :_size(size)
{
    _thickness = size * 0.05f;          // толщина стенки
}

float GeometryBall::getSize() const
{
    return _size;
}

float GeometryBall::getThickness() const
{
    return _thickness;
}
