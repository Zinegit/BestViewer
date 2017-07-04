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

#include "include/simpleViewer.hpp"
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

using namespace std;

void Viewer::init()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it's closer to the camera than the former one
    glDepthFunc(GL_LESS);
    glCullFace( GL_BACK );
    glEnable(GL_CULL_FACE);

    // Set 'L' as the key to enable backface culling
    setKeyDescription(Qt::Key_L, "Toggles backface culling");
    // Set 'K' as the key to mix between fill and line
    setKeyDescription(Qt::Key_K, "Toggles surface filling");

    // Enlighten everything (not just the well-oriented faces of the triangles)
    // Light setup
     glDisable(GL_LIGHT0);
     glEnable(GL_LIGHT1);

     // Light default parameters
     const GLfloat light_ambient[4] = {1.0, 1.0, 1.0, 1.0};
     const GLfloat light_specular[4] = {1.0, 1.0, 1.0, 1.0};
     const GLfloat light_diffuse[4] = {1.0, 1.0, 1.0, 1.0};

     glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 3.0);
     glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 10.0);
     glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.1f);
     glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.3f);
     glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.3f);
     glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
     glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
     glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK)
    {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return;
    }
    // Dark red background
    glClearColor(0.2f, 0.0f, 0.0f, 0.0f);

    // Creation of VAO
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);


    /*// ////////////READING .PLY FILES//////////// //
    // Geometry
    vector<float> vertex_positions;
    // Topology
    vector<int> index_triangles;
    Ply ply;
    ply.readPly("../PLY_FILES/anneau_bin.ply");
    // Retrieve geometry
    vertex_positions = ply.getPos();
    // Retrieve topology
    index_triangles = ply.getIndex();
    // ////////////READING .PLY FILES//////////// //*/


    // ////////////READING .DAT FILES//////////// //
    // Geometry
    vector<float> vertex_positions;
    // Topology
    vector<int> index_triangles;
    Dat dat;
    dat.readDat("../DAT_FILES/Anneau_Res3.dat", 0);
    // Retrieve geometry
    vertex_positions = dat.getPos();
    // Retrieve topology
    index_triangles = dat.getIndex();
    // ////////////READING .DAT FILES//////////// //

    // Get normal vertices
    vector<float> normals = getBackTriangles(vertex_positions, index_triangles);


    m_nb_points_buffer = vertex_positions.size();
    // Create pointer to vector for glBufferData
    float *pointer_to_vertex_positions = vertex_positions.data();
    // Generate 1 buffer, put the resulting identifier in m_vertex_buffer
    glGenBuffers(1, &m_vertex_buffer);
    // The following commands will talk about our 'm_vertex_buffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, m_nb_points_buffer * sizeof(float), pointer_to_vertex_positions, GL_STATIC_DRAW);


    m_pointer_to_index_triangles = index_triangles.data();
    m_nb_indices = index_triangles.size();


    glGenBuffers(1, &m_index_triangles);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_triangles);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_nb_indices * sizeof(int), m_pointer_to_index_triangles, GL_STATIC_DRAW);

    //Show the entire scene from the beginning
    float max = *std::max_element(vertex_positions.begin(), vertex_positions.end());
    setSceneRadius(max);
    const qglviewer::Vec center = barycentre(vertex_positions);
    setSceneCenter(center);
    showEntireScene();
    // Opens help window
    help();
}

void Viewer::keyPressEvent(QKeyEvent *e)
{
	// Get event modifiers key
	const Qt::KeyboardModifiers modifiers = e->modifiers();

	bool handled = false;
    // Bug avec glDisable(GL_CULL_FACE) depuis l'update vers qgl 2.7.0
    if (e->key() == Qt::Key_L)
    {
        if(glIsEnabled(GL_CULL_FACE))
        {
            glDisable(GL_CULL_FACE);
            cout << " disabled " << endl;
        } else {
            glEnable(GL_CULL_FACE);
            cout << " enabled " << endl;
        }
    }
    else if ((e->key() == Qt::Key_K))
	{
		if (m_mix)
		{
			m_mix = false;
		} else {
			m_mix = true;
		}
        handled = true;
    }
    if(!handled)
		QGLViewer::keyPressEvent(e);
}

void Viewer::drawOutlines()
{
    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
    glVertexAttribPointer(
       0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
       3,                  // size
       GL_FLOAT,           // type
       GL_FALSE,           // normalized?
       0,                  // stride
       (void*)0            // array buffer offset
    );

    if (m_mix)// Set object color to black
        glColor3f(0,0,0);
    else
        glColor3f(1,1,1);
    // Draw black outline
    // Draw black wireframe version of geometry
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // Shift depth values
    glPolygonOffset(-0.1f, -1.0f);
    glEnable(GL_POLYGON_OFFSET_LINE);
    //Draw lines antialiased
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glLineWidth(2.5f);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    //glDrawArrays(GL_POINTS, 0, m_nb_indices);
    glDrawElements(GL_TRIANGLES, m_nb_indices, GL_UNSIGNED_INT, NULL);

    glDisable(GL_POLYGON_OFFSET_LINE);

    glDisableVertexAttribArray(0);
}


void Viewer::drawSurfaces()
{
	// Use our shader
	//glUseProgram(m_program_id);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
	glVertexAttribPointer(
	   0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
	   3,                  // size
	   GL_FLOAT,           // type
	   GL_FALSE,           // normalized?
	   0,                  // stride
	   (void*)0            // array buffer offset
	);

	// Set object color to white
	glColor3f(1,1,1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glDrawElements(GL_TRIANGLES, m_nb_indices, GL_UNSIGNED_INT, NULL);

	glDisableVertexAttribArray(0);
}

vector<bool> isFrontFace(qglviewer::Vec& direction, vector<float>& normals)
{
    vector<bool> frontFaceTriangles(normals.size(), 0);
    for (int i = 0; i < normals.size(); i += 3)
    {

    }
}

void Viewer::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Get camera's viewing direction
    qglviewer::Vec dir = camera() -> viewDirection();
    if (m_mix)
    {
        drawSurfaces();
    }
    drawOutlines();
}

QString Viewer::helpString() const {
	QString text("<h2>B e s t V i e w e r</h2>");
	text += "<b> First of all Press C </b> to deactivate auto frustum culling.<br> <br>";
	text += " Press <b> L </b> to enable/disable backface culling.<br> <br> ";
	text += " Press <b> K </b> to fill the surfaces.<br> <br> ";
	text += "Use the mouse to move the camera around the object. ";
	text += "You can respectively revolve around, zoom and translate with the "
			  "three mouse buttons. ";
	text += "Left and middle buttons pressed together rotate around the camera "
			  "view direction axis<br><br>";
	text += "Press <b>A</b> for the world axis ";
	text += "and <b>Control+S</b> to save "
			  "a snapshot. ";
	text += "Double clicks automates single click actions: A left button double "
			  "click aligns the closer axis with the camera (if close enough). ";
	text += "A middle button double click fits the zoom of the camera and the "
			  "right button re-centers the scene.<br><br>";
	text += "Press <b>Escape</b> to exit the viewer.";
	return text;
}

