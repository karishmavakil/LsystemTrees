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

#include "DirectionMatrix.hpp"
#include <iostream>
using namespace std;
#include <stdio.h>

class Turtle {
    Vector3D position;
    DirectionMatrix direction;
public:
    Turtle();
    void setPos (GLfloat xpos, GLfloat ypos, GLfloat zpos);
    void setHeading (GLfloat xpos, GLfloat ypos, GLfloat zpos);
    void setLeft (GLfloat xpos, GLfloat ypos, GLfloat zpos);
    void setUp (GLfloat xpos, GLfloat ypos, GLfloat zpos);
    void forward(GLfloat step);
    void printState();
    Vector3D getPos();
    DirectionMatrix getDir();
    Vector3D getHeading();
    Vector3D getLeft();
    Vector3D getUp();
    void roll(GLfloat angle);
    void yaw(GLfloat angle);
    void pitch(GLfloat angle);
};

#endif /* Turtle_hpp */



