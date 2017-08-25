#include "include/viewer.hpp"

using namespace std;

void Viewer::init()
{
	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		return;
	}

	std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	camera()->setType(qglviewer::Camera::ORTHOGRAPHIC);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//We made these functions better
	//Enable depth test
	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);
	//glCullFace( GL_BACK );
	//glEnable(GL_CULL_FACE);

	setKeyDescription(Qt::Key_L, "Toggles backface culling");
	setKeyDescription(Qt::Key_M, "Toggles frontline updating");
	setKeyDescription(Qt::Key_N, "Toggles partial frontline updating");
	setKeyDescription(Qt::Key_T, "Produces the coefficients file");
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

	// Create and compile our GLSL program from the shaders
	ShaderProgram shader_program;
//	shader_program.loadShader(GL_VERTEX_SHADER, "../shaders/vertexShader.vert");
//	shader_program.loadShader(GL_FRAGMENT_SHADER, "../shaders/fragmentShader.frag");
	shader_program.loadShader(GL_VERTEX_SHADER, "../shaders/texture.vert");
	shader_program.loadShader(GL_FRAGMENT_SHADER, "../shaders/texture.frag");
	m_var.render_programID = shader_program.getProgramId();

	// Dark red background
	glClearColor(0.2f, 0.0f, 0.0f, 0.0f);

	// Creation of VAO
	GLuint VertexArrayID;
	glGenVertexArrays(3, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

//	// ////////////READING .PLY FILES//////////// //
//	Ply ply;
//	ply.readPly("../PLY_FILES/anneau_bin.ply");
//	// Retrieve geometry
//	m_var.vertex_positions = ply.getPos();
//	// Retrieve topology
//	m_var.index = ply.getIndex();
//	 // //////////READING .PLY FILES//////////// //

//	// ////////////READING .DAT FILES//////////// //
//	std::vector<float> geometry_coarse_lvl;
//	std::vector<float> geometry_wanted_lvl;
//	std::vector<float> geometry_wanted_lvl_only;
//	std::vector<int> connectivity_coarse_lvl;
//	std::vector<int> connectivity_wanted_lvl;
//	Dat dat;
//	dat.readDat("../DAT_FILES/rabbit2.dat");
//	readLvlXDat(dat,
//					 1,
//					 geometry_coarse_lvl,
//					 geometry_wanted_lvl,
//					 geometry_wanted_lvl_only,
//					 connectivity_coarse_lvl,
//					 connectivity_wanted_lvl);
//	m_var.vertex_positions = geometry_wanted_lvl;
//	m_var.index = connectivity_wanted_lvl;
//	// ////////////READING .DAT FILES//////////// //

	// ////////////READING .OBJ FILES//////////// //
	// Normals are useless for us for now
	std::vector<float> normals;
	bool res = loadOBJ("../OBJ_FILES/cube.obj", m_var.vertices, m_var.uvs, normals);

	std::vector<float> indexed_normals;
	indexVBO_slow(m_var.vertices, m_var.uvs, normals, m_var.indices, m_var.indexed_vertices, m_var.indexed_uvs, indexed_normals);
	std::cout << m_var.vertices.size() << " " << m_var.indexed_vertices.size() << " " << m_var.uvs.size() << " " << m_var.indexed_uvs.size() << " " << m_var.indices.size() << std::endl;
	for (int i : m_var.indices)
		std::cout << i << std::endl;
	// //////////READING .OBJ FILES///////////// //

	m_var.colors.resize(m_var.indices.size(), 1.f);
	m_var.triangles_to_show_t1.resize(m_var.indices.size() / 3, 1);
	m_var.triangles_to_show_t2.resize(m_var.indices.size() / 3, 1);

	// Get normal vertices
	m_var.normals = getNormals(m_var.vertices, m_var.indices);

	// Place viewer
	float max = *std::max_element(m_var.vertices.begin(), m_var.vertices.end());
	setSceneRadius(max);
	const qglviewer::Vec center = barycenter(m_var.vertices);
	setSceneCenter(center);
	showEntireScene();

	m_var.nb_vertices = m_var.indexed_vertices.size();
	// Create pointer to vector for glBufferData
	m_var.pointer_to_vertices = m_var.indexed_vertices.data();
	// Generate 1 buffer, put the resulting identifier in m_vertex_buffer
	glGenBuffers(1, &m_var.vertices_buffer);
	// The following commands will talk about our 'm_vertex_buffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_var.vertices_buffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, m_var.nb_vertices * sizeof(float), m_var.pointer_to_vertices, GL_STATIC_DRAW);

	m_var.nb_uvs = m_var.indexed_uvs.size();
	m_var.pointer_to_uvs = m_var.indexed_uvs.data();
	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, m_var.nb_uvs * sizeof(float), m_var.pointer_to_uvs, GL_STATIC_DRAW);

	m_var.nb_indices = m_var.temp_indices.size();
	m_var.pointer_to_indices = m_var.temp_indices.data();
	glGenBuffers(1, &m_var.indices_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_var.indices_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_var.nb_indices * sizeof(int), m_var.pointer_to_indices, GL_STATIC_DRAW);

	glGenBuffers(1, &m_var.color_buffer);
	// Opens help window
	// help();
	std::list<MR_Face> multi_res_connectivity;
	m_var.halfedgeMesh.build(m_var.vertices, m_var.indices, multi_res_connectivity);
	m_var.predicted_vertex.resize(12, 0);
	m_var.true_vertex.resize(3, 0);

	// Create one OpenGL texture
	glGenTextures(1, &m_var.textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, m_var.textureID);

	// If you want to use BMP files, comment line "uv[1] = -uv[1];" in objLoader.cpp
//	m_var.Texture = loadBMP_custom("../TEXTURE_FILES/uvtemplate.bmp");
//	m_var.Texture = loadDDS("../TEXTURE_FILES/uvtemplate.DDS");
	m_var.Texture = loadDDS("../TEXTURE_FILES/uvmap.DDS");
	m_var.pointer_to_uvs = m_var.uvs.data();
	glGenBuffers(1, &m_var.uvs_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_var.uvs_buffer);
	glBufferData(GL_ARRAY_BUFFER, m_var.nb_vertices * sizeof(float), m_var.pointer_to_uvs, GL_STATIC_DRAW);
}

void Viewer::record()
{
	if (m_var.recording)
	{
		m_var.triangles_to_show_t2 = m_var.triangles_to_show;
		m_var.triangles_status = appearance(m_var.triangles_to_show_t1, m_var.triangles_to_show_t2);
		m_var.frontline = getFrontLine(m_var.triangles_status, m_var.frontline_colors, m_var.halfedgeMesh);
		m_var.colors = colorize(m_var.triangles_status, m_var.vertices, m_var.indices, m_var.frontline_colors);
		m_var.recording = false;
	} else {
		m_var.triangles_to_show_t1 = m_var.triangles_to_show;
		m_var.recording = true;
	}
}

void Viewer::predictStep()
{
	if (!m_var.frontline.empty())
	{
		TempUpdateFrontLine(m_var.frontline, m_var.triangles_status, m_var.vertices, m_var.indices, m_var.frontline_colors, m_var.halfedgeMesh, m_var.true_vertex, m_var.predicted_vertex);
		m_var.colors = colorize(m_var.triangles_status, m_var.vertices, m_var.indices, m_var.frontline_colors);
	}
}

void Viewer::predict()
{
	std::vector<float> dist_true_predicted = updateFrontLine(m_var.frontline, m_var.triangles_status, m_var.frontline_colors, m_var.vertices, m_var.indices, m_var.halfedgeMesh);
	m_var.colors = colorize(m_var.triangles_status, m_var.vertices, m_var.indices, m_var.frontline_colors);
	exportToTxt(dist_true_predicted, "../analyses/data.txt");
}

void Viewer::keyPressEvent(QKeyEvent *e)
{
	if (Viewer::debug_mode)
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
				m_var.colors = colorize(m_var.triangles_status, m_var.vertices, m_var.indices, m_var.frontline_colors);
				m_var.recording = false;
			} else {
				m_var.triangles_to_show_t1 = m_var.triangles_to_show;
				m_var.recording = true;
			}
			update();
		}
		else if (e->key() == Qt::Key_M)
		{
			std::vector<float> dist_true_predicted = updateFrontLine(m_var.frontline, m_var.triangles_status, m_var.frontline_colors, m_var.vertices, m_var.indices, m_var.halfedgeMesh);
			m_var.colors = colorize(m_var.triangles_status, m_var.vertices, m_var.indices, m_var.frontline_colors);
			float mean_distances = mean(dist_true_predicted);
			exportToTxt(dist_true_predicted, "../analyses/data.txt");
			update();
		}
		else if (e->key() == Qt::Key_N)
		{
			if (!m_var.frontline.empty())
			{
				TempUpdateFrontLine(m_var.frontline, m_var.triangles_status, m_var.vertices, m_var.indices, m_var.frontline_colors, m_var.halfedgeMesh, m_var.true_vertex, m_var.predicted_vertex);
				m_var.colors = colorize(m_var.triangles_status, m_var.vertices, m_var.indices, m_var.frontline_colors);
				update();
			}
		}
		else if (e->key() == Qt::Key_T)
		{
			//findCoefficients(m_var.vertex_positions, m_var.index, m_var.triangles_status, m_var.halfedgeMesh);
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
}

void Viewer::drawOutlines()
{
	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_var.vertices_buffer);
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

void Viewer::drawSurfaces()
{
	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_var.vertices_buffer);
	glVertexAttribPointer(
	   0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
	   3,                  // size
	   GL_FLOAT,           // type
	   GL_FALSE,           // normalized?
	   0,                  // stride
	   (void*)0            // array buffer offset
	);

//	// 2nd attribute buffer : colors
//	glEnableVertexAttribArray(1);
//	glBindBuffer(GL_ARRAY_BUFFER, m_var.color_buffer);
//	glVertexAttribPointer(
//		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
//		3,                                // size
//		GL_FLOAT,                         // type
//		GL_FALSE,                         // normalized?
//		0,                                // stride
//		(void*)0                          // array buffer offset
//	);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_var.Texture);
	// Set our "myTextureSampler" sampler to user Texture Unit 0
	glUniform1i(m_var.textureID, 0);

	// 2nd bis attribute buffer : texture
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_var.uvs_buffer);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		2,                                // size
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
	glUniformMatrix4fv(glGetUniformLocation(m_var.render_programID, "MVP"), 1, GL_FALSE, glm::value_ptr(mvp_matrix_o));  //&MVP[0][0]

	this -> camera() -> getFrustumPlanesCoefficients(m_var.plane_coefficients);

	m_var.near_projected_vertex_positions = project(m_var.vertices, m_var.plane_coefficients, 3);

	// Get viewer's viewing direction
	qglviewer::Vec viewer_dir = camera() -> viewDirection();


	m_var.front_face_triangles = isFrontFace(viewer_dir, m_var.normals);
	m_var.inside_frustum_triangles = areInsideFrustum(m_var.vertices, m_var.indices, m_var.plane_coefficients);
	// Depth culling
	//m_first_plane_triangles = notOccultedTriangles(m_near_projected_vertex_positions, m_vertex_positions, m_index, plane_coefficients);
	// Only display frontface triangles
	//m_index_temp = updateIndex(m_front_face_triangles, m_index);
	// Only display triangles in the frustum
	//m_index_temp = updateIndex(m_inside_frustum_triangles, m_index);
	// Only display occulted triangles. Really slow
	//m_index_temp = updateIndex(m_first_plane_triangles, m_index);
	m_var.triangles_to_show = fusionBools(m_var.front_face_triangles, m_var.inside_frustum_triangles);
	// Display combination of both
	m_var.temp_indices = updateIndex(m_var.triangles_to_show, m_var.indices);

	m_var.pointer_to_colors = m_var.colors.data();
	glBindBuffer(GL_ARRAY_BUFFER, m_var.color_buffer);
	glBufferData(GL_ARRAY_BUFFER, m_var.nb_vertices * sizeof(float), m_var.pointer_to_colors, GL_STATIC_DRAW);

	m_var.pointer_to_indices = m_var.temp_indices.data();
	m_var.nb_indices = m_var.temp_indices.size();
	glGenBuffers(1, &m_var.indices_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_var.indices_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_var.nb_indices * sizeof(int), m_var.pointer_to_indices, GL_STATIC_DRAW);
	if (m_var.mix)
	{
		drawSurfaces();
	}
	glUseProgram(0);
	drawOutlines();
	glUseProgram(m_var.render_programID);

	// Display of predictions

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

//	glBegin(GL_LINES);
//	glVertex3f(m_var.predicted_vertex[9], m_var.predicted_vertex[10], m_var.predicted_vertex[11]);
//	glVertex3f(m_var.true_vertex[0], m_var.true_vertex[1], m_var.true_vertex[2]);
//	glEnd();

	// Synchronize observer and viewer
	Q_EMIT this->drawNeeded();
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
