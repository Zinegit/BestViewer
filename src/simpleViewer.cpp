#include "include/simpleViewer.hpp"
#include "include/globalVariables.hpp"

using namespace std;



//vector<bool> isHidden(vector<float> positions)
//{
//}

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

	// Dark red background
	glClearColor(0.2f, 0.0f, 0.0f, 0.0f);

	// Creation of VAO
	GLuint VertexArrayID;
	glGenVertexArrays(2, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	if (!observed_camera)
	{
//		// ////////////READING .PLY FILES//////////// //
//		Ply ply;
//		ply.readPly("../PLY_FILES/skull.ply");
//		// Retrieve geometry
//		m_vertex_positions = ply.getPos();
//		// Retrieve topology
//		m_index = ply.getIndex();
//		// ////////////READING .PLY FILES//////////// //

		// ////////////READING .DAT FILES//////////// //
		Dat dat;
		dat.readDat("../DAT_FILES/Anneau_Res3.dat", 0);
		// Retrieve geometry
		m_vertex_positions = dat.getPos();
		// Retrieve topology
		m_index = dat.getIndex();
		// ////////////READING .DAT FILES//////////// //


		// Get normal vertices
		m_normals = getNormals(m_vertex_positions, m_index);

		// Get camera's viewing direction
		qglviewer::Vec viewer_dir = camera() -> viewDirection();

		m_front_face_triangles = isFrontFace(viewer_dir, m_normals);
		m_inside_frustum_triangles = areInsideFrustum(m_vertex_positions, m_index, plane_coefficients);
		// Only display frontface triangles
		//m_index_temp = updateIndex(m_front_face_triangles, m_index);
		// Only display triangles in the frustum
		//m_index_temp = updateIndex(m_inside_frustum_triangles, m_index);
		m_triangles_to_show = fusionBools(m_front_face_triangles, m_inside_frustum_triangles);
		m_index_temp = updateIndex(m_triangles_to_show, m_index);

		m_nb_points_buffer = m_vertex_positions.size();
		// Create pointer to vector for glBufferData
		m_pointer_to_vertex_positions = m_vertex_positions.data();
		// Generate 1 buffer, put the resulting identifier in m_vertex_buffer
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



	//Main viewer configuration

//    // Import camera skin
//    // Need to change every coordinate to fit the viewer's camera's place
//    dat.readDat("../DAT_FILES/rabbit1.dat", 0);
//    m_vertex_positions_cam = dat.getPos();
//    m_index_cam = dat.getIndex();
//    m_nb_points_buffer_cam = m_vertex_positions_cam.size();
//    m_pointer_to_vertex_positions_cam = m_vertex_positions_cam.data();
//    glGenBuffers(1, &m_vertex_buffer_cam);
//    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_cam);
//    glBufferData(GL_ARRAY_BUFFER, m_nb_points_buffer_cam * sizeof(float), m_pointer_to_vertex_positions_cam, GL_STATIC_DRAW);
//    m_pointer_to_index_triangles_cam = m_index_cam.data();
//    m_nb_indices_cam = m_index_cam.size();
//    glGenBuffers(1, &m_index_triangles_cam);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_triangles_cam);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_nb_indices_cam * sizeof(int), m_pointer_to_index_triangles_cam, GL_STATIC_DRAW);



	if (observed_camera)
	{
		// Place observer
		setSceneRadius(20.0);
		camera() -> setViewDirection(qglviewer::Vec(0.0, -1.0, 0.0));
		showEntireScene();
	}
	else
	{
		// Place main viewer
		// Show the entire scene from the beginning
		float max = *std::max_element(m_vertex_positions.begin(), m_vertex_positions.end());
		setSceneRadius(max);
		const qglviewer::Vec center = barycenter(m_vertex_positions);
		setSceneCenter(center);
		showEntireScene();
	}
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
		if(!glIsEnabled(GL_CULL_FACE))
		{
			glEnable(GL_CULL_FACE);
		} else {
			glDisable(GL_CULL_FACE);
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
	glEnable(GL_BLEND);
	glLineWidth(2.0f);
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

	glColor3f(1,1,1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawElements(GL_TRIANGLES, m_nb_indices, GL_UNSIGNED_INT, NULL);
	glDisableVertexAttribArray(0);
}

//void Viewer::drawCam()
//{
//    // Use our shader
//    //glUseProgram(m_program_id);

//    // 1rst attribute buffer : vertices
//    glEnableVertexAttribArray(0);
//    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_cam);
//    glVertexAttribPointer(
//       0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
//       3,                  // size
//       GL_FLOAT,           // type
//       GL_FALSE,           // normalized?
//       0,                  // stride
//       (void*)0            // array buffer offset
//    );

//    glColor3f(1,1,1);
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//    glDrawElements(GL_TRIANGLES, m_nb_indices_cam, GL_UNSIGNED_INT, NULL);
//    glDisableVertexAttribArray(0);
//}


void Viewer::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (!observed_camera)
	{
		// Get viewer's viewing direction
		qglviewer::Vec viewer_dir = camera() -> viewDirection();

		m_front_face_triangles = isFrontFace(viewer_dir, m_normals);

		m_inside_frustum_triangles = areInsideFrustum(m_vertex_positions, m_index, plane_coefficients);
		// Only display frontface triangles
		//m_index_temp = updateIndex(m_front_face_triangles, m_index);
		// Only display triangles in the frustum
		//m_index_temp = updateIndex(m_inside_frustum_triangles, m_index);
		m_triangles_to_show = fusionBools(m_front_face_triangles, m_inside_frustum_triangles);
		// Display combination of both
		m_index_temp = updateIndex(m_triangles_to_show, m_index);

	}
	else if (observed_camera)
	{
		// Draw viewer's camera orientation
		glColor3f(1.0, 0.0, 0.0);
		observed_camera -> draw();

		qglviewer::Vec out_dir = observed_camera -> viewDirection();
		qglviewer::Vec out_pos = observed_camera -> position();

		observed_camera -> getFrustumPlanesCoefficients(plane_coefficients);
		//drawCam();
	}
	m_pointer_to_index_triangles = m_index_temp.data();
	m_nb_indices = m_index_temp.size();
	glGenBuffers(1, &m_index_triangles);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_triangles);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_nb_indices * sizeof(int), m_pointer_to_index_triangles, GL_STATIC_DRAW);
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

