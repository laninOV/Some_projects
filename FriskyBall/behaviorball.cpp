#include "behaviorball.h"

BehaviorBall::BehaviorBall(float coef_energy_loss)
    :_coef_energy_loss(coef_energy_loss)
{

}

void BehaviorBall::setPosition(Point position)
{
    _position = position;
}

void BehaviorBall::setVelocity(Point velocity)
{
    _velocity = velocity;
}

Point BehaviorBall::getPosition() const
{
    return _position;
}

Point BehaviorBall::getVelocity() const
{
    return _velocity;
}
