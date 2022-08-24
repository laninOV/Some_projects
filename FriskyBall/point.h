#ifndef POINT_H
#define POINT_H
#include <iostream>
#include <cmath>

struct Point{
    // Инициализируем переменные
    float pointX = 0;
    float pointY = 0;

public:
    // Присваиваем реализацию по умолчанию
    Point() = default;

    /*  Создаём конструктор Point с списком инициализации членов.
     *  Используется как для инициализации членов класса,
     *  так и для вызова конструктора базового/базовых классов*/
    Point(float x, float y): pointX(x), pointY(y)
    {
    }

    Point operator+(const Point& other) const{
        return {pointX + other.pointX, pointY + other.pointY};
    }

    Point& operator+=(const Point& other){
        pointX += other.pointX;
        pointY += other.pointY;
        return *this;
    }
};
#endif // POINT_H
