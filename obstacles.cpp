#include "obstacles.h"

Obstacles::Obstacles()
{
}

void Obstacles::addObstacle(Vector2f firstPoint, Vector2f secondPoint)
{
    Vector2f tmp;
    if (firstPoint.x() > secondPoint.x() && firstPoint.y() > secondPoint.y()) {
        tmp = firstPoint;
        firstPoint = secondPoint;
        secondPoint = tmp;
    } else if (firstPoint.x() < secondPoint.x() && firstPoint.y() > secondPoint.y()) {
        int height = firstPoint.y() - secondPoint.y();
        firstPoint.y() -= height;
        secondPoint.y() += height;
    } else if (firstPoint.x() > secondPoint.x() && firstPoint.y() < secondPoint.y()) {
        int length = firstPoint.x() - secondPoint.x();
        firstPoint.x() -= length;
        secondPoint.x() += length;
    }
    obstacles.push_back(make_pair(firstPoint, secondPoint));
}

bool Obstacles::isPointInObstacle(Vector2f coord)
{
    for(int i = 0; i < (int)obstacles.size(); i++) {
        if (coord.x() >= obstacles[i].first.x() && coord.x() <= obstacles[i].second.x() &&
                coord.y() >= obstacles[i].first.y() && coord.y() <= obstacles[i].second.y())
            return true;
    }
    return false;
}

void Obstacles::displayObstacles()
{
    for(int i = 0; i < (int)obstacles.size(); i++) {
        qDebug() << obstacles[i].first.x() << ", " << obstacles[i].first.y() << " : " << obstacles[i].second.x() << ", " << obstacles[i].second.y() << endl;
    }
    qDebug() << " --- " << endl;
}

pair<Vector2f, Vector2f> Obstacles::getObstacle(int index)
{
    assert(index < (int)obstacles.size());
    return obstacles[index];
}

int Obstacles::totalObstacles()
{
    return (int)obstacles.size();
}
