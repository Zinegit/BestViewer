/**
 * \file viewer.cpp
 * \brief The viewer whose job is to observe the object
 * \author Tom Mourot-Faraut
 * \version 1.0
 */

#include "include/viewer.hpp"

using namespace std;

/**
 * \fn void init()
 * \brief This function initializes the viewer, loads the object, shaders and generates buffers to send to the GPU
 *
 * \return void
 */
void Viewer::init()
{
	camera()->setType(qglviewer::Camera::ORTHOGRAPHIC);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// We made these functions better
	// Enable depth test
	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);
	//glCullFace( GL_BACK );
	//glEnable(GL_CULL_FACE);

	setKeyDescription(Qt::Key_L, "Toggles backface culling");
	setKeyDescription(Qt::Key_M, "Toggles frontline updating");
	setKeyDescription(Qt::Key_N, "Toggles partial frontline updating");
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

	// Create and compile our GLSL program from the shaders
	ShaderProgram shader_program;
	shader_program.loadShader(GL_VERTEX_SHADER, "../shaders/vertexShader.vert");
	shader_program.loadShader(GL_FRAGMENT_SHADER, "../shaders/fragmentShader.frag");
	m_var.render_programID = shader_program.getProgramId();

	// Dark red background
	glClearColor(0.2f, 0.0f, 0.0f, 0.0f);

	// Creation of VAO
	GLuint VertexArrayID;
	glGenVertexArrays(3, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// ////////////READING .PLY FILES//////////// //
	Ply ply;
	ply.readPly("../PLY_FILES/anneau_bin.ply");
	// Retrieve geometry
	m_var.vertex_positions = ply.getPos();
	// Retrieve topology
	m_var.index = ply.getIndex();
	// ////////////READING .PLY FILES//////////// //

//	// ////////////READING .DAT FILES//////////// //
//	std::vector<float> geometry_coarse_lvl;
//	std::vector<float> geometry_wanted_lvl;
//	std::vector<float> geometry_wanted_lvl_only;
//	std::vector<int> connectivity_coarse_lvl;
//	std::vector<int> connectivity_wanted_lvl;
//	Dat dat;
//	dat.readDat("../DAT_FILES/Teapot_Res3.dat");
//	readLvlXDat(dat,
//					 2,
//					 geometry_coarse_lvl,
//					 geometry_wanted_lvl,
//					 geometry_wanted_lvl_only,
//					 connectivity_coarse_lvl,
//					 connectivity_wanted_lvl);
//	// Retrieve geometry
//	m_var.m_vertex_positions = geometry_wanted_lvl;
//	// Retrieve topology
//	m_var.m_index = connectivity_wanted_lvl;
//	// ////////////READING .DAT FILES//////////// //

	m_var.colors.resize(m_var.index.size(), 1.f);
	m_var.triangles_to_show_t1.resize(m_var.index.size() / 3, 1);
	m_var.triangles_to_show_t2.resize(m_var.index.size() / 3, 1);

//	m_var.m_triangles_to_show_t1.reserve(m_var.m_index.size() / 3);
//	m_var.m_triangles_to_show_t2.reserve(m_var.m_index.size() / 3);
//	for (int i = 0; i < m_var.m_index.size() / 3 ; i++)
//	{
//		m_var.m_triangles_to_show_t1.push_back(1);
//		m_var.m_triangles_to_show_t2.push_back(1);
//	}
	// Get normal vertices
	m_var.normals = getNormals(m_var.vertex_positions, m_var.index);

	// Place viewer
	float max = *std::max_element(m_var.vertex_positions.begin(), m_var.vertex_positions.end());
	setSceneRadius(max);
	const qglviewer::Vec center = barycenter(m_var.vertex_positions);
	setSceneCenter(center);
	showEntireScene();

	m_var.nb_points_buffer = m_var.vertex_positions.size();
	// Create pointer to vector for glBufferData
	m_var.pointer_to_vertex_positions = m_var.vertex_positions.data();
	// Generate 1 buffer, put the resulting identifier in m_vertex_buffer
	glGenBuffers(1, &m_var.vertex_buffer);
	// The following commands will talk about our 'm_vertex_buffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_var.vertex_buffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, m_var.nb_points_buffer * sizeof(float), m_var.pointer_to_vertex_positions, GL_STATIC_DRAW);

	m_var.pointer_to_index_triangles = m_var.index_temp.data();
	m_var.nb_indices = m_var.index_temp.size();
	glGenBuffers(1, &m_var.index_triangles);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_var.index_triangles);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_var.nb_indices * sizeof(int), m_var.pointer_to_index_triangles, GL_STATIC_DRAW);

	glGenBuffers(1, &m_var.color_buffer);
	// Opens help window
	//help();
	std::list<MR_Face> multi_res_connectivity;
	m_var.halfedgeMesh.build(m_var.vertex_positions, m_var.index, multi_res_connectivity);
	m_var.predicted_vertex.resize(12, 0);
	m_var.true_vertex.resize(3, 0);
}

/**
 * \fn void keyPressEvent(QKeyEvent *e)
 * \brief This function records keystrokes. If the pressed key is L and is pressed 2 times, the colors of appearing/disappearing/frontline triangles are updated. If K is pressed, m_mix is set to true or false and make the object appear in filled form or in line form.
 *
 * \param e : the pressed key
 * \return void
 */
void Viewer::keyPressEvent(QKeyEvent *e)
{
	this->update();
	// Get event modifiers key
	const Qt::KeyboardModifiers modifiers = e->modifiers();

	// Bug avec glDisable(GL_CULL_FACE) depuis l'update vers qgl 2.7.0
	if (e->key() == Qt::Key_L)
	{
		if (m_var.recording)
		{
			m_var.triangles_to_show_t2 = m_var.triangles_to_show;
			m_var.triangles_status = appearance(m_var.triangles_to_show_t1, m_var.triangles_to_show_t2);
			m_var.frontline = getFrontLine(m_var.triangles_status, m_var.frontline_colors, m_var.halfedgeMesh);
			m_var.colors = colorize(m_var.triangles_status, m_var.vertex_positions, m_var.index, m_var.frontline_colors);
			m_var.recording = false;
		} else {
			m_var.triangles_to_show_t1 = m_var.triangles_to_show;
			m_var.recording = true;
		}
		update();
	}
	else if (e->key() == Qt::Key_M)
	{
		updateFrontLine(m_var.frontline, m_var.triangles_status, m_var.frontline_colors, m_var.halfedgeMesh);
		m_var.colors = colorize(m_var.triangles_status, m_var.vertex_positions, m_var.index, m_var.frontline_colors);
		update();
	}
	else if (e->key() == Qt::Key_N)
	{
		if (!m_var.frontline.empty())
		{
			TempUpdateFrontLine(m_var.frontline, m_var.triangles_status, m_var.vertex_positions, m_var.index, m_var.frontline_colors, m_var.halfedgeMesh, m_var.true_vertex, m_var.predicted_vertex);
			m_var.colors = colorize(m_var.triangles_status, m_var.vertex_positions, m_var.index, m_var.frontline_colors);
			update();
		}
	}
	else if (e->key() == Qt::Key_K)
	{
		if (m_var.mix)
		{
			m_var.mix = false;
		} else {
			m_var.mix = true;
		}
		update();
	}
	else
		QGLViewer::keyPressEvent(e);
}

/**
 * \fn void drawOutlines()
 * \brief This function draws the outlines of the triangles composing the object
 *
 * \return void
 */
void Viewer::drawOutlines()
{
	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_var.vertex_buffer);
	glVertexAttribPointer(
	   0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
	   3,                  // size
	   GL_FLOAT,           // type
	   GL_FALSE,           // normalized?
	   0,                  // stride
	   (void*)0            // array buffer offset
	);

	if (m_var.mix)// Set object color to black
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

	// Conflict with shader
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDrawElements(GL_TRIANGLES, m_var.nb_indices, GL_UNSIGNED_INT, NULL);

	glDisable(GL_POLYGON_OFFSET_LINE);

	glDisableVertexAttribArray(0);
}

/**
 * \fn void drawSurfaces()
 * \brief This function draws the surfaces of the triangles composing the object
 *
 * \return void
 */
void Viewer::drawSurfaces()
{
	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_var.vertex_buffer);
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
	glBindBuffer(GL_ARRAY_BUFFER, m_var.color_buffer);
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
	glDrawElements(GL_TRIANGLES, m_var.nb_indices, GL_UNSIGNED_INT, NULL);
	glDisableVertexAttribArray(0);
}

/**
 * \fn void draw()
 * \brief This function is called repeatedly until the program is stopped. It draws the object according to how it is manipulated.

 * \return void
 */
void Viewer::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::dmat4 mvp_matrix_d;
	this -> camera() -> getModelViewProjectionMatrix(glm::value_ptr(mvp_matrix_d));

	glm::mat4 mvp_matrix_o;
	for(int j = 0; j < 4; ++j)
	{
		for(int k = 0; k < 4; ++k)
		{
			mvp_matrix_o[j][k] = (GLfloat)mvp_matrix_d[j][k];
		}
	}
	// Use our shader
	glUseProgram(m_var.render_programID);

	// Send our transformation to the currently bound shader,
	// in the "MVP" uniform
	glUniformMatrix4fv(glGetUniformLocation(m_var.render_programID, "MVP"), 1, GL_FALSE, value_ptr(mvp_matrix_o));  //&MVP[0][0]

	this -> camera() -> getFrustumPlanesCoefficients(m_var.plane_coefficients);

	m_var.near_projected_vertex_positions = project(m_var.vertex_positions, m_var.plane_coefficients, 3);

	// Get viewer's viewing direction
	qglviewer::Vec viewer_dir = camera() -> viewDirection();

	glm::mat4 mvp_matrix_o2;
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
	// Send our transformation to the currently bound shader,
	// in the "MVP" uniform
	glUniformMatrix4fv(glGetUniformLocation(m_var.render_programID, "MVP2"), 1, GL_FALSE, value_ptr(mvp_matrix_o2));  //&MVP[0][0]

	m_var.front_face_triangles = isFrontFace(viewer_dir, m_var.normals);
	m_var.inside_frustum_triangles = areInsideFrustum(m_var.vertex_positions, m_var.index, m_var.plane_coefficients);
	// Depth culling
	//m_first_plane_triangles = notOccultedTriangles(m_near_projected_vertex_positions, m_vertex_positions, m_index, plane_coefficients);
	// Only display frontface triangles
	//m_index_temp = updateIndex(m_front_face_triangles, m_index);
	// Only display triangles in the frustum
	//m_index_temp = updateIndex(m_inside_frustum_triangles, m_index);
	// Only display occulted triangles
	//m_index_temp = updateIndex(m_first_plane_triangles, m_index);
	m_var.triangles_to_show = fusionBools(m_var.front_face_triangles, m_var.inside_frustum_triangles);
	// Display combination of both
	m_var.index_temp = updateIndex(m_var.triangles_to_show, m_var.index);

	m_var.pointer_to_colors = m_var.colors.data();
	glBindBuffer(GL_ARRAY_BUFFER, m_var.color_buffer);
	glBufferData(GL_ARRAY_BUFFER, m_var.nb_points_buffer * sizeof(float), m_var.pointer_to_colors, GL_STATIC_DRAW);

	m_var.pointer_to_index_triangles = m_var.index_temp.data();
	m_var.nb_indices = m_var.index_temp.size();
	glGenBuffers(1, &m_var.index_triangles);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_var.index_triangles);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_var.nb_indices * sizeof(int), m_var.pointer_to_index_triangles, GL_STATIC_DRAW);
	if (m_var.mix)
	{
		drawSurfaces();
	}
	glUseProgram(0);
	drawOutlines();
	glUseProgram(m_var.render_programID);

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(m_var.predicted_vertex[0], m_var.predicted_vertex[1], m_var.predicted_vertex[2]+0.01);
	glVertex3f(m_var.predicted_vertex[3], m_var.predicted_vertex[4], m_var.predicted_vertex[5]+0.01);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(m_var.predicted_vertex[6], m_var.predicted_vertex[7], m_var.predicted_vertex[8]+0.01);
	glVertex3f(m_var.predicted_vertex[3], m_var.predicted_vertex[4], m_var.predicted_vertex[5]+0.01);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(m_var.predicted_vertex[0], m_var.predicted_vertex[1], m_var.predicted_vertex[2]+0.01);
	glVertex3f(m_var.predicted_vertex[9], m_var.predicted_vertex[10], m_var.predicted_vertex[11]+0.01);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(m_var.predicted_vertex[6], m_var.predicted_vertex[7], m_var.predicted_vertex[8]+0.01);
	glVertex3f(m_var.predicted_vertex[9], m_var.predicted_vertex[10], m_var.predicted_vertex[11]+0.01);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(m_var.true_vertex[0], m_var.true_vertex[1], m_var.true_vertex[2]+0.01);
	glEnd();
}

/**
 * \fn QString Viewer::helpString() const {
 * \brief This function opens a help windows
 * \return a help window
 */
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
