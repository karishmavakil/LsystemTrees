//
//  Rule.cpp
//  LsystemTrees
//
//  Created by Karishma Vakil on 14/01/2018.
//  Copyright © 2018 Karishma Vakil. All rights reserved.
//

#include "Rule.hpp"
#include <functional>

Rule::Rule(Symbol in) : input(in){
    input = in;
    parametric = true;
}
Rule::Rule(Symbol in, vector<Symbol> out) : input(in){
    input = in;
    parametric = false;
    output = out;
}
bool Rule::isApplicable(Symbol in){
    return (in.letter==input.letter);
}
vector<Symbol> Rule::apply(Symbol in){
    return output;
}
void Rule::printState() {
    cout<<"Input ";
    input.printState();
    cout<<" "<<"Output ";
    for (vector<Symbol>::iterator it = output.begin(); it != output.end(); ++it){
        it->printState();
    }
    cout<<endl;
}