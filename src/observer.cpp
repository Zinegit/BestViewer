#include "include/observer.hpp"

using namespace std;

void Observer::init()
{
	camera() -> setType(qglviewer::Camera::ORTHOGRAPHIC);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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

	// Create and compile our GLSL program from the shaders
	ShaderProgram shader_program;
	shader_program.loadShader(GL_VERTEX_SHADER, "../shaders/vertexShader.vert");
	shader_program.loadShader(GL_FRAGMENT_SHADER, "../shaders/fragmentShader.frag");

	// Dark red background
	glClearColor(0.2f, 0.0f, 0.0f, 0.0f);

	// Creation of VAO
	GLuint VertexArrayID;
	glGenVertexArrays(3, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Place observer
	camera() -> setViewDirection(qglviewer::Vec(0.5, 0.5, 0.5));
	float max = 4 * *std::max_element(m_var -> vertex_positions.begin(), m_var -> vertex_positions.end());
	setSceneRadius(max);
	const qglviewer::Vec center = barycenter(m_var -> vertex_positions);
	setSceneCenter(center);
	showEntireScene();

	// Why not putting viewer and observer in the same context? (see qgl multiview example)

	glGenBuffers(1, &m_var -> vertex_buffer);
	// The following commands will talk about our 'm_vertex_buffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_var -> vertex_buffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, m_var -> nb_points_buffer * sizeof(float), m_var -> pointer_to_vertex_positions, GL_STATIC_DRAW);

	glGenBuffers(1, &m_var -> index_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_var -> index_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_var -> nb_indices * sizeof(int), m_var -> pointer_to_index_triangles, GL_STATIC_DRAW);

	glGenBuffers(1, &m_var -> color_buffer);

}

void Observer::drawOutlines()
{
	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_var -> vertex_buffer);
	glVertexAttribPointer(
	   0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
	   3,                  // size
	   GL_FLOAT,           // type
	   GL_FALSE,           // normalized?
	   0,                  // stride
	   (void*)0            // array buffer offset
	);

	if (m_var -> mix)// Set object color to black
		glColor3f(0,0,0);
	else // Set object color to white
		glColor3f(1,1,1);
	// Draw black wireframe version of geometry
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// Shift depth values (arbitrary)
	glPolygonOffset(-0.25f, -1.0f);
	glEnable(GL_POLYGON_OFFSET_LINE);
	//Draw lines antialiased
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(1.0f);

	glDrawElements(GL_TRIANGLES, m_var -> nb_indices, GL_UNSIGNED_INT, NULL);

	glDisable(GL_POLYGON_OFFSET_LINE);

	glDisableVertexAttribArray(0);
}

void Observer::drawSurfaces()
{
	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_var -> vertex_buffer);
	glVertexAttribPointer(
	   0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
	   3,                  // size
	   GL_FLOAT,           // type
	   GL_FALSE,           // normalized?
	   0,                  // stride
	   (void*)0            // array buffer offset
	);

	// 2nd attribute buffer : colors
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_var -> color_buffer);
	glVertexAttribPointer(
	    1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
	    3,                                // size
	    GL_FLOAT,                         // type
	    GL_FALSE,                         // normalized?
	    0,                                // stride
	    (void*)0                          // array buffer offset
	);

	glColor3f(1,1,1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawElements(GL_TRIANGLES, m_var -> nb_indices, GL_UNSIGNED_INT, NULL);
	glDisableVertexAttribArray(0);
}

void Observer::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::dmat4 mvp_matrix_d;
	this->camera()->getModelViewProjectionMatrix(glm::value_ptr(mvp_matrix_d));

	glm::mat4 mvp_matrix_o;
	for(int j = 0; j < 4; ++j)
	{
		for(int k = 0; k < 4; ++k)
		{
			mvp_matrix_o[j][k] = (GLfloat)mvp_matrix_d[j][k];
		}
	}
	// Use our shader
	glUseProgram(m_var -> render_programID);

	// Send our transformation to the currently bound shader,
	// in the "MVP" uniform
	glUniformMatrix4fv(glGetUniformLocation(m_var -> render_programID, "MVP"), 1, GL_FALSE, value_ptr(mvp_matrix_o));  //&MVP[0][0]


	glm::mat4 mvp_matrix_o2;

	glUseProgram(0);
	glColor3f(1.0, 0.0, 0.0);
	observed_camera -> draw();
	glUseProgram(m_var -> render_programID);

	for(int j = 0; j < 4; ++j)
	{
		for(int k = 0; k < 4; ++k)
		{
			mvp_matrix_o2[j][k] = 0;
		}
	}
	mvp_matrix_o2[0][0] = 1;
	mvp_matrix_o2[1][1] = 1;
	mvp_matrix_o2[2][2] = 1;
	mvp_matrix_o2[3][3] = 1;
	glUniformMatrix4fv(glGetUniformLocation(m_var -> render_programID, "MVP2"), 1, GL_FALSE, value_ptr(mvp_matrix_o2));  //&MVP[0][0]
	observed_camera -> getFrustumPlanesCoefficients(m_var -> plane_coefficients);

	glBindBuffer(GL_ARRAY_BUFFER, m_var -> color_buffer);
	glBufferData(GL_ARRAY_BUFFER, m_var -> nb_points_buffer * sizeof(float), m_var -> pointer_to_colors, GL_STATIC_DRAW);

	glGenBuffers(1, &m_var -> index_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_var -> index_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_var -> nb_indices * sizeof(int), m_var -> pointer_to_index_triangles, GL_STATIC_DRAW);
	if (m_var -> mix)
	{
		drawSurfaces();
	}
	glUseProgram(0);
	drawOutlines();
	glUseProgram(m_var -> render_programID);

}
