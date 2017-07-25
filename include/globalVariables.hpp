#include <QGLViewer/qglviewer.h>

using namespace qglviewer;

// This will identify our vertex buffer

std::vector<int> m_index;
std::vector<float> m_vertex_positions;
GLuint m_vertex_buffer;
GLuint m_nb_points_buffer;
GLuint m_index_triangles;
GLuint m_nb_indices;
//GLuint m_render_programID;
std::vector<float> m_normals;
int* m_pointer_to_index_triangles;
float* m_pointer_to_vertex_positions;
bool m_mix = true;
std::vector<bool> m_front_face_triangles;
std::vector<bool> m_inside_frustum_triangles;
std::vector<bool> m_first_plane_triangles;
std::vector<float> m_near_projected_vertex_positions;
std::vector<bool> m_triangles_to_show;
std::vector<int> m_index_temp;
GLdouble plane_coefficients[6][4];
int compteur = 0;
std::vector<bool> m_triangles_to_show_t1;
std::vector<bool> m_triangles_to_show_t2;

