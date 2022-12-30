#include "gmap.h"

gmap::gmap()
{

}

void gmap::setData(QString lat,QString lang)
{
    qDebug(lat.toLatin1());

    emit getLat(lat.toDouble());
    emit getLang(lang.toDouble());
}
