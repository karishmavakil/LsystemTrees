//
//  DirectionMatrix.hpp
//  LsystemTrees
//
//  Created by Karishma Vakil on 12/01/2018.
//  Copyright © 2018 Karishma Vakil. All rights reserved.
//

#ifndef DirectionMatrix_hpp
#define DirectionMatrix_hpp

#include <stdio.h>

#include "Vector3D.hpp"
#include "Matrix.hpp"

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

class DirectionMatrix : public Matrix {
public:
    DirectionMatrix();
    void printState();
    void rotate(Matrix r);
};


#endif /* DirectionMatrix_hpp */
