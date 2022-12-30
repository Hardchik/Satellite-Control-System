#ifndef BAR_H
#define BAR_H
#include <QWidget>


class bar : public QWidget
{
Q_OBJECT

public:
QPixmap *imgb = new QPixmap;
double val1=250;
double k=0;
void getpos(int *val);
void getpos(double *val);
void getpos(int val);




bar(QWidget *parent=nullptr);

virtual ~bar()

{};


protected:
void paintEvent(QPaintEvent *event) ;

};
#endif // BAR_H
