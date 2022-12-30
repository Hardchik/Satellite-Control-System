#ifndef GMAP_H
#define GMAP_H

#include <QObject>

class gmap : public QObject
{
    Q_OBJECT


public:
    gmap();


signals:
    void getLat(double lat);
    void getLang(double lang);


public slots:
    void setData(QString lat,QString lang);



};

#endif // GMAP_H
