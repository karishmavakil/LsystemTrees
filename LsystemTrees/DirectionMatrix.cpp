//
//  DirectionMatrix.cpp
//  LsystemTrees
//
//  Created by Karishma Vakil on 12/01/2018.
//  Copyright © 2018 Karishma Vakil. All rights reserved.
//

#include "DirectionMatrix.hpp"

#include <stdio.h>

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


DirectionMatrix::DirectionMatrix() {
    col1 = Vector3D(1.0f, 0.0f, 0.0f);
    col2 = Vector3D(0.0f, 0.0f, 1.0f);
    col3 = Vector3D(0.0f, 1.0f, 0.0f);
}
void DirectionMatrix::rotate(Matrix r) {
    Vector3D row1 = Vector3D(col1.getX(), col2.getX(), col3.getX());
    Vector3D row2 = Vector3D(col1.getY(), col2.getY(), col3.getY());
    Vector3D row3 = Vector3D(col1.getZ(), col2.getZ(), col3.getZ());
    col1.set(row1.dot(r.col1), row2.dot(r.col1), row3.dot(r.col1));
    col2.set(row1.dot(r.col2), row2.dot(r.col2), row3.dot(r.col2));
    col3.set(row1.dot(r.col3), row2.dot(r.col3), row3.dot(r.col3));
}
void DirectionMatrix::printState() {
    cout<<"heading : ";
    col1.printState();
    cout<<"up : ";
    col2.printState();
    cout<<"left : ";
    col3.printState();
}