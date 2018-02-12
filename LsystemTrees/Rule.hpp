//
//  Rule.hpp
//  LsystemTrees
//
//  Created by Karishma Vakil on 14/01/2018.
//  Copyright © 2018 Karishma Vakil. All rights reserved.
//

#ifndef Rule_hpp
#define Rule_hpp

#include <stdio.h>
// standard C++ libraries
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <vector>
#include <list>

#include <iostream>

#include "Symbol.hpp"
class Rule {
public:
    Symbol input;
    Symbol left;
    Symbol right;
    vector<Symbol> output;
    string condition;
    float probability;
    bool isLeftContextSensitive;
    bool isRightContextSensitive;
    //input symbol must have single variables or numbers
    //output symbols may have expressions using those variables in their parameters
    bool isApplicable(Symbol input);
    bool isApplicableWithContext(Symbol left, Symbol input, Symbol right);
    Rule(Symbol left, Symbol input, Symbol right, string condition, vector<Symbol> output);
    Rule(Symbol input, string condition, vector<Symbol> output);
    Rule(Symbol input, vector<Symbol> output);
    vector<Symbol> apply(Symbol input);
    vector<Symbol> applyWithContext(Symbol left, Symbol input, Symbol right);
    void printState();
};
vector<string> replaceParam(vector<string> &parameters, string variable, string value);
#endif /* Rule_hpp */
