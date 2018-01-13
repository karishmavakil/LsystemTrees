//
//  PitchMatrix.hpp
//  LsystemTrees
//
//  Created by Karishma Vakil on 05/01/2018.
//  Copyright © 2018 Karishma Vakil. All rights reserved.
//

#ifndef PitchMatrix_hpp
#define PitchMatrix_hpp

#include <stdio.h>
#include "RotationMatrix.hpp"
#include <stdio.h>

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

class PitchMatrix : public RotationMatrix {
public:
    PitchMatrix(float angle);
};


#endif /* PitchMatrix_hpp */
