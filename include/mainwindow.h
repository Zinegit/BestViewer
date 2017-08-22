#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "include/viewer.hpp"
#include "include/variableToShare.hpp"
#include <GL/glew.h>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0, Viewer* viewer = NULL);
	~MainWindow();
	void addViewer(QGLViewer* viewer);

private slots:
	void on_wire_button_clicked();

	void on_record_button_clicked();

	void on_predict_step_clicked();

	void on_predict_button_clicked();

private:
	Ui::MainWindow *ui;
	Viewer* vi;
};

#endif // MAINWINDOW_H
