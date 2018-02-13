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
#include <sstream>

#include <stdexcept>
#include <cmath>
#include <vector>
#include <list>
#include <fstream>
#include <cstdlib>
#include <regex>
#include <random>

#include "Window.hpp"
#include "Shaders.hpp"
#include "Turtle.hpp"
#include "Tests.hpp"
#include "TurtleInterpreter.hpp"
#include "Controls.hpp"
#include "Parser.hpp"
#include "JSONReader.hpp"

using namespace std;

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/ext.hpp"
#include "json.hpp"

// for convenience
using json = nlohmann::json;

using namespace glm;


int testGraphics() {
    
    GLFWwindow *window = createWindow();
    
    GLuint shaderProgram = loadShaders("/Users/karishmavakil/Documents/Project/LSystemTrees/LSystemTrees/vert.shader", "/Users/karishmavakil/Documents/Project/LSystemTrees/LSystemTrees/frag.shader");
        
    // Get a handle for our "MVP" uniform
    GLuint MatrixID = glGetUniformLocation(shaderProgram, "MVP");
//    // Camera matrix
//    mat4 View = lookAt(
//                                 vec3(5,-2,15), // Camera is at (4,3,3), in World Space
//                                 vec3(0,0,0), // and looks at the origin
//                                 vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
//                                );
//    // Model matrix : an identity matrix (model will be at the origin)
    mat4 ModelMatrix      = mat4(1.0f);
    mat4 ProjectionMatrix = perspective(radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

    GLfloat vertices[1000000] = {};
    GLfloat colours[1000000] = {};
//    Turtle turtle = Turtle();
//    turtle.setPosition(0.0f, -6.0f, 0.0f);
//    
//    
//    LSystem tree = createLsystem("/Users/karishmavakil/Documents/Project/LSystemTrees/LSystemTrees/tree.txt");
//    tree.applyRules(4);
//    

    TurtleInterpreter interpreter= createInterpreter("/Users/karishmavakil/Documents/Project/LsystemTrees/LsystemTrees/tree1.json");
    interpreter.printVariables();

    interpreter.generateInformation();
    
    vector<vec3> vert = interpreter.getVertices();
    vector<vec3> col = interpreter.getColours();
    int i = 0;
    vector<vec3>::iterator itV;
    vector<vec3>::iterator itC;
    for (itV = vert.begin(), itC = col.begin(); itV != vert.end() || itC != col.end(); itV++, itC++, i++){
        vertices[3*i] = itV->x;
        vertices[3*i+1] = itV->y;
        vertices[3*i+2] = itV->z;
        colours[3*i] = itC->x;
        colours[3*i+1] = itC->y;
        colours[3*i+2] = itC->z;
    }

    GLuint VAO;
    glGenVertexArrays( 1, &VAO);
    glBindVertexArray(VAO);
    
    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer( GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 3 * sizeof( GLfloat), (GLvoid *) 0);
    glEnableVertexAttribArray(0);
    glBindBuffer( GL_ARRAY_BUFFER, 0);

    GLuint colourbuffer;
    glGenBuffers(1, &colourbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colourbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colours), colours, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colourbuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        
    
    glBindVertexArray( 0 );
    glfwPollEvents();

    while ((!glfwWindowShouldClose(window)) && glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS) {

        // Enable depth test
        glEnable(GL_DEPTH_TEST);
        // Accept fragment if it closer to the camera than the former one

        glDepthFunc(GL_LESS);

        glfwPollEvents();
        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear( GL_COLOR_BUFFER_BIT |  GL_DEPTH_BUFFER_BIT);
        // Compute the MVP matrix from keyboard and mouse input
        computeMatricesFromInputs(window);
        mat4 ViewMatrix = getViewMatrix();
        mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

        
        glUseProgram( shaderProgram );
        
        // Send our transformation to the currently bound shader,
        // in the "MVP" uniform
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
        
        glBindVertexArray( VAO );
        glDrawArrays(interpreter.drawingMode, 0, 50000);
        glBindVertexArray(0);
        
        glfwSwapBuffers(window);
        glfwPollEvents();

        
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteVertexArrays(1, &vertexbuffer);
    glDeleteVertexArrays(1, &colourbuffer);

    glfwTerminate();

    return 0;
}

int main () {
//    testTurtle();
//    testSymbol();
//    testRule();
//    testList();
//    testLSystem();
//    testParametersLSystem();
    testGraphics();
//    testJSONReader();
//    testRegexes();
//    testD0LSystemTurtle();
//    testReader();
//    testParser();
//    testInterpreter();
//    std::ifstream i("/Users/karishmavakil/Documents/Project/LsystemTrees/LsystemTrees/file.json");
//    json o;
//    i >> o;
//    // special iterator member functions for objects
//    for (json::iterator it = o.begin(); it != o.end(); ++it) {
//        if (it.key()=="answer") {
//            for (json::iterator it2 = it.value().begin(); it2 != it.value().end() ; it2++) {
//                cout<<it2.key()<<" "<<it2.value();
//            }
//        }
//    }
//    
//    // find an entry
//    if (o.find("foo") != o.end()) {
//        // there is an entry with key "foo"
//    }
//    TurtleInterpreter interpreter= createInterpreter("/Users/karishmavakil/Documents/Project/LsystemTrees/LsystemTrees/file.json");
//
//    random_device rd{}; // use to seed the rng
//    mt19937 rng{rd()}; // rng
//    
//    double p = 0.2; // probability
//    std::bernoulli_distribution d(p);
//    
//    // generate 5 runs
//    for(std::size_t i = 0; i < 50; ++i)
//        std::cout << d(rng) << " ";
//    
//    
    
}


