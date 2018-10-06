

#include "Rule.hpp"
#include <functional>
#include "boost/algorithm/string/replace.hpp"
#include "Parser.hpp"

Rule::Rule(Symbol in, string cond, vector<Symbol> out) : input(in){
    input = in;
    condition = cond;
    output = out;
    left = Symbol();
    right = Symbol();
    isLeftContextSensitive = false;
    isRightContextSensitive = false;
    probability = 1;
}
Rule::Rule(Symbol in, vector<Symbol> out) : input(in){
    input = in;
    condition = "";
    output = out;
    left = Symbol();
    right = Symbol();
    isLeftContextSensitive = false;
    isRightContextSensitive = false;
    probability = 1;

}
Rule::Rule(Symbol l, Symbol in, Symbol r, string cond, vector<Symbol> out) {
    input = in;
    condition = cond;
    output = out;
    left = l;
    right = r;
    isLeftContextSensitive = !l.equals(Symbol());
    isRightContextSensitive = !r.equals(Symbol());
    probability = 1;
}

//checks if rule can be applied to this Symbol in
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
bool Rule::isApplicableWithContext(Symbol l, Symbol in, Symbol r) {
    
    string con = condition;
    bool conditional = !condition.empty();
    
    bool matches = in.letter == input.letter && in.parameters.size() == input.parameters.size();
    //either there is no left context or it matches with the one given
    matches = matches && (!isLeftContextSensitive || (l.letter == left.letter && l.parameters.size() == left.parameters.size()));
    //either there is no right context or it matches with the one given
    matches = matches &&  (!isRightContextSensitive || (r.letter == right.letter && r.parameters.size() == right.parameters.size()));
    //if matched so far let's compare individual parameters
    if (matches) {
        //check for the input
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
        //if leftCS compare lefts
        if (isLeftContextSensitive){
            for(vector<string>::iterator it = left.parameters.begin(), itValue = l.parameters.begin(); it != left.parameters.end() && matches; it++, itValue++) {
                if (!isNumber(*itValue)) {
                    cout<<"left context Parameter is not a number";
                    break;
                }
                if (!isVariable(*it)){
                    matches = matches && (stof(*it) == stof(*itValue));
                }
                else if (conditional) {
                    boost::replace_all(con, *it, *itValue);
                }
            }
        }
        //if rightCS compare rights
        if (isRightContextSensitive) {
            for(vector<string>::iterator it = right.parameters.begin(), itValue = r.parameters.begin(); it != right.parameters.end() && matches; it++, itValue++) {
                if (!isNumber(*itValue)) {
                    cout<<"right context Parameter is not a number";
                    break;
                }
                if (!isVariable(*it)){
                    matches = matches && (stof(*it) == stof(*itValue));
                }
                else if (conditional) {
                    boost::replace_all(con, *it, *itValue);
                }
            }
        }
        //if condition then evaluate it
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
vector<Symbol> Rule::applyWithContext(Symbol l, Symbol in, Symbol r) {
    vector<string>::iterator itValue;
    vector<Symbol> out = output;
    vector<Symbol>::iterator itOut;
    //replace all variables in output using input
    for(vector<string>::iterator itVar = input.parameters.begin(), itValue = in.parameters.begin(); itVar != input.parameters.end(); itVar++, itValue++) {
        if (isVariable(*itVar)){
            for (itOut = out.begin(); itOut != out.end(); itOut++) {
                itOut->replaceParameters(*itVar, *itValue);
            }
        }
    }
    //if left CS do the same for left input
    if(isLeftContextSensitive) {
        for(vector<string>::iterator itVar = left.parameters.begin(), itValue = l.parameters.begin(); itVar != left.parameters.end(); itVar++, itValue++) {
            if (isVariable(*itVar)){
                for (itOut = out.begin(); itOut != out.end(); itOut++) {
                    itOut->replaceParameters(*itVar, *itValue);
                }
            }
        }

    }
    //if right CS do the same for right input
    if (isRightContextSensitive) {
        for(vector<string>::iterator itVar = right.parameters.begin(), itValue = r.parameters.begin(); itVar != right.parameters.end(); itVar++, itValue++) {
            if (isVariable(*itVar)){
                for (itOut = out.begin(); itOut != out.end(); itOut++) {
                    itOut->replaceParameters(*itVar, *itValue);
                }
            }
        }
    }
    //evaluate parameters
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
    cout<<" Left ";
    left.printState();
    cout<<" Right ";
    right.printState();
    cout<<" Probability ";
    cout<<probability;
    cout<<endl;
}