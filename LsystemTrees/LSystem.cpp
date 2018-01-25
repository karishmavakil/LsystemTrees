//
//  LSystem.cpp
//  LsystemTrees
//
//  Created by Karishma Vakil on 14/01/2018.
//  Copyright © 2018 Karishma Vakil. All rights reserved.
//

#include "LSystem.hpp"

LSystem::LSystem(Symbol start, vector<Rule> ruleset) {
    current = vector<Symbol>();
    current.push_back(start);
    rules = vector<Rule>();
    rules = ruleset;
}
void LSystem::printCurrent() {
    for (vector<Symbol>::iterator it = current.begin(); it != current.end(); ++it){
        it->printState();
    }
    cout<<endl;
}
void LSystem::applyRules(){
    //iterator over rules
    vector<Rule>::iterator itRul = rules.begin();
    //creating updated vector
    vector<Symbol> updated = vector<Symbol>();
    //iterate through current vector of symbols
    for (vector<Symbol>::iterator itCur = current.begin(); itCur!= current.end(); itCur++) {
        cout<<"current symbol ";
        itCur->printState();
        bool found = false;
        //iterate over all rules
        for(itRul = rules.begin(); itRul!= rules.end(); itRul++) {
            cout<<" rule input ";
            itRul->input.printState();
            //if you find a rule whose input matches the current Symbol
            if(itRul->isApplicable(*itCur)){
                cout<<" matched ";
                //find the output of the rule
                vector<Symbol> out = itRul->apply(*itCur);
                //insert it in updated
                updated.insert(updated.end(), out.begin(), out.end());
                //rule was found
                found = true;
                break;
            }
        }
        // went through all rules, none applied, so we keep the symbol the same
        if (!found)
            updated.push_back(*itCur);
        cout<<endl;
    }
    current = updated;
    cout<<endl<<"Updated ";
    printCurrent();
}
void LSystem::applyRules(int n) {
    for (int i =0; i < n; i++) {
        applyRules();
    }
}
        