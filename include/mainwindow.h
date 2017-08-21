#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "include/viewer.hpp"
#include <GL/glew.h>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	void addViewer(QGLViewer* viewer);

//private slots:
//	void on_pushButton_clicked();

private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
