#include "mainwindow.h"
#include <QDebug>
#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QString>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCommandLineParser parser;
    QCommandLineOption port_param       (QStringList()<<"p"<<"port","Port for coonection with another man","11111");
    QCommandLineOption type_server_param(QStringList()<<"s"<<"server");
    QCommandLineOption ip_param         (QStringList()<<"i"<<"host", "Ip address","Ip", "127.0.0.1");


    parser.addOption(type_server_param);
    parser.addOption(port_param);
    parser.addOption(ip_param);
    parser.process(a);


//    if(parser.isSet(port_param))
//        qDebug()<<"Port is" << parser.value(port_param);
//    if(parser.isSet(type_server_param))
//        qDebug()<<"Name is server";
//    else qDebug()<<"Name is client";
//    if(parser.isSet(ip_param))
//        qDebug()<<"Ip: 127.0.0.1";

    QString  ip     = parser.value(ip_param);
    QString  port   = parser.value(port_param);
    bool     server = parser.isSet(type_server_param);


    MainWindow w(ip, port, server, nullptr);
    w.show();
    return a.exec();


}
