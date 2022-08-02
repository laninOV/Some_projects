#include "mainwindow.h"
//#include "qlampwidget.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QString ip, QString port, bool server, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QLabel label;

    QFont font("Microsoft YaHei", 14, 50);                   // устанавливаем шрифт
    ui->textBrowser->setFont(font);

    if (server == true){
        setWindowTitle ("Server");

        QPixmap pixmap("D:/Downloads/red.png");
        ui->label->setPixmap(pixmap);
        ui->label->setPixmap(pixmap.scaled(ui->label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));


        _server = new QTcpServer;
        connect(_server,&QTcpServer::newConnection, this, &MainWindow::newConnection);
        _server->listen(QHostAddress::Any, port.toInt());
        qDebug()<<"Try listen"<<port;
        printMessage("<font color=\"Green\">Try listen</font>"); //вывод уведомления в окно диолога
    }
    else {
         setWindowTitle ("Client");

         QPixmap pixmap("D:/Downloads/red.png");
         ui->label->setPixmap(pixmap);
         ui->label->setPixmap(pixmap.scaled(ui->label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));



         _socket = new QTcpSocket(this); // создаём сокет

         connect(_socket, &QTcpSocket::readyRead,    this,  &MainWindow::slotReadyRead);
         connect(_socket, &QTcpSocket::connected,    this,  &MainWindow::socketConnected);
         connect(_socket, &QTcpSocket::disconnected, this,  &MainWindow::socketDisconnected);

         _socket->connectToHost(ip, port.toInt());
         qDebug()<<"Try connect to host"<<ip<<port;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newConnection()
{
    _socket = _server->nextPendingConnection();

    connect(_socket, &QTcpSocket::connected,    this,  &MainWindow::socketConnected);
    connect(_socket, &QTcpSocket::readyRead,    this,  &MainWindow::slotReadyRead);
    connect(_socket, &QTcpSocket::disconnected, this,  &MainWindow::socketDisconnected);

    socketConnected();
}

void MainWindow::slotReadyRead()                            // слот для чтения сообщений
{
    _socket = (QTcpSocket*)sender();                        // откуда приходит запрос
    QDataStream in(_socket);                                // приём передача данных
    in.setVersion(QDataStream::Qt_DefaultCompiledVersion);  // работаем с данными находящимися в сокете
    if(in.status() == QDataStream::Ok){                     // проверяем состояние объекта in
        qDebug() << "read...";

        QString str;                                        // создаём строковую переменную
        QTime time;                                         // переменная time

        in>>time>>str;                                      // записываем в неё строку
        ui->textBrowser->append("<font color=blue>"+time.toString()+" "+str);   // формируем вывод текста

        QFont font("Microsoft YaHei", 14, 50);              // устанавливаем шрифт
        ui->textBrowser->setFont(font);
        qDebug()<<str;                                      // выведем её в консоль
    }
    else{
        qDebug() << "DataStream error";
    }
}

void MainWindow::SendToClient(QString str)                  // сообщение которое надо отправить
{
   Data.clear();
   // чистим массив Data


   QDataStream out(&Data, QIODevice::ReadWrite);            // данные на вывод, режим работы только на запись
   out.setVersion(QDataStream::Qt_DefaultCompiledVersion);  // устанавливаем текущую версию
   out << QTime::currentTime() << str;                      // записываем через объект out строку в массив Date

   _socket->write(Data);                                    // записываем массив в сокет

   ui->textBrowser->append("<font color=red>"+QTime::currentTime().toString()+" "+str);         // формируем вывод текста
   ui->lineEdit->clear();                                   // отчиска строки ввода
}

void MainWindow::socketConnected()                          // уведовление о подключении
{
    qDebug()<<"socket was connected";
    printMessage("<font color=\"Green\">socket was connected</font>"); //вывод уведомления в окно диолога
    QPixmap pixmap("D:/Downloads/green.png");
    ui->label->setPixmap(pixmap.scaled(ui->label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void MainWindow::socketDisconnected()                       // уведомление об отключении
{
    qDebug()<<"socket was disconnected";
    printMessage("<font color=\"Red\">socket was disconnected</font>"); //вывод уведомления в окно диолога
    QPixmap pixmap("D:/Downloads/red.png");
    ui->label->setPixmap(pixmap.scaled(ui->label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));


}


void MainWindow::on_pushButton_clicked(){ // отправка текста по клику мыши
    SendToClient(ui->lineEdit->text());
}


void MainWindow::on_lineEdit_returnPressed(){ // отправка текста при нажатии enter
    SendToClient(ui->lineEdit->text());
}


void MainWindow::printMessage(QString message)
{
    ui->textBrowser->append(message);
}

