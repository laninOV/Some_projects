// Подключаем заголовок класса QGuiApplication из модуля QtGui.
#include "mainwindow.h"
#include "qwindow.h"
#include <QtGui>

// Объявляем функцию main, принимающую аргументы командной строки в параметрах argc и argv
int main(int argc, char *argv[])
{
    // Объявляем переменную app типа QGuiApplication.
    // Объявить её надо как можно раньше, так как при инициализации Q*Application
    //  неявно инициализируются различные подсистемы Qt
    QGuiApplication app(argc, argv);

    // Объявляем переменную window типа QWindow.
    // Эта переменная представляет окно операционной системы.
    MainWindow window;

    window.setAnimating(true);
    // Инициируем показ окна: показ случится позже, когда начнётся цикл событий
    window.show();

    // Запускаем цикл событий: метод exec выполняется вплоть до завершения
    //  работы приложения, и возвращает в main код возврата (ненулевой в случае ошибки).
    return app.exec();
}
