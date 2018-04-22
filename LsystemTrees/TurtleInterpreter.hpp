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
#include "Lsystem.hpp"
using namespace std;

class TurtleInterpreter {
    Turtle turtle;
    LSystem lsystem;
//    vector<Symbol> instructions;
    vector<vec3> branchVertices;
    vector<vec3> branchColours;
    vector<vec3> branchNormals;
    vector<vec2> branchUVs;
    vector<vec3> leafVertices;
    vector<vec3> leafColours;
    vector<vec3> leafNormals;
    vector<vec2> leafUVs;
    stack<vec3> positionStack;
    stack<vec3> headingStack;
    stack<vec3> leftStack;
    stack<vec3> upStack;
    stack<GLfloat> radiusStack;
    stack<GLfloat> stepStack;
    void addBranchVertices (vec3 centre1, vec3 centre2, vec3 axis, vec3 normal, GLfloat radius);
    void addLeafVertices(vec3 end, vec3 dir, vec3 perp);
    void addLeavesVertices (vec3 centre1, vec3 centre2, vec3 axis, vec3 normal, GLfloat radius);
public:
    GLfloat branchRadius = 0.06f;
    GLfloat treeRadius = 0.06f;

    GLfloat branchStep = 0.25f;
    GLfloat branchAngle = 0.6f;
    GLfloat branchThicknessRatio = 0.93;
    GLfloat branchStepRatio = 0.95;
    GLfloat minRadius = 0.015;
    GLfloat maxLeafRadius = 0.15;
    GLfloat leafLength = 0.6;
    GLfloat leafWidth = 0.35;
    int leafDensity;
    string woodTextureFile;
    string leafTextureFile;
    size_t branchVerticesSize;
    size_t leafVerticesSize;
    bool useContexts;
    int iterations;
    GLenum drawingMode = GL_TRIANGLES;
    TurtleInterpreter(Turtle t, LSystem l);
    vector<Symbol> getInstructions();
    vector<vec3> getVertices();
    vector<vec3> getColours();
    vector<vec3> getNormals();
    vector<vec2> getUVs();
    LSystem getLSystem();
    void refreshTurtle();
    void generateInformation();
    void printVariables();
};
#endif /* TurtleInterpreter_hpp */
