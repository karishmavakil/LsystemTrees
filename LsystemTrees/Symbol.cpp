//
//  Symbol.cpp
//  LsystemTrees
//
//  Created by Karishma Vakil on 14/01/2018.
//  Copyright © 2018 Karishma Vakil. All rights reserved.
//
#include <stdio.h>

#include "Symbol.hpp"
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

Symbol::Symbol(char l, vector<GLfloat> p) {
    letter = l;
    parameters = p;
}

Symbol::Symbol(char l){
    letter = l;
    parameters = vector<GLfloat>();
}

void Symbol::printState(){
    cout<<"Letter: "<<letter<<" Parameters: ";
    for (vector<GLfloat>::iterator it = parameters.begin(); it != parameters.end(); ++it){
        cout<<*it<<" ";
    }
    cout<<endl;
}