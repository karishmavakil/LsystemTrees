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
#include "Parser.hpp"

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
    vector<string> parameters;
    Symbol(char l, string p);
    Symbol(char l);
    Symbol();
    void printState();
    bool equals(Symbol);
    void evaluateParameters();
    vector<GLfloat> getParameters();
    void replaceParameters(string variable, string value);

};

#endif /* Symbol_hpp */
