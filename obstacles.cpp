#include "obstacles.h"

Obstacles::Obstacles()
{
}

/**
 * @brief Obstacles are stored as rectangles. Rectangle is denoted by two points : topLeft and bottomRight.
 * @param firstPoint
 * @param secondPoint
 */
void Obstacles::addObstacle(Vector2f firstPoint, Vector2f secondPoint)
{
    // Get topLeft and bottomRight points from the given points.
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
    firstPoint.x() -= BOT_CLEARANCE;
    firstPoint.y() -= BOT_CLEARANCE;
    secondPoint.x() += BOT_CLEARANCE;
    secondPoint.y() += BOT_CLEARANCE;
    obstacles.push_back(make_pair(firstPoint, secondPoint));
}

/**
 * @brief Check if a line segment intersects a rectangle.
 * @param p1
 * @param p2
 * @return
 */
bool Obstacles::isSegmentInObstacle(Vector2f &p1, Vector2f &p2)
{
    QLineF lineSegment(p1.x(), p1.y(), p2.x(), p2.y());
    QPointF *intersectPt = new QPointF;
    for(int i = 0; i < (int)obstacles.size(); i++) {
        float length = obstacles[i].second.x() - obstacles[i].first.x();
        float breadth = obstacles[i].second.y() - obstacles[i].first.y();
        QLineF lseg1(obstacles[i].first.x(), obstacles[i].first.y(), obstacles[i].first.x() + length, obstacles[i].first.y());
        QLineF lseg2(obstacles[i].first.x(), obstacles[i].first.y(), obstacles[i].first.x(), obstacles[i].first.y() + breadth);
        QLineF lseg3(obstacles[i].second.x(), obstacles[i].second.y(), obstacles[i].second.x(), obstacles[i].second.y() - breadth);
        QLineF lseg4(obstacles[i].second.x(), obstacles[i].second.y(), obstacles[i].second.x() - length, obstacles[i].second.y());
        QLineF::IntersectType x1 = lineSegment.intersect(lseg1, intersectPt);
        QLineF::IntersectType x2 = lineSegment.intersect(lseg2, intersectPt);
        QLineF::IntersectType x3 = lineSegment.intersect(lseg3, intersectPt);
        QLineF::IntersectType x4 = lineSegment.intersect(lseg4, intersectPt);
        // check for bounded intersection. IntersectType for bounded intersection is 1.
        if (x1 == 1 || x2 == 1 || x3 == 1 || x4 == 1)
            return true;
    }
    return false;
}
