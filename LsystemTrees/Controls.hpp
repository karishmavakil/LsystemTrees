//
//  Controls.hpp
//  LsystemTrees
//
//  Created by Karishma Vakil on 30/01/2018.
//  Copyright © 2018 Karishma Vakil. All rights reserved.
//

#ifndef Controls_hpp
#define Controls_hpp

#include <stdio.h>
// Include GLM
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
using namespace glm;
// Include GLFW
#include <GLFW/glfw3.h>
void computeMatricesFromInputs(GLFWwindow* window);
mat4 getViewMatrix();
vec3 getLightPos();

#endif /* Controls_hpp */
