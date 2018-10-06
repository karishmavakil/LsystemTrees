//adapted from tutorials on http://www.opengl-tutorial.org
#ifndef Controls_hpp
#define Controls_hpp

#include <stdio.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <GLFW/glfw3.h>
using namespace glm;

void computeMatricesFromInputs(GLFWwindow* window);
mat4 getViewMatrix();
vec3 getLightPos();

#endif /* Controls_hpp */