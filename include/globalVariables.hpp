
#include <QGLViewer/qglviewer.h>

using namespace qglviewer;

// This will identify our vertex buffer

vector<int> m_index;
vector<float> m_vertex_positions;
GLuint m_vertex_buffer;
GLuint m_nb_points_buffer;
GLuint m_index_triangles;
GLuint m_nb_indices;
GLuint m_render_programID;
vector<float> m_normals;
int* m_pointer_to_index_triangles;
float* m_pointer_to_vertex_positions;
bool m_mix = false;
qglviewer::Vec m_dir;
vector<bool> m_front_face_triangles;
vector<int> m_index_temp;
qglviewer::Vec m_cam_pos;

// Import Cam
//vector<float> m_vertex_positions_cam;
//vector<int> m_index_cam;
//GLuint m_nb_points_buffer_cam;
//float* m_pointer_to_vertex_positions_cam;
//GLuint m_vertex_buffer_cam;
//int* m_pointer_to_index_triangles_cam;
//GLuint m_nb_indices_cam;
//GLuint m_index_triangles_cam;
