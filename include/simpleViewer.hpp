#include <QGLViewer/qglviewer.h>

#include <glm/glm.hpp>

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
    GLuint m_nb_indices;
    GLuint m_render_programID;
    int* m_pointer_to_index_triangles;
    bool m_mix = true;
};

