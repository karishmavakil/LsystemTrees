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
#include <sstream>
using namespace std;

Symbol::Symbol(char l, string p) {
    letter = l;
    parameters = p;
}
Symbol::Symbol(char l){
    letter = l;
    parameters = "";
}
Symbol::Symbol(){
    letter = ' ';
    parameters = "";
}
void Symbol::printState(){
    
    cout<<letter;
    if(!parameters.empty()) {
        cout<<parameters;
    }
}
bool Symbol::equals(Symbol s) {
    return (s.letter==letter && s.parameters==parameters);
}
vector<GLfloat> Symbol::getParameters() {
    vector<GLfloat> parameterList;
    string p = parameters.size()>1 ? parameters.substr(1, parameters.size()-2) : "";
    stringstream ss(p);
    string val;
    while (getline(ss, val, ',')){
        parameterList.push_back(stof(val));
    }
    return parameterList;
}