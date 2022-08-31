#ifndef POINT_H
#define POINT_H
#include <iostream>
#include <cmath>

class Point{
    // Инициализируем переменные
    float _pointX = 0;
    float _pointY = 0;

public:
    // Присваиваем реализацию по умолчанию
    Point() = default;

    /*  Создаём конструктор Point с списком инициализации членов.
     *  Используется как для инициализации членов класса,
     *  так и для вызова конструктора базового/базовых классов*/
    Point(float x, float y): _pointX(x), _pointY(y)
    {
    }

    Point operator=(const Point& other){
     _pointX = other._pointX;
     _pointY = other._pointY;
     return *this;
    }

    Point operator+(const Point& other) const{
        return {_pointX + other._pointX, _pointY + other._pointY};
    }

    Point& operator+=(const Point& other){
        _pointX += other._pointX;
        _pointY += other._pointY;
        return *this;
    }

    Point& operator+=(float offset){
        _pointX += offset;
        _pointY += offset;
        return *this;
    }

    Point operator*(float scale)
    {
        return { scale * _pointX, scale * _pointY };
    }

    Point& operator*=(float scale){
        _pointX *= scale;
        _pointY *= scale;
        return *this;
    }

    //4 функции

    inline void setPointX(const float pointX){
        _pointX = pointX;
    }

    inline float getPointX() const{
        return _pointX;
    }

    inline void setPointY(const float pointY){
        _pointY = pointY;
    }

    inline float getPointY() const{
        return _pointY;
    }

};



#endif // POINT_H
