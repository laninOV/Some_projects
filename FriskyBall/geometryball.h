#ifndef GEOMETRYBALL_H
#define GEOMETRYBALL_H


class GeometryBall
{
    float _size = 100;
    float _thickness = 5;
public:
    GeometryBall(float size);

    float getSize() const;
    float getThickness() const;
};

#endif // GEOMETRYBALL_H
