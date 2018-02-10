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
//checks is rule can be applied to this Symbol in
//first checks letters match and no of parameters are equal
//then iterate through individual parameters
//if input is a variable, shouldn't work
//if input and in both have numbers check they are equal
//if input has variable replace it in the in condition
//at the end evaluate the condition
bool Rule::isApplicable(Symbol in){
    //check letters match and
    bool matches = in.letter == input.letter && in.parameters.size() == input.parameters.size();
    string con = condition;
    bool conditional = !condition.empty();
    if (matches) {
        vector<string>::iterator itValue;
        for(vector<string>::iterator it = input.parameters.begin(), itValue = in.parameters.begin(); it != input.parameters.end() && matches; it++, itValue++) {
            if (!isNumber(*itValue)) {
                cout<<"Input Parameter is not a number";
                break;
            }
            if (!isVariable(*it)){
                matches = matches && (stof(*it) == stof(*itValue));
            }
            else if (conditional) {
                boost::replace_all(con, *it, *itValue);
            }
        }
        if (conditional) {
            matches = matches && evaluateCondition(con);
        }
    }
    return matches;
}
//apply the rule - basically just calculate output
//we know now that symbols match, just need to replace variables in output if there are any
//compare parameters again - if there is a variable to be replaced, iterate through output and replace variable with value in each output symbol
//after this is done iterate through output symbols and evaluate parameters for each symbol
//returns the output
vector<Symbol> Rule::apply(Symbol in){
    vector<string>::iterator itValue;
    vector<Symbol> out = output;
    vector<Symbol>::iterator itOut;
    for(vector<string>::iterator itVar = input.parameters.begin(), itValue = in.parameters.begin(); itVar != input.parameters.end(); itVar++, itValue++) {
        if (isVariable(*itVar)){
            for (itOut = out.begin(); itOut != out.end(); itOut++) {
                itOut->replaceParameters(*itVar, *itValue);
            }
        }
    }
    for (itOut = out.begin(); itOut != out.end(); itOut++) {
        itOut -> evaluateParameters();
    }
    return out;
}
void Rule::printState() {
    cout<<"Input ";
    input.printState();
    cout<<" Condition ";
    cout<<condition;
    cout<<" "<<"Output ";
    for (vector<Symbol>::iterator it = output.begin(); it != output.end(); ++it){
        it->printState();
    }
    cout<<endl;
}