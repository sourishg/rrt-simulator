#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    renderArea = ui->renderArea;
    rrt = renderArea->rrt;
}
void MainWindow::on_startButton_clicked()
{
    rrt->setMaxIterations(ui->maxIterations->text().toInt());
    rrt->setStepSize(ui->stepSize->text().toInt());
    assert(rrt->step_size != 0);
    assert(rrt->max_iter != 0);
    for(int i = 0; i < renderArea->rrt->max_iter; i++) {
        Node *q = rrt->getRandomNode();
        if (q) {
            Node *qNearest = rrt->nearest(q->position);
            if (rrt->distance(q->position, qNearest->position) > rrt->step_size) {
                Vector2f newConfig = rrt->newConfig(q, qNearest);
                if (!rrt->obstacles->isSegmentInObstacle(newConfig, qNearest->position)) {
                    Node *qNew = new Node;
                    qNew->position = newConfig;
                    rrt->add(qNearest, qNew);
                }
            }
        }
        if (rrt->reached()) {
            break;
        }
    }
    Node *q;
    if (rrt->reached())
        q = rrt->lastNode;
    else
        q = rrt->nearest(rrt->endPos);
    while (q != NULL) {
        rrt->path.push_back(q);
        q = q->parent;
    }
    renderArea->update();
}
void MainWindow::on_resetButton_clicked()
{
    rrt->obstacles->obstacles.clear();
    rrt->obstacles->obstacles.resize(0);
    rrt->deleteNodes(rrt->root);
    rrt->nodes.clear();
    rrt->nodes.resize(0);
    rrt->path.clear();
    rrt->path.resize(0);
    rrt->initialize();
    renderArea->update();
}

MainWindow::~MainWindow()
{
    delete ui;
}
