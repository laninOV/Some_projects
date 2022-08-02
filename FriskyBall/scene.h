#ifndef SCENE_H
#define SCENE_H
#include "limitfield.h"
#include <QtGui>


class Scene
{
public:
    Scene();
    void update(float deltaSeconds);
    void redraw(QPainter& painter);

    explicit Scene(const limitfield& borders); //??

private:

    /*добавим поля для хранения скорости шарика (которая теперь будет изменяться динамически),
     * размера шарика (неизменного), границ сцены (неизменных).*/

    //float m_ballPositionX = 0;
    //float m_ballPositionY = 0;

    QVector2D           m_ballPosition;
    QVector2D           m_ballSpeed;
    const double        m_gravity;
    const QVector2D     m_ballSize;
    const limitfield    m_borders;
};

#endif // SCENE_H
