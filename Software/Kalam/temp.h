#ifndef TEMP_H
#define TEMP_H
#include <QWidget>


class temp : public QWidget
{
Q_OBJECT

public:
QPixmap *imgb = new QPixmap;
double val1=250;
double k=0;
void getpos(int *val);
void getpos(double *val);
void getpos(int val);




temp(QWidget *parent=nullptr);

virtual ~temp()

{};


protected:
void paintEvent(QPaintEvent *event) ;

};
#endif // TEMP_H
