/* Documentation tag for Doxygen
 */

/*! \mainpage BestViewer documentation
 *
 * \section intro_sec Introduction
 *
 * This documentation provides a description of every class, every file and every function inside it.
 *
 * <BR><BR>
 *
 */

/**
* \file main.cpp
* \brief Instantiate viewer and observer, connect them and run the main loop
* \author Tom Mourot-Faraut
* \version 1.0
* \date 01/08/2017
*/

#include <GL/glew.h>

#include <typeinfo>

#include <qapplication.h>
#include <QGLViewer/manipulatedCameraFrame.h>

#include "include/viewer.hpp"
#include "include/observer.hpp"
#include "include/mainwindow.h"

/**
 * \fn int main (int argc, char **argv)
 * \brief Entry of the program.
 * \return application.exec() - Boucle draw.
 */

int main(int argc, char **argv) {

	// Mode debug
	bool debug = false;
	if (argc <= 2)
	{
		if(argc == 2)
		{
			std::string arg(argv[1]);
			if(arg == "-debug")
			{
				debug = true;
			}
			else
			{
				std::cerr << "Usage : " << argv[0] << " [-debug (activates the debugging mode)]" << std::endl;
				exit(-1);
			}
		}
		if(debug)
		{
			std::cout << "Debug mode activated" << std::endl;
		}
		else
		{
			std::cout << "Release mode activated" << std::endl;
		}
	}
	else if(argc > 1)
	{
		std::cerr << "Usage : " << argv[0] << " [-debug (activate the debugging mode)]" << std::endl;
		exit(-1);
	}

	// Read command lines arguments
	QApplication application(argc, argv);



	// Instantiate the viewer
	Viewer viewer(debug);
	// GUI
	MainWindow window(0, &viewer);
	// Instantiate the observer
	Observer observer(&viewer);

	window.addViewer(&viewer);

//	viewer.setWindowTitle("viewer");
//	// Make the viewer window visible on screen.
//	viewer.show();

	if (debug)
	{
		//Observer gets the viewer's camera as an outsideCamera
		observer.setOutsideCamera(viewer.camera());
		PlanesCamera* cam = new PlanesCamera(qreal(0.0001), qreal(1000.));
		observer.setCamera(cam) ;

		// Make sure every viewer movement updates the observer
		// Not really useful
//		QObject::connect(viewer.camera()->frame(), SIGNAL(manipulated()), &observer, SLOT(update()));
//		QObject::connect(viewer.camera()->frame(), SIGNAL(spun()), &observer, SLOT(update()));
		QObject::connect(&viewer, SIGNAL(drawNeeded()), &observer, SLOT(update()));

//		observer.show();

		window.addViewer(&observer);
	}

	window.show();

	// Run main loop.
	return application.exec();
}
