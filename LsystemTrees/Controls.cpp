//
//  Controls.cpp
//  LsystemTrees
//
//  Created by Karishma Vakil on 30/01/2018.
//  Copyright © 2018 Karishma Vakil. All rights reserved.
//

#include "Controls.hpp"
// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
using namespace glm;

#include "controls.hpp"

mat4 ViewMatrix;
mat4 getViewMatrix(){
    return ViewMatrix;
}

// Initial position : on +Z
float radius = 16;
float height = -4.0f;
vec3 position = vec3( 0, height, radius );
float angle = 3.14f/2.0f;
float speed = 3.0f; // 3 units / second
vec3 LightPos = vec3( 16/ 2 * cos(angle - 3.14/5),
                                 0,
                     16 / 2 * sin(angle - 3.14/5));

vec3 getLightPos(){
    return LightPos;
}
void computeMatricesFromInputs(GLFWwindow* window){
    
    // glfwGetTime is called only once, the first time this function is called
    static double lastTime = glfwGetTime();
    
    // Compute time difference between current and last frame
    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime);
    
    // Move closer
    if (glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS){
        radius -= speed * deltaTime * 0.5;
    }
    // Move back
    if (glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS){
        radius += speed * deltaTime * 0.5;
    }
    // Move up
    if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS){
        height += speed * deltaTime * 0.5;
    }
    // Move down
    if (glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS){
        height -= speed * deltaTime * 0.5;
    }
    // Move right
    if (glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
        angle +=  speed * deltaTime * 0.5;
    }
    // Strafe left
    if (glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS){
        angle -=  speed * deltaTime * 0.5;
    }
    position = vec3(
                        radius * cos(angle),
                        height,
                        radius * sin(angle)
                        );
    LightPos = vec3( 16/ 2 * cos(angle - 3.14/5),
                    0,
                   16 / 2 * sin(angle - 3.14/5)
);
    // Camera matrix
    
    ViewMatrix       = lookAt(
                                   position,           // Camera is here
                                   vec3(0,-1,0), // and looks here : at the same position
                                   vec3(0,1,0)                  // Head is up (set to 0,-1,0 to look upside-down)
                                   );
    
    // For the next frame, the "last time" will be "now"
    lastTime = currentTime;
}