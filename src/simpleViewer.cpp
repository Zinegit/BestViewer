#include "include/simpleViewer.hpp"
#include "include/globalVariables.hpp"

using namespace std;

void Viewer::init()
{
	camera()->setType(Camera::ORTHOGRAPHIC);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// We made these functions better
	// Enable depth test
	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);
	//glCullFace( GL_BACK );
	//glEnable(GL_CULL_FACE);

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

	// Create and compile our GLSL program from the shaders
	ShaderProgram shader_program;
	shader_program.loadShader(GL_VERTEX_SHADER, "../shaders/vertexShader.vert");
	shader_program.loadShader(GL_FRAGMENT_SHADER, "../shaders/fragmentShader.frag");
	m_render_programID = shader_program.getProgramId();

	// Dark red background
	glClearColor(0.2f, 0.0f, 0.0f, 0.0f);

	// Creation of VAO
	GLuint VertexArrayID;
	glGenVertexArrays(3, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	if (!observed_camera)
	{
		// ////////////READING .PLY FILES//////////// //
		Ply ply;
		ply.readPly("../PLY_FILES/cow.ply");
		// Retrieve geometry
		m_vertex_positions = ply.getPos();
		// Retrieve topology
		m_index = ply.getIndex();
		// ////////////READING .PLY FILES//////////// //

//		// ////////////READING .DAT FILES//////////// //
//		std::vector<float> geometry_coarse_lvl;
//		std::vector<float> geometry_wanted_lvl;
//		std::vector<float> geometry_wanted_lvl_only;
//		std::vector<int> connectivity_coarse_lvl;
//		std::vector<int> connectivity_wanted_lvl;
//		Dat dat;
//		dat.readDat("../DAT_FILES/rabbit2.dat");
//		readLvlXDat(dat,
//						 1,
//						 geometry_coarse_lvl,
//						 geometry_wanted_lvl,
//						 geometry_wanted_lvl_only,
//						 connectivity_coarse_lvl,
//						 connectivity_wanted_lvl);
//		// Retrieve geometry
//		m_vertex_positions = geometry_wanted_lvl;
//		// Retrieve topology
//		m_index = connectivity_wanted_lvl;
//		// ////////////READING .DAT FILES//////////// //

		m_triangles_to_show_t1.reserve(m_index.size() / 3);
		m_triangles_to_show_t2.reserve(m_index.size() / 3);
		for (int i = 0; i < m_index.size() / 3 ; i++)
		{
			m_triangles_to_show_t1.push_back(1);
			m_triangles_to_show_t2.push_back(1);
		}
		// Get normal vertices
		m_normals = getNormals(m_vertex_positions, m_index);

		m_nb_points_buffer = m_vertex_positions.size();
		// Create pointer to vector for glBufferData
		m_pointer_to_vertex_positions = m_vertex_positions.data();
		// Generate 1 buffer, put the resulting identifier in m_vertex_buffer

		// Place viewer
		float max = *std::max_element(m_vertex_positions.begin(), m_vertex_positions.end());
		setSceneRadius(max);
		const qglviewer::Vec center = barycenter(m_vertex_positions);
		setSceneCenter(center);
		showEntireScene();
	} else {
		// Place observer
		camera() -> setViewDirection(qglviewer::Vec(0.5, 0.5, 0.5));
		float max = 4 * *std::max_element(m_vertex_positions.begin(), m_vertex_positions.end());
		setSceneRadius(max);
		const qglviewer::Vec center = barycenter(m_vertex_positions);
		setSceneCenter(center);
		showEntireScene();
		//camera() -> getOrthoWidthHeight(halfWidth, halfHeight);
	}

	glGenBuffers(1, &m_vertex_buffer);
	// The following commands will talk about our 'm_vertex_buffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, m_nb_points_buffer * sizeof(float), m_pointer_to_vertex_positions, GL_STATIC_DRAW);

	m_pointer_to_index_triangles = m_index_temp.data();
	m_nb_indices = m_index_temp.size();
	glGenBuffers(1, &m_index_triangles);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_triangles);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_nb_indices * sizeof(int), m_pointer_to_index_triangles, GL_STATIC_DRAW);

	glGenBuffers(1, &m_color_buffer);
	// Opens help window
	//help();
}

void Viewer::keyPressEvent(QKeyEvent *e)
{
	this->update();
	// Get event modifiers key
	const Qt::KeyboardModifiers modifiers = e->modifiers();

	// Bug avec glDisable(GL_CULL_FACE) depuis l'update vers qgl 2.7.0
	if (e->key() == Qt::Key_L)
	{
		if(m_recording)
		{
			m_recording = false;
		} else {
			m_recording = true;
		}
		update();
	}
	else if ((e->key() == Qt::Key_K))
	{
		if (m_mix)
		{
			m_mix = false;
		} else {
			m_mix = true;
		}
		update();
	}
	else
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
	else // Set object color to white
		glColor3f(1,1,1);
	// Draw black wireframe version of geometry
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// Shift depth values (arbitrary)
	glPolygonOffset(-0.25f, -1.0f);
	glEnable(GL_POLYGON_OFFSET_LINE);
	//Draw lines antialiased
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(2.0f);

	// Conflict with shader
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDrawElements(GL_TRIANGLES, m_nb_indices, GL_UNSIGNED_INT, NULL);

	glDisable(GL_POLYGON_OFFSET_LINE);

	glDisableVertexAttribArray(0);
}

void Viewer::drawSurfaces()
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

	// 2nd attribute buffer : colors
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_color_buffer);
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
	glDrawElements(GL_TRIANGLES, m_nb_indices, GL_UNSIGNED_INT, NULL);
	glDisableVertexAttribArray(0);
}

void Viewer::draw()
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
	glUseProgram(m_render_programID);

	// Send our transformation to the currently bound shader,
	// in the "MVP" uniform
	glUniformMatrix4fv(glGetUniformLocation(m_render_programID, "MVP"), 1, GL_FALSE, value_ptr(mvp_matrix_o));  //&MVP[0][0]

	if (observed_camera)
	{

		glm::mat4 mvp_matrix_o2;

		glUseProgram(0);
		glColor3f(1.0, 0.0, 0.0);
		observed_camera -> draw();
		glUseProgram(m_render_programID);

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
		glUniformMatrix4fv(glGetUniformLocation(m_render_programID, "MVP2"), 1, GL_FALSE, value_ptr(mvp_matrix_o2));  //&MVP[0][0]
		observed_camera -> getFrustumPlanesCoefficients(plane_coefficients);
	}

	else
	{
		m_near_projected_vertex_positions = project(m_vertex_positions, plane_coefficients, 3);

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
		glUniformMatrix4fv(glGetUniformLocation(m_render_programID, "MVP2"), 1, GL_FALSE, value_ptr(mvp_matrix_o2));  //&MVP[0][0]

		m_front_face_triangles = isFrontFace(viewer_dir, m_normals);
		m_inside_frustum_triangles = areInsideFrustum(m_vertex_positions, m_index, plane_coefficients);
		// Depth culling
		//m_first_plane_triangles = notOccultedTriangles(m_near_projected_vertex_positions, m_vertex_positions, m_index, plane_coefficients);
		// Only display frontface triangles
		//m_index_temp = updateIndex(m_front_face_triangles, m_index);
		// Only display triangles in the frustum
		//m_index_temp = updateIndex(m_inside_frustum_triangles, m_index);
		// Only display occulted triangles
		//m_index_temp = updateIndex(m_first_plane_triangles, m_index);
		m_triangles_to_show = fusionBools(m_front_face_triangles, m_inside_frustum_triangles);
		// Display combination of both
		m_index_temp = updateIndex(m_triangles_to_show, m_index);
		if (m_recording)
		{
			for (int i = 0; i < m_triangles_to_show.size(); i++)
			{
				m_triangles_to_show_t1[i] = m_triangles_to_show_t2[i];
				m_triangles_to_show_t2[i] = m_triangles_to_show[i];
			}
			m_triangles_color = appearance(m_triangles_to_show_t1, m_triangles_to_show_t2);
			m_recording = false;
		}
	}
	m_colors = colorize( m_triangles_color, m_vertex_positions, m_index);
	m_pointer_to_colors = m_colors.data();
	glBindBuffer(GL_ARRAY_BUFFER, m_color_buffer);
	glBufferData(GL_ARRAY_BUFFER, m_nb_points_buffer * sizeof(float), m_pointer_to_colors, GL_STATIC_DRAW);

	m_pointer_to_index_triangles = m_index_temp.data();
	m_nb_indices = m_index_temp.size();
	glGenBuffers(1, &m_index_triangles);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_triangles);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_nb_indices * sizeof(int), m_pointer_to_index_triangles, GL_STATIC_DRAW);
	if (m_mix)
	{
		drawSurfaces();
	}
	glUseProgram(0);
	drawOutlines();
	glUseProgram(m_render_programID);
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
