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
    float size = (float)getSize();// - getThickness() * 0.5;
    painter->setBrush(QBrush(_color));
    painter->setPen(QPen(Qt::black, getThickness()));
    painter->drawEllipse(QRectF(position.getPointX() - size/2, position.getPointY() - size/2,size, size));

    //painter->drawEllipse(QRectF(position._pointX - size/2, position._pointY - size/2,size, size));
    // (pos+vel)*size / |vel| !длина вектора!
    //painter->drawLine(QPointF(position.pointX+size/2, position.pointY+size/2), QPointF((velocity.pointX *200),(velocity.pointY*200)));
}


