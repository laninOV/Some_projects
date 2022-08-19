#include "scene.h"
#include "point.h"
#include "limitfield.h"
#include <math.h>
#include <cstdlib>

    /*мы используем constexpr для определения констант
    мы используем анонимные пространства имён,
    чтобы при компоновке с другими файлами исходного кода не возникало конфликтов имён
    т.е. другой файл в большой программе тоже может содержать константу BALL_SIZE,
    но с другим значением*/

namespace{
    constexpr double GRAVITATIONAL_FORCE = 0;                  // ускорение свободного падения
    constexpr double    COEF_ENERGY_LOSS = 1 - 0.2;            // потеря энергии при отскоке 20%
    constexpr int                  SCALE = 480;                // коэффициент, для приведения к нормальным величинам
    int                     JUMP_COUNTER = 0;                  // количество отскоков
    constexpr int          BALLS_COUNTER = 2;                // количество шариков
    constexpr unsigned      WINDOW_WIDTH = 1920;
    constexpr unsigned     WINDOW_HEIGHT = 1000;

}

Scene::Scene(const limitfield &borders)
    : m_gravity(GRAVITATIONAL_FORCE*SCALE)
    , m_borders(borders)
{
    srand(time(NULL));

    for(int i = 0; i < BALLS_COUNTER; i++){
        Point position;
        position.pointX = 0 + rand() % WINDOW_WIDTH + 1;
        position.pointY = 0 + rand() % WINDOW_HEIGHT + 1;

        Point velocity;
        velocity.pointX = -50 + rand() % 300 + 1;
        velocity.pointY = -50 + rand() % 300 + 1;

        int size;
        size = 250 + rand() % 350 + 1;

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

void Scene::ProcessCollideOneBall(float deltaSeconds, Ball *one_ball)
{
    Point m_ballSpeed    = one_ball->getVelocity();
    Point m_ballPosition = one_ball->getPosition();
    int m_ballSize       = one_ball->getSize();



    m_ballSpeed.pointX += 1 * deltaSeconds;            // нахождение "новой скорости для оси oX"
    m_ballSpeed.pointY += m_gravity * deltaSeconds;    // нахождение "новой скорости для оси oY"

    m_ballPosition.pointX += m_ballSpeed.pointX * deltaSeconds;    // нахождение "новой координаты oX"
    m_ballPosition.pointY += m_ballSpeed.pointY * deltaSeconds;    // нахождение "новой координаты oY"


//    /* здесь будет реализовываться взаимодействие между шариками */
//    for (int i = 0; i < BALLS_COUNTER; ++i)
//    {
//        for(int j = i + 1; j < BALLS_COUNTER; ++j)
//        {
//            Ball* FirstBall = m_balls.at(i);
//            Ball* SecondBall = m_balls.at(j);

//            Point FirstBallPosition = FirstBall->getPosition();
//            Point SecondBallPosition = SecondBall->getPosition();

//            Point FirstBallSpeed = FirstBall->getVelocity();
//            Point SecondBallSpeed = SecondBall->getVelocity();

//            int FirstBallSize = FirstBall->getSize();
//            int SecondBallSize = SecondBall->getSize();

//            int FirstBallMass = FirstBallSize*4;
//            int SecondBallMass = SecondBallSize*4;

//             /* расстояние между центрами шаров */
//            int TotalDistanseBetweenEdgeBalls   = FirstBallSize/2 + SecondBallSize/2;

//             /* расстояние между центрами шаров */
//            int DistanceBetweenCentreBalls      = ((sqrt(pow(SecondBallPosition.pointX - FirstBallPosition.pointX, 2)
//                                                       + pow(SecondBallPosition.pointY - FirstBallPosition.pointY, 2))));

//            /* расстояние между границами шаров */
//            int DistanceBetweenEdgeBalls        = DistanceBetweenCentreBalls - TotalDistanseBetweenEdgeBalls;


//            if (DistanceBetweenEdgeBalls  < 0)
//            {
//                //qDebug()<<"КАСАНИЕ";
//            //m_ballSpeed.pointX = ;
//            //m_ballSpeed.pointY = ;

//            m_ballSpeed.pointX = (FirstBallSpeed.pointX * (FirstBallMass - SecondBallMass) / (FirstBallMass + SecondBallMass) + SecondBallSpeed.pointX * (2 * SecondBallMass) / (FirstBallMass + SecondBallMass));
//            m_ballSpeed.pointY = (FirstBallSpeed.pointY * (FirstBallMass - SecondBallMass) / (FirstBallMass + SecondBallMass) + SecondBallSpeed.pointY * (2 * SecondBallMass) / (FirstBallMass + SecondBallMass));

//            one_ball->setVelocity(m_ballSpeed);

//            m_ballSpeed.pointX = (SecondBallSpeed.pointX * (2 * FirstBallMass) / (FirstBallMass + SecondBallMass) + SecondBallSpeed.pointX * (SecondBallMass - FirstBallMass)) / (SecondBallMass + FirstBallMass);
//            m_ballSpeed.pointY = (SecondBallSpeed.pointY * (2 * FirstBallMass) / (FirstBallMass + SecondBallMass) + SecondBallSpeed.pointY * (SecondBallMass - FirstBallMass)) / (SecondBallMass + FirstBallMass);

//            second_ball->setVelocity(m_ballSpeed);
//            //std::exit(0);
//            }
//            else if (DistanceBetweenEdgeBalls  > 0)
//            {
//                //qDebug()<<"ВСЁ ОКЕЙ";
//            }
//        }
//    }

    /*мы должны проверить два случая
      - левая граница шарика левее левой границы поля
      - правая граница шарика правее правой границы поля */

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

    if (m_ballPosition.pointY - m_ballSize < m_borders.topEdge() - m_ballSize)
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

    //second_ball->setVelocity(m_ballSpeed);
}

void Scene::ProcessCollideBettwenBalls(Ball *one_ball, Ball *second_ball)
{
    Point m_ballSpeed    = one_ball->getVelocity();
    Point m_ballPosition = one_ball->getPosition();
    int m_ballSize       = one_ball->getSize();

    float deltaSeconds = 1;

    m_ballSpeed.pointX += 1 * deltaSeconds;            // нахождение "новой скорости для оси oX"
    m_ballSpeed.pointY += m_gravity * deltaSeconds;    // нахождение "новой скорости для оси oY"

    m_ballPosition.pointX += m_ballSpeed.pointX * deltaSeconds;    // нахождение "новой координаты oX"
    m_ballPosition.pointY += m_ballSpeed.pointY * deltaSeconds;    // нахождение "новой координаты oY"

    /* здесь будет реализовываться взаимодействие между шариками */
    for (int i = 0; i < BALLS_COUNTER; ++i)
    {
        for(int j = i + 1; j < BALLS_COUNTER; ++j)
        {
            Ball* FirstBall = m_balls.at(i);
            Ball* SecondBall = m_balls.at(j);

            Point FirstBallPosition = FirstBall->getPosition();
            Point SecondBallPosition = SecondBall->getPosition();

            Point FirstBallSpeed = FirstBall->getVelocity();
            Point SecondBallSpeed = SecondBall->getVelocity();

            int FirstBallSize = FirstBall->getSize();
            int SecondBallSize = SecondBall->getSize();

            int FirstBallMass = FirstBallSize*4;
            int SecondBallMass = SecondBallSize*4;

             /* расстояние между центрами шаров */
            int TotalDistanseBetweenEdgeBalls   = FirstBallSize/2 + SecondBallSize/2;

             /* расстояние между центрами шаров */
            int DistanceBetweenCentreBalls      = ((sqrt(pow(SecondBallPosition.pointX - FirstBallPosition.pointX, 2)
                                                       + pow(SecondBallPosition.pointY - FirstBallPosition.pointY, 2))));

            /* расстояние между границами шаров */
            int DistanceBetweenEdgeBalls        = DistanceBetweenCentreBalls - TotalDistanseBetweenEdgeBalls;


            if (DistanceBetweenEdgeBalls  < 0)
            {
                //qDebug()<<"КАСАНИЕ";
            //m_ballSpeed.pointX = ;
            //m_ballSpeed.pointY = ;

            m_ballSpeed.pointX = (FirstBallSpeed.pointX * (FirstBallMass - SecondBallMass) / (FirstBallMass + SecondBallMass) + SecondBallSpeed.pointX * (2 * SecondBallMass) / (FirstBallMass + SecondBallMass));
            m_ballSpeed.pointY = (FirstBallSpeed.pointY * (FirstBallMass - SecondBallMass) / (FirstBallMass + SecondBallMass) + SecondBallSpeed.pointY * (2 * SecondBallMass) / (FirstBallMass + SecondBallMass));

            one_ball->setVelocity(m_ballSpeed);


            m_ballSpeed.pointX = (SecondBallSpeed.pointX * (2 * FirstBallMass) / (FirstBallMass + SecondBallMass) + SecondBallSpeed.pointX * (SecondBallMass - FirstBallMass)) / (SecondBallMass + FirstBallMass);
            m_ballSpeed.pointY = (SecondBallSpeed.pointY * (2 * FirstBallMass) / (FirstBallMass + SecondBallMass) + SecondBallSpeed.pointY * (SecondBallMass - FirstBallMass)) / (SecondBallMass + FirstBallMass);

            second_ball->setVelocity(m_ballSpeed);
            //std::exit(0);
            }
            else if (DistanceBetweenEdgeBalls  > 0)
            {
                //qDebug()<<"ВСЁ ОКЕЙ";
            }
        }
    }
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
        ProcessCollideOneBall(deltaSeconds, ball);
        ProcessCollideBettwenBalls(ball, ball);
    }
}
