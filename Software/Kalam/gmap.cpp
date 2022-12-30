#include "gmap.h"

gmap::gmap()
{

}

void gmap::setData(QString lat,QString lang)
{
    emit getLat(lat.toDouble());
    emit getLang(lang.toDouble());
}
