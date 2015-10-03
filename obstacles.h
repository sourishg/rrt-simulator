#ifndef OBSTACLES_H
#define OBSTACLES_H

#include <QDebug>
#include <vector>
#include <eigen3/Eigen/Dense>
#include <assert.h>

using namespace Eigen;
using namespace std;

class Obstacles
{
public:
    Obstacles();
    void addObstacle(Vector2f firstPoint, Vector2f secondPoint);
    bool isPointInObstacle(Vector2f coord);
    void displayObstacles();
    pair<Vector2f, Vector2f> getObstacle(int index);
    int totalObstacles();
private:
    vector<pair<Vector2f, Vector2f> > obstacles;
};

#endif // OBSTACLES_H
