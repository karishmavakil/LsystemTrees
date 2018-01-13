//
//  RotationMatrix.cpp
//  LsystemTrees
//
//  Created by Karishma Vakil on 03/01/2018.
//  Copyright © 2018 Karishma Vakil. All rights reserved.
//

#include "RotationMatrix.hpp"

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


RotationMatrix::RotationMatrix() {
    col1 = Vector3D();
    col2 = Vector3D();
    col3 = Vector3D();
}
void RotationMatrix::printState(){
    cout<<"col1: ";
    col1.printState();
    cout<<"col2: ";
    col2.printState();
    cout<<"col3: ";
    col3.printState();
    cout<<endl;
}