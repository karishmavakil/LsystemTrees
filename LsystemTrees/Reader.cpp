//
//  Reader.cpp
//  LsystemTrees
//
//  Created by Karishma Vakil on 24/01/2018.
//  Copyright © 2018 Karishma Vakil. All rights reserved.
//

#include "Reader.hpp"
#include "Symbol.hpp"
#include "Rule.hpp"
#include "LSystem.hpp"

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

regex e ("(.)(\\([\\w|\\.|,]+\\))?");

using namespace std;
Symbol createSymbol(string s) {
    //match it's either a char or char followed by ()
    //split char and parameters
//    cout<<"Match? : "<<regex_match(s, e)<<endl;
    return Symbol(s[0], s.erase(0, 1));
}
vector<Symbol> createSymbols(string s){
    vector<Symbol> symbols;
    regex_iterator<string::iterator> rit ( s.begin(), s.end(), e );
    regex_iterator<string::iterator> rend;
    while (rit!=rend) {
        cout<<endl;
        symbols.push_back(createSymbol(rit->str()));
        ++rit;
    }
    return symbols;
}
LSystem createLsystem(const char * lsystem_file_path) {
    ifstream file(lsystem_file_path);
    string line;
    getline(file, line);
//    first line is start
//    str is the start symbol
    cout<<"Start "<<line;
    Symbol start = createSymbol(line);
//    next lines will be rules - so split on spaces, get input output
    vector<Rule> rules;
    while (getline(file, line))
    {
        stringstream rule(line);
        getline(rule, line, ' ');
        Symbol in = createSymbol(line);
        getline(rule, line, ' ');
        vector<Symbol> out = createSymbols(line);
        cout<<endl<<"Rule: ";
        Rule(in, out).printState();
        rules.push_back(Rule(in, out));
    }
    return LSystem(start, rules);
}
void readDelimit(const char * file_path) {
    ifstream file(file_path);
    string str;
    while (file.good()){
        getline(file, str, ',');
        cout<<str<<endl;
    }
}




