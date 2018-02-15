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
#include "Texture.hpp"
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
    GLuint ViewMatrixID = glGetUniformLocation(shaderProgram, "V");
    GLuint ModelMatrixID = glGetUniformLocation(shaderProgram, "M");
    GLuint TextureID  = glGetUniformLocation(shaderProgram, "myTexture");
//    // Camera matrix
//    mat4 View = lookAt(
//                                 vec3(5,-2,15), // Camera is at (4,3,3), in World Space
//                                 vec3(0,0,0), // and looks at the origin
//                                 vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
//                                );
//    // Model matrix : an identity matrix (model will be at the origin)


//    Turtle turtle = Turtle();
//    turtle.setPosition(0.0f, -6.0f, 0.0f);
//    
//    
//    LSystem tree = createLsystem("/Users/karishmavakil/Documents/Project/LSystemTrees/LSystemTrees/tree.txt");
//    tree.applyRules(4);
//
    GLuint Texture = loadBMP_custom("/Users/karishmavakil/Documents/Project/LsystemTrees/LsystemTrees/woodtexture.bmp");

    TurtleInterpreter interpreter= createInterpreter("/Users/karishmavakil/Documents/Project/LsystemTrees/LsystemTrees/tree2.json");
    interpreter.printVariables();

    interpreter.generateInformation();
    
    vector<vec3> vert = interpreter.getVertices();
    vector<vec3> col = interpreter.getColours();
    vector<vec3> norm = interpreter.getNormals();
    vector<vec2> uv = interpreter.getUVs();
    cout<<"vertices "<<vert.size()<<" uvs "<<uv.size()<<" normals "<<norm.size()<<endl;
    GLuint VAO;
    glGenVertexArrays( 1, &VAO);
    glBindVertexArray(VAO);
    
    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer( GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData( GL_ARRAY_BUFFER, vert.size() * sizeof(vec3), &vert[0], GL_STATIC_DRAW );
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 3 * sizeof( GLfloat), (GLvoid *) 0);
    glEnableVertexAttribArray(0);
    glBindBuffer( GL_ARRAY_BUFFER, 0);

    GLuint colourbuffer;
    glGenBuffers(1, &colourbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colourbuffer);
    glBufferData(GL_ARRAY_BUFFER, col.size() * sizeof(vec3), &col[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colourbuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    
    GLuint normalbuffer;
    glGenBuffers(1, &normalbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glBufferData(GL_ARRAY_BUFFER, norm.size() * sizeof(glm::vec3), &norm[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glVertexAttribPointer(2, 3, GL_FLOAT,GL_FALSE, 0, (void*)0);
    
    GLuint uvbuffer;
    glGenBuffers(1, &uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, uv.size() * sizeof(glm::vec2), &uv[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(3);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glVertexAttribPointer(3, 2, GL_FLOAT,GL_FALSE, 0, (void*)0);

    
    glBindVertexArray( 0 );
    glfwPollEvents();

    
    GLuint LightID = glGetUniformLocation(shaderProgram, "LightPosition_worldspace");
    glUseProgram( shaderProgram );
    //
    while ((!glfwWindowShouldClose(window)) && glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS) {

        // Enable depth test
        glEnable(GL_DEPTH_TEST);
        // Accept fragment if it closer to the camera than the former one

        glDepthFunc(GL_LESS);

        glfwPollEvents();
        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear( GL_COLOR_BUFFER_BIT |  GL_DEPTH_BUFFER_BIT);

        glUseProgram( shaderProgram );
         //Compute the MVP matrix from keyboard and mouse input
        computeMatricesFromInputs(window);
        mat4 ViewMatrix = getViewMatrix();
        mat4 ModelMatrix      = mat4(1.0f);
        mat4 ProjectionMatrix = perspective(radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
        mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;


        glm::vec3 lightPos = getLightPos();


        glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);
        // Bind our texture in Texture Unit 0
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, Texture);
        // Set our "myTextureSampler" sampler to use Texture Unit 0
        glUniform1i(TextureID, 0);

        // Send our transformation to the currently bound shader,
        // in the "MVP" uniform
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
        glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
        glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);

         //Send our transformation to the currently bound shader,
        // in the "MVP" uniform

        glBindVertexArray( VAO );
        glDrawArrays(interpreter.drawingMode, 0, 50000);
        glBindVertexArray(0);
        
        glfwSwapBuffers(window);
        glfwPollEvents();

        
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteVertexArrays(1, &vertexbuffer);
    glDeleteVertexArrays(1, &colourbuffer);
    glDeleteVertexArrays(1, &normalbuffer);
    glDeleteTextures(1, &Texture);
    glDeleteProgram(shaderProgram);


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


