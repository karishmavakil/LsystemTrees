//
//  Symbol.hpp
//  LsystemTrees
//
//  Created by Karishma Vakil on 14/01/2018.
//  Copyright © 2018 Karishma Vakil. All rights reserved.
//

#ifndef Symbol_hpp
#define Symbol_hpp

#include <stdio.h>
#include <stdio.h>
// third-party libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// standard C++ libraries
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <vector>
#include <vector>
#include <iostream>

using namespace std;

class Symbol {
public:
    char letter;
    vector<GLfloat> parameters;
    Symbol(char l, vector<GLfloat> p);
    Symbol(char l);
    void printState();
};

#endif /* Symbol_hpp */
