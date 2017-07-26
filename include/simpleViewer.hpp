// Include basic libraries
#include <stdio.h>
#include <stdlib.h>
#include <chrono>

// Include GLEW
#include <GL/glew.h>

#include <QGLViewer/qglviewer.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>

// Display elements of vectors
#include <vector>
#include <iostream>

// Keypress
#include <QCursor>
#include <QKeyEvent>
#include <QMap>
#include <QMenu>
#include <QMouseEvent>

#include "include/shader.hpp"
#include "include/barycenter.hpp"
#include "include/normals.hpp"
#include "include/updateIndex.hpp"
#include "include/distanceToPlane.hpp"
#include "include/isInsideFrustum.hpp"
#include "include/areInsideFrustum.hpp"
#include "include/notOccultedTriangles.hpp"
#include "include/fusionBools.hpp"
#include "include/isFrontFace.hpp"
#include "include/incircle.hpp"
#include "include/projection.hpp"
#include "include/appearance.hpp"
#include "ply.h"
#include "dat.h"
#include "import_structure.h"

class outsideCamera;

class Viewer : public QGLViewer
{

public:
	void setOutsideCamera(qglviewer::Camera *oc) { observed_camera = oc;}

protected:
  virtual void draw();
  virtual void init();
  virtual void drawSurfaces();
  virtual void drawOutlines();
  // virtual void drawCam();
  virtual void keyPressEvent(QKeyEvent *e);
  virtual QString helpString() const;

private:
	qglviewer::Camera *observed_camera = NULL;

};

//class Observer : public QGLViewer
//{

//public:
//	void setOutsideCamera(qglviewer::Camera *oc) { observed_camera = oc;}

//protected:
//  virtual void draw();
//  virtual void init();
//  virtual void drawSurfaces();
//  virtual void drawOutlines();
//  // virtual void drawCam();
//  virtual void keyPressEvent(QKeyEvent *e);
//  virtual QString helpString() const;

//private:
//	qglviewer::Camera *observed_camera = NULL;

//};
