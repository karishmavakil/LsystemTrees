//adapted from tutorials on http://www.opengl-tutorial.org
#include "Window.hpp"
//GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <cstdlib>

const GLint WIDTH = 800, HEIGHT = 600;

GLFWwindow *createWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "L-systems", nullptr, nullptr);
    
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    
    if (nullptr == window) {
        std::cout <<"Failed to create GLFW window" <<std::endl;
        glfwTerminate();
                }
        glfwMakeContextCurrent(window);
        
        glewExperimental = GL_TRUE;
        if ( GLEW_OK != glewInit()) {
            std::cout <<"Failed to initialize GLEW" <<std::endl;
        }
        glViewport(0, 0, screenWidth, screenHeight);
    return window;
}