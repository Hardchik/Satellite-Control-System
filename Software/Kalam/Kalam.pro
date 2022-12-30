QT       += core gui charts qml quick quickwidgets serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport datavisualization

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bar.cpp \
    gmap.cpp \
    ledc.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp \
    temp.cpp

HEADERS += \
    bar.h \
    gmap.h \
    ledc.h \
    mainwindow.h \
    qcustomplot.h \
    temp.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc

DISTFILES += \
    Images/bar-06.png \
    Images/bar-07.png \
    Images/greenled.png \
    Images/redled.png
