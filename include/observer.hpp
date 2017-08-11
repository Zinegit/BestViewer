/**
 * \file observer.hpp
 * \brief The observer class. Its job is to observe the viewer
 * \author Tom Mourot-Faraut
 * \version 1.0
 */

#ifndef OBSERVER_HPP
#define OBSERVER_HPP

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

// My files
#include "include/shader.hpp"
#include "include/barycenter.hpp"
#include "include/updateVisibleTriangles.hpp"
#include "include/frustumCulling.hpp"
#include "include/depthCulling.hpp"
#include "include/backFaceCulling.hpp"
#include "include/incircleDepthCulling.hpp"
#include "include/appearance.hpp"
#include "include/addColor.hpp"
#include "include/viewer.hpp"
#include "include/variableToShare.hpp"
#include "ply.h"
#include "dat.h"
#include "import_structure.h"

/**
 * \class PlanesCamera
 * \brief This class changes the z of far and near planes of the observer's camera
 */

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

/**
 * \class Observer
 * \brief This class is the viewer's viewer that let the user visualize what the viewer is visualizing. It is mainly used for debugging and does not make any calculus
 */

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
	/**
	 * \fn void draw()
	 * \brief This function is called repeatedly until the program is stopped. It draws the object according to how it is calculated in viewer
	 * \return void
	 */
	virtual void draw();

	/**
	 * \fn void init()
	 * \brief This function initializes the viewer, loads the object, shaders and generates buffers to send to the GPU
	 * \return void
	 */
	virtual void init();

	/**
	 * \fn void drawSurfaces()
	 * \brief This function draws the surfaces of the triangles composing the object
	 * \return void
	 */
	virtual void drawSurfaces();

	/**
	 * \fn void drawOutlines()
	 * \brief This function draws the outlines of the triangles composing the object
	 * \return void
	 */
	virtual void drawOutlines();
};

#endif // OBSERVER_HPP
