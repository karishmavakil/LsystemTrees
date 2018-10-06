//adapted from tutorials on http://www.opengl-tutorial.org

#include "Controls.hpp"
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
using namespace glm;

mat4 ViewMatrix;
mat4 getViewMatrix(){
    return ViewMatrix;
}

// Initial position
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
    
    // time difference between curr and last frame
    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime);
    
    // move closer
    if (glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS){
        radius -= speed * deltaTime;
    }
    // move back
    if (glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS){
        radius += speed * deltaTime;
    }
    // move up
    if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS){
        height += speed * deltaTime;
    }
    // move down
    if (glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS){
        height -= speed * deltaTime;
    }
    // move right
    if (glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
        angle +=  speed * deltaTime;
    }
    // move left
    if (glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS){
        angle -=  speed * deltaTime;
    }
    position = vec3(
                        radius * cos(angle),
                        height,
                        radius * sin(angle)
                        );
    LightPos = vec3( 16 / 2 * cos(angle - 3.14/5),
                    0,
                   16 / 2 * sin(angle - 3.14/5)
);
    // camera matrix
    
    ViewMatrix       = lookAt(
                                   position,           // Camera is here
                                   vec3(0,-1,0), // and looks here : at the same position
                                   vec3(0,1,0)                  // Head is up (set to 0,-1,0 to look upside-down)
                                   );
    
    // For the next frame, the "last time" will be "now"
    lastTime = currentTime;
}