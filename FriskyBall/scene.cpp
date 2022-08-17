#include "scene.h"
#include "point.h"
#include "limitfield.h"

    /*мы используем constexpr для определения констант
    мы используем анонимные пространства имён,
    чтобы при компоновке с другими файлами исходного кода не возникало конфликтов имён
    т.е. другой файл в большой программе тоже может содержать константу BALL_SIZE,
    но с другим значением*/

namespace{
//    /*  100pix = 0.02(m/s) or 0.072(km/h)       */
//    constexpr float         BALL_SPEED_X = 0.8;                // скорость пикселей в секунду по оси оX
//    constexpr float         BALL_SPEED_Y = 0.02;               // 0.01(m/s) or (1cm/s) скорость пикселей в секунду по оси оY
//    /*  100pix = 0.02(m) or 20(cm)              */
//    constexpr int              BALL_SIZE = 100;                // размер шарика
//    /*  9.81m/s^2 = 981 см/s^2                  */
    constexpr double GRAVITATIONAL_FORCE = 0;               // ускорение свободного падения
    constexpr double    COEF_ENERGY_LOSS = 1 - 0.2;            // потеря энергии при отскоке 20%
    constexpr int                  SCALE = 480;                // коэффициент, для приведения к нормальным величинам
    int                     JUMP_COUNTER = 0;
    constexpr int          BALLS_COUNTER = 100;
    constexpr unsigned      WINDOW_WIDTH = 1920;
    constexpr unsigned     WINDOW_HEIGHT = 1000;

}

Scene::Scene(const limitfield &borders)
    : m_gravity(GRAVITATIONAL_FORCE*SCALE)
    , m_borders(borders)
{
    srand ( time(NULL) );

    for(int i = 0; i < BALLS_COUNTER; i++){
        Point position;
        position.pointX = 0 + rand() % WINDOW_WIDTH + 1;
        position.pointY = 0 + rand() % WINDOW_HEIGHT + 1;

        Point velocity;
        velocity.pointX = -50 + rand() % 100 + 1;
        velocity.pointY = -50 + rand() % 100 + 1;

        float size;
        size = 0 + rand() % 50 + 1;

        float loss;
        loss = (rand() % 100)/(100*1.0); // диапазон чисел от 0 до 1

        QColor color;
        color.setBlue (rand() % 255 + 1);
        color.setRed  (rand() % 255 + 1);
        color.setGreen(rand() % 255 + 1);

        Ball *ball = new Ball(size, loss, color);
        ball->setPosition(position);
        ball->setVelocity(velocity);

        m_balls << ball;
    };
}
//setPos или добавить в конструктор (видимо сюда)
void Scene::updateOneBall(float deltaSeconds, Ball *one_ball)
{
    Point m_ballSpeed    = one_ball->getVelocity();
    Point m_ballPosition = one_ball->getPosition();
    float m_ballSize     = one_ball->getSize();


    m_ballSpeed.pointX += 1 * deltaSeconds;            // нахождение "новой скорости для оси oX"
    m_ballSpeed.pointY += m_gravity * deltaSeconds;    // нахождение "новой скорости для оси oY"

    m_ballPosition.pointX += m_ballSpeed.pointX * deltaSeconds;    // нахождение "новой координаты oX"
    m_ballPosition.pointY += m_ballSpeed.pointY * deltaSeconds;    // нахождение "новой координаты oY"

    /*мы должны проверить два случая
      - левая граница шарика левее левой границы поля
      - правая граница шарика правее правой границы поля*/

    if (m_ballPosition.pointX < m_borders.leftEdge())
    {
        m_ballPosition.pointX = m_borders.leftEdge();
        m_ballSpeed.pointX = -m_ballSpeed.pointX * COEF_ENERGY_LOSS;
    }
    else if (m_ballPosition.pointX > m_borders.rightEdge() - m_ballSize)
    {
        m_ballPosition.pointX = m_borders.rightEdge() - m_ballSize;
        m_ballSpeed.pointX = -m_ballSpeed.pointX * COEF_ENERGY_LOSS;
    }

    /*Аналогичные проверки потребуются для верхней и нижней границ.*/

    else if (m_ballPosition.pointY - m_ballSize < m_borders.topEdge() - m_ballSize)
    {
        m_ballPosition.pointY = m_borders.topEdge();
        m_ballSpeed.pointY = -m_ballSpeed.pointY;
    }
    else if (m_ballPosition.pointY > m_borders.bottomEdge() - m_ballSize)
    {
        m_ballPosition.pointY = m_borders.bottomEdge()  - m_ballSize;
        m_ballSpeed.pointY = -m_ballSpeed.pointY * COEF_ENERGY_LOSS;
        if (m_ballPosition.pointY == m_borders.bottomEdge() - m_ballSize){
            JUMP_COUNTER = JUMP_COUNTER + 1;
        }
        if (JUMP_COUNTER > 70){
            m_ballSpeed.pointX = m_ballSpeed.pointX * (0.991);    // замедление качения шарика
        }
    }

    one_ball->setPosition(m_ballPosition);
    one_ball->setVelocity(m_ballSpeed);
}

void Scene::redraw(QPainter &painter)
{
    painter.setRenderHint(QPainter::Antialiasing);

    for(auto ball : m_balls){
        ball->draw(&painter);
    }
}


void Scene::update(float deltaSeconds) //период времени
{
    for(auto ball : m_balls){
        updateOneBall(deltaSeconds, ball);
    }
}
