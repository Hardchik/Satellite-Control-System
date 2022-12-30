#ifndef LEDC_H
#define LEDC_H
#include <QWidget>

class ledc : public QWidget
{
Q_OBJECT

public:

int lit = 0;
QPixmap *img1 = new QPixmap;
QPixmap *img2 = new QPixmap;


ledc(QWidget *parent=nullptr);

void toggle(int n);


protected:
void paintEvent(QPaintEvent *event) ;

};

#endif // LEDC_H
