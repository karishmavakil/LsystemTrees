//
//  JSONReader.hpp
//  LsystemTrees
//
//  Created by Karishma Vakil on 08/02/2018.
//  Copyright © 2018 Karishma Vakil. All rights reserved.
//

#ifndef JSONReader_hpp
#define JSONReader_hpp

#include <stdio.h>
#include "Symbol.hpp"
#include "Rule.hpp"
#include "LSystem.hpp"
#include "TurtleInterpreter.hpp"
#include "json.hpp"
#include "Turtle.hpp"
using json = nlohmann::json;

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

TurtleInterpreter createInterpreter(const char * json_file);
LSystem createLSystem(json j);
Turtle createTurtle(json j);
Rule createRule(json j);
Symbol createSymbol(string str);
vector<Symbol> createSymbols(string s);





#endif /* JSONReader_hpp */
