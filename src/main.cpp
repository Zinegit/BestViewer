#include <GL/glew.h>
#include <qapplication.h>
#include <stdio.h>
#include <stdlib.h>

#include "include/getNormals.hpp"
#include "include/simpleViewer.hpp"
#include <QGLViewer/manipulatedCameraFrame.h>

using namespace qglviewer;

int main(int argc, char **argv) {
  // Read command lines arguments.
  QApplication application(argc, argv);

  // Instantiate the viewer.
  Viewer viewer;
  Viewer observer;

  // Observer gets a outsideCamera
  observer.setOutsideCamera(viewer.camera());

  //qglviewer::Vec pos = viewer.camera() -> position();

  // Make sure every Camera movement updates the observer
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

