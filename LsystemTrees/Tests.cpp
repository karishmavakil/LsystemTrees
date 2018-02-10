//
//  Tests.cpp
//  LsystemTrees
//
//  Created by Karishma Vakil on 27/01/2018.
//  Copyright © 2018 Karishma Vakil. All rights reserved.
//

#include <iostream>
#define _USE_MATH_DEFINES

//GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>


// standard C++ libraries
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <vector>
#include <list>
#include <fstream>
#include <cstdlib>


#include "Window.hpp"
#include "Shaders.hpp"
#include "Turtle.hpp"
#include "Symbol.hpp"
#include "JSONReader.hpp"
#include "Tests.hpp"
#include "TurtleInterpreter.hpp"

using namespace std;

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/ext.hpp"

using namespace glm;

void testTurtle(){
    Turtle turtle = Turtle();
    turtle.printState();
    cout<<endl;
    cout<<"position: " <<to_string(turtle.getPosition())<<endl;
    cout<<"heading: "<<to_string(turtle.getHeading())<<endl;
    cout<<"left: "<<to_string(turtle.getLeft())<<endl;
    cout<<"up: "<<to_string(turtle.getUp())<<endl;
    
    cout<<"Checking movement of turtle"<<endl;
    turtle.forward(5);
    turtle.printState();
    cout<<endl;
    //    cout<<"position: " <<to_string(turtle.getPosition())<<endl;
    //    cout<<"heading: "<<to_string(turtle.getHeading())<<endl;
    //    cout<<"left: "<<to_string(turtle.getLeft())<<endl;
    //    cout<<"up: "<<to_string(turtle.getUp())<<endl;
    cout<<"yaw"<<endl;
    turtle.yaw(-M_PI/2);
    turtle.printState();
    cout<<"forward"<<endl;
    
    turtle.forward(3);
    turtle.printState();
    cout<<endl;
    //    cout<<"position: " <<to_string(turtle.getPosition());
    //    cout<<"heading: "<<to_string(turtle.getHeading());
    //    cout<<"left: "<<to_string(turtle.getLeft());
    //    cout<<"up: "<<to_string(turtle.getUp());
    cout<<"pitch"<<endl;
    turtle.pitch(M_PI/3);
    turtle.printState();
    cout<<"forward"<<endl;
    turtle.forward(8);
    turtle.printState();
    cout<<"roll"<<endl;
    turtle.roll(-M_PI/2);
    turtle.printState();
    cout<<"forward"<<endl;
    turtle.forward(3);
    turtle.printState();
    cout<<"yaw"<<endl;
    turtle.yaw(M_PI/4);
    turtle.printState();
    cout<<"forward"<<endl;
    turtle.forward(1.4);
    turtle.printState();
    cout<<"pitch"<<endl;
    turtle.pitch(-M_PI/3);
    turtle.printState();
    cout<<"forward"<<endl;
    turtle.forward(2);
    turtle.printState();
    
    cout<<"Testing setters"<<endl;
    turtle.setPosition(1.0f, 2.3f, 4.5f);
    turtle.setHeading(0, 1, 0);
    turtle.setUp(0, 0, 1);
    turtle.setLeft(-1, 0, 0);
    turtle.printState();
    
    cout<<"1.00000453, 0.000536, -0.999999943 "<<to_string(round(vec3(1.00000453f, 0.000536f, -0.999943f)))<<endl;
    cout<<"0.000003, 0.0536, -1.9943 "<<to_string(round(vec3(0.000003f, 0.0536f, -1.9943f)));
}

void testSymbol() {
    Symbol s = Symbol('k');
    s.printState();
    cout<<endl<<"Testing parameters: "<<endl;
    vector<GLfloat> p = s.getParameters();
    if (p.empty()) {
        cout<<"no parameters "<<endl;
    }
    for(vector<GLfloat>::iterator it = p.begin(); it != p.end(); it++){
        cout<<*it<<" "<<*it+1<<". ";
    }
    string para = "{1.0,2.2,3}";
    Symbol s2 = Symbol('h', para);
    s2.printState();
    cout<<endl<<"Testing parameters: "<<endl;
    vector<GLfloat> p2 = s2.getParameters();
    for(vector<GLfloat>::iterator it = p2.begin(); it != p2.end(); it++){
        cout<<*it<<" "<<*it+1<<". ";
    }
    cout<<endl;
    para = "{1.0 + 5, 2.2 ,3 * ( 2.0 - 1.1 ) }";
    Symbol s3 = Symbol('h', para);
    s3.printState();
    s3.evaluateParameters();
    s3.printState();
    cout<<endl<<"Testing parameters: "<<endl;
    
    vector<GLfloat> p3 = s3.getParameters();
    for(vector<GLfloat>::iterator it = p3.begin(); it != p3.end(); it++){
        cout<<*it<<" "<<*it+1<<". ";
    }
    cout<<endl;
    cout<<s2.equals(s2)<<endl;
    cout<<Symbol('H').equals(s)<<endl;

    cout<<endl<<endl;
    cout<<"Testing parameter evaluation and getParameters"<<endl;
    Symbol y = Symbol('S', "{1 + 2.0 + 3, 5 * 2.1, 6.2 / 2}");
    y.printState();
    cout<<endl;
    y.evaluateParameters();
    y.printState();
    cout<<endl;
    vector<GLfloat> py = y.getParameters();
    cout<<endl;
    for(vector<GLfloat>::iterator it = py.begin(); it != py.end(); it++){
        cout<<*it<<" "<<*it+1<<" . ";
    }
    cout<<endl;
    Symbol z = Symbol('A', "{1 + 2.0 8 + 3, 5 * 2.1, 6.2 / 2}");
    z.printState();
    cout<<endl;
    z.evaluateParameters();
    z.printState();
    cout<<endl;
    vector<GLfloat> pz = z.getParameters();
    for(vector<GLfloat>::iterator it = pz.begin(); it != pz.end(); it++){
        cout<<*it<<" "<<*it*2.1<<" . ";
    }
    cout<<endl;
    y = Symbol('[', "{1 + -2.0 + 3, 5 * -2.1, 6.2 / 2}");
    y.printState();
    cout<<endl;
    y.evaluateParameters();
    y.printState();
    cout<<endl;
    py = y.getParameters();
    for(vector<GLfloat>::iterator it = py.begin(); it != py.end(); it++){
        cout<<*it<<" "<<*it+1<<" . ";
    }
    cout<<endl;
    z = Symbol('+', "{1 + 2.0, -8 + 3, ( 5 * 2.1 ) + 1, 6.2 / 2}");
    z.printState();
    cout<<endl;
    z.evaluateParameters();
    z.printState();
    cout<<endl;
    pz = z.getParameters();
    for(vector<GLfloat>::iterator it = pz.begin(); it != pz.end(); it++){
        cout<<*it<<" "<<*it/0.5<<" . ";
    }
    cout<<endl;
    cout<<"Testing replace variable "<<endl;
    Symbol x = Symbol('X', "{1 + 2.0 + 3, x + 5 * 2.1, 6.2 / 2 - x}");
    x.printState();
    cout<<endl;
    x.replaceParameters("x", "1.564");
    x.printState();
    cout<<endl;
    x = Symbol('X', "{1 + 2.0 + 3, x + 5 * 2.1, 6.2 / 2 - x}");
    x.printState();
    cout<<endl;
    x.replaceParameters("X", "1.564");
    x.printState();
    cout<<endl;
    x = Symbol('X', "{1 + 2.0 + 3, x + 5 * 2.1, 6.2 / 2 - x}");
    x.printState();
    cout<<endl;
    x.replaceParameters("a", "1.564");
    x.printState();
    cout<<endl;
    x = Symbol('X', "{1 + -2.0 + y, x + 5 * -2.1, 6.2 / z - x}");
    x.printState();
    cout<<endl;
    x.replaceParameters("x", "1.564");
    x.printState();
    cout<<endl;
    x.replaceParameters("y", "0");
    x.printState();
    cout<<endl;
    x.replaceParameters("z", "4.3");
    x.printState();
    cout<<endl;

}
void testList(){
    list<int> l = list<int>();
    l.push_back(5);
    list<int>::iterator it = l.begin();
    cout<<*it<<endl;
    l.push_back(6);
    it++;
    cout<<*it<<endl;
}
void testLSystem(){
    vector<Symbol> output = vector<Symbol>();
    Symbol s = Symbol('A');
    output.push_back(s);
    output.push_back(Symbol('B'));
    Rule rule1 = Rule(Symbol('A'), output);
    rule1.printState();
    cout<<endl;
    output.clear();
    output.push_back(Symbol('C'));
    Rule rule2 = Rule(Symbol('B'), output);
    rule2.printState();
    cout<<endl;
    output.clear();
    output.push_back(Symbol('D'));
    output.push_back(Symbol('B'));
    output.push_back(Symbol('D'));
    Rule rule3 = Rule(Symbol('C'), output);
    rule3.printState();
    vector<Rule> rules = vector<Rule>();
    rules.push_back(rule1);
    rules.push_back(rule2);
    rules.push_back(rule3);
    LSystem d0l = LSystem(Symbol('A'), rules);
    cout<<"Current ";
    d0l.printCurrent();
    cout<<endl;
    d0l.applyRules();
    d0l.applyRules();
    d0l.applyRules();
    d0l.applyRules();
    d0l.applyRules();
    d0l.applyRules(3);
    output.clear();
    output.push_back(Symbol('B'));
    output.push_back(Symbol('B'));
    rules.clear();
    rules.push_back(Rule(Symbol('A'), output));
    output.clear();
    output.push_back(Symbol('A'));
    output.push_back(Symbol('B'));
    output.push_back(Symbol('A'));
    rules.push_back(Rule(Symbol('B'), output));
    LSystem d0l2 = LSystem('B', rules);
    d0l2.applyRules(5);
    d0l2.clear();
    d0l2.applyRules();
    
}
//not using this currently
vector<Symbol> testD0LSystemTurtle() {
    vector<Symbol> output = vector<Symbol>();
    Symbol s = Symbol('F');
    output.push_back(s);
    output.push_back(Symbol('+'));
    output.push_back(Symbol('F'));
    
    Rule rule1 = Rule(Symbol('F'), output);
    rule1.printState();
    cout<<endl;
    output.clear();
    output.push_back(Symbol('-'));
    output.push_back(Symbol('F'));
    
    Rule rule2 = Rule(Symbol('-'), output);
    rule2.printState();
    cout<<endl;
    output.clear();
    output.push_back('+');
    output.push_back('F');
    output.push_back('-');
    Rule rule3 = Rule(Symbol('+'), output);
    vector<Rule> rules = vector<Rule>();
    rules.push_back(rule1);
    rules.push_back(rule2);
    rules.push_back(rule3);
    LSystem d0l = LSystem(Symbol('F'), rules);
    cout<<"Current ";
    d0l.printCurrent();
    cout<<endl;
    d0l.applyRules();
    d0l.applyRules();
    
    return d0l.current;
}

vector<Symbol> testTree() {
    vector<Symbol> output = vector<Symbol>();
    Symbol s = Symbol('F');
    //    output.push_back(Symbol('F'));
    //    output.push_back(Symbol('['));
    //    output.push_back(Symbol('+'));
    //    output.push_back(Symbol('F'));
    //    output.push_back(Symbol(']'));
    //    output.push_back(Symbol('F'));
    //    output.push_back(Symbol('['));
    //    output.push_back(Symbol('-'));
    //    output.push_back(Symbol('F'));
    //    output.push_back(Symbol(']'));
    //    output.push_back(Symbol('F'));
    output.push_back(Symbol('F'));
    output.push_back(Symbol('['));
    output.push_back(Symbol('+'));
    output.push_back(Symbol('F'));
    output.push_back(Symbol(']'));
    output.push_back(Symbol('['));
    output.push_back(Symbol('%'));
    output.push_back(Symbol('F'));
    output.push_back(Symbol('-'));
    output.push_back(Symbol('%'));
    
    output.push_back(Symbol('F'));
    output.push_back(Symbol(']'));
    output.push_back(Symbol('%'));
    output.push_back(Symbol('F'));
    
    output.push_back(Symbol('['));
    output.push_back(Symbol('/'));
    output.push_back(Symbol('F'));
    output.push_back(Symbol(']'));
    output.push_back(Symbol('F'));
    
    
    Rule rule1 = Rule(Symbol('F'), output);
    rule1.printState();
    vector<Rule> rules = vector<Rule>();
    rules.push_back(rule1);
    LSystem d0l = LSystem(Symbol('F'), rules);
    cout<<"Current ";
    d0l.printCurrent();
    cout<<endl;
    d0l.applyRules(4);
    return d0l.current;
}

void testJSONReader(){
    TurtleInterpreter interpreter = createInterpreter("/Users/karishmavakil/Documents/Project/LSystemTrees/LSystemTrees/file.json");
    cout<<"Current ";
    interpreter.generateInformation();
    interpreter.printVariables();;
}

void testNewTurtle() {
    Turtle turtle = Turtle();
    turtle.printState();
    cout<<endl;
    turtle.forward(5);
    turtle.printState();
    cout<<endl;
    turtle.pitch(M_PI/4);
    turtle.printState();
    cout<<endl;
    turtle.yaw(M_PI/2);
    turtle.printState();
    cout<<endl;
    turtle.forward(3);
    turtle.printState();
    cout<<endl;
    turtle.roll(M_PI/5);
    turtle.printState();
    cout<<endl;
    turtle.pitch(M_PI/3);
    turtle.printState();
    cout<<endl;
    turtle.forward(8);
    turtle.printState();
    
}

void testParser(){
    
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<(toPostfix("5.2 + 4.7 - 5.3 / 6 * 3 / 2 + 45.0 ")=="5.2 4.7 + 5.3 6 / 3 * 2 / - 45.0 +")<<endl;
    cout<<(toPostfix("( 4 - 5 ) * 1.0 / 4.5 - 6.7 / ( 2 - 4 ) ")=="4 5 - 1.0 * 4.5 / 6.7 2 4 - / -")<<endl;
    cout<<(toPostfix("1 - 2 - 3 - 4 * ( 6 - 2 - 6.5 ) - 0.0 * 2.2 / ( 5 - 5 - 1 )")=="1 2 - 3 - 4 6 2 - 6.5 - * - 0.0 2.2 * 5 5 - 1 - / -")<<endl;
    cout<<"testing eval"<<endl;
    string exp = toPostfix("( 1 + 2 ) * 3 + 4 - 6 / 2");
    cout<<evaluatePostfix(exp)<<endl;
    exp = toPostfix("5.2 + 4.7 - 5.3 / 6 * 3 / 2 + 45.0");
    cout<<evaluatePostfix(exp)<<endl;
    exp = toPostfix("( 4 - 5 ) * 1.0 / 4.5 - 6.7 / ( 2 - 4 )");
    
    cout<<evaluatePostfix(exp)<<endl;
    
    cout<<"Testing evaluateCondition"<<endl;
    exp = "1 - 2 - 3 - 4 * ( 6 - 2 - 6.5 ) > 2.2 / ( 5 - 5 - 1 )";
    cout<<"1 - 2 - 3 - 4 * ( 6 - 2 - 6.5 ) > 2.2 / ( 5 - 5 - 1 ) True";
    cout<<evaluateCondition(exp)<<endl;
    
    exp = "1 - 2 - 3 - 4 * ( 6 - 2 - 6.5 ) + 6 == 0.0 * 2.2 / ( 5 - 5 - 1 )";
    cout<<"1 - 2 - 3 - 4 * ( 6 - 2 - 6.5 ) + 6 == 0.0 * 2.2 / ( 5 - 5 - 1 ) False";
    cout<<evaluateCondition(exp)<<endl;
    exp = "1 == 1 ";
    cout<<"1 == 1 True";
    cout<<evaluateCondition(exp)<<endl;
    exp = "2 + 3 == 5";
    cout<<"2 + 3 == 5 True ";
    cout<<evaluateCondition(exp)<<endl;
    exp = "4 * 1 == 4 / 1 ";
    cout<<"4 * 1 == 4 / 1 True ";
    cout<<evaluateCondition(exp)<<endl;
    exp = "1.3  > 8.2";
    cout<<"1.3 > 8.2  False ";
    cout<<evaluateCondition(exp)<<endl;
    exp = "1.6 * 9.0 < 9   ";
    cout<<"1.6 * 9.0 < 9  False ";
    cout<<evaluateCondition(exp)<<endl;
    exp = " 1.4 * 9 > 8.435";
    cout<<"1.4 * 9 > 8.435  True ";
    cout<<evaluateCondition(exp)<<endl;
    exp = " 1.4 * 9 > 8.435  && 1 == 1";
    cout<<"1.4 * 9 > 8.435   && 1 == 1 True ";
    cout<<evaluateCondition(exp)<<endl;
    exp = " 1.4 * 9 > 8.435 && ( 2 == 1 ) ";
    cout<<"1.4 * 9 > 8.435  && ( 2 == 1 ) False ";
    cout<<evaluateCondition(exp)<<endl;
    exp = "1.4 * 9 < 8.435 || 3 > 2";
    cout<<"1.4 * 9 < 8.435 || 3 > 2 True ";
    cout<<evaluateCondition(exp)<<endl;
    exp = "1.4 * 9 < 8.435 || 3 > 2 + 4";
    cout<<"1.4 * 9 < 8.435 || 3 > 2 + 4 False ";
    cout<<evaluateCondition(exp)<<endl;
    exp = "1.4 * 9 + 8.435 || 3 - 2";
    cout<<"1.4 * 9 + 8.435 || 3 - 2";
    cout<<evaluateCondition(exp)<<endl;
    
    
    cout<<"Testing evaluate infix"<<endl;
    
    cout<<"2 + 3 * 6 * 5 / 6 + ( 4 - 3 ) - ( 7 - 1 ) : "<<evaluateInfix("2 + 3 * 6 * 5 / 6 + ( 4 - 3 ) - ( 7 - 1 )")<<endl;
    cout<<"2.000001 + 3 * 6 - 5 / 6.3 + ( 4 / 3 ) - ( 7 + 1 ) : "<<evaluateInfix("2.000001 + 3 * 6 - 5 / 6.3 + ( 4 / 3 ) - ( 7 + 1 )")<<endl;
    cout<<"2 + ( 3 * 6 ) * 5.1 / ( 6 + ( 4 * 3 ) ): "<<evaluateInfix("2 + ( 3 * 6 ) * 5.1 / ( 6 + ( 4 * 3 ) )")<<endl;
    cout<<"( 2 + 3 ) * 6 * 5.0 / 6 + ( 7.345 - 1.34 ) : "<<evaluateInfix("( 2 + 3 ) * 6 * 5.0 / 6 + ( 7.345 - 1.34 )")<<endl;
    cout<<"2 + 3 * 6 * 5 / 6 + ( 4 3 ) - ( 7 - 1 ) : error "<<evaluateInfix("2 + 3 * 6 * 5 / 6 + ( 4 3 ) - ( 7 - 1 )")<<endl;
    cout<<"2.000001 + 3 * 6 - 5 / A 6.3 + ( 4 / 3 ) - ( 7 + 1 ) : error "<<evaluateInfix("2.000001 + 3 * 6 - 5 A / 6.3 + ( 4 / 3 ) - ( 7 + 1 )")<<endl;
    cout<<"2 + ( 3 * 6 )) * 5.1 / ( 6 + ( 4 * 3 ) : error "<<evaluateInfix("2 + ( 3 * 6 )) * 5.1 / ( 6 + ( 4 * 3 )")<<endl;
    cout<<"2 + 3 * 6 * 5 / 6 + ( 4 - 3 ) - ( 7 - 1 ) : "<<evaluateInfix("2 + 3 * 6 * 5 / 6 + ( 4 - 3 ) - ( 7 - 1 )")<<endl;
    cout<<"2.000001 + 3 * -6 - 5 / 6.3 + ( 4 / 3 ) - ( 7 + 1 ) : "<<evaluateInfix("2.000001 + 3 * -6 - 5 / 6.3 + ( 4 / 3 ) - ( 7 + 1 )")<<endl;
    cout<<"2 + ( 3 * 6 ) * 5.1 / ( 6 + ( 4 * 3 ) ): "<<evaluateInfix("2 + ( 3 * 6 ) * 5.1 / ( 6 + ( 4 * 3 ) )")<<endl;
    cout<<"( 2 + 3 ) * 6 * -5.0 / 6 + ( 7.345 - 1.34 ) : "<<evaluateInfix("( 2 + 3 ) * 6 * -5.0 / 6 + ( 7.345 - 1.34 )")<<endl;
    cout<<"2 + 3 * 6 * 5 / 6 + ( 4 + 3 ) - ( 7 - -1 ) : "<<evaluateInfix("2 + 3 * 6 * 5 / 6 + ( 4 + 3 ) - ( 7 - -1 )")<<endl;
    cout<<"-2.000001 + 3 * 6 - 5 / 6.3 + ( 4 / 3 ) - ( 7 + 1 ) : "<<evaluateInfix("-2.000001 + 3 * 6 - 5 / 6.3 + ( 4 / 3 ) - ( 7 + 1 )")<<endl;
    cout<<"-2 + ( 3 * -6 ) * 5.1 / ( 6 + ( 4 * 3 ) ): "<<evaluateInfix("-2 + ( 3 * -6 ) * 5.1 / ( 6 + ( 4 * 3 ) )")<<endl;
    
    
    cout<<"Testing trim: "<<endl;
    cout<<"\""<<trim("  dfdfhkj dfgh , dgdfhgkj,gfs")<<"\""<<endl;
    cout<<"\""<<trim("dfd  fhkj dfgh , dgdfhgkj,gfs")<<"\""<<endl;
    cout<<"\""<<trim("  dfdfhkj dfgh , dgdfhgkj,gfs   \n")<<"\""<<endl;
    cout<<"\""<<trim("  dfdfhkj dfgh , dg  dfhgkj,gfs")<<"\""<<endl;
    cout<<"\""<<trim("      ")<<"\""<<endl;

    cout<<"Testing isVariable, number, operator"<<endl;
    cout<<"isop + "<<isOperator("+")<<endl;
    cout<<"isop - "<<isOperator("-")<<endl;
    cout<<"isop da "<<isOperator("da")<<endl;
    cout<<"isvar x "<<isVariable("x")<<endl;
    cout<<"isvar X "<<isVariable("X")<<endl;
    cout<<"isvar 0 "<<isVariable("0")<<endl;
    cout<<"isnum 5 "<<isNumber("5")<<endl;
    cout<<"isnum 6.45234 "<<isNumber("6.45234")<<endl;
    cout<<"isnum 0.0 "<<isNumber("0.0")<<endl;
    cout<<"isnum . "<<isNumber(".")<<endl;
    cout<<"isnum -2 "<<isNumber("-2")<<endl;
    cout<<"isnum -2.345 "<<isNumber("-2.345")<<endl;

    cout<<"Testing parseParameters";
    cout<<"{1,0, 2 + 4, x + 7.0 , 2 * 6 , 5 }"<<endl;
    parseParameters("{1,0, 2 + 4, x + 7.0 , 2 * 6 , 5 }");
    cout<<"{1,0, 5 ,2 + 4, ( x + 7.0 ) * 5, 4.55555 , 2 * 6.3 , 5.1 }"<<endl;
    parseParameters("{1,0, 5 ,2 + 4, ( x + 7.0 ) * 5, 4.55555 , 2 * 6.3 , 5.1 }");
    cout<<"{1,0.0 , a , b,c * 5.245 , 5 }"<<endl;
    parseParameters("{1,0.0 , a , b,c * 5.245 , 5 }");
    cout<<"Testing eval";
    cout<<"eval 1 + 2 "<<eval("1", "+", "2")<<endl;
    cout<<"eval \" 1.00 \" + 2 "<<eval("1.00 ", "+", "2")<<endl;
    cout<<"eval 1 * -2 "<<eval("1", "*", "-2")<<endl;
    cout<<"eval 1 $ 2 "<<eval("1", "$", "2")<<endl;
    cout<<"eval 1 + 5.3453 "<<eval("1", "+", "5.3453")<<endl;
    cout<<"eval 1 / -5.3453 "<<eval("1", "/", "-5.3453")<<endl;
    cout<<"eval 1 || 0 "<<eval("1", "||", "0")<<endl;
    cout<<"eval 1.00 || 0 "<<eval("1.00", "||", "0")<<endl;
    cout<<"eval 0 || 0 "<<eval("0", "||", "0")<<endl;
    cout<<"eval 0.00 || 1 "<<eval("0.00", "||", "1")<<endl;
    cout<<"eval 1 && 1.0 "<<eval("1", "&&", "1.0")<<endl;
    cout<<"eval 0 && 1.0 "<<eval("0", "&&", "1.0")<<endl;
    cout<<"eval 1 && 0.0 "<<eval("1", "&&", "0.0")<<endl;
    cout<<"eval 0 && 0.0 "<<eval("0", "&&", "0.0")<<endl;

    cout<<"Testing getOperatorWeight"<<endl;
    cout<<"+ :"<<getOperatorWeight("+")<<endl;
    cout<<"- :"<<getOperatorWeight("-")<<endl;
    cout<<"& :"<<getOperatorWeight("&")<<endl;
    cout<<"/ :"<<getOperatorWeight("/")<<endl;
    cout<<"== :"<<getOperatorWeight("==")<<endl;
    cout<<"> :"<<getOperatorWeight(">")<<endl;
    cout<<"&& :"<<getOperatorWeight("&&")<<endl;
    cout<<"|| :"<<getOperatorWeight("||")<<endl;

    cout<<"Testing contains no variables"<<endl;
    cout<<containsNoVariables("2 + 3 * 6 * 5 / 6 + ( || 4 - 3 ) - ( 7 - 1 )")<<endl;
    cout<<containsNoVariables("2.000001 + 3 * 6 - 5 / 6.3 + ( 4 / 3 ) - ( 7 + 1 ) ")<<endl;
    cout<<containsNoVariables("2 + ( 3 * 6 ) * 5.1 / ( 6 + ( 4 * 3 ) ) ")<<endl;
    cout<<containsNoVariables("( 2 + 3 ) * 6 * 5.0 / 6 + ( 7.345 - 1.34 ) x ")<<endl;
    cout<<containsNoVariables("2 + 3 * 6 * 5 / A + ( 4  &&3 ) - ( 7 - 1 )  ")<<endl;
    cout<<containsNoVariables("2.000001 + 3 * 6 - 5 / A 6.3 + ( 4 // 3 ) - ( 7 + 1 )")<<endl;
    cout<<containsNoVariables("2 + ( 3 *  >6 )) * 5.1 / ( 6 + ( 4 * 3 ) : error ")<<endl;
    cout<<containsNoVariables("2 + 3 * 6 * 5 / 6 + ( 4 - 3 ) - ( 7 - 1 ) && 1 == 2")<<endl;
    cout<<containsNoVariables("2.000001 + 3 * -6 - < 5 / 6.3 + ( 4 / 3 ) - ( 7 + 1 )")<<endl;

    
}
void testRule() {
    vector<Symbol> output;
    Rule r1 = Rule(Symbol('F', "{3}"), output);
    cout<<"isApplicable "<<r1.isApplicable(Symbol('F', "{3}"))<<endl;
    cout<<"isApplicable "<<r1.isApplicable(Symbol('G', "{3}"))<<endl;
    cout<<"isApplicable "<<r1.isApplicable(Symbol('F', "{1}"))<<endl;
    cout<<"isApplicable "<<r1.isApplicable(Symbol('F', "{}"))<<endl;
    cout<<"isApplicable "<<r1.isApplicable(Symbol('F', "{A,  5)"))<<endl;
    cout<<endl;
    r1 = Rule(Symbol('F', "{x}"), output);
    cout<<"isApplicable "<<r1.isApplicable(Symbol('F', "{3}"))<<endl;
    cout<<"isApplicable "<<r1.isApplicable(Symbol('G', "{3}"))<<endl;
    cout<<"isApplicable "<<r1.isApplicable(Symbol('F', "{1}"))<<endl;
    cout<<"isApplicable "<<r1.isApplicable(Symbol('F', "{1, 3}"))<<endl;
    cout<<"isApplicable "<<r1.isApplicable(Symbol('F', "{1 3}"))<<endl;
    cout<<endl;
    r1 = Rule(Symbol('F', "{x}"), "x > 3", output);
    cout<<"isApplicable "<<r1.isApplicable(Symbol('F', "{3}"))<<endl;
    cout<<"isApplicable "<<r1.isApplicable(Symbol('G', "{3.3  }"))<<endl;
    cout<<"isApplicable "<<r1.isApplicable(Symbol('F', "{3.3  }"))<<endl;
    cout<<"isApplicable "<<r1.isApplicable(Symbol('F', "{5.5}"))<<endl;
    cout<<"isApplicable "<<r1.isApplicable(Symbol('F', "{900, 3}"))<<endl;
    cout<<"isApplicable "<<r1.isApplicable(Symbol('F', "{1 3}"))<<endl;
    cout<<endl;
    r1 = Rule(Symbol('G', "{x, 6.6}"), output);
    cout<<"isApplicable "<<r1.isApplicable(Symbol('G', "{3, 6.6}"))<<endl;
    cout<<"isApplicable "<<r1.isApplicable(Symbol('G', "{3, 2.1}"))<<endl;
    cout<<"isApplicable "<<r1.isApplicable(Symbol('F', "{1}"))<<endl;
    cout<<"isApplicable "<<r1.isApplicable(Symbol('G', "{1, 6.6000}"))<<endl;
    cout<<"isApplicable "<<r1.isApplicable(Symbol('F', "{1 3}"))<<endl;
    cout<<endl;
    cout<<endl;
    r1 = Rule(Symbol('G', "{x, 6.6, y}"), output);
    cout<<"isApplicable "<<r1.isApplicable(Symbol('G', "{3, 6.6, 1}"))<<endl;
    cout<<"isApplicable "<<r1.isApplicable(Symbol('G', "{3, 2.1, 1}"))<<endl;
    cout<<"isApplicable "<<r1.isApplicable(Symbol('F', "{1}"))<<endl;
    cout<<"isApplicable "<<r1.isApplicable(Symbol('G', "{1, 6.6000, z}"))<<endl;
    cout<<"isApplicable "<<r1.isApplicable(Symbol('F', "{1 3}"))<<endl;
    cout<<endl;
    r1 = Rule(Symbol('G', "{x, 6.6, y}"), "y == 2.3", output);
    cout<<"isApplicable "<<r1.isApplicable(Symbol('G', "{3, 6.6, 2.3}"))<<endl;
    cout<<"isApplicable "<<r1.isApplicable(Symbol('G', "{3, 6.6, 2.33}"))<<endl;
    cout<<"isApplicable "<<r1.isApplicable(Symbol('G', "{3, 6.6, 2.3000}"))<<endl;
    cout<<"isApplicable "<<r1.isApplicable(Symbol('G', "{3, 6.600001, 2.300}"))<<endl;
    cout<<"isApplicable "<<r1.isApplicable(Symbol('G', "{3, 2.1, 1}"))<<endl;
    cout<<"isApplicable "<<r1.isApplicable(Symbol('F', "{1}"))<<endl;
    cout<<"isApplicable "<<r1.isApplicable(Symbol('F', "{1 3}"))<<endl;
    cout<<endl;
    r1 = Rule(Symbol('G', "{x, 6.6, y}"), "y == 2.3 && x == 4", output);
    cout<<"isApplicable "<<r1.isApplicable(Symbol('G', "{4, 6.6, 2.3}"))<<endl;
    cout<<"isApplicable "<<r1.isApplicable(Symbol('G', "{3, 6.6, 2.33}"))<<endl;
    cout<<"isApplicable "<<r1.isApplicable(Symbol('G', "{4, 6.6, 2.3000}"))<<endl;
    cout<<"isApplicable "<<r1.isApplicable(Symbol('G', "{4.00, 6.500000, 2.300}"))<<endl;
    cout<<endl;
    r1 = Rule(Symbol('G', "{x, y, z}"), "( y == 2.3 && x > 4 ) || z < 2", output);
    cout<<"isApplicable "<<r1.isApplicable(Symbol('G', "{3, 2.3, 0.3}"))<<endl;
    cout<<"isApplicable "<<r1.isApplicable(Symbol('G', "{3, 2.31, 1.33}"))<<endl;
    cout<<"isApplicable "<<r1.isApplicable(Symbol('G', "{5, 2.3, 2.3000}"))<<endl;
    cout<<"isApplicable "<<r1.isApplicable(Symbol('G', "{4.01, 2.300000, 2.300}"))<<endl;
    cout<<"Testing applying Rule"<<endl;
    output.push_back(Symbol('D', "{1,3,4}"));
    output.push_back(Symbol('B', "{( x + 1.5 ) * 2.0, y, 5.4 , 0, 0 / x, z + ( x + y + 1 ) }"));
    output.push_back(Symbol('Y'));
    r1 = Rule(Symbol('G', "{x, y, z}"), "( y == 2.3 && x > 4 ) || z < 2", output);
    cout<<"isApplicable "<<r1.isApplicable(Symbol('G', "{5.0, 2.3, 0.3}"))<<endl;
    vector<Symbol> out = r1.apply(Symbol('G',  "{5.0, 2.3, 0.3}"));
    for(vector<Symbol>::iterator it = out.begin(); it != out.end(); it++) {
        it->printState();
        cout<<" ";
    }
    cout<<endl;
    r1 = Rule(Symbol('G', "{x, y, 4}"), "( y == 2.3 && x > 4 ) || x < 2", output);
    out = r1.apply(Symbol('G',  "{5.0, 2.3, 0.3}"));
    for(vector<Symbol>::iterator it = out.begin(); it != out.end(); it++) {
        it->printState();
        cout<<" ";
    }
}

void testParametersLSystem() {
    vector<Symbol> output;
    output.push_back(Symbol('F', "{x + 1}"));
    output.push_back(Symbol('F', "{x + 0.5}"));
    
    Rule r1 = Rule(Symbol('F', "{x}"), "x < 9", output);
    r1.printState();
    vector<Rule> rules = vector<Rule>();
    rules.push_back(r1);
    
    LSystem d0l = LSystem(Symbol('F', "{5.0}"), rules);
    d0l.applyRules(9);
    d0l.clear();
    cout<<"Cleared";
    cout<<"Start "<<endl;
    d0l.start.printState();
    d0l.printCurrent();
    d0l.applyRules();

}

void testInterpreter() {
    TurtleInterpreter interpreter = TurtleInterpreter(Turtle(), LSystem());
    interpreter.printVariables();
    interpreter.generateInformation();
    interpreter.printVariables();
}
void testRegexes() {
    regex number ("\\-?\\d+(\\.\\d+)?");
    regex vari ("[a-z]");
    regex parameter ("[{][^\\[\\]{}]+[}]");
    regex symbolExp("([A-Z\\[\\]&\\-^\\\\/\\+])([{][^\\[\\]{}]+[}])?");
    regex varAss("[a-zA-Z]+\\s*=\\s*(\\d+(\\.\\d+)?)");
    regex numberExpression ("[0-9+\\-*\\/<>&|=()\\s,.]+");
    string s = "{12323, 5645 ,g}";
    cout<<s<<" "<<regex_match(s, parameter)<<endl;
    s = "{12323, 5645 ,g   })";
    cout<<s<<" "<<regex_match(s, parameter)<<endl;
    s = "{12323, 564[]5 ,g   }";
    cout<<s<<" "<<regex_match(s, parameter)<<endl;
    s = "{12323, 56.]2 , 45 ,g   }";
    cout<<s<<" "<<regex_match(s, parameter)<<endl;
    s = "{-12323, 56)45 ,g   }";
    cout<<s<<" "<<regex_match(s, parameter)<<endl;
    s = "{12323, 56}45 ,g   }";
    cout<<s<<" "<<regex_match(s, parameter)<<endl;
    s = "{12323, 56}45 ,g   }";
    cout<<s<<" "<<regex_match(s, parameter)<<endl;
    s = "0.5345";
    cout<<s<<" "<<regex_match(s, number)<<endl;
    s = "0.534.5";
    cout<<s<<" "<<regex_match(s, number)<<endl;
    s = "A";
    cout<<s<<" "<<regex_match(s, number)<<endl;
    
    s = "-0.5345";
    cout<<s<<" "<<regex_match(s, number)<<endl;
    s = "-45643";
    cout<<s<<" "<<regex_match(s, number)<<endl;
    s = "-1";
    cout<<s<<" "<<regex_match(s, number)<<endl;
    s = "-0.534.5";
    cout<<s<<" "<<regex_match(s, number)<<endl;
    s = "A";
    cout<<s<<" "<<regex_match(s, number)<<endl;
    s = "6 ";
    cout<<s<<" "<<regex_match(s, number)<<endl;
    s = "5 4";
    cout<<s<<" "<<regex_match(s, number)<<endl;
    s = "6.%";
    cout<<s<<" "<<regex_match(s, number)<<endl;
    s = "a";
    cout<<s<<" "<<regex_match(s, vari)<<endl;
    s = "B";
    cout<<s<<" "<<regex_match(s, vari)<<endl;
    s = "aaaa";
    cout<<s<<" "<<regex_match(s, vari)<<endl;
    s = "a b";
    cout<<s<<" "<<regex_match(s, vari)<<endl;
    s = "F";
    cout<<s<<" "<<regex_match(s, symbolExp)<<endl;
    s = " ";
    cout<<s<<" "<<regex_match(s, symbolExp)<<endl;
    s = "F{1, -345, }";
    cout<<s<<" "<<regex_match(s, symbolExp)<<endl;
    s = "t{343, }}";
    cout<<s<<" "<<regex_match(s, symbolExp)<<endl;
    s = "F{[a}";
    cout<<s<<" "<<regex_match(s, symbolExp)<<endl;
    s = "5{345, 534. 345}";
    cout<<s<<" "<<regex_match(s, symbolExp)<<endl;
    s = "F  {2}";
    cout<<s<<" "<<regex_match(s, symbolExp)<<endl;
    s = "[{1, 34, -5 * x + 2}";
    cout<<s<<" "<<regex_match(s, symbolExp)<<endl;
    s = "{{sf, fg}";
    cout<<s<<" "<<regex_match(s, symbolExp)<<endl;
    s = "+{rgewg, rtgert, 456345}";
    cout<<s<<" "<<regex_match(s, symbolExp)<<endl;
    s = "-{rgewg, rtgert, 456345}";
    cout<<s<<" "<<regex_match(s, symbolExp)<<endl;
    s = "[{rgewg, rtgert, 456345}";
    cout<<s<<" "<<regex_match(s, symbolExp)<<endl;
    s = "]{rgewg, rtgert, 456345}";
    cout<<s<<" "<<regex_match(s, symbolExp)<<endl;
    s = "%{rgewg, rtgert, 456345}";
    cout<<s<<" "<<regex_match(s, symbolExp)<<endl;
    s = "&{rgewg, rtgert, 456345}";
    cout<<s<<" "<<regex_match(s, symbolExp)<<endl;
    s = "^{rgewg, rtgert, 456345}";
    cout<<s<<" "<<regex_match(s, symbolExp)<<endl;
    s = "/{rgewg, rtgert, 456345}";
    cout<<s<<" "<<regex_match(s, symbolExp)<<endl;
    s = "\\{rgewg, rtgert, 456345}";
    cout<<s<<" "<<regex_match(s, symbolExp)<<endl;
    s = "abc  = 0.5";
    cout<<s<<" "<<regex_match(s, varAss)<<endl;
    s = "abc  = 5 0.5";
    cout<<s<<" "<<regex_match(s, varAss)<<endl;
    s = "ab4c  = 0.5";
    cout<<s<<" "<<regex_match(s, varAss)<<endl;
    s = "abc  == 56450.5";
    cout<<s<<" "<<regex_match(s, varAss)<<endl;
    s = "abc  = 0 5";
    cout<<s<<" "<<regex_match(s, varAss)<<endl;
    s = "a=0.5";
    cout<<s<<" "<<regex_match(s, varAss)<<endl;
    s = "123423 + - )( < | ...";
    cout<<s<<" "<<regex_match(s, numberExpression)<<endl;
    s = "123&&423 + - )( < | ...";
    cout<<s<<" "<<regex_match(s, numberExpression)<<endl;
    s = "1234+23 + - )( < | ...";
    cout<<s<<" "<<regex_match(s, numberExpression)<<endl;
    s = "123/ 423 + - )( < | ...";
    cout<<s<<" "<<regex_match(s, numberExpression)<<endl;
    s = "12/ 3423 +x - )( < | ...";
    cout<<s<<" "<<regex_match(s, numberExpression)<<endl;
    s = "123A423 + - )( < | ...";
    cout<<s<<" "<<regex_match(s, numberExpression)<<endl;
    
}


