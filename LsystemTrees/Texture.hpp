//adapted from tutorials on http://www.opengl-tutorial.org
#ifndef Texture_hpp
#define Texture_hpp
//GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>
#include <stdio.h>
// Load a .BMP file using our custom loader
GLuint loadBMP_custom(const char * imagepath);

#endif /* Texture_hpp */
