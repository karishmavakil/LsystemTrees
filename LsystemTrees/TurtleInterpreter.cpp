//
//  TurtleInterpreter.cpp
//  LsystemTrees
//
//  Created by Karishma Vakil on 20/01/2018.
//  Copyright © 2018 Karishma Vakil. All rights reserved.
//

#include "TurtleInterpreter.hpp"


#include <stdio.h>
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
#include <stack>
#include <sstream>
#include <regex>
#include "Turtle.hpp"
#include "Symbol.hpp"
#include "Parser.hpp"
#include "Lsystem.hpp"

using namespace std;

TurtleInterpreter::TurtleInterpreter(Turtle t, LSystem l){
    turtle = t;
    lsystem = l;
    branchRadius = 0.08f;
    branchStep = 0.4f;
    branchAngle = 0.6f;
    branchThicknessRatio = 0.87;
    branchStepRatio = 0.85;
    minRadius = 0.03;
    iterations = 5;
    useContexts = false;
};
vector<Symbol> TurtleInterpreter::getInstructions(){
    return lsystem.current;
};
vector<vec3> TurtleInterpreter::getVertices(){
    return vertices;
};
vector<vec3> TurtleInterpreter::getColours(){
    return colours;
};
vector<vec3> TurtleInterpreter::getNormals(){
    return normals;
};
vector<vec2> TurtleInterpreter::getUVs(){
    return uvs;
};
LSystem TurtleInterpreter::getLSystem(){
    return lsystem;
}
void TurtleInterpreter::refreshTurtle(){
    turtle = Turtle();
};
void TurtleInterpreter::generateInformation(){
    lsystem.clear();
    if (useContexts) {
        lsystem.applyRulesWithContext(iterations);
    }
    else {
        lsystem.applyRules(iterations);
    }
    vector<Symbol> instructions = lsystem.current;
    for(vector<Symbol>::iterator itInstr = instructions.begin(); itInstr != instructions.end(); itInstr++) {
        vector<GLfloat> p = itInstr->getParameters();
        vector<vec3> v1;
        vec3 oldPosition;
        switch (itInstr->letter) {
            case 'F':
                oldPosition = turtle.getPosition();
                turtle.forward(p[0]*branchStep);
                addCylinderVertices(oldPosition, turtle.getPosition(), turtle.getHeading(), turtle.getLeft(), branchRadius);
                //                vertices.push_back(oldPos);
                //                vertices.push_back(position);
                if (branchRadius > minRadius){
                    branchRadius = branchThicknessRatio * branchRadius;
                    branchStep = branchStepRatio * branchStep;
                }
                break;
            case 'f':
                turtle.forward(p[0]*0.35f);
                break;
            case '+':
                turtle.yaw(branchAngle);
                break;
            case '-':
                turtle.yaw(-branchAngle);
                break;
            case '&':
                turtle.pitch(branchAngle);
                break;
            case '^':
                turtle.pitch(-branchAngle);
                break;
            case '/':
                turtle.roll(branchAngle);
                break;
            case '\\':
                turtle.roll(-branchAngle);
                break;
            case '[':
                positionStack.push(turtle.getPosition());
                headingStack.push(turtle.getHeading());
                leftStack.push(turtle.getLeft());
                upStack.push(turtle.getUp());
                radiusStack.push(branchRadius);
                stepStack.push(branchStep);
                break;
            case ']':
                turtle.setPosition(positionStack.top());
                positionStack.pop();
                turtle.setHeading(headingStack.top());
                headingStack.pop();
                turtle.setLeft(leftStack.top());
                leftStack.pop();
                turtle.setUp(upStack.top());
                upStack.pop();
                branchRadius = radiusStack.top();
                radiusStack.pop();
                branchStep = stepStack.top();
                stepStack.pop();
                break;
            default:
                break;
        }
    }
}
//#declare DarkBrown = color red 0.36 green 0.25 blue 0.20
//#declare DarkTan = color red 0.59 green 0.41 blue 0.31
//#declare Bronze = color red 0.55 green 0.47 blue 0.14
//#declare MediumWood = color red 0.65 green 0.50 blue 0.39
//#declare LightWood = color red 0.91 green 0.76 blue 0.65

void TurtleInterpreter::addCylinderVertices (vec3 centre1, vec3 centre2, vec3 axis, vec3 perp, GLfloat radius) {
    vector<vec3> cylinderVertices;
    vector<vec3> cylinderColours;
    vector<vec3> cylinderNormals;
    vector<vec2> cylinderUVs;
    vec4 point1 = radius * vec4(normalize(perp), 0);
    vec4 point2 = radius * 0.75f * vec4(normalize(perp), 0);
    vec3 side1, side2;
    vec3 normal;
    float n = 11;
    mat4 rotation = rotate(mat4(1.0f),(float) (2 * M_PI )/ n, normalize(axis));
    for(int i = 0; i < n; i++){
        
        cylinderVertices.push_back(vec3(point1) + centre1);
        cylinderUVs.push_back(vec2(1, i/n));
        cylinderColours.push_back(vec3(0.36, 0.25, 0.2));
        cylinderVertices.push_back(vec3(point2) + centre2);
        cylinderUVs.push_back(vec2(0, i/n));

        cylinderColours.push_back(vec3(0.59, 0.41, 0.31));
        side1 = vec3(point1) + centre1 - vec3(point2) - centre2;
        vec3 prev = vec3(point2) + centre2;
        point1 = point1 * rotation;
        point2 = point2 * rotation;
        cylinderVertices.push_back(vec3(point1) + centre1);
        cylinderUVs.push_back(vec2(1, (i+1)/n));

        side2 = - prev + vec3(point1) + centre1;
        normal = cross(side1, side2);
        cylinderNormals.push_back(normal);
        cylinderNormals.push_back(normal);
        cylinderNormals.push_back(normal);
        cylinderColours.push_back(vec3(0.55, 0.47, 0.14));
        cylinderVertices.push_back(prev);
        cylinderUVs.push_back(vec2(0, i/n));

        cylinderColours.push_back(vec3(0.65, 0.5, 0.39));
        cylinderVertices.push_back(vec3(point1) + centre1);
        cylinderUVs.push_back(vec2(1, (i+1)/n));

        side1 = vec3(point2) + centre2 - vec3(point1) - centre1;
        normal = cross(side2, side1);
        cylinderNormals.push_back(normal);
        cylinderNormals.push_back(normal);
        cylinderNormals.push_back(normal);
        cylinderColours.push_back(vec3(0.91, 0.76, 0.65));
        cylinderVertices.push_back(vec3(point2) + centre2);
        cylinderUVs.push_back(vec2(0, (i+1)/n));
        cylinderColours.push_back(vec3(0.36, 0.25, 0.2));

    }
    vertices.insert(vertices.end(), cylinderVertices.begin(), cylinderVertices.end());
    colours.insert(colours.end(), cylinderColours.begin(), cylinderColours.end());
    normals.insert(normals.end(), cylinderNormals.begin(), cylinderNormals.end());
    uvs.insert(uvs.end(), cylinderUVs.begin(), cylinderUVs.end());
}

void TurtleInterpreter::addLeafVertices(vec3 end, vec3 dir, GLfloat length) {
    
}
void TurtleInterpreter::printVariables() {
    cout<<"branchRadius "<<branchRadius<<endl;
    cout<<"branchStep "<<branchStep<<endl;
    cout<<"branchAngle "<<branchAngle<<endl;
    cout<<"branchThicknessRatio "<<branchThicknessRatio<<endl;
    cout<<"branchStepRatio "<<branchStepRatio<<endl;
    cout<<"minRadius "<<minRadius<<endl;
}