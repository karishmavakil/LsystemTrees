//
//  Parser.cpp
//  LsystemTrees
//
//  Created by Karishma Vakil on 02/02/2018.
//  Copyright © 2018 Karishma Vakil. All rights reserved.
//


// standard C++ libraries
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <vector>
#include <stack>
#include <fstream>
#include <cstdlib>
#include <regex>
#include <sstream>
using namespace std;

regex num ("\\-?\\d+(\\.\\d+)?");
regex variable ("[a-z]");
regex parameterList ("[{][^\\[\\]{}]+[}]");
//regex op ("[+|-|*|/]");


bool isNumber(string s) {
    return regex_match(s, num);
}
bool isOperator(string s) {
    return (s=="+"||s=="-"||s=="*"||s=="/"||s=="=="||s=="<"||s==">");
}
bool isVariable(string a) {
    return regex_match(a, variable);
}
bool isBracket(string b) {
    return (b == "(" || b == ")");
}
//removes white space from front and back on a string
string trim(string str) {
    //find the first not space position
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first) {
    //if that's then end then the whole string is just spaces so clear the string completely
        return "";
    }
    //find the last not space position
    size_t last = str.find_last_not_of(' ');
    //from first, get the last - first + 1 characters so [first...last]
    return str.substr(first, (last - first + 1));
}
int getOperatorWeight(string op)
{
    //valid operator check is done when it is used so not doing it inside
    int weight = -1;
    if (op=="*" | op=="/") {
        weight =50;
    }
    else if (op=="+" | op=="-") {
        weight = 40;
    }
    else if (op=="==" | op==">" | op=="<") {
        weight = 30;
    }
    return weight;
}

bool hasHigherPrecedence(string op1, string op2) {
    if (!isOperator(op1) || !isOperator(op2)){
        cout<<"Invalid input "<<op1<<" "<<op2<<endl;
    }
    return getOperatorWeight(op1) >= getOperatorWeight(op2);
}

//converts infix to postfix
//handles white space trimming of input expression, tokens, returned expression, empty input, invalid token
string toPostfix(string expression) {
    //we trim the string
    stringstream exp(trim(expression));
    string token;
    stack<string> expStack;
    //updated expression
    string postfixExpression = "";
    //space separated strings should be tokens
    while (getline(exp, token, ' ')) {
        //trimming each token - so any postfix expression will always be formatted correctly
        token = trim(token);
        if (token=="") {
            continue;
        }
        if(!isNumber(token) && !isVariable(token) && !isOperator(token) && !isBracket(token)) {
            cout<<"Invalid token encountered "<<"\""<<token<<"\""<<endl;
            break;
        }
        if (isNumber(token)) {
            postfixExpression+=token;
            postfixExpression+=" ";
        }
        else if (isOperator(token)) {
            while (!expStack.empty() && expStack.top()!="(" && hasHigherPrecedence(expStack.top(), token)) {
                postfixExpression+=expStack.top();
                postfixExpression+=" ";
                expStack.pop();
            }
            expStack.push(token);
        }
        else if (token=="("){
            expStack.push(token);
        }
        else if (token==")"){
            while (!expStack.empty() && expStack.top()!="(") {
                //don't put in the ")"
                //put in the others until the "("
                postfixExpression+=expStack.top();
                postfixExpression+=" ";
                expStack.pop();
            }
            //removing "(" from the stack
            expStack.pop();
        }
    }
    while (!expStack.empty()) {
        postfixExpression += expStack.top();
        expStack.pop();
        postfixExpression+=" ";
    }
//  trimming final expression
    return trim(postfixExpression);
}
// return a1 op b1
string eval(string a1, string op, string b1) {
    if (!isOperator(op)) {
        cout<<"Invalid operator "<<op<<endl;
    }
    float a = stof(a1);
    float b = stof(b1);
    string ans = "";
    if (op=="+") {
        ans = to_string(a + b);
    }
    else if (op=="-") {
        ans = to_string(a - b);
    }
    else if (op=="*") {
        ans = to_string(a * b);
    }
    else if (op=="/") {
        ans = to_string(a / b);
    }
    else if (op=="==") {
        ans = to_string(a == b);
    }
    else if (op==">") {
        ans = to_string(a > b);
    }
    else if (op=="<") {
        ans = to_string(a < b);
    }
    return ans;
}
//return evaluated postfix expression - could be a number or 0 or 1 if boolean
string evaluatePostfix(string postfixExpression) {
    //string will be trimmed correctly at this point, so nothing to worry about
    //further checks below so that expression can def be evaluated
    stringstream exp(postfixExpression);
    string token;
    //evalStack will hold numbers only
    stack<string> evalStack;
    string output;
    string a,b;
    
    while (getline(exp, token, ' ')) {
        if (isNumber(token)) {
            evalStack.push(token);
        }
        else if(isOperator(token)) {
            a = evalStack.top();
            evalStack.pop();
            b = evalStack.top();
            evalStack.pop();
            evalStack.push(eval(b, token, a));
        }
        else {
            cout<<"Invalid token encountered - not a number or operator: "<<token<<endl;
            break;
        }
    }
    if (! (evalStack.size() == 1)) {
        cout<<"Something went wrong while evaluating... check the expression :"<<endl;
        return "0";
    }
    return evalStack.top();
}
//evaluate an infix expression
string evaluateInfix(string infixExpression) {
    //checking only num op or () is in toPostfix
    //trimming happens in toPostfix
    string postfix = toPostfix(infixExpression);
    //check only numbers and operators is in evaluatepostfix
    //so nothing to worry about regarding expressions having spaces or incorrect form while passing them here, it will be caught
    return evaluatePostfix(postfix);
}
//enter a comma separated list of parameters enclosed in {} without any brackets like [, ]
//parameters should be numbers or variables or expressions
//expressions should have tokens separated by spaces
vector<string> parseParameters(string param) {
    //the string will look like this { , , , }
    //{} will be taken off
    //expressions separated by commas and trimmed
    //other than that expression itself could be incorrect
    //but the expression will not have []{} to confuse with other brackets
    //if there is no parameters just return empty
    vector<string> paramList;
    
    if (param.empty()){
        return paramList;
    }
    if(!regex_match(param, parameterList)) {
        cout<<"Invalid parameter list "<<param<<endl;
        return paramList;
    }
    string p = param.size()>1 ? param.substr(1, param.size()-2) : "";
    stringstream ss(p);
    string val;
    while (getline(ss, val, ',')){
        paramList.push_back(trim(val));
    }
    return paramList;
}

