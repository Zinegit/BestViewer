#ifndef VIEWER_HPP
#define VIEWER_HPP

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
#include "include/updateVisibleTriangles.hpp"
#include "include/frustumCulling.hpp"
#include "include/depthCulling.hpp"
#include "include/backFaceCulling.hpp"
#include "include/incircleDepthCulling.hpp"
#include "include/appearance.hpp"
#include "include/addColor.hpp"
#include "include/variableToShare.hpp"
#include "include/frontLine.hpp"
#include "ply.h"
#include "dat.h"
#include "import_structure.h"
#include "halfedgemesh.h"

class Viewer : public QGLViewer
{
private:
	variable_to_share m_var;

protected:
  virtual void draw();
  virtual void init();
  virtual void drawSurfaces();
  virtual void drawOutlines();
  virtual void keyPressEvent(QKeyEvent *e);
  virtual QString helpString() const;

public:
	variable_to_share* getVariableToShare()
	{
		return &m_var;
	}

};


#endif // VIEWER_H
