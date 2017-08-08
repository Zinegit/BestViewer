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
#include <qapplication.h>
#include <QGLViewer/manipulatedCameraFrame.h>

#include "include/viewer.hpp"
#include "include/observer.hpp"

/**
 * \fn int main (int argc, char **argv)
 * \brief Entry of the program.
 *
 * \return application.exec() - Boucle draw.
 */
int main(int argc, char **argv) {
  // Read command lines arguments
  QApplication application(argc, argv);

  // Instantiate the viewer
  Viewer viewer;
  Observer observer(viewer);

  //Observer gets the viewer's camera as an outsideCamera
  observer.setOutsideCamera(viewer.camera());
  PlanesCamera* cam = new PlanesCamera(qreal(0.0001), qreal(1000.));
  observer.setCamera(cam) ;

  // Make sure every viewer movement updates the observer
   QObject::connect(viewer.camera()->frame(), SIGNAL(manipulated()), &observer,
					SLOT(update()));
   QObject::connect(viewer.camera()->frame(), SIGNAL(spun()), &observer,
					SLOT(update()));

  viewer.setWindowTitle("viewer");
  observer.setWindowTitle("observer");

  // Make the viewer window visible on screen.
  viewer.show();
  observer.show();

  // Run main loop.
  return application.exec();
}
