#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCharts/QChartView>
#include <gmap.h>
#include <temp.h>
#include <QMainWindow>
#include <QtCharts/QtCharts>
#include <QtCharts/QChartView>
#include <QtSerialPort>
#include <QtCharts/QLineSeries>
#include <QQuickWidget>
#include <QtSerialPort/QSerialPortInfo>
#include <QtQuick/QQuickView>
#include <QtSerialPort/QSerialPort>
#include <QQmlContext>
#include <ledc.h>
#include <bar.h>
#include <QDebug>
//#include <backend.h>
#include <qcustomplot.h>
//#include <QtMqtt/QMqttClient>
#include <QFile>
#include <QtDataVisualization>
#include <QtMath>
#include <QPixmap>

gmap locator;
QSerialPort *serial;

using namespace QtDataVisualization;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap pix("D:/Hardik/Team Kalam/Kalam-2022-GCS/Software/Kalam/Images/team-logo.png");
    ui->logo->setPixmap(pix.scaled(100,100, Qt::KeepAspectRatio));

    QPixmap pic("D:/Hardik/Team Kalam/Kalam-2022-GCS/Software/Kalam/Images/color-bar.png");
    ui->thermo->setPixmap(pic.scaled(320,270, Qt::KeepAspectRatio));

    ui->map->setSource(QUrl::fromLocalFile("../Kalam/maps/maps/main.qml"));
    ui->map->rootContext()->setContextProperty("gmap",&locator);
    ui->map->show();

//    updateLed1("1");
//    updateLed2("2");

    Q3DScatter *scatter = new Q3DScatter();
    QWidget *GPS = QWidget::createWindowContainer(scatter);
    QWidget *widget = new QWidget;
    scatter->setFlags(scatter->flags() ^ Qt::FramelessWindowHint);
    QScatter3DSeries *series = new QScatter3DSeries(GPS);
    QScatterDataArray *data = new QScatterDataArray();
    *data << QVector3D(0.5f, 0.5f, 0.5f) << QVector3D(-0.3f, -0.5f, -0.4f) << QVector3D(0.0f, -0.3f, 0.2f);
    series->dataProxy()->addItems(*data);
//    series->addWidget(GPS, 1);
    scatter->addSeries(series);
    ui->GPS->show();

    configureGraph();
    readSampleCSV();
//    serial = new QSerialPort(this);
//    serialsetup();
//    serialwrite(str);

//    locator.setData("28.608", "77.0406");
}

MainWindow::~MainWindow()
{
    delete ui;
    serial->close();
}

void MainWindow::configureGraph()
{
//    ui->sp1Pressure->addGraph();
    ui->spAltitude->addGraph();
    ui->spVoltage->addGraph();
//    ui->spTemperature->addGraph();

//    graphSetting(ui->sp1Pressure);
    graphSetting(ui->spAltitude);
    graphSetting(ui->spVoltage);
//    graphSetting(ui->spTemperature);

//    ui->spGyro->addGraph();
    ui->spGyroR->addGraph();
    ui->spGyroP->addGraph();
    ui->spGyroY->addGraph();

//    graphSetting(ui->spGyro);
    graphSetting(ui->spGyroR);
    graphSetting(ui->spGyroP);
    graphSetting(ui->spGyroY);

//    ui->spMag->addGraph();
    ui->spMagR->addGraph();
    ui->spMagP->addGraph();
    ui->spMagY->addGraph();

//    graphSetting(ui->spMag);
    graphSetting(ui->spMagR);
    graphSetting(ui->spMagP);
    graphSetting(ui->spMagY);

//    ui->spAcc->addGraph();
//    ui->spAccR->addGraph();
//    ui->spAccP->addGraph();
//    ui->spAccY->addGraph();

//    graphSetting(ui->spAcc);
//    graphSetting(ui->spAccR);
//    graphSetting(ui->spAccP);
//    graphSetting(ui->spAccY);

    ui->containerAltitude->addGraph();
    ui->containerVoltage->addGraph();
//    ui->containerTemperature->addGraph();
//    ui->containerPacketCount->addGraph();

    graphSetting(ui->containerAltitude);
    graphSetting(ui->containerVoltage);
//    graphSetting(ui->containerTemperature);
//    graphSetting(ui->containerPacketCount);

//    ui->gpsaltitude->addGraph();
//    graphSetting(ui->gpsaltitude);

    ui->pointingError->addGraph();
    graphSetting(ui->pointingError);

}

void MainWindow::graphSetting(QCustomPlot *p)
{
    QColor col = QColor(233, 250, 255);
    QColor text = QColor(46, 27, 58);
    p->setBackground(col);
    p->graph(0)->setScatterStyle(QCPScatterStyle::ssDisc);
    p->graph(0)->setLineStyle(QCPGraph::lsLine);
    QPen pen;
    pen.setColor(text);
    p->xAxis->setBasePen(pen);
    p->xAxis->setTickLabelColor(text);
    p->yAxis->setBasePen(pen);
    p->yAxis->setTickLabelColor(text);
    p->xAxis->grid()->setPen(Qt::NoPen);
    p->yAxis->grid()->setPen(Qt::NoPen);
    p->xAxis->grid()->setSubGridVisible(false);
    p->yAxis->grid()->setSubGridVisible(false);

}

void MainWindow::updateContainerLabel(QStringList element) {
    ui->teamIDval->setText(element[0]);
    ui->missionTimeval->setText(element[1]);
    ui->packetCountval->setText(element[2]);
    ui->packetTypeval->setText(element[3]);
    ui->modeval->setText(element[4]);
    ui->spReleasedval->setText(element[5]);
    ui->AltitudeVal->setText(element[6]);
    ui->TempVal->setText(element[7]);
    ui->BatteryVoltageVal->setText(element[8]);
    ui->gpsTimeval->setText(element[9]);
    ui->gpsLatitudeval->setText(element[10]);
    ui->gpsLongitudeval->setText(element[11]);
    ui->gpsAltitudeval->setText(element[12]);
    ui->gpsStateval->setText(element[13]);
    ui->softwareStateval->setText(element[14]);
    ui->cmdEchoval->setText(element[15]);
}

void MainWindow::updatePayloadLabel(QStringList element)
{
    // 21,23,24,25,p(23)
    ui->SPVoltage->setText(element[23]);
    ui->SPALTITUDE->setText(element[21]);
    ui->SPTEMPERATURE->setText(element[22]);
    ui->SPGYROR->setText(element[22]);
    ui->SPGYROP->setText(element[22]);
    ui->SPGYROY->setText(element[22]);
    ui->SPACCR->setText(element[22]);
    ui->SPACCP->setText(element[22]);
    ui->SPACCY->setText(element[22]);
    ui->SPMAGR->setText(element[29]);
    ui->SPMAGP->setText(element[30]);
    ui->SPMAGY->setText(element[31]);
    ui->SPSoftwareState->setText(element[33]);
//    ui->SP1PRESSURE->setText(QString::number(altitudeToPressure(sensorData[23])));
}

void MainWindow::updateGraphArray(QStringList element)
{
    // 6,7,8,23,24,25,30,31,32,p(23),p(30); change of ports
    graphTime.append(count++);

    CAltitude.append(element[6].toDouble());
    CVoltage.append(element[8].toDouble());
    CTemp.append(element[7].toDouble());
//    CPacket.append(element[2].toDouble());

    SPAltitude.append(element[20].toDouble());
    SPTEMP.append(element[21].toDouble());
    SPVoltage.append(element[22].toDouble());
//    SPPacketCount.append(element[21].toDouble());

    SPGyroR.append(element[23].toDouble());
    SPGyroP.append(element[24].toDouble());
    SPGyroY.append(element[25].toDouble());
//    SP2PacketCount.append(element[28].toDouble());

    SPMagR.append(element[29].toDouble());
    SPMagP.append(element[30].toDouble());
    SPMagY.append(element[31].toDouble());

    SPAccR.append(element[26].toDouble());
    SPAccP.append(element[27].toDouble());
    SPAccY.append(element[28].toDouble());

    GPSALTITUDE.append(element[12].toDouble());
    PointingError.append(element[32].toDouble());
}

void MainWindow::plot()
{
    ui->spAltitude->graph(0)->setData(graphTime, SPAltitude);
    ui->spAltitude->replot();
    ui->spAltitude->xAxis->rescale(true);
    ui->spAltitude->yAxis->rescale(true);

    ui->spVoltage->graph(0)->setData(graphTime, SPVoltage);
    ui->spVoltage->replot();
    ui->spVoltage->xAxis->rescale(true);
    ui->spVoltage->yAxis->rescale(true);

//    ui->spTemperature->graph(0)->setData(graphTime, SPTEMP);
//    ui->spTemperature->replot();
//    ui->spTemperature->xAxis->rescale(true);
//    ui->spTemperature->yAxis->rescale(true);

    ui->spGyroR->graph(0)->setData(graphTime, SPGyroR);
    ui->spGyroR->replot();
    ui->spGyroR->xAxis->rescale(true);
    ui->spGyroR->yAxis->rescale(true);

    ui->spGyroP->graph(0)->setData(graphTime, SPGyroP);
    ui->spGyroP->replot();
    ui->spGyroP->xAxis->rescale(true);
    ui->spGyroP->yAxis->rescale(true);

    ui->spGyroY->graph(0)->setData(graphTime, SPGyroY);
    ui->spGyroY->replot();
    ui->spGyroY->xAxis->rescale(true);
    ui->spGyroY->yAxis->rescale(true);

    ui->spMagR->graph(0)->setData(graphTime, SPMagR);
    ui->spMagR->replot();
    ui->spMagR->xAxis->rescale(true);
    ui->spMagR->yAxis->rescale(true);

    ui->spMagP->graph(0)->setData(graphTime, SPMagP);
    ui->spMagP->replot();
    ui->spMagP->xAxis->rescale(true);
    ui->spMagP->yAxis->rescale(true);

    ui->spMagY->graph(0)->setData(graphTime, SPMagY);
    ui->spMagY->replot();
    ui->spMagY->xAxis->rescale(true);
    ui->spMagY->yAxis->rescale(true);

//    ui->spAccR->graph(0)->setData(graphTime, SPAccR);
//    ui->spAccR->replot();
//    ui->spAccR->xAxis->rescale(true);
//    ui->spAccR->yAxis->rescale(true);

//    ui->spAccP->graph(0)->setData(graphTime, SPAccP);
//    ui->spAccP->replot();
//    ui->spAccP->xAxis->rescale(true);
//    ui->spAccP->yAxis->rescale(true);

//    ui->spAccY->graph(0)->setData(graphTime, SPAccY);
//    ui->spAccY->replot();
//    ui->spAccY->xAxis->rescale(true);
//    ui->spAccY->yAxis->rescale(true);

    ui->containerAltitude->graph(0)->setData(graphTime, CAltitude);
    ui->containerAltitude->replot();
    ui->containerAltitude->xAxis->rescale(true);
    ui->containerAltitude->yAxis->rescale(true);

//    ui->containerTemperature->graph(0)->setData(graphTime, CTemp);
//    ui->containerTemperature->replot();
//    ui->containerTemperature->xAxis->rescale(true);
//    ui->containerTemperature->yAxis->rescale(true);

//    ui->containerPacketCount->graph()->setData(graphTime, CPacket);
//    ui->containerPacketCount->replot();
//    ui->containerPacketCount->xAxis->rescale(true);
//    ui->containerPacketCount->yAxis->rescale(true);

    ui->containerVoltage->graph(0)->setData(graphTime, CVoltage);
    ui->containerVoltage->replot();
    ui->containerVoltage->xAxis->rescale(true);
//    ui->containerVoltage->yAxis->setRange(8.0, 9.0);
    ui->containerVoltage->yAxis->rescale(true);


//    ui->gpsaltitude->graph(0)->setData(graphTime, GPSALTITUDE);
//    ui->gpsaltitude->replot();
//    ui->gpsaltitude->xAxis->rescale(true);
//    ui->gpsaltitude->yAxis->rescale(true);

    ui->pointingError->graph(0)->setData(graphTime, PointingError);
    ui->pointingError->replot();
    ui->pointingError->xAxis->rescale(true);
    ui->pointingError->yAxis->rescale(true);

}

void MainWindow::setPrecision()
{
    // 7, 8, 9, 13, 23, 24, 25, 30, 31, 32
    element[6] = QString::number(element[6].toDouble(), 'f', 1);
    element[7] = QString::number(element[7].toDouble(), 'f', 1);
    element[8] = QString::number(element[8].toDouble(), 'f', 2);
    element[10] = QString::number(element[10].toDouble(), 'f', 4);
    element[11] = QString::number(element[11].toDouble(), 'f', 4);
    element[12] = QString::number(element[12].toDouble(), 'f', 1);
    element[20] = QString::number(element[20].toDouble(), 'f', 1);
    element[21] = QString::number(element[21].toDouble(), 'f', 1);
    element[22] = QString::number(element[22].toDouble(), 'f', 2);
}

void MainWindow::updateLed1(QString state)
{
    ui->state1_c->toggle(0);
    ui->state2_c->toggle(0);
    ui->state3_c->toggle(0);
    ui->state4_c->toggle(0);
    ui->state5_c->toggle(0);
    ui->state6_c->toggle(0);
    ui->state7_c->toggle(0);
    int st = state.toInt();
    switch(st) {
    case 1: ui->state1_c->toggle(1);
        break;
    case 2: ui->state2_c->toggle(1);
        break;
    case 3: ui->state3_c->toggle(1);
        break;
    case 4: ui->state4_c->toggle(1);
        break;
    case 5: ui->state5_c->toggle(1);
        break;
    case 6: ui->state6_c->toggle(1);
        break;
    case 7: ui->state7_c->toggle(1);
        break;
    }
}

//void MainWindow::updateLed2(QString state)
//{
//    ui->state1_p->toggle(0);
//    ui->state2_p->toggle(0);
//    ui->state3_p->toggle(0);
//    ui->state4_p->toggle(0);
//    ui->state5_p->toggle(0);
//    ui->state6_p->toggle(0);
//    ui->state7_p->toggle(0);
//    int st = state.toInt();
//    switch(st) {
//    case 1: ui->state1_p->toggle(1);
//        break;
//    case 2: ui->state2_p->toggle(1);
//        break;
//    case 3: ui->state3_p->toggle(1);
//        break;
//    case 4: ui->state4_p->toggle(1);
//        break;
//    case 5: ui->state5_p->toggle(1);
//        break;
//    case 6: ui->state6_p->toggle(1);
//        break;
//    case 7: ui->state7_p->toggle(1);
//        break;
//    }
//}

//void MainWindow::updateBar(bar *b, QString val)
//{
//    int value = val.toInt();
//    b->getpos(value);
//}

void MainWindow::updateTemp(temp *t, QString val) {
    QString value = QString::number(val.toDouble(), 'f', 1);
    double val1 = QString(value).toDouble();
    t->getpos(val1);
}


QFile file("D:/Hardik/Team Kalam/Kalam-2022-GCS/Software/Kalam/write.csv");
QFile Cfile("D:/Hardik/Team Kalam/Kalam-2022-GCS/Software/Kalam/Flight_1077_C.csv");
QFile Pfile("D:/Hardik/Team Kalam/Kalam-2022-GCS/Software/Kalam/Flight_1077_T.csv");

void MainWindow::csvc(QString telemetry)
{

    if (Cfile.open(QFile::WriteOnly | QFile::Append))
    {
        QTextStream output(&Cfile);
        output << telemetry<<"\n";

    }
    Cfile.close();
}
void MainWindow::csvp(QString telemetry)
{
    if (Pfile.open(QFile::WriteOnly | QFile::Append))
    {
        QTextStream output(&Pfile);
        output<<"1077," << telemetry<<"\n";

    }
    Pfile.close();
}

void MainWindow::csv(QString telemetry)
{
    // QFile file("csv.xslx");
    // if(!file.exit())
    //{
    //   qDebug()<<file.filename()<<"does not exists";
    //}

    if (file.open(QFile::WriteOnly | QFile::Append))
    {
        QTextStream output(&file);
        output << telemetry<<"\n";

    }
    file.close();
}
void MainWindow::serialwrite(QString cmd)
{
   serial->write(cmd.toLocal8Bit());
}

void MainWindow::serialReceived()
{
    QByteArray ba;
    ba = serial->readAll();
    buffer += ba;
    buffer_split = buffer.split("\r\n");
    if (buffer_split.length() >= 2)
    {
        token = buffer_split[0];
         sensordata=token.split(",1077,");
        if (check())
        {   setPrecision();
            updateGraphArray(element);
            updateContainerLabel(element);
            updatePayloadLabel(element);
            plot();
            csvc(sensordata[0]);
            csvp(sensordata[1]);
            updateLed1(element[14]);
//            updateLed2(element[33]);

//            updateBar(ui->pressureBar_1, "85000");
//            updateBar(ui->pressureBar_2, "85000");


            updateTemp(ui->tempBar, element[21]);

      locator.setData(element[10], element[11]);

            csv(buffer_split[0]);
            //updatelabel(buffer_split[0])
            qDebug() << buffer_split[0];
            buffer = buffer_split[1];
        }
        else
        {
            buffer = buffer_split[1];
            // qDebug() << "packet is not complete\n";
            // buffer_split[0].clear();
            // QMessageBox::information(this, " Error", "packet is not complete.");
        }

    }

    // ui->label->setText(ba);
}
bool MainWindow::check()
{
    element = token.split(",");
    // data << token.split(",");
    if (element.length() >= 34)
    {

        return true;
    }
    else
        return false;
}

void MainWindow::serialsetup()
{
    bool arduino_is_available = false;
    QString arduino_uno_port_name;
    //
    //  For each available serial port
    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    {
        //  check if the serialport has both a product identifier and a vendor identifier
        if (serialPortInfo.hasProductIdentifier() && serialPortInfo.hasVendorIdentifier())
        {
            //  check if the product ID and the vendor ID match those of the arduino uno
            if ((serialPortInfo.productIdentifier() == arduino_uno_product_id) && (serialPortInfo.vendorIdentifier() == arduino_uno_vendor_id))
            {
                arduino_is_available = true; //    arduino uno is available on this port
                arduino_uno_port_name = serialPortInfo.portName();
            }
        }
    }
    if (arduino_is_available)
    {
        serial->setPortName(arduino_uno_port_name);
        serial->setBaudRate(QSerialPort::Baud9600);
        serial->setDataBits(QSerialPort::Data8);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        serial->setFlowControl(QSerialPort::NoFlowControl);
        serial->open(QIODevice::ReadWrite);
        // serial->write("ok");
        connect(serial, SIGNAL(readyRead()), this, SLOT(serialReceived()));
    }
    else
    {
        qDebug() << "Couldn't find the correct port for the arduino.\n";
        QMessageBox::information(this, "Serial Port Error", "Couldn't open serial port to arduino.");
    }
}

void MainWindow::readSampleCSV()
{
    QFile d("D:/Hardik/Team Kalam/Kalam-2022-GCS/Software/Kalam/SampleData.csv");
    qDebug() << "CSV printing";


    if(d.open(QFile::ReadOnly)) {
        while(!d.atEnd()) {
            QString s = d.readLine();
            buffer.append(s);
        }
    }

    QStringList buffer_split = buffer.split("\r\n");
    qDebug() << buffer_split;
    for(int i=0; i<230; i++) {
//        qDebug() << s;
        element = buffer_split[i].split(",");
        qDebug() << element;
        setPrecision();
        updateGraphArray(element);
        updateContainerLabel(element);
        updatePayloadLabel(element);
        plot();
//        csvc(a[0]);
//        csvp(a[1]);
        updateLed1(element[14]);
        updateTemp(ui->tempBar, element[21]);
        locator.setData(element[10], element[11]);
     }

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(plotSec()));
    timer->start(1000);
}

int loop1 = 0;
void MainWindow::plotSec()
{
    if(loop1 < buffer_split.size()) {
//        QStringList element = buffer_split[loop1++].split("\r\n");
        element = buffer_split[loop1++].split(",");
        //        element = a[0].split(",");

        ui->rawData->setText(element.join(','));

        //setting Precision
        setPrecision();
        updateGraphArray(element);
        updateContainerLabel(element);
        updatePayloadLabel(element);
        plot();
//        csvc(a[0]);
//        csvp(a[1]);
        updateLed1(element[14]);
        updateTemp(ui->tempBar, element[21]);
        locator.setData(element[10], element[11]);


        // publish telemetry to mqtt
//        if(startMqtt)
//            publishMqtt(element);

    }
}
