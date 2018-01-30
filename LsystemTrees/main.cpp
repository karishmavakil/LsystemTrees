#include <iostream>
#define _USE_MATH_DEFINES

//GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>

// standard C++ libraries
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <vector>
#include <list>
#include <fstream>
#include <cstdlib>


#include "Window.hpp"
#include "Shaders.hpp"
#include "Turtle.hpp"
#include "Reader.hpp"
#include "Tests.hpp"

using namespace std;

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/ext.hpp"

using namespace glm;

int testGraphics() {
    
    GLFWwindow *window = createWindow();
    
    GLuint shaderProgram = LoadShaders("/Users/karishmavakil/Documents/Project/LSystemTrees/LSystemTrees/vert.shader", "/Users/karishmavakil/Documents/Project/LSystemTrees/LSystemTrees/frag.shader");
        
    // Get a handle for our "MVP" uniform
    GLuint MatrixID = glGetUniformLocation(shaderProgram, "MVP");
    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    mat4 Projection = perspective(radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    // Camera matrix
    mat4 View = lookAt(
                                 vec3(0,1,15), // Camera is at (4,3,3), in World Space
                                 vec3(0,0,0), // and looks at the origin
                                 vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
                                );
    // Model matrix : an identity matrix (model will be at the origin)
    mat4 Model      = mat4(1.0f);
   //mat4 Model = translate(mat4(), vec3(0.4f, 0.6f, 0.0f));
    mat4 MVP        = Projection * View * Model;

    
    GLfloat vertices[1000000] = {};
    GLfloat colors[1000000] = {};

    Turtle turtle = Turtle();
    turtle.setPosition(0.0f, -6.0f, 0.0f);
    LSystem tree = createLsystem("/Users/karishmavakil/Documents/Project/LSystemTrees/LSystemTrees/tree.txt");
    tree.applyRules(2);
    vector<vec3> vert = turtle.draw3D(tree.current);
    int i = 0 ;
    for (vector<vec3>::iterator it = vert.begin(); it != vert.end(); it++){
        vertices[i] = it->x;
        vertices[i+1] = it->y;
        vertices[i+2] = it->z;
        if (i%2==0){
            colors[i] = 0.0f;
            colors[i+1] = 0.8f;
            colors[i+2] = 0.0f;
        }
        else {
            colors[i] = 0.0f;
            colors[i+1] = 0.5f;
            colors[i+2] = 0.2f;
        }
        i+=3;
    }
    
    GLuint vertexbuffer, VAO;
    
    glGenVertexArrays( 1, &VAO);
    glGenBuffers(1, &vertexbuffer);
    
    glBindVertexArray(VAO);
    
    glBindBuffer( GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );
    
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 3 * sizeof( GLfloat), (GLvoid *) 0);
    glEnableVertexAttribArray(0);
    glBindBuffer( GL_ARRAY_BUFFER, 0);

    GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        
    
    glBindVertexArray( 0 );
    
    while ((!glfwWindowShouldClose(window))) {
        
        // Enable depth test
        glEnable(GL_DEPTH_TEST);
        // Accept fragment if it closer to the camera than the former one

        glDepthFunc(GL_LESS);
        glfwPollEvents();
        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear( GL_COLOR_BUFFER_BIT |  GL_DEPTH_BUFFER_BIT);
        
        glUseProgram( shaderProgram );
        
        // Send our transformation to the currently bound shader,
        // in the "MVP" uniform
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
        
        glBindVertexArray( VAO );
        glDrawArrays(GL_TRIANGLES, 0, 50000);
        glBindVertexArray(0);
        
        glfwSwapBuffers(window);
        
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteVertexArrays(1, &vertexbuffer);
    glDeleteVertexArrays(1, &colorbuffer);

    glfwTerminate();

    return 0;
}

int main () {
//    testTurtle();
//    testSymbol();
//    testList();
//    testLSystem();
    testGraphics();
//    testD0LSystemTurtle();
//    testReader();    
}


