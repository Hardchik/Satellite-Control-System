#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gmap.h>
#include <bar.h>
#include <temp.h>
#include <QMainWindow>
#include <QtCharts/QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QQuickWidget>
#include <QtSerialPort/QSerialPortInfo>
#include <QtQuick/QQuickView>
#include <QtSerialPort/QSerialPort>
#include <QSerialPort>
#include <QByteArray>
//#include <QtMqtt/QMqttMessage>
//#include <QtMqtt/QMqttSubscription>
#include <QFile>
#include <qcustomplot.h>
#include <QtDataVisualization>
#include <QMainWindow>
#include <QString>
//#include <QtMqtt/QMqttClient>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // graph function
    void configureGraph();
    void graphSetting(QCustomPlot *p);

    // data plotting on gui
    void updateGraphArray(QStringList element);
    void plot();
    void setPrecision();
    void updateContainerLabel(QStringList element);
    void updatePayloadLabel(QStringList element);
//    void updatePayload2Label(QStringList element);
//    void updateLed(QString state);
//    void updateBar(bar *b, QString val);
    void updateLed1(QString state);
    void updateLed2(QString state);
    void updateBar(bar *b, QString val);
    void updateTemp(temp *t, QString val);

    void readSampleCSV();
    void plotSec();

private slots:
   void serialReceived();
   void serialsetup();
   void serialwrite(QString);
   bool check();
   void csv( QString);
   void csvc( QString);
   void csvp( QString);

private:
    Ui::MainWindow *ui;

    static const quint16 arduino_uno_vendor_id = 9025;
    static const quint16 arduino_uno_product_id = 67;
    QString buffer ="";
    QStringList buffer_split;
    QString token ="";
    QStringList element;
    QString telemetry;
    QString str = "print";
    QStringList sensordata;
    QStringList a;
    QTimer *timer;
    QString s;

    QVector<double> CTemp, CPacket, CAltitude, CVoltage, SPAltitude, SPTEMP, SPVoltage, SPGyroR, SPGyroP, SPGyroY, SPMagR, SPMagP, SPMagY, SPAccR, SPAccP, SPAccY ;
    QVector<double> SPALTITUDE, SPTEMPERATURE, SPVoltage_1, SPMAGR, SPMAGP, SPMAGY, SPACCR, SPACCP, SPACCY, SPGYROR, SPGYROP, SPGYROY, SPSoftwareState;
    double pressure;
    QVector<double> graphTime;
    QVector<double> GPSALTITUDE, PointingError;
    double count = 1;
};
#endif // MAINWINDOW_H
