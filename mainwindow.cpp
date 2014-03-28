#include <QGraphicsView>
#include <QTimer>

#include "constants.h"
#include "gamecontroller.h"
#include "mainwindow.h"
#include "vld.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      scene(new QGraphicsScene(this)),
      view(new QGraphicsView(scene, this)),
      game(new GameController(*scene, this))
{
    setCentralWidget(view);
    resize(600, 600);

    initScene();
    initSceneBackground();

    QTimer::singleShot(0, this, SLOT(adjustViewSize()));
	connect(game, SIGNAL(deleteFood(QGraphicsItem*)), this, SLOT(deleteFood(QGraphicsItem*)));
}

void MainWindow::deleteFood(QGraphicsItem* food)
{
	//QList<QGraphicsItem*> list = scene->items();
	scene->removeItem(food);
	delete food;
	//food = NULL;
}

MainWindow::~MainWindow()
{
    
}

void MainWindow::adjustViewSize()
{
    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatioByExpanding);
}

void MainWindow::initScene()
{
    scene->setSceneRect(-100, -100, 200, 200);
//    scene->setSceneRect(0, 0, 200, 200);
}

void MainWindow::initSceneBackground()
{
    QPixmap bg(TILE_SIZE, TILE_SIZE);
    QPainter p(&bg);
    p.setBrush(QBrush(Qt::gray));
    p.drawRect(0, 0, TILE_SIZE, TILE_SIZE);

    view->setBackgroundBrush(QBrush(bg));
}
