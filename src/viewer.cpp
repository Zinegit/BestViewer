#include "include/viewer.hpp"

int Viewer::typeFile(const std::string& file_path)
{
	std::string file_type;
	int i = 0;
	while (file_path[file_path.size() - i] != '.')
	{
		file_type += file_path[file_path.size() - i];
		i += 1;
	}
	reverse(file_type.begin(), file_type.end());
	if (file_type.compare("ply") == 1)
	{
		return 1;
	}
	else if (file_type.compare("dat") == 1)
		return 2;
	else if (file_type.compare("obj") == 1)
		return 3;
	else
	{
		std::cout << "Wrong type of file" << std::endl;
		return 0;
	}
}

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

	// Create our GLSL program from the shaders
	ShaderProgram shader_program;

	m_var.render_programID = shader_program.getProgramId();

	// Dark red background
	glClearColor(0.2f, 0.0f, 0.0f, 0.0f);

	// Creation of VAO
	GLuint VertexArrayID;
	glGenVertexArrays(3, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Read the file extension
	m_var.type_file = typeFile(file_path);
	// Read the file depending on the extension

	// Regular visioning of PLY FILES
//	if (m_var.type_file == 1)
//	{
//		shader_program.loadShader(GL_VERTEX_SHADER, "../shaders/vertexShader.vert");
//		shader_program.loadShader(GL_FRAGMENT_SHADER, "../shaders/fragmentShader.frag");
//		Ply ply;
//		ply.readPly(file_path);
//		// Retrieve geometry
//		m_var.vertices = ply.getPos();
//		// Retrieve topology
//		m_var.indices = ply.getIndex();
//		// Function pointer
//		drawSurfaces = &Viewer::drawSurfacesColor;

//		m_var.nb_vertices = m_var.vertices.size();
//		// Create pointer to vector for glBufferData
//		m_var.pointer_to_vertices = m_var.vertices.data();
//		// Generate 1 buffer, put the resulting identifier in m_vertex_buffer
//		glGenBuffers(1, &m_var.vertices_buffer);
//		// The following commands will talk about our 'm_vertex_buffer' buffer
//		glBindBuffer(GL_ARRAY_BUFFER, m_var.vertices_buffer);
//		// Give our vertices to OpenGL.
//		glBufferData(GL_ARRAY_BUFFER, m_var.nb_vertices * sizeof(float), m_var.pointer_to_vertices, GL_STATIC_DRAW);

//		std::list<MR_Face> multi_res_connectivity;
//		m_var.halfedgeMesh.build(m_var.vertices, m_var.indices, multi_res_connectivity);
//	}

	// Visualize PLY FILES and generates coeff files
	if (m_var.type_file == 1)
	{
		Ply ply;
		ply.readPly(file_path);
		m_var.vertices = ply.getPos();
		m_var.indices = ply.getIndex();

		shader_program.loadShader(GL_VERTEX_SHADER, "../shaders/vertexShader.vert");
		shader_program.loadShader(GL_FRAGMENT_SHADER, "../shaders/fragmentShader.frag");
		std::list<MR_Face> multiResConnectivity;	//Useless
		std::vector<int> depth_vertex_location;		//Useless
		m_var.depth = 1;

		m_var.old_halfedgeMesh.build(m_var.vertices, m_var.indices, multiResConnectivity);
		m_var.halfedgeMesh.build(m_var.vertices, m_var.indices, multiResConnectivity);

		m_var.vertices = m_var.halfedgeMesh.getNewVertPos();
		m_var.indices = m_var.halfedgeMesh.getTriangleIndices();

		// Information on the coarse model
		m_var.old_vertices = m_var.vertices;
		m_var.old_indices = m_var.indices;

		m_var.halfedgeMesh.subdiv(loop_lifted, m_var.depth, m_var.vertices, m_var.indices, depth_vertex_location, multiResConnectivity);

		drawSurfaces = &Viewer::drawSurfacesColor;

		m_var.nb_vertices = m_var.vertices.size();
		// Create pointer to vector for glBufferData
		m_var.pointer_to_vertices = m_var.vertices.data();
		// Generate 1 buffer, put the resulting identifier in m_vertex_buffer
		glGenBuffers(1, &m_var.vertices_buffer);
		// The following commands will talk about our 'm_vertex_buffer' buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_var.vertices_buffer);
		// Give our vertices to OpenGL.
		glBufferData(GL_ARRAY_BUFFER, m_var.nb_vertices * sizeof(float), m_var.pointer_to_vertices, GL_STATIC_DRAW);
	}
	// DAT FILES
	// Function readDat does not exist anymore. See with I3S_Meshing
//	else if (m_var.type_file == 2)
//	{
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
//		m_var.vertex_positions = geometry_wanted_lvl;
//		// Retrieve topology
//		m_var.index = connectivity_wanted_lvl;
//	}
	// OBJ FILES
	else if (m_var.type_file == 3)
	{
		shader_program.loadShader(GL_VERTEX_SHADER, "../shaders/texture.vert");
		shader_program.loadShader(GL_FRAGMENT_SHADER, "../shaders/texture.frag");
		// Need to replace m_var.indices with m_var.indexed_indices and m_var.vertices with m_var.indexed_vertices in buffer building
		// Normals are useless for us for now
		std::vector<float> in_vertices;
		std::vector<float> in_uvs;
		std::vector<float> in_normals;
		const char* file_path_obj = file_path.c_str();
		bool res = loadOBJ(file_path_obj, in_vertices, in_uvs, in_normals);
		std::vector<float> normals;
		indexVBO(in_vertices, in_uvs, in_normals, m_var.indices, m_var.vertices, m_var.uvs, normals);
		drawSurfaces = &Viewer::drawSurfacesTexture;
		// Create one OpenGL texture
		glGenTextures(1, &m_var.textureID);

		// "Bind" the newly created texture : all future texture functions will modify this texture
		glBindTexture(GL_TEXTURE_2D, m_var.textureID);

		//If you want to use BMP files, comment line "uv[1] = -uv[1];" in objLoader.cpp
		//m_var.Texture = loadBMP_custom("../TEXTURE_FILES/uvtemplate.bmp");
		//m_var.Texture = loadDDS("../TEXTURE_FILES/uvtemplate.DDS");
		m_var.Texture = loadDDS("../TEXTURE_FILES/uvmap.DDS");
		m_var.nb_uvs = m_var.uvs.size();
		m_var.pointer_to_uvs = m_var.uvs.data();
		glGenBuffers(1, &m_var.uvs_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_var.uvs_buffer);
		glBufferData(GL_ARRAY_BUFFER, m_var.nb_uvs * sizeof(float), m_var.pointer_to_uvs, GL_STATIC_DRAW);

		m_var.nb_vertices = m_var.vertices.size();
		// Create pointer to vector for glBufferData
		m_var.pointer_to_vertices = m_var.vertices.data();
		// Generate 1 buffer, put the resulting identifier in m_vertex_buffer
		glGenBuffers(1, &m_var.vertices_buffer);
		// The following commands will talk about our 'm_vertex_buffer' buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_var.vertices_buffer);
		// Give our vertices to OpenGL.
		glBufferData(GL_ARRAY_BUFFER, m_var.nb_vertices * sizeof(float), m_var.pointer_to_vertices, GL_STATIC_DRAW);
	}

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

	m_var.nb_indices = m_var.temp_indices.size();
	m_var.pointer_to_indices = m_var.temp_indices.data();
	glGenBuffers(1, &m_var.indices_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_var.indices_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_var.nb_indices * sizeof(int), m_var.pointer_to_indices, GL_STATIC_DRAW);

	glGenBuffers(1, &m_var.color_buffer);

	m_var.predicted_vertex.resize(12, 0);
	m_var.true_vertex.resize(3, 0);
}

void Viewer::record()
{
	if (Viewer::debug_mode)
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
}

void Viewer::predictStep()
{
	if (Viewer::debug_mode)
	{
		if (!m_var.frontline.empty())
		{
			TempUpdateFrontLine(m_var.frontline, m_var.triangles_status, m_var.vertices, m_var.indices, m_var.frontline_colors, m_var.halfedgeMesh, m_var.true_vertex, m_var.predicted_vertex);
			m_var.colors = colorize(m_var.triangles_status, m_var.vertices, m_var.indices, m_var.frontline_colors);
		}
	}
}

void Viewer::predict()
{
	if (Viewer::debug_mode)
	{
		std::vector<float> dist_true_predicted = updateFrontLine(m_var.frontline, m_var.triangles_status, m_var.frontline_colors, m_var.vertices, m_var.indices, m_var.halfedgeMesh);
		m_var.colors = colorize(m_var.triangles_status, m_var.vertices, m_var.indices, m_var.frontline_colors);
	}
}

void Viewer::keyPressEvent(QKeyEvent *e)
{
	if (Viewer::debug_mode)
	{
		this->update();
		// Get event modifiers key
		const Qt::KeyboardModifiers modifiers = e->modifiers();

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
			findCoefficients(m_var.vertices, m_var.indices, m_var.old_halfedgeMesh,	m_var.halfedgeMesh, m_var.depth);
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

void Viewer::drawSurfacesColor()
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

void Viewer::drawSurfacesTexture()
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
	// m_var.first_plane_triangles = notOccultedTriangles(m_var.near_projected_vertex_positions, m_var.vertices, m_var.indices, m_var.plane_coefficients);
	// Only display frontface triangles
	//m_var.temp_indices = updateIndex(m_var.front_face_triangles, m_var.indices);
	// Only display triangles in the frustum
	//m_var.temp_indices = updateIndex(m_var.inside_frustum_triangles, m_var.indices);
	// Only display not occulted triangles. Really slow
	//m_var.temp_indices = updateIndex(m_var.first_plane_triangles, m_var.indices);
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
	// Appeler une autre fonction (pointeur)
	if (m_var.mix)
	{
		(this->*drawSurfaces)();
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

	// Synchronize observer and viewer by sending a signal
	Q_EMIT this->drawNeeded();
}
