/**
 * \file shader.hpp
 * \brief Load the shaders
 * \author Tom Mourot-Faraut
 * \version 1.0
 */

#ifndef SHADER_HPP
#define SHADER_HPP

/**
 * \class ShaderProgram
 * \brief This class is used to load the vertex and fragment shaders
 */
class ShaderProgram {
	GLuint m_program_id;

public:

	/**
	 * \fn ShaderProgram()
	 * \brief Constructor
	 */
	ShaderProgram();

	/**
	 * \fn ~ShaderProgram()
	 * \brief Destructor
	 */
	~ShaderProgram();

	/**
	 * \fn void loadShader(GLenum shaderType, const char* shader_file_path)
	 * \brief This function loads the fragment and vertex shaders given to it
	 * \param shaderType : The type of the shader
	 * \param shader_file_path : The path to the shader
	 * \return void
	 */
	void loadShader(GLenum shaderType, const char* file_path);

	/**
	 * \fn GLuint getProgramId()
	 * \brief get the program Id
	 * \return the program id
	 */
	GLuint getProgramId() { return m_program_id; }
};

#endif // SHADER_HPP
