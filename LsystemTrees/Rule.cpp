//
//  Rule.cpp
//  LsystemTrees
//
//  Created by Karishma Vakil on 14/01/2018.
//  Copyright © 2018 Karishma Vakil. All rights reserved.
//

#include "Rule.hpp"
#include <functional>
#include "boost/algorithm/string/replace.hpp"
#include "Parser.hpp"

Rule::Rule(Symbol in, string cond, vector<Symbol> out) : input(in){
    input = in;
    condition = cond;
    output = out;
    parametric = true;
}
Rule::Rule(Symbol in, vector<Symbol> out) : input(in){
    input = in;
    parametric = false;
    condition = "";
    output = out;
}
bool Rule::isApplicable(Symbol in){
    bool matches = in.letter == input.letter && in.parameters.size() == input.parameters.size();
    //add check that in.parameters dont have variables?
    string con = condition;
    bool conditional = !condition.empty();
    if (matches) {
        vector<string>::iterator itValue;
        for(vector<string>::iterator it = input.parameters.begin(), itValue = in.parameters.begin(); it != input.parameters.end() && matches; it++, itValue++) {
            if (! isVariable(*it)){
                matches = matches && (stof(*it) == stof(*itValue));
            }
            else if (conditional) {
                boost::replace_all(con, *it, *itValue);
            }
        }
        if (con != "") {
            //make evaluating conditions more sophisticated
            //check conditions only have numbers no variables
            matches = matches && evaluateInfix(con) == "1";
        }
    }
    return matches;
}
vector<Symbol> Rule::apply(Symbol in){
    vector<string>::iterator itValue;
    vector<Symbol> out = output;
    vector<Symbol>::iterator itOut;
    for(vector<string>::iterator itVar = input.parameters.begin(), itValue = in.parameters.begin(); itVar != input.parameters.end(); itVar++, itValue++) {
        if (isVariable(*itVar)){
            for (itOut = out.begin(); itOut != out.end(); itOut++) {
                itOut->replaceParameters(*itVar, *itValue);
                itOut -> evaluateParameters();
            }
        }
    }
    return out;
}
void Rule::printState() {
    cout<<"Input ";
    input.printState();
    cout<<"Condition ";
    cout<<condition;
    cout<<" "<<"Output ";
    for (vector<Symbol>::iterator it = output.begin(); it != output.end(); ++it){
        it->printState();
    }
    cout<<endl;
}