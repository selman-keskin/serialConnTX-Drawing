#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>


QPoint point;
QPoint previousPoint;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new paintScene();       // Init graphics scene
    ui->graphicsView->setScene(scene);  // Set graphics scene

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_closeButton_clicked()
{
    close();
}
