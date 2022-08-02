#include "scene.h"
#include "limitfield.h"

    /*мы используем constexpr для определения констант
    мы используем анонимные пространства имён,
    чтобы при компоновке с другими файлами исходного кода не возникало конфликтов имён
    т.е. другой файл в большой программе тоже может содержать константу BALL_SIZE,
    но с другим значением*/

namespace{
    // скорость пикселей в секунду
    constexpr float BALL_SPEED_X = 0;
    constexpr float BALL_SPEED_Y = 0;
    // размер шарика
    constexpr float BALL_SIZE    = 150;
    // ускорение свободного падения
    constexpr double GRAVITATIONAL_FORCE = 10009.81;
}


Scene::Scene(const limitfield &borders)
    : m_ballSpeed(BALL_SPEED_X, BALL_SPEED_Y)
    , m_gravity(GRAVITATIONAL_FORCE)
    , m_ballSize(BALL_SIZE, BALL_SIZE)
    , m_borders(borders)
{
}


void Scene::redraw(QPainter &painter)
{
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(QColor(255, 4, 34)));
    painter.drawEllipse(QRectF(m_ballPosition.x(), m_ballPosition.y(), BALL_SIZE, BALL_SIZE));
}


void Scene::update(float deltaSeconds )
{
    m_ballPosition.setX(m_ballSpeed.x() * deltaSeconds + m_ballPosition.x());
    m_ballPosition.setY(m_ballSpeed.y() * deltaSeconds + m_ballPosition.y());

    //m_ballPosition.setY(m_ballPosition.y() + m_ballSpeed.y() * deltaSeconds + (m_gravity*(deltaSeconds*deltaSeconds)) / 2);
    //m_ballPosition.setX(m_ballPosition.x() + m_ballSpeed.x() * deltaSeconds + (m_gravity*(deltaSeconds*deltaSeconds)) / 2);


    /*мы должны проверить два случая
      - левая граница шарика левее левой границы поля
      - правая граница шарика правее правой границы поля*/

    if (m_ballPosition.x() < m_borders.leftEdge())
    {
        m_ballPosition.setX(m_borders.leftEdge());
        m_ballSpeed.setX(-m_ballSpeed.x());
    }
    else if (m_ballPosition.x() > m_borders.rightEdge() - m_ballSize.x())
    {
        m_ballPosition.setX(m_borders.rightEdge() - m_ballSize.x());
        m_ballSpeed.setX(-m_ballSpeed.x());
    }

    /*Аналогичные проверки потребуются для верхней и нижней границ.*/

    if (m_ballPosition.y() < m_borders.topEdge())
    {
        m_ballPosition.setY(m_borders.topEdge());
        m_ballSpeed.setY(-m_ballSpeed.y());
    }
    else if (m_ballPosition.y() > m_borders.bottomEdge() - m_ballSize.y())
    {
        m_ballPosition.setY(m_borders.bottomEdge() - m_ballSize.y());
        m_ballSpeed.setY(-m_ballSpeed.y());
    }
}




