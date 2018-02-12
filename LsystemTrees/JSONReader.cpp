//
//  JSONReader.cpp
//  LsystemTrees
//
//  Created by Karishma Vakil on 08/02/2018.
//  Copyright © 2018 Karishma Vakil. All rights reserved.
//

#include "JSONReader.hpp"

#include "Symbol.hpp"
#include "Rule.hpp"
#include "LSystem.hpp"
#include "Turtle.hpp"

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

//1 Symbols can have A-Z, [, ], +, -, &, ^, /, \  as letters
//2 Parameters must be encapsulated in {}
//Parameters should be separated by commas
//If a parameter is an expression, the tokens must be separated by spaces otherwise will not be evaluated"
//only enforcing 1 and 2 here
//regex symbol("([A-Z\\[\\]&-^\\/+])([{][^\\[\\]{}]+[}])?");
regex symbol("([A-Z\\[\\]&\\-^\\\\/\\+])([{][^\\[\\]{}]+[}])?");
using namespace std;

//create a Symbol from a string - take the first char and make it the letter, the rest will be the parameters like {a, b, c... }
Symbol createSymbol(string str) {
    //match it's either a char or char followed by {params}
    //split char and parameters
    //trims for Symbol
    string s = trim(str);
    if (!regex_match(s, symbol)) {
        cout<<"Invalid Symbol string "<<s<<endl;
    }
    Symbol a = Symbol(s[0], s.erase(0, 1));
    return a;
}
//create a list of Symbols from a string by finding all matches in a string
vector<Symbol> createSymbols(string s){
    vector<Symbol> symbols;
    regex_iterator<string::iterator> rit ( s.begin(), s.end(), symbol);
    regex_iterator<string::iterator> rend;
    while (rit!=rend) {
        symbols.push_back(createSymbol(rit->str()));
        ++rit;
    }
    return symbols;
}
//create the interpreter
TurtleInterpreter createInterpreter(const char * json_file) {
    std::ifstream i(json_file);
    json j;
    i >> j;
    LSystem l = LSystem();
    Turtle t = Turtle();
    if (j.find("LSystem") != j.end()) {
        l = createLSystem(j["LSystem"]);
    }
    else {
        cout<<"No LSystem provided";
    }
    if (j.find("Turtle") != j.end()) {
        t = createTurtle(j["Turtle"]);
    }
    else {
        cout<<"No Turtle provided";
    }
    TurtleInterpreter interpreter = TurtleInterpreter(t, l);
    if (j.find("branchRadius") != j.end()) {
        interpreter.branchRadius = j["branchRadius"];
    }
    if (j.find("branchStep") != j.end()) {
        interpreter.branchStep = j["branchStep"];
    }
    if (j.find("branchAngle") != j.end()) {
        interpreter.branchAngle = j["branchAngle"];
    }
    if (j.find("branchThicknessRatio") != j.end()) {
        interpreter.branchThicknessRatio = j["branchThicknessRatio"];
    }
    if (j.find("branchStepRatio") != j.end()) {
        interpreter.branchStepRatio = j["branchStepRatio"];
    }
    if (j.find("minRadius") != j.end()) {
        interpreter.minRadius = j["minRadius"];
    }
    if (j.find("iterations") != j.end()) {
        interpreter.iterations = j["iterations"];
    }
    if (j.find("useContexts") != j.end()) {
        interpreter.useContexts = j["useContexts"];
    }
    interpreter.printVariables();
    return interpreter;
}
//Lsystem must have Start and Rules
LSystem createLSystem(json j){
    Symbol start = createSymbol(j["Start"]);
    vector<json> rulesJson = j["Rules"];
    vector<Rule> rules = vector<Rule>();
    for (vector<json>::iterator it = rulesJson.begin(); it != rulesJson.end(); it++){
        rules.push_back(createRule(*it));
    }
    return LSystem(start, rules);
    
}
//Turtle must have x y z
Turtle createTurtle(json j) {
    Turtle t = Turtle();
    t.setPosition(j["x"], j["y"], j["z"]);
    t.printState();
    return t;
}
//Rule must have input and output
Rule createRule(json j) {
    Symbol input = createSymbol(j["Input"]);
    Symbol left = Symbol();
    Symbol right = Symbol();
    float probability = 1;
    vector<Symbol> output = createSymbols(j["Output"]);
    string condition = "";
    if (j.find("Condition") != j.end()) {
        condition = j["Condition"];
    }
    if (j.find("Left Context") != j.end()) {
        left = createSymbol(j["Left Context"]);
    }
    if (j.find("Right Context") != j.end()) {
        right = createSymbol(j["Right Context"]);
    }
    if (j.find("Probability") != j.end()) {
        probability = j["Probability"];
    }
//    Rule(input, condition, output).printState();
    if (left.equals(Symbol()) && right.equals(Symbol())) {
        Rule r = Rule(input, condition, output);
        r.probability = probability;
        r.printState();
        return r;
    }
    else {
        Rule r = Rule(left, input,right, condition, output);
        r.probability = probability;
        r.printState();
        return r;
    }
}