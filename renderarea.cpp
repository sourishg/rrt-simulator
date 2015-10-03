#include "renderarea.h"
#include <queue>
#include <QTimer>

RenderArea::RenderArea(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    scribbling = false;
    rrt = new RRT;
}
void RenderArea::drawField(QPainter &painter)
{
    painter.save();
    painter.setRenderHint(QPainter::Antialiasing);
    QRect field;
    field.setTopLeft(QPoint(this->x(), this->y()));
    field.setBottomRight(QPoint(this->width()-1, this->height()-1));
    painter.setPen(Qt::black);
    painter.setBrush(QBrush(Qt::green));
    painter.drawRect(field);
    painter.restore();
}
void RenderArea::drawStartPos(QPainter &painter)
{
    painter.save();
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::black);
    painter.setBrush(QBrush(Qt::red));
    painter.drawEllipse(this->x()+20, this->y()+20, 21.6, 21.6);
    painter.restore();
}
void RenderArea::drawEndPos(QPainter &painter)
{
    painter.save();
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::black);
    painter.setBrush(QBrush(Qt::blue));
    painter.drawEllipse(this->width()-40, this->height()-40, 21.6, 21.6);
    painter.restore();
}
void RenderArea::drawObstacles(QPainter &painter)
{
    painter.save();
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::black);
    painter.setBrush(QBrush(Qt::black));
    pair<Vector2f, Vector2f> obstacle;
    for(int i = 0; i < rrt->obstacles->totalObstacles(); i++) {
        obstacle = rrt->obstacles->getObstacle(i);
        QPoint topLeft(obstacle.first.x(), obstacle.first.y());
        QPoint bottomRight(obstacle.second.x(), obstacle.second.y());
        QRect rect(topLeft, bottomRight);
        painter.drawRect(rect);
    }
    painter.restore();
}
void RenderArea::drawNodes(QPainter &painter)
{
    painter.save();
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::black);
    painter.setBrush(QBrush(Qt::black));
    Vector2f pos;
    for(int i = 0; i < (int)rrt->nodes.size(); i++) {
        for(int j = 0; j < (int)rrt->nodes[i]->children.size(); j++) {
            pos = rrt->nodes[i]->children[j]->position;
            painter.drawEllipse(pos.x()-1.5, pos.y()-1.5, 3, 3);
        }
        pos = rrt->nodes[i]->position;
        painter.drawEllipse(pos.x()-1.5, pos.y()-1.5, 3, 3);
    }
    painter.setPen(Qt::magenta);
    painter.setBrush(QBrush(Qt::magenta));
    for(int i = 0; i < (int)rrt->path.size() - 1; i++) {
        QPointF p1(rrt->path[i]->position.x(), rrt->path[i]->position.y());
        QPointF p2(rrt->path[i+1]->position.x(), rrt->path[i+1]->position.y());
        painter.drawLine(p1, p2);
    }
    painter.restore();
}

void RenderArea::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    drawField(painter);
    drawStartPos(painter);
    drawEndPos(painter);
    drawObstacles(painter);
    drawNodes(painter);
    emit painting();
}
void RenderArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastMouseClickedPoint = event->pos();
        scribbling = true;
        qDebug() << event->x() << ", " << event->y() << endl;
    }
}

void RenderArea::mouseMoveEvent(QMouseEvent *event)
{

}

void RenderArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling) {
        QPoint curPoint = event->pos();
        rrt->obstacles->addObstacle(Vector2f(lastMouseClickedPoint.x(), lastMouseClickedPoint.y()), Vector2f(curPoint.x(), curPoint.y()));
        // obstacles->displayObstacles();
        update();
        scribbling = false;
    }
}
