#include "include/mainWindow.hpp"

#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent, Viewer *viewer) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	vi = viewer;
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::addViewer(QGLViewer* viewer)
{
	ui->viewer_layout->addWidget(viewer);
}

void MainWindow::on_wire_button_clicked()
{
	vi->changeVisual();
	vi->update();
}

void MainWindow::on_record_button_clicked()
{
	vi->record();
	vi->update();
}

void MainWindow::on_predict_step_clicked()
{
	vi->predictStep();
	vi->update();
}

void MainWindow::on_predict_button_clicked()
{
	vi->predict();
	vi->update();
}
