//
//  Turtle.hpp
//  LsystemTrees
//
//  Created by Karishma Vakil on 07/12/2017.
//  Copyright © 2017 Karishma Vakil. All rights reserved.
//

#ifndef Turtle_hpp
#define Turtle_hpp

// third-party libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// standard C++ libraries
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <vector>

#include "DirectionMatrix.hpp"
#include "Symbol.hpp"
#include "Vector3D.hpp"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/ext.hpp"
using namespace glm;
#include <iostream>
using namespace std;
#include <stdio.h>

class Turtle {
    vec3 position;
    vec3 heading;
    vec3 left;
    vec3 up;
public:
    Turtle();
    void setPosition (GLfloat xpos, GLfloat ypos, GLfloat zpos);
    void setHeading (GLfloat xpos, GLfloat ypos, GLfloat zpos);
    void setLeft (GLfloat xpos, GLfloat ypos, GLfloat zpos);
    void setUp (GLfloat xpos, GLfloat ypos, GLfloat zpos);
    void forward(GLfloat step);
    void printState();
    vec3 getPosition();
    vec3 getHeading();
    vec3 getLeft();
    vec3 getUp();
    void roll(GLfloat angle);
    void yaw(GLfloat angle);
    void pitch(GLfloat angle);
    vector<vec3> draw3D(vector<Symbol>);
};

vec3 round(vec3 v);
vector<vec3> cylinderVertices (vec3 centre1, vec3 centre2, vec3 axis, vec3 normal, GLfloat radius);
#endif /* Turtle_hpp */



