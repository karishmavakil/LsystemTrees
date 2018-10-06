//adapted from tutorials on http://www.opengl-tutorial.org

#ifndef Window_hpp
#define Window_hpp

#include <stdio.h>
//GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>

GLFWwindow *createWindow();

#endif /* Window_hpp */
