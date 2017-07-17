#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "include/simpleViewer.hpp"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	ui->openGLWidget = simple
}

MainWindow::~MainWindow()
{
	delete ui;
}
