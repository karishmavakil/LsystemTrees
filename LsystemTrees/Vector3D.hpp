//
//  Vector3D.hpp
//  LsystemTrees
//
//  Created by Karishma Vakil on 03/01/2018.
//  Copyright © 2018 Karishma Vakil. All rights reserved.
//

#ifndef Vector3D_hpp
#define Vector3D_hpp

#include <stdio.h>
// third-party libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

class Vector3D {
    GLfloat x;
    GLfloat y;
    GLfloat z;
public:
    Vector3D();
    Vector3D(GLfloat x1, GLfloat y1, GLfloat z1);
    bool equals(Vector3D v);
    bool equals(GLfloat x1);
    void set(GLfloat x1, GLfloat y1, GLfloat z1);
    GLfloat getX();
    GLfloat getY();
    GLfloat getZ();
    Vector3D add(Vector3D v);
    Vector3D scalar(GLfloat a);
    GLfloat dot(Vector3D v);
    void printState();
};
#endif /* Vector3D_hpp */

