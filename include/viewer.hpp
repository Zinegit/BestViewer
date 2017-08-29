/**
 * \file viewer.hpp
 * \brief The viewer whose job is to observe the object
 * \author Tom Mourot-Faraut
 * \version 1.0
 */

#ifndef VIEWER_HPP
#define VIEWER_HPP

// Include GLEW
#include <GL/glew.h>

// Include basic libraries
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <cstring>
#include <algorithm>


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
#include "include/statistics.hpp"
#include "include/toTxt.hpp"
#include "include/coefficients.hpp"
#include "include/texture.hpp"
#include "include/objLoader.hpp"
#include "ply.h"
#include "dat.h"
#include "import_structure.h"
#include "halfedgemesh.h"
#include "QGLViewer/manipulatedCameraFrame.h"

/**
 * \class Viewer
 * \brief This class is the viewer that let the user visualize the object. It also uses all the functions made for culling and so on
 */
class Viewer : public QGLViewer
{
private:
	variable_to_share m_var;
	bool debug_mode = false;
	void (Viewer::*drawSurfaces)();
	std::string file_path;

protected:

	/**
	 * \fn void draw()
	 * \brief This function is called repeatedly until the program is stopped. It draws the object according to how it is manipulated.
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
	 * \fn int typeFile(std::string& file_path);
	 * \brief This function indicates the type of file to read
	 * \return the number corresponding to the type of file (ply, dat, obj...)
	 */
	virtual int typeFile(const std::__cxx11::string &file_path);

	virtual void drawSurfacesColor();

	virtual void drawSurfacesTexture();

	/**
	 * \fn void drawOutlines()
	 * \brief This function draws the outlines of the triangles composing the object
	 * \return void
	 */
	virtual void drawOutlines();

	/**
	 * \fn void keyPressEvent(QKeyEvent *e)
	 * \brief This function records keystrokes. If the pressed key is L and is pressed 2 times, the colors of appearing/disappearing/frontline triangles are updated. If K is pressed, m_mix is set to true or false and make the object appear in filled form or in line form.
	 * \brief If the pressed key is M all triangles are predicted. If the pressed key is N then the prediction is made triangle by triangle
	 * \param e : the pressed key
	 * \return void
	 */
	virtual void keyPressEvent(QKeyEvent *e);

	/**
	 * \fn QString Viewer::helpString() const {
	 * \brief This function opens a help windows
	 * \return a help window
	 */
	virtual QString helpString() const;

public:
	variable_to_share* getVariableToShare()
	{
		return &m_var;
	}

	Viewer(std::string file, bool debug = false)
	{
		file_path = file;
		debug_mode = debug;
	}

	void changeVisual()
	{
		m_var.mix = !m_var.mix;
	}

	void record();

	void predictStep();

	void predict();
};

#endif // VIEWER_HPP
