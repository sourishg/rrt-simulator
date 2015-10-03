#include "rrt.h"

RRT::RRT()
{
    obstacles = new Obstacles;
    startPos.x() = 30;
    startPos.y() = 30;
    endPos.x() = 270;
    endPos.y() = 270;
    root = new Node;
    root->parent = NULL;
    root->position = startPos;
    lastNode = root;
    nodes.push_back(root);
    step_size = 3;
    max_iter = 2000;
}

Node* RRT::getRandomNode()
{
    Node* ret;
    Vector2f point(drand48() * 500.0, drand48() * 451.0);
    if (point.x() >= 0 && point.x() <= 300 && point.y() >= 0 && point.y() <= 300) {
        if (!obstacles->isPointInObstacle(point)) {
            ret = new Node;
            ret->position = point;
            return ret;
        }
    }
    return NULL;
}

int RRT::distance(Vector2f &p, Vector2f &q)
{
    Vector2f v = p - q;
    return sqrt(powf(v.x(), 2) + powf(v.y(), 2));
}

Node* RRT::nearest(Vector2f point)
{
    float minDist = 1e9;
    Node *closest = NULL;
    for(int i = 0; i < (int)nodes.size(); i++) {
        float dist = distance(point, nodes[i]->position);
        if (dist < minDist) {
            minDist = dist;
            closest = nodes[i];
        }
    }
    return closest;
}

Vector2f RRT::newConfig(Node *q, Node *qNearest)
{
    Vector2f to = q->position;
    Vector2f from = qNearest->position;
    Vector2f intermediate = to - from;
    intermediate = intermediate / intermediate.norm();
    Vector2f ret = from + step_size * intermediate;
    return ret;
}

void RRT::add(Node *qNearest, Node *qNew)
{
    qNew->parent = qNearest;
    qNearest->children.push_back(qNew);
    nodes.push_back(qNew);
    lastNode = qNew;
}

bool RRT::reached()
{
    if (distance(lastNode->position, endPos) < 15.0)
        return true;
    return false;
}
