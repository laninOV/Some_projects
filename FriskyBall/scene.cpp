#include "scene.h"
#include "limitfield.h"

    /*мы используем constexpr для определения констант
    мы используем анонимные пространства имён,
    чтобы при компоновке с другими файлами исходного кода не возникало конфликтов имён
    т.е. другой файл в большой программе тоже может содержать константу BALL_SIZE,
    но с другим значением*/

namespace{
                    /*  100pix = 0.02(m/s) or 0.072(km/h)    */
    constexpr float        BALL_SPEED_X = 0.01;                 // скорость пикселей в секунду по оси оX
    constexpr float        BALL_SPEED_Y = 0;                    // 0.01(m/s) or (1cm/s) скорость пикселей в секунду по оси оY
                    /*  100pix = 0.02(m) or 20(cm)           */
    constexpr int             BALL_SIZE = 100;                  // размер шарика
                    /*  9.81m/s^2 = 981 см/s^2               */
    constexpr double GRAVITATIONAL_FORCE = 1.62;                // ускорение свободного падения
    constexpr double         ENERGY_LOSS = 1 - 0.2;             // потеря энергии при отскоке 30%
    constexpr int scale = 4800;
}

Scene::Scene(const limitfield &borders)
    : m_ballSpeed(BALL_SPEED_X*scale, BALL_SPEED_Y*scale)
    , m_gravity(GRAVITATIONAL_FORCE*scale)
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


void Scene::update(float deltaSeconds) //период времени
{
    m_ballSpeed.setX(m_ballSpeed.x() + 1 * deltaSeconds);             // нахождение "новой скорости для оси oX"
    m_ballSpeed.setY(m_ballSpeed.y() + m_gravity * deltaSeconds);     // нахождение "новой скорости для оси oY"


    m_ballPosition.setX(m_ballSpeed.x() * deltaSeconds + m_ballPosition.x());   // нахождение "новой координаты oX"
    m_ballPosition.setY(m_ballSpeed.y() * deltaSeconds + m_ballPosition.y());   // нахождение "новой координаты oY"

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
        m_ballSpeed.setX(-m_ballSpeed.x() * ENERGY_LOSS);
    }

    /*Аналогичные проверки потребуются для верхней и нижней границ.*/

    if (m_ballPosition.y() < m_borders.topEdge())
    {
        m_ballPosition.setY(m_borders.topEdge());
        m_ballSpeed.setY(-m_ballSpeed.y());
    }
    else if (m_ballPosition.y() > m_borders.bottomEdge() - m_ballSize.y())
    {
        m_ballPosition.setY(m_borders.bottomEdge()  - m_ballSize.y());
        m_ballSpeed.setY(-m_ballSpeed.y() * ENERGY_LOSS);

    }

}




