#ifndef SCENE_H
#define SCENE_H
#include "ball.h"
#include "limitfield.h"
#include <QtGui>


class Scene
{
public:
    Scene();
    void update(float deltaSeconds);
    void redraw(QPainter& painter);
    explicit Scene(const limitfield& borders); //??
    void reBuild();


private:
    void processCollideBallsWithEdge(float deltaSecond);
    void processCollideBettwenBalls (float deltaSecond);
    void processCollideOneBall (float deltaSecond, Ball *one_ball);

    const double        m_gravity;
    const limitfield    m_borders;
    QList <Ball*>       m_balls;
};

#endif // SCENE_H
