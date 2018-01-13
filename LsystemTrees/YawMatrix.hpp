//
//  YawMatrix.hpp
//  LsystemTrees
//
//  Created by Karishma Vakil on 05/01/2018.
//  Copyright © 2018 Karishma Vakil. All rights reserved.
//

#ifndef YawMatrix_hpp
#define YawMatrix_hpp

#include <stdio.h>
//
//  RollMatrix.hpp
//  LsystemTrees
//
//  Created by Karishma Vakil on 05/01/2018.
//  Copyright © 2018 Karishma Vakil. All rights reserved.
//


#include <stdio.h>
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

class YawMatrix : public RotationMatrix {
public:
    YawMatrix(float angle);
};



#endif /* YawMatrix_hpp */
