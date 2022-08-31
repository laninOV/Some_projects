#include "scene.h"
#include "point.h"
#include "limitfield.h"
#include <math.h>
#include <cstdlib>
#include <iostream>
#include <algorithm>


/*мы используем constexpr для определения констант
    мы используем анонимные пространства имён,
    чтобы при компоновке с другими файлами исходного кода не возникало конфликтов имён
    т.е. другой файл в большой программе тоже может содержать константу BALL_SIZE,
    но с другим значением*/

namespace{
constexpr double GRAVITATIONAL_FORCE = 10;                  // ускорение свободного падения
constexpr double    COEF_ENERGY_LOSS = 1 - 0.2;            // потеря энергии при отскоке 20%
constexpr int                  SCALE = 480;                // коэффициент, для приведения к нормальным величинам
int                     JUMP_COUNTER = 0;                  // количество отскоков
constexpr int          BALLS_COUNTER = 10;                 // количество шариков
constexpr unsigned      WINDOW_WIDTH = 1920;
constexpr unsigned     WINDOW_HEIGHT = 1000;
}

Scene::Scene(const limitfield &borders)
    : m_gravity(GRAVITATIONAL_FORCE*SCALE)
    , m_borders(borders)
{
    reBuild();
}

void Scene::reBuild()
{
    for(auto ball : m_balls){
        delete ball;
    }

    m_balls.clear();

    srand(time(NULL));

    for(int i = 0; i < BALLS_COUNTER; i++){
        Point position((0 + rand() % WINDOW_HEIGHT + 1), (0 + rand() % WINDOW_WIDTH + 1));

        Point velocity((-50 + rand() % 2000 + 1), (-50 + rand() % 2000 + 1));

        int size;
        size = 50 + rand() % 200 + 1;

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

void Scene::processCollideBallsWithEdge(float deltaSeconds)
{
    for(auto ball : m_balls){
        processCollideOneBall(deltaSeconds, ball);
    }
}

void Scene::processCollideOneBall(float deltaSeconds, Ball *one_ball)
{
    Point m_ballSpeed    = one_ball->getVelocity();
    Point m_ballPosition = one_ball->getPosition();
    int m_ballSize       = one_ball->getSize();

    // нахождение "ускорения"
    Point deltaSpeed(0 , m_gravity);

    //x = x0 +v0*t+(a*t^2)/2 нахождение новой координаты
    m_ballPosition += m_ballSpeed * deltaSeconds + (deltaSpeed * pow(deltaSeconds , 2)) * 0.5;

    //v = v0 + a*t; нахождение новой скорости
    m_ballSpeed += deltaSpeed * deltaSeconds;

    //

    /*мы должны проверить два случая
      - левая граница шарика левее левой границы поля
      - правая граница шарика правее правой границы поля */

    if ((m_ballPosition.getPointX()) < m_borders.leftEdge() + m_ballSize*0.5)
    {
        m_ballPosition.setPointX(m_borders.leftEdge() + m_ballSize*0.5);
        m_ballSpeed.setPointX(-m_ballSpeed.getPointX() * COEF_ENERGY_LOSS);
    }

    else if (m_ballPosition.getPointX() > m_borders.rightEdge() - m_ballSize*0.5)
    {
        m_ballPosition.setPointX(m_borders.rightEdge() - m_ballSize*0.5);
        m_ballSpeed.setPointX(-m_ballSpeed.getPointX() * COEF_ENERGY_LOSS);
    }

    /*Аналогичные проверки потребуются для верхней и нижней границ.*/

    if (m_ballPosition.getPointY() - m_ballSize < m_borders.topEdge() - m_ballSize*0.5)
    {
        m_ballPosition.setPointY(m_borders.topEdge() + m_ballSize*0.5);
        m_ballSpeed.setPointY(-m_ballSpeed.getPointY());
    }
    else if (m_ballPosition.getPointY() > m_borders.bottomEdge() - m_ballSize*0.5)
    {
        m_ballPosition.setPointY(m_borders.bottomEdge()  - m_ballSize*0.5);
        m_ballSpeed.setPointY(-m_ballSpeed.getPointY() * COEF_ENERGY_LOSS);
        if (m_ballPosition.getPointY() == m_borders.bottomEdge() - m_ballSize*0.5){
            JUMP_COUNTER = JUMP_COUNTER + 1;
        }
        if (JUMP_COUNTER > 70){
            m_ballSpeed.setPointX(m_ballSpeed.getPointX() * (0.991));    // замедление качения шарика
        }
    }

    one_ball->setPosition(m_ballPosition);
    one_ball->setVelocity(m_ballSpeed);
}

void Scene::processCollideBettwenBalls(float deltaSecond)
{
    QSet<Ball*> forDelete; //список для удаления шариков
    /* здесь будет реализовываться взаимодействие между шариками */

    for (int i = 0; i < m_balls.size(); ++i) // количество шариков в массиве m_balls вместо BALLS_COUNTER
    {
        for(int j = i + 1; j < m_balls.size(); ++j)
        {
            Ball* FirstBall = m_balls.at(i);
            Ball* SecondBall = m_balls.at(j);

            if (forDelete.contains(FirstBall) || forDelete.contains(SecondBall)){
                continue;
            }

            Point FirstBallPosition = FirstBall->getPosition();
            Point SecondBallPosition = SecondBall->getPosition();

            Point FirstBallSpeed = FirstBall->getVelocity();
            Point SecondBallSpeed = SecondBall->getVelocity();

            double FirstBallSize = FirstBall->getSize();
            double SecondBallSize = SecondBall->getSize();

            double FirstBallMass = FirstBallSize*4;
            double SecondBallMass = SecondBallSize*4;

            /* расстояние между центрами шаров */
            double TotalDistanseBetweenEdgeBalls   = FirstBallSize/2 + SecondBallSize/2;

            /* расстояние между центрами шаров */
            double DistanceBetweenCentreBalls      = sqrt(pow(SecondBallPosition.getPointX() - FirstBallPosition.getPointX(), 2)
                                                          + pow(SecondBallPosition.getPointY() - FirstBallPosition.getPointY(), 2));

            /* расстояние между границами шаров */
            double DistanceBetweenEdgeBalls        = DistanceBetweenCentreBalls - TotalDistanseBetweenEdgeBalls;

            if (DistanceBetweenEdgeBalls  < 0 && abs(DistanceBetweenEdgeBalls) > 10)
            {
                bool first_for_delete = FirstBall->colideCounter(50);
                bool second_for_delete = SecondBall->colideCounter(50);

                if (first_for_delete == true){
                    forDelete << FirstBall;
                }
                if (second_for_delete == true){
                    forDelete << SecondBall;
                }
                if (first_for_delete || second_for_delete){
                    continue;
                }

                Point m_ballSpeedFirst = ((FirstBallSpeed * ((FirstBallMass - SecondBallMass) / (FirstBallMass + SecondBallMass))
                                         + SecondBallSpeed * (2 * SecondBallMass / (FirstBallMass + SecondBallMass))));

                Point m_ballSpeedSecond = ((FirstBallSpeed * ((2 * FirstBallMass) / (FirstBallMass + SecondBallMass))
                                         + SecondBallSpeed * ((SecondBallMass - FirstBallMass) / (SecondBallMass + FirstBallMass))));

                //FirstBall->setVelocity(m_ballSpeed);
                //SecondBall->setVelocity(m_ballSpeed);
                FirstBall->setVelocity(m_ballSpeedFirst);
                SecondBall->setVelocity(m_ballSpeedSecond);


            }
        }
    }
    //удаляем шарики тут
    for (auto del : forDelete){
        delete del;
    }

    QList<Ball*> tmp;       //список для оставшихся шариков
    for(auto ball : m_balls){
        if(!forDelete.contains(ball)){
            tmp.append(ball);
        }
    }
    m_balls = tmp;
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
    processCollideBallsWithEdge(deltaSeconds);
    processCollideBettwenBalls (deltaSeconds);
}
