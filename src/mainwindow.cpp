#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include "include/viewer.hpp"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	//Ici tu dois donner associer à opengl_widget le viewer que tu souhaites afficher dans ta fenêtre
//	ui->opengl_widget = ;
//	ui->openGLWidget = simple
}

MainWindow::~MainWindow()
{
	delete ui;
}
