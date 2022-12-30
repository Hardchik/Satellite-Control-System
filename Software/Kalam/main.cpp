#include "mainwindow.h"
#include <QtQuick/QQuickView>
#include <QQuickWidget>
#include    <QDebug>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("TEAM KALAM-1077 GCS");
    w.show();
    gmap locator;
    return a.exec();
}
