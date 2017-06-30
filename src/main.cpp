#include <GL/glew.h>
#include <qapplication.h>
#include <stdio.h>
#include <stdlib.h>
#include "include/simpleViewer.hpp"



int main(int argc, char **argv) {
  // Read command lines arguments.
  QApplication application(argc, argv);

  // Instantiate the viewer.
  Viewer viewer;

  viewer.setWindowTitle("bestViewer");

  // Make the viewer window visible on screen.
  viewer.show();

  // Run main loop.
  return application.exec();
}

