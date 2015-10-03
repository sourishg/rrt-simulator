#ifndef RRT_H
#define RRT_H

#include "obstacles.h"
#include <stdlib.h>
#include <vector>
#include <math.h>

using namespace std;
using namespace Eigen;

struct Node {
    vector<Node *> children;
    Node *parent;
    Vector2f position;
};

class RRT
{
public:
    RRT();
    void initialize();
    Node* getRandomNode();
    Node* nearest(Vector2f point);
    int distance(Vector2f &p, Vector2f &q);
    Vector2f newConfig(Node *q, Node *qNearest);
    void add(Node *qNearest, Node *qNew);
    bool reached();
    void setStepSize(int step);
    void setMaxIterations(int iter);
    void deleteNodes(Node *root);
    Obstacles *obstacles;
    vector<Node *> nodes;
    vector<Node *> path;
    Node *root, *lastNode;
    Vector2f startPos, endPos;
    int max_iter;
    int step_size;
};

#endif // RRT_H
