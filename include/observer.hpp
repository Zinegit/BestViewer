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
#include "include/addColor.hpp"
#include "include/viewer.hpp"
#include "include/variableToShare.hpp"
#include "ply.h"
#include "dat.h"
#include "import_structure.h"

class Viewer;

class PlanesCamera : public qglviewer::Camera
{
private:
	qreal m_znear;
	qreal m_zfar;

public:
	PlanesCamera(qreal z_near, qreal z_far){
		m_znear = z_near;
		m_zfar = z_far;
	}

	qreal zNear(){
		return m_znear;
	}

	qreal zFar(){
		return m_zfar;
	}

	void setZNear(qreal z_near){
		m_znear = z_near;
	}

	void setZFar(qreal z_far){
		m_zfar = z_far;
	}
};

class Observer : public QGLViewer
{
private:
	variable_to_share *m_var;
	qglviewer::Camera *observed_camera = NULL;

public:
	Observer(Viewer& viewer)
	{
		m_var = viewer.getVariableToShare();
	}
	void setOutsideCamera(qglviewer::Camera *oc) { observed_camera = oc;}

protected:
  virtual void draw();
  virtual void init();
  virtual void drawSurfaces();
  virtual void drawOutlines();
};
