#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    renderArea = ui->renderArea;
}
void MainWindow::on_startButton_clicked()
{
    //for(int i = 0; i < renderArea->rrt->max_iter; i++) {
    while (!renderArea->rrt->reached()) {
        Node *q = renderArea->rrt->getRandomNode();
        if (q) {
            Node *qNearest = renderArea->rrt->nearest(q->position);
            if (renderArea->rrt->distance(q->position, qNearest->position) > renderArea->rrt->step_size) {
                Vector2f newConfig = renderArea->rrt->newConfig(q, qNearest);
                if (!renderArea->rrt->obstacles->isPointInObstacle(newConfig)) {
                    Node *qNew = new Node;
                    qNew->position = newConfig;
                    renderArea->rrt->add(qNearest, qNew);
                    qDebug() << renderArea->rrt->distance(renderArea->rrt->lastNode->position, renderArea->rrt->endPos) << endl;
                }
            }
        }
    }
    Node *q = renderArea->rrt->lastNode;
    while (q != NULL) {
        renderArea->rrt->path.push_back(q);
        q = q->parent;
    }
    renderArea->update();
}
MainWindow::~MainWindow()
{
    delete ui;
}
