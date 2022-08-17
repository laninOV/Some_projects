#include "ball.h"
#include "qpainter.h"
#include <QDebug>

Ball::Ball(float size, float coef_energy_loss, QColor color):GeometryBall(size)
    ,BehaviorBall(coef_energy_loss)
    ,_color(color)
{
}

void Ball::draw(QPainter *painter)
{
    Point position = getPosition();
    float size = (float)getSize() - getThickness() * 0.5;

    painter->setBrush(QBrush(_color));
    painter->setPen(QPen(Qt::black, getThickness()));
    painter->drawEllipse(QRectF(position.pointX, position.pointY,size, size));
}


