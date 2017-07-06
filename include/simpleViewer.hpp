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


class Viewer : public QGLViewer
{
protected:
  virtual void draw();
  virtual void init();
  virtual void drawSurfaces();
  virtual void drawOutlines();
  virtual void keyPressEvent(QKeyEvent *e);
  virtual QString helpString() const;

    // This will identify our vertex buffer
private:
    GLuint m_vertex_buffer;
    GLuint m_nb_points_buffer;
    GLuint m_index_triangles;
    vector<int> m_index;
    vector<float> m_vertex_positions;
    GLuint m_nb_indices;
    GLuint m_render_programID;
    vector<float> m_normals;
    int* m_pointer_to_index_triangles;
    bool m_mix = false;
    qglviewer::Vec m_dir;
    vector<bool> m_front_face_triangles;
    vector<int> m_index_temp;

};

