//
//  Parser.hpp
//  LsystemTrees
//
//  Created by Karishma Vakil on 02/02/2018.
//  Copyright © 2018 Karishma Vakil. All rights reserved.
//

#ifndef Parser_hpp
#define Parser_hpp

#include <stdio.h>
// standard C++ libraries
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <vector>
#include <list>
#include <fstream>
#include <cstdlib>
#include <regex>
#include <sstream>

using namespace std;

bool isNumber(string s);
bool isOperator(string s);
bool isVariable(string s);
bool isBracket(string s);
int getOperatorWeight(string op);
bool hasHigherPrecedence(string op1, string op2);
string toPostfix(string infixExpression);
string eval(string a, string op, string b);
string evaluatePostfix(string postfixExpression);
string evaluateInfix(string infixExpression);
vector<string> parseParameters(string param);
string trim(string str);



#endif /* Parser_hpp */
