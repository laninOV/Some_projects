QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ball.cpp \
    behaviorball.cpp \
    geometryball.cpp \
    main.cpp \
    mainwindow.cpp \
    representation.cpp \
    scene.cpp

HEADERS += \
    ball.h \
    behaviorball.h \
    geometryball.h \
    limitfield.h \
    mainwindow.h \
    point.h \
    representation.h \
    scene.h

FORMS += \
    mainwindow.ui

DESTDIR=bin
OBJECTS_DIR=build
MOC_DIR=build
RCC_DIR=build



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
