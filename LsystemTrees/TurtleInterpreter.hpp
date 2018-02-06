//
//  TurtleInterpreter.hpp
//  LsystemTrees
//
//  Created by Karishma Vakil on 20/01/2018.
//  Copyright © 2018 Karishma Vakil. All rights reserved.
//

#ifndef TurtleInterpreter_hpp
#define TurtleInterpreter_hpp

#include <stdio.h>
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
#include <stack>

#include "Turtle.hpp"
#include "Symbol.hpp"

using namespace std;

class TurtleInterpreter {
    Turtle turtle;
    vector<Symbol> instructions;
    vector<vec3> vertices;
    vector<vec3> colours;
    stack<vec3> positionStack;
    stack<vec3> headingStack;
    stack<vec3> leftStack;
    stack<vec3> upStack;
    stack<GLfloat> radiusStack;
    stack<GLfloat> stepStack;
    void addCylinderVertices (vec3 centre1, vec3 centre2, vec3 axis, vec3 normal, GLfloat radius);
public:
    GLfloat branchRadius = 0.06f;
    GLfloat branchStep = 0.25f;
    GLfloat branchAngle = 0.6f;
    GLfloat branchThicknessRatio = 0.93;
    GLfloat branchStepRatio = 0.95;
    GLfloat minRadius = 0.015;
    GLenum drawingMode = GL_TRIANGLES;
    TurtleInterpreter(Turtle t);
    vector<Symbol> getInstructions();
    vector<vec3> getVertices();
    vector<vec3> getColours();
    void refreshTurtle();
    void generateInformation(vector<Symbol> instructions);
    void printVariables();
    void readVariables(const char * variables_file_path);

};
#endif /* TurtleInterpreter_hpp */
