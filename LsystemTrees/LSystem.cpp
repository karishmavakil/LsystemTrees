

#include "LSystem.hpp"
#include <random>
LSystem::LSystem(Symbol s, vector<Rule> ruleset) {
    start = s;
    current = vector<Symbol>();
    current.push_back(s);
    rules = ruleset;
}
LSystem::LSystem(){
    
}
void LSystem::clear() {
    //restart from original start
    current.clear();
    current.push_back(start);
}
void LSystem::printCurrent() {
    //print each symbol
    for (vector<Symbol>::iterator it = current.begin(); it != current.end(); ++it){
        it->printState();
    }
    cout<<endl;
}
void LSystem::applyRules(){
    //iterator over rules
    int countOp = 0;
    vector<Rule>::iterator itRul = rules.begin();
    int ruleApp = 0;
    //creating updated vector
    vector<Symbol> updated = vector<Symbol>();
    //iterate through current vector of symbols
    for (vector<Symbol>::iterator itCur = current.begin(); itCur!= current.end(); itCur++) {
        
//        cout<<"current symbol ";
//        itCur->printState();
        //haven't found it yet
        bool found = false;
        float probScale = 1.0f;
        random_device rd{}; // use to seed the rng
        mt19937 rng{rd()};
        //iterate over all rules
        for(itRul = rules.begin(); itRul!= rules.end(); itRul++) {
//            cout<<" rule input ";
//            itRul->input.printState();
            //if you find a rule to which the current Symbol is applicable
            if(itRul->isApplicable(*itCur)){
//                cout<<" matched ";
                //find the output of the rule
                double p = itRul->probability / probScale;
                bernoulli_distribution d(p);
                bool yes = d(rng);
                if (yes) {
                    vector<Symbol> out = itRul->apply(*itCur);
                    ruleApp++;
                    //insert it in updated
                    countOp += out.size();
                    updated.insert(updated.end(), out.begin(), out.end());
                    //rule was found
                    found = true;
                    break;
                }
                else {
                    probScale = probScale * (1 - itRul->probability/ probScale);
                    countOp += 1;
                    continue;
                }
            }
        }
        // went through all rules, none applied, so we keep the symbol the same
        if (!found) {
            updated.push_back(*itCur);
            countOp +=1;
        }
//        cout<<endl;
    }
    current = updated;
    countOp +=1;
    cout<<"RuleApp "<<ruleApp<<endl;
    cout<<"Current Length "<<current.size()<<endl;
//    cout<<endl<<"Updated ";
//    printCurrent();
}
void LSystem::applyRulesWithContext(){
    //creating updated vector
    int ruleApp = 0;
    vector<Symbol> updated = vector<Symbol>();
    vector<Symbol>::iterator itNext = current.begin();
    itNext++;
    //iterate through current vector of symbols
    //iteration 1 ; l will be 0, determine current as itCur and r as itNext
    Symbol l = Symbol();
    Symbol r = Symbol();
    for (vector<Symbol>::iterator itCur = current.begin(); itCur!= current.end(); itCur++, itNext++) {
        //subsequently l will have been updated in last round, current input and r are given by itCur and itNext
        //itNext starts at pos 2
        //in the last iteration itNext will be meaningless. r must be assigned to empty
        if (itNext == current.end()) {
            r = Symbol();
        }
        else {
            r = *itNext;
        }
        //at this point we have the relevant l and r and current and we loop through the rules to find something relevant
        float probScale = 1.0f;
        random_device rd{}; // use to seed the rng
        mt19937 rng{rd()};
        bool found = false;
        //iterate over all rules
        for(vector<Rule>::iterator itRul = rules.begin(); itRul!= rules.end(); itRul++) {
            //            cout<<" rule input ";
//            itRul->input.printState();
            //if you find a rule to which the current Symbol is applicable with contexts l and r
            if(itRul->isApplicableWithContext(l, *itCur, r)){
                //                cout<<" matched ";
                //find the output of the rule
                double p = itRul->probability / probScale;
                bernoulli_distribution d(p);
                bool yes = d(rng);
                if (yes) {
                    vector<Symbol> out = itRul->applyWithContext(l, *itCur, r);
                    ruleApp++;
                    //insert it in updated
                    updated.insert(updated.end(), out.begin(), out.end());
                    //rule was found
                    found = true;
                    break;
                }
                else {
                    probScale = probScale * (1 - itRul->probability/ probScale);
                    continue;
                }
            }
        }
        // went through all rules, none applied, so we keep the symbol the same
        if (!found)
            updated.push_back(*itCur);
        //        cout<<endl;
        l = *itCur;
    }
    current = updated;
    cout<<"RuleApp with Context "<<ruleApp<<endl;
    cout<<"Current Length "<<current.size();

//        cout<<endl<<"Updated ";
//        printCurrent();
}
void LSystem::applyRules(int n) {
    for (int i =0; i < n; i++) {
        applyRules();
    }
}
void LSystem::applyRulesWithContext(int n) {
    for (int i =0; i < n; i++) {
        applyRulesWithContext();
    }
}
        