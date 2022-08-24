#ifndef BEHAVIORBALL_H
#define BEHAVIORBALL_H
#include "point.h"


class BehaviorBall
{
    Point _position;
    Point _velocity;
    float _coef_energy_loss = 1;
    int _colide_count = 0;
    //счётчик ударов между шариками counterColide, bool
public:
    BehaviorBall(float coef_energy_loss);

    void setPosition(Point position);
    void setVelocity(Point velocity);
    Point getPosition() const;
    Point getVelocity() const;

    bool colideCounter(int max_colide_count);
};

#endif // BEHAVIORBALL_H
