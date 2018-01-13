//
//  Matrix.hpp
//  LsystemTrees
//
//  Created by Karishma Vakil on 03/01/2018.
//  Copyright © 2018 Karishma Vakil. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp

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

class Matrix {
public:
    Vector3D col1;
    Vector3D col2;
    Vector3D col3;
    Matrix();
    void printState();
};


#endif /* Matrix_hpp */
