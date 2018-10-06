
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
//empty symbol for use in Contexts later
Symbol::Symbol() {
    letter = ' ';
}
void Symbol::printState(){
    cout<<letter<<" ";
    if(!parameters.empty()) {
        for(vector<string>::iterator it = parameters.begin(); it != parameters.end(); it++) {
            if (it!= parameters.begin()) {
                cout<<", ";
            }
            cout<<*it;
        }
        cout<<" ";
    }
}
bool Symbol::equals(Symbol s) {
    return (s.letter==letter && s.parameters==parameters);
}
//go through all the parameters and evaluate each one - each one will be an infix expression
void Symbol::evaluateParameters(){
    //check only numbers - is checked in evaluateInfix
    vector<string> evaluatedParameters;
    for(vector<string>::iterator it = parameters.begin(); it != parameters.end(); it++) {
        evaluatedParameters.push_back(evaluateInfix(*it));
    }
    parameters = evaluatedParameters;
}
//go through all the parameters - at this point they will all be floats strings - convert them to float type
vector<GLfloat> Symbol::getParameters() {
    vector<GLfloat> parameterList;
    for(vector<string>::iterator it = parameters.begin(); it != parameters.end(); it++) {
        parameterList.push_back(stof(*it));
    }
   return parameterList;
}
//replace a variable with a value in all the parameters
//checks if it is a variable being replaced
void Symbol::replaceParameters(string variable, string value) {
    vector<string>::iterator itParameters;
    if (!isVariable(variable)) {
        cout<<"Can't replace a token that is not a variable "<<endl;
    }
    for (itParameters = parameters.begin(); itParameters != parameters.end(); itParameters++) {
        boost::replace_all(*itParameters, variable, value);
    }
}