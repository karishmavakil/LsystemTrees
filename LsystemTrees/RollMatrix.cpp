//
//  RollMatrix.cpp
//  LsystemTrees
//
//  Created by Karishma Vakil on 05/01/2018.
//  Copyright © 2018 Karishma Vakil. All rights reserved.
//

#include "RollMatrix.hpp"
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

RollMatrix::RollMatrix(GLfloat angle) {
    
    GLfloat x = cos(angle);
    GLfloat y = sin(angle);
    for(int i = -1; i <=1; i++){
        if(fabs(x-i) < 0.0000001f) {
            x = i;
        }
        if(fabs(y-i) < 0.0000001f) {
            y = i;
        }
    }
    col1 = Vector3D(1, 0, 0);
    col2 = Vector3D(0, x, y);
    col3 = Vector3D(0, -y, x);
}