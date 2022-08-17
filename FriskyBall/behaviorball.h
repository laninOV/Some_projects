#ifndef BEHAVIORBALL_H
#define BEHAVIORBALL_H
#include "point.h"


class BehaviorBall
{
    Point _position;
    Point _velocity;
    float _coef_energy_loss = 1;
public:
    BehaviorBall(float coef_energy_loss);

    void setPosition(Point position);
    void setVelocity(Point velocity);
    Point getPosition() const;
    Point getVelocity() const;
};

#endif // BEHAVIORBALL_H
