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

bool BehaviorBall::colideCounter(int max_colide_count)
{
    _colide_count += 1;
    if (_colide_count == max_colide_count){
        return true;
    }
    else{
        return false;
    }
}
