#include <GL/glew.h>
#include <qapplication.h>
#include <QGLViewer/manipulatedCameraFrame.h>

#include "include/simpleViewer.hpp"

int main(int argc, char **argv) {
  // Read command lines arguments.
  QApplication application(argc, argv);

  // Instantiate the viewer.
  Viewer viewer;
  Viewer observer;

  // Observer gets a outsideCamera
  observer.setOutsideCamera(viewer.camera());
  PlanesCamera* cam = new PlanesCamera(qreal(0.0001), qreal(1000.));
  observer.setCamera(cam) ;

  //qglviewer::Vec pos = viewer.camera() -> position();

  // Make sure every viewer movement updates the observer
   QObject::connect(viewer.camera()->frame(), SIGNAL(manipulated()), &observer,
					SLOT(update()));
   QObject::connect(viewer.camera()->frame(), SIGNAL(spun()), &observer,
					SLOT(update()));

  viewer.setWindowTitle("bestViewer");
  observer.setWindowTitle("observer");

  // Make the viewer window visible on screen.
  viewer.show();
  observer.show();

  // Run main loop.
  return application.exec();
}
