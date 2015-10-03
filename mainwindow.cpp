#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    renderArea = ui->renderArea;
    rrt = renderArea->rrt;
    simulated = false;
}

/**
 * @brief Start the simulator.
 */
void MainWindow::on_startButton_clicked()
{
    if (simulated) {
        ui->statusBox->setText(tr("Please reset!"));
        renderArea->update();
        return;
    }
    simulated = true;
    // get step size and max iterations from GUI.
    rrt->setMaxIterations(ui->maxIterations->text().toInt());
    rrt->setStepSize(ui->stepSize->text().toInt());

    assert(rrt->step_size > 0);
    assert(rrt->max_iter > 0);

    // RRT Algorithm
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
            ui->statusBox->setText(tr("Reached Destination!"));
            break;
        }
    }
    Node *q;
    if (rrt->reached()) {
        q = rrt->lastNode;
    }
    else
    {
        // if not reached yet, then shortestPath will start from the closest node to end point.
        q = rrt->nearest(rrt->endPos);
        ui->statusBox->setText(tr("Exceeded max iterations!"));
    }
    // generate shortest path to destination.
    while (q != NULL) {
        rrt->path.push_back(q);
        q = q->parent;
    }
    renderArea->update();
}

/**
 * @brief Delete all obstacles, nodes and paths from the simulator.
 */
void MainWindow::on_resetButton_clicked()
{
    simulated = false;
    ui->statusBox->setText(tr(""));
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
