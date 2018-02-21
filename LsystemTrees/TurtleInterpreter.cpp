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
    maxLeafRadius = 0.13;
    leafLength = 0.6;
    leafWidth = 0.35;
    leafDensity = 8;
    woodTextureFile = "woodtexture.bmp";
    leafTextureFile = "leaf2.bmp";
};
vector<Symbol> TurtleInterpreter::getInstructions(){
    return lsystem.current;
};
vector<vec3> TurtleInterpreter::getVertices(){
    vector<vec3> vertices = branchVertices;
    vertices.insert(vertices.end(), leafVertices.begin(), leafVertices.end());
    return vertices;
};
vector<vec3> TurtleInterpreter::getColours(){
    vector<vec3> colours = branchColours;
    colours.insert(colours.end(), leafColours.begin(), leafColours.end());
    return colours;
};
vector<vec3> TurtleInterpreter::getNormals(){
    vector<vec3> normals = branchNormals;
    normals.insert(normals.end(), leafNormals.begin(), leafNormals.end());
    return normals;
};
vector<vec2> TurtleInterpreter::getUVs(){
    vector<vec2> uvs = branchUVs;
    uvs.insert(uvs.end(), leafUVs.begin(), leafUVs.end());
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
                addBranchVertices(oldPosition, turtle.getPosition(), turtle.getHeading(), turtle.getLeft(), branchRadius);
                if(branchRadius <= maxLeafRadius){
                    addLeavesVertices(oldPosition, turtle.getPosition(), turtle.getHeading(), turtle.getLeft(), branchRadius);
                }
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
    branchVerticesSize = branchVertices.size();
    leafVerticesSize = leafVertices.size();
}
//#declare DarkBrown = color red 0.36 green 0.25 blue 0.20
//#declare DarkTan = color red 0.59 green 0.41 blue 0.31
//#declare Bronze = color red 0.55 green 0.47 blue 0.14
//#declare MediumWood = color red 0.65 green 0.50 blue 0.39
//#declare LightWood = color red 0.91 green 0.76 blue 0.65

void TurtleInterpreter::addBranchVertices (vec3 centre1, vec3 centre2, vec3 axis, vec3 perp, GLfloat radius) {
    vec4 point1 = radius * vec4(normalize(perp), 0);
    vec4 point2 = radius * 0.8f * vec4(normalize(perp), 0);
    vec3 side1, side2;
    vec3 normal;
    float n = 8;
    mat4 rotation = rotate(mat4(1.0f),(float) (2 * M_PI )/ n, normalize(axis));
    for(int i = 0; i < n; i++){
        
        branchVertices.push_back(vec3(point1) + centre1);
        branchUVs.push_back(vec2(1, i/n));
        branchColours.push_back(vec3(0.36, 0.25, 0.2));
        branchVertices.push_back(vec3(point2) + centre2);
        branchUVs.push_back(vec2(0, i/n));

        branchColours.push_back(vec3(0.59, 0.41, 0.31));
        side1 = vec3(point1) + centre1 - vec3(point2) - centre2;
        vec3 prev = vec3(point2) + centre2;
        point1 = point1 * rotation;
        point2 = point2 * rotation;
        branchVertices.push_back(vec3(point1) + centre1);
        branchUVs.push_back(vec2(1, (i+1)/n));

        side2 = - prev + vec3(point1) + centre1;
        normal = cross(side1, side2);
        branchNormals.push_back(normal);
        branchNormals.push_back(normal);
        branchNormals.push_back(normal);
        branchColours.push_back(vec3(0.55, 0.47, 0.14));
        branchVertices.push_back(prev);
        branchUVs.push_back(vec2(0, i/n));

        branchColours.push_back(vec3(0.65, 0.5, 0.39));
        branchVertices.push_back(vec3(point1) + centre1);
        branchUVs.push_back(vec2(1, (i+1)/n));

        side1 = vec3(point2) + centre2 - vec3(point1) - centre1;
        normal = cross(side2, side1);
        branchNormals.push_back(normal);
        branchNormals.push_back(normal);
        branchNormals.push_back(normal);
        branchColours.push_back(vec3(0.91, 0.76, 0.65));
        branchVertices.push_back(vec3(point2) + centre2);
        branchUVs.push_back(vec2(0, (i+1)/n));
        branchColours.push_back(vec3(0.36, 0.25, 0.2));

    }
}

void TurtleInterpreter::addLeafVertices(vec3 end, vec3 dir, vec3 perp) {
    GLfloat width = leafWidth;
    GLfloat length = leafLength;
    vec3 normal = cross(dir, perp);
    vec3 outer = end + length * dir;
    vec3 left = end + length/3 * dir + width / 2 * perp + 0.08 * normal;
    vec3 right = end + length/3 * dir - width / 2 * perp + 0.08 * normal;
    vec3 side1 = left - end;
    vec3 side2 = right - end;
    leafVertices.push_back(end);
    leafUVs.push_back(vec2(1, 0.5));
    leafVertices.push_back(left);
    leafUVs.push_back(vec2(0.7, 0));
    leafVertices.push_back(outer);
    leafUVs.push_back(vec2(0, 0.5));
    leafVertices.push_back(end);
    leafUVs.push_back(vec2(1, 0.5));
    leafVertices.push_back(right);
    leafUVs.push_back(vec2(0.7, 1));
    leafVertices.push_back(outer);
    leafUVs.push_back(vec2(0, 0.5));

    leafColours.push_back(vec3(0.00, 0.76, 0.30));
    leafColours.push_back(vec3(0.00, 0.76, 0.40));
    leafColours.push_back(vec3(0.00, 0.76, 0.30));
    leafColours.push_back(vec3(0.00, 0.76, 0.40));
    leafColours.push_back(vec3(0.00, 0.76, 0.30));
    leafColours.push_back(vec3(0.00, 0.76, 0.40));
    normal = cross(dir, side1);
    leafNormals.push_back(normal);
    leafNormals.push_back(normal);
    leafNormals.push_back(normal);
    normal = cross(side2, dir);
    leafNormals.push_back(normal);
    leafNormals.push_back(normal);
    leafNormals.push_back(normal);
    
}
void TurtleInterpreter::addLeavesVertices(vec3 centre1, vec3 centre2, vec3 axis, vec3 perp, GLfloat radius) {
//    GLfloat ratio = 0.8f;
    vec4 endDir = radius * vec4(normalize(perp), 0);
    vec3 normal;
    GLfloat n = (float) leafDensity;
    mat4 rotation = rotate(mat4(1.0f),(float) (2 * M_PI )/ n, normalize(axis));
    for(int i = 0; i < n; i++){
        endDir = endDir * rotation;
//        vec3 leafEnd = centre1 + (i/n) * (centre2 - centre1) + ((i/n) * ratio + (n - i/n)) * vec3(endDir);
        vec3 leafEnd = centre1 + (i/n) * (centre2 - centre1) + vec3(endDir);
        addLeafVertices(leafEnd, normalize(endDir), axis);
    }
    
}
void TurtleInterpreter::printVariables() {
    cout<<"branchRadius "<<branchRadius<<endl;
    cout<<"branchStep "<<branchStep<<endl;
    cout<<"branchAngle "<<branchAngle<<endl;
    cout<<"branchThicknessRatio "<<branchThicknessRatio<<endl;
    cout<<"branchStepRatio "<<branchStepRatio<<endl;
    cout<<"minRadius "<<minRadius<<endl;
    cout<<"maxLeafRadius "<<maxLeafRadius<<endl;
    cout<<"leafLength "<<leafLength<<endl;
    cout<<"leafWidth "<<leafWidth<<endl;
    cout<<"leafDensity "<<leafDensity<<endl;
    cout<<"woodTextureFile "<<woodTextureFile<<endl;
    cout<<"leafTextureFile "<<leafTextureFile<<endl;
    cout<<"leafStyle "<<endl;

}