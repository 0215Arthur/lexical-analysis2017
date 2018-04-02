#ifndef DRAW_H
#define DRAW_H
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <math.h>
#include "map.h"
#include "node.h"

class DrawWidget : public QWidget
{
public:

     VNode * vex;
     int vexnum;
     DrawWidget(QWidget *p = 0);
    void paintEvent(QPaintEvent *);

};



#endif // DRAW_H
