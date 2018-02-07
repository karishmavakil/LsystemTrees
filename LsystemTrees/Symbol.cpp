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
#include "Parser.hpp"
#include "boost/algorithm/string/replace.hpp"

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
    parameters = parseParameters(p);
}
Symbol::Symbol(char l) {
    letter = l;
}
Symbol::Symbol() {
    letter = ' ';
}
void Symbol::printState(){
    cout<<letter<<" ";
    if(!parameters.empty()) {
        for(vector<string>::iterator it = parameters.begin(); it != parameters.end(); it++) {
            cout<<*it<<" ";
        }
    }
}
bool Symbol::equals(Symbol s) {
    return (s.letter==letter && s.parameters==parameters);
}
void Symbol::evaluateParameters(){
    //check only numbers - is checked in evaluateInfix
    vector<string> evaluatedParameters;
    for(vector<string>::iterator it = parameters.begin(); it != parameters.end(); it++) {
        evaluatedParameters.push_back(evaluateInfix(*it));
    }
    parameters = evaluatedParameters;
}
vector<GLfloat> Symbol::getParameters() {
    vector<GLfloat> parameterList;
    for(vector<string>::iterator it = parameters.begin(); it != parameters.end(); it++) {
        parameterList.push_back(stof(*it));
    }
   return parameterList;
}
void Symbol::replaceParameters(string variable, string value) {
    vector<string>::iterator itParameters;
    for (itParameters = parameters.begin(); itParameters != parameters.end(); itParameters++) {
        boost::replace_all(*itParameters, variable, value);
    }
}