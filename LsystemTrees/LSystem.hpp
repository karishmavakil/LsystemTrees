

#ifndef LSystem_hpp
#define LSystem_hpp

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
#include <list>

#include <iostream>

#include "Symbol.hpp"
#include "Rule.hpp"
using namespace std;

class LSystem {
public:
    Symbol start;
//    vector<Symbol> alphabet;
    vector<Symbol> current;
    vector<Rule> rules;
    LSystem(Symbol current, vector<Rule> rules);
    LSystem();
    void clear();
    void applyRules();
    void applyRulesWithContext();
    void applyRules(int n);
    void applyRulesWithContext(int n);
    void printCurrent();
};


#endif /* LSystem_hpp */
