/**
 * \file texture.hpp
 * \brief Load the textures
 * \author http://www.opengl-tutorial.org/fr/
 * \version 2.0
 */

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

/**
 * \fn GLuint loadBMP_custom(const char * imagepath);
 * \brief Load a .BMP file using our custom loader
 * \param imagepath : The path to the texture file
 * \return The ID of the texture created
 */
GLuint loadBMP_custom(const char * imagepath);


/**
 * \fn GLuint loadBMP_custom(const char * imagepath);
 * \brief // Since GLFW 3, glfwLoadTexture2D() has been removed. You have to use another texture loading library or do it yourself (just like loadBMP_custom and loadDDS). Load a .TGA file using GLFW's own loader
 * \param imagepath : The path to the texture file
 * \return The ID of the texture created
 */
//GLuint loadTGA_glfw(const char * imagepath);

/**
 * \fn GLuint loadBMP_custom(const char * imagepath);
 * \brief Load a .DDS file using GLFW's own loader
 * \param imagepath : The path to the texture file
 * \return The ID of the texture created
 */
GLuint loadDDS(const char * imagepath);

#endif
