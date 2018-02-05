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
    vector<Symbol> output;
    string condition;
    bool parametric;
    bool isApplicable(Symbol input);
    //input symbol must have single variables or numbers
    //output symbols may have expressions using those variables in their parameters
    Rule(Symbol input, string condition, vector<Symbol> output);
    Rule(Symbol input, vector<Symbol> output);
    vector<Symbol> apply(Symbol input);
    void printState();
};
vector<string> replaceParam(vector<string> &parameters, string variable, string value);
#endif /* Rule_hpp */
