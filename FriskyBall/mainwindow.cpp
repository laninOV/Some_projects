    /* Подключаем заголовки используемых классов. */
#include <mainwindow.h>

constexpr unsigned WINDOW_WIDTH = 1920;
constexpr unsigned WINDOW_HEIGHT = 1000;

    /*В конструкторе создадим в динамической памяти новый объект QBackingStore.
    В современном C++ не принято использовать "new", но пока вы работаете с Qt,
    "new" - это норма, т.к. Qt использует особый механизм управления памятью
    parent-child.
    Именно поэтому мы передали "this" в конструктор QBackingStore.
    Объект класса MainWindow становится родителем объекта класса QBackingStore.
    Когда будет вызван деструктор MainWindow, Qt удалит и все дочерние объекты.*/

MainWindow::MainWindow(QWindow *parent)
    : QWindow(parent)
    , m_backingStore(new QBackingStore(this))
    , m_scene(std::make_unique<Scene>(limitfield{0, 0, float(WINDOW_WIDTH), float(WINDOW_HEIGHT)}))
{
    /* Устанавливаем минимальные размеры окна. */
    setMinimumSize(QSize(WINDOW_WIDTH, WINDOW_HEIGHT));

    /* В конструкторе мы будем создавать новый объект сцены,
     * связывая его отношением parent-child с классом окна путём передачи указателя this:*/
    m_updateTimer.start();
}

    /*выполнение метода render путём вызова метода renderLater: */

bool MainWindow::isAnimating() const
{
    return m_isAnimating;
}

void MainWindow::setAnimating(bool isAnimating)
{
    m_isAnimating = isAnimating;
    if (isAnimating){
        renderLater();
    }
}
    /*мы должны обработать только событие UpdateRequest,
     которое уведомляет о запросе на изменение окна
     изменение размера должно приводить к перерисовке окна*/

bool MainWindow::event(QEvent *event)
{
    if(event->type() == QEvent::UpdateRequest){
        renderNow();
        return true;
    }
    return QWindow::event(event);
}

    /*Опишем метод resizeEvent: этот метод класса QWindow
    библиотека Qt вызывает при изменении размера окна.*/

void MainWindow::resizeEvent(QResizeEvent *resizeEvent)
{
    m_backingStore->resize(resizeEvent->size());
}

    /*Опишем метод exposeEvent: этот метод класса QWindow
    библиотека Qt вызывает при фактическом показе окна.*/

void MainWindow::exposeEvent(QExposeEvent *)
{
    if(isExposed()){
        renderNow();
    }
}

     /*Метод “renderLater” будет добавлять в очередь событий Qt
     событие обновления экрана (UpdateRequest),
     тем самым форсируя перерисовку кадра в ближайшем будущем.*/

void MainWindow::renderLater()
{
    requestUpdate();
}

void MainWindow::renderNow()
{
    if (!isExposed())
    {
        return;
    }

    updateScene();
    renderScene();

    if (m_isAnimating){
        renderLater();
    }

    /* Самый важный трюк мы разместим в методе “renderNow”.
     * Если окно зациклено на анимацию, то после рисования кадра мы должны нарисовать новый кадр.
     * Делать это немедленно нельзя: мы уйдём в бесконечную рекурсию, что приведёт к переполнению стека программы.
     * Поэтому мы будем лишь планировать перерисовку путём добавления события в очередь событий.
     * Фактически перерисовка состоится тогда, когда на то будет воля Qt.
     * Тем не менее, мы рассчитываем на частоту порядка 60Гц (благодаря вертикальной синхронизации и её обработке в Qt).
     * Добавим в конец метода планирование перерисовки:*/

    if (m_isAnimating){
        renderLater();
    }
}

    /*Метод updateScene будет содержать получение времени у таймера, перезапуск таймера и обновление сцены.
     * В случае, если кадры рисуются слишком быстро и время, прошедшее с предыдущего кадра,
     * оказалось меньше 1 миллисекунды, обновление сцены будет пропущено.*/

void MainWindow::updateScene()
{
    const float elapsedSeconds = float(m_updateTimer.elapsed()) / 1000.f;

    /* перезапуск обновления, если таймер не успел засечь прошедшее время */

    if (elapsedSeconds > 0){
        m_updateTimer.restart();
        m_scene->update(elapsedSeconds);
    }
}

    /*Метод renderScene будет содержать подготовку объекта QPainter,
     * заполнение буфера кадра белым цветом и затем вызов метода redraw() у класса сцены.*/

void MainWindow::renderScene()
{
    QRect rect(0, 0, width(), height());
    m_backingStore->beginPaint(rect);

    QPaintDevice *device = m_backingStore->paintDevice();
    QPainter painter(device);

    painter.fillRect(0, 0, width(), height(), Qt::white);
    m_scene->redraw(painter);
    painter.end();

    m_backingStore->endPaint();
    m_backingStore->flush(rect);
}
