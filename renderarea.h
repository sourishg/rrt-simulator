#ifndef RENDERAREA_H
#define RENDERAREA_H

#include "rrt.h"
#include <QWidget>
#include <QColor>
#include <QDebug>
#include <QPoint>
#include <QMouseEvent>
#include <QPainterPath>
#include <QPainter>
#include <QRect>

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    RenderArea(QWidget *parent = 0);
    RRT *rrt;
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void drawField(QPainter &event);
    void drawStartPos(QPainter &event);
    void drawEndPos(QPainter &event);
    void drawObstacles(QPainter &event);
    void drawNodes(QPainter &event);
private:
    bool scribbling;
    QPoint lastMouseClickedPoint;
signals:
    void painting();
};

#endif // RENDERAREA_H
