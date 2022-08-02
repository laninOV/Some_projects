#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <scene.h>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWindow
{
    Q_OBJECT

public:
    // Конструктор класса: принимает один (опциональный) параметр типа QWindow,
    // в этом параметре можно передать родительское окно (например, для модального диалога)
    explicit MainWindow(QWindow *parent = nullptr);
    bool isAnimating() const;
    void setAnimating(bool isAnimating);
    // Добавим булево поле для хранения данных этого свойства.
    //bool m_isAnimating = false;

            //?????свойство” и “поле” — это разные вещи.?????

protected: // Начало секции полей и методов, доступных только в наследниках этого класса

    // Ниже перегружены полиморфные методы родительского класса QWindow
    // Библиотека Qt рассылает различные события по этим методам
    //  - метод event вызывается перед обработкой любых событий, включая resizeEvent и exposeEvent
    //  - метод resizeEvent вызывается при изменении размера окна
    //  - метод exposeEvent вызывается при показе окна
    bool event(QEvent *event) override;
    void resizeEvent(QResizeEvent *resizeEvent) override;
    void exposeEvent(QExposeEvent *event) override;


private: // Начало секции полей и методов, доступных только в наследниках этого класса
    Ui::MainWindow *ui;

    void renderLater();
    void renderNow();
    void updateScene(); // обновляет состояние сцены
    void renderScene(); // перерисовывает содержимое сцены
    //void render(QPainter *painter);

    // Класс QBackingStore предоставляет окну буфер рисования кадра.
    // Грубо говоря, этот буфер содержит будущие пиксели окна и позволяет
    // рисовать векторную графику (фигуры, изображения, текст), заполняя
    // этот буфер пикселей.
    QBackingStore *m_backingStore = nullptr;
    std::unique_ptr<Scene> m_scene; // объект сцены
    QElapsedTimer m_updateTimer;    // таймер обновления сцены
    bool m_isAnimating = false;

};
#endif // MAINWINDOW_H
