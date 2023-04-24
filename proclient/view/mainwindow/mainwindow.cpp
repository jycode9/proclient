#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QScroller>

#include "base/glog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    GLOG_ADD(GLogLevel::Debug, "My Name=%s, %s, %d", "WenJingyu", "JIM", 123);

    //ui->lineEdit->setEnabled(false);
    connectSignal();
}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::connectSignal(){

}


