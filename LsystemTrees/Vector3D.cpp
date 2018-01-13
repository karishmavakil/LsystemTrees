//
//  Vector3D.cpp
//  LsystemTrees
//
//  Created by Karishma Vakil on 03/01/2018.
//  Copyright © 2018 Karishma Vakil. All rights reserved.
//

#include "Vector3D.hpp"

// third-party libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// standard C++ libraries
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <cmath>

#include <iostream>
using namespace std;
Vector3D::Vector3D() {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
    }
Vector3D::Vector3D(GLfloat x1, GLfloat y1, GLfloat z1) {
        x = x1;
        y = y1;
        z = z1;
    }
bool Vector3D::equals( Vector3D v2) {
        GLfloat e = 0.00001f;
        return (fabs(x - v2.x) < e && fabs(y - v2.y) < e && fabs(z - v2.z) < e);
    }
void Vector3D::set(GLfloat x1, GLfloat y1, GLfloat z1) {
        x = x1;
        y = y1;
        z = z1;
    }
GLfloat Vector3D::getX() {
    return x;
}
GLfloat Vector3D::getY() {
    return y;
}
GLfloat Vector3D::getZ() {
    return z;
}
Vector3D Vector3D::add(Vector3D v) {
    return Vector3D(x + v.getX(), y + v.getY(), z + v.getZ());
}
Vector3D Vector3D::scalar(GLfloat a){
    return Vector3D(a*x, a*y, a*z);
}
GLfloat Vector3D::dot(Vector3D v){
    return (x * v.getX() + y * v.getY() + z * v.getZ());
}
void Vector3D::printState(){
    cout<<x<<" "<<y<<" "<<z<<endl;
}

