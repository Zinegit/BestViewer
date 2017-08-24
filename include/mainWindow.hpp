/**
 * \file mainWindow.hpp
 * \brief The mainWindow class. It contains every other widget
 * \author Tom Mourot-Faraut
 * \version 1.0
 */

#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "include/viewer.hpp"
#include "include/variableToShare.hpp"
#include <GL/glew.h>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

/**
 * \class MainWindow
 * \brief This class contains the different viewers and every other widget such as the buttons etc..
 */
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0, Viewer* viewer = NULL);
	~MainWindow();
	void addViewer(QGLViewer* viewer);

private slots:
	/**
	 * \fn void on_wire_button_clicked();
	 * \brief This function changes the display of the model (filled or not)
	 * \return void
	 */
	void on_wire_button_clicked();

	/**
	 * \fn void on_record_button_clicked();
	 * \brief This function records the change of state of triangles between two frames
	 * \return void
	 */
	void on_record_button_clicked();

	/**
	 * \fn void on_predict_step_clicked();
	 * \brief This function predicts the position of a vertex
	 * \return void
	 */
	void on_predict_step_clicked();

	/**
	 * \fn on_predict_button_clicked();
	 * \brief This function predicts the position of all the vertices
	 * \return void
	 */
	void on_predict_button_clicked();

private:
	Ui::MainWindow *ui;
	Viewer* vi;
};

#endif // MAINWINDOW_HPP
