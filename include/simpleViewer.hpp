// Include basic libraries
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLM
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>

#include "include/shader.hpp"
#include "include/barycentre.hpp"
#include "include/getNormals.hpp"
#include "external/I3S-Meshing/ply.h"
#include "external/I3S-Meshing/dat.h"

// Display elements of vectors
#include <vector>
#include <iostream>

// Keypress
#include <QCursor>
#include <QKeyEvent>
#include <QMap>
#include <QMenu>
#include <QMouseEvent>

#include <math.h>
#include <boost/geometry.hpp>

#include <QGLViewer/qglviewer.h>

#include <glm/glm.hpp>

#include <Eigen/Dense>
#include <vector>


class outsideCamera;

class Viewer : public QGLViewer
{

public:
    void setOutsideCamera(qglviewer::Camera *oc) { outside_camera = oc;}

protected:
  virtual void draw();
  virtual void init();
  virtual void drawSurfaces();
  virtual void drawOutlines();
  // virtual void drawCam();
  virtual void keyPressEvent(QKeyEvent *e);
  virtual QString helpString() const;

private:
    qglviewer::Camera *outside_camera = NULL;

};

