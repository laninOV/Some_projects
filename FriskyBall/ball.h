#ifndef BALL_H
#define BALL_H
#include <point.h>
#include <QColor>
#include <geometryball.h>
#include <behaviorball.h>

class QPainter;
class Ball : public GeometryBall, public BehaviorBall
{
    QColor _color = Qt::red;
public:
    Ball(float size, float coef_energy_loss, QColor);

    void draw(QPainter *painter);
};

#endif // BALL_H
