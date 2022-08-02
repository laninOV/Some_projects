#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTime>
#include <QFont>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QString  ip, QString  port, bool server, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTcpServer *_server;                // указатель на объект Server класса QTcpServer
    QTcpSocket *_socket;                // указатель на объект Socket класса QTcpSocket
    QByteArray Data;                    // объект Data, который будет путешестваовать между объектом и сервером
    void SendToClient(QString str);     // функция отправки сообщений клиенту
    void printMessage(QString message); // вывод уведомлений


public slots:
    void newConnection();
    void slotReadyRead();
    void socketConnected();
    void socketDisconnected();
private slots:
    void on_pushButton_clicked();
    void on_lineEdit_returnPressed();
};
#endif // MAINWINDOW_H
