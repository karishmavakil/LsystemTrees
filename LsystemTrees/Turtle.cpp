//
//  Turtle.cpp
//  LsystemTrees
//
//  Created by Karishma Vakil on 07/12/2017.
//  Copyright © 2017 Karishma Vakil. All rights reserved.
//

#include "Turtle.hpp"
#include "Symbol.hpp"

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/ext.hpp"

using namespace glm;
#define _USE_MATH_DEFINES
// third-party libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// standard C++ libraries
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <stack>

#include <iostream>
using namespace std;
Turtle::Turtle() {
    position = vec3(0.0f,0.0f,0.0f);
    heading = vec3(0.0f,1.0f,0.0f);
    up = vec3(0.0f,0.0f,1.0f);
    left = vec3(-1.0f,0.0f,0.0f);
}

void Turtle::setPosition (GLfloat xpos, GLfloat ypos, GLfloat zpos) {
    position = vec3(xpos, ypos, zpos);
}
void Turtle::setHeading (GLfloat xpos, GLfloat ypos, GLfloat zpos) {
    heading = vec3(xpos, ypos, zpos);
}
void Turtle::setUp (GLfloat xpos, GLfloat ypos, GLfloat zpos) {
    up = vec3(xpos, ypos, zpos);
}
void Turtle::setLeft (GLfloat xpos, GLfloat ypos, GLfloat zpos){
    left = vec3(xpos, ypos, zpos);
}
void Turtle::setPosition (vec3 p){
    position = p;
};
void Turtle::setHeading (vec3 h){
    heading = h;
};
void Turtle::setLeft (vec3 l){
    left = l;
};
void Turtle::setUp (vec3 u){
    up = u;
};
vec3 Turtle::getPosition() {
    return position;
}
vec3 Turtle::getHeading() {
    return heading;
}
vec3 Turtle::getUp() {
    return up;
}
vec3 Turtle::getLeft() {
    return left;
}
void Turtle::forward(GLfloat step) {
    position = position + step * heading;
}
void Turtle::roll(GLfloat angle){
    mat4 r = rotate(angle, heading);
    up = round(vec3(vec4(up, 0) * r));
    left = round(vec3(vec4(left, 0) * r));
}
void Turtle::yaw(GLfloat angle){
    mat4 r = rotate(-angle, up);
    left = round(vec3(vec4(left, 0) * r));
    heading = round(vec3(vec4(heading, 0) * r));
}
void Turtle::pitch(GLfloat angle){
    mat4 r = rotate(angle, left);
    heading = round(vec3(vec4(heading, 0) * r));
    up = round(vec3(vec4(up, 0) * r));
}
void Turtle::printState() {
    cout<<"(x, y, z): ("<<position.x<<", " <<position.y <<", " <<position.z<<")"<<endl;
    cout<<"direction: "<<endl;
    cout<<"heading : ";
    cout<<heading.x<<" "<<heading.y<<" "<<heading.z<<endl;
    cout<<"up : ";
    cout<<up.x<<" "<<up.y<<" "<<up.z<<endl;
    cout<<"left : ";
    cout<<left.x<<" "<<left.y<<" "<<left.z<<endl;
}
vector<vec3> Turtle::draw3D(vector<Symbol> symbols){
    vector<vec3> vertices = vector<vec3>();
    GLfloat radius = 0.06f;
    GLfloat step = 0.25f;
    GLfloat angle = 0.6f;
    GLfloat radiusRatio = 0.93;
    GLfloat stepRatio = 0.95;
    GLfloat minRadius = 0.015;
    stack<vec3> positionStack = stack<vec3>();
    stack<vec3> headingStack = stack<vec3>();
    stack<vec3> leftStack = stack<vec3>();
    stack<vec3> upStack = stack<vec3>();
    stack<GLfloat> radiusStack = stack<GLfloat>();
    stack<GLfloat> stepStack = stack<GLfloat>();

    for(vector<Symbol>::iterator itSym = symbols.begin(); itSym != symbols.end(); itSym++) {
        vector<GLfloat> p = itSym->getParameters();
        vector<vec3> v1;
        vec3 oldPos;
        switch (itSym->letter) {
            case 'F':
                oldPos = position;
                forward(p[0]*step);
                v1 = cylinderVertices(oldPos, position, heading, left, radius);
                vertices.insert(vertices.end(), v1.begin(), v1.end());
//                vertices.push_back(oldPos);
//                vertices.push_back(position);
                if (radius > minRadius){
                    radius = radiusRatio * radius;
                    step = stepRatio * step;
                }
                break;
            case 'f':
                forward(p[0]*0.35f);
                break;
            case '+':
                yaw(angle);
                break;
            case '-':
                yaw(-angle);
                break;
            case '&':
                pitch(angle);
                break;
            case '^':
                pitch(-angle);
                break;
            case '/':
                roll(angle);
                break;
            case '\\':
                roll(-angle);
                break;
            case '[':
                positionStack.push(position);
                headingStack.push(heading);
                leftStack.push(left);
                upStack.push(up);
                radiusStack.push(radius);
                stepStack.push(step);
                break;
            case ']':
                position = positionStack.top();
                positionStack.pop();
                heading = headingStack.top();
                headingStack.pop();
                left = leftStack.top();
                leftStack.pop();
                up = upStack.top();
                upStack.pop();
                radius = radiusStack.top();
                radiusStack.pop();
                step = stepStack.top();
                stepStack.pop();
                break;
            default:
                break;
        }
    }
    return vertices;
}
vec3 round(vec3 v) {
    for(int i = -1; i <=1; i++){
        if(fabs(v.x-i) < 0.0001f) {
            v.x = i;
        }
        if(fabs(v.y-i) < 0.0001f) {
            v.y = i;
        }
        if(fabs(v.z-i) < 0.0001f) {
            v.z = i;
        }
    }
    return v;
}
vector<vec3> cylinderVertices (vec3 centre1, vec3 centre2, vec3 axis, vec3 normal, GLfloat radius) {
    vector<vec3> vertices;
    vec4 point1 = radius * vec4(normalize(normal), 0);
    vec4 point2 = radius * 0.8f * vec4(normalize(normal), 0);

    mat4 rotation = rotate(mat4(1.0f),(float) M_PI/3, normalize(axis));
    for(int i = 0; i < 6; i++){
        vertices.push_back(vec3(point1) + centre1);
        vertices.push_back(vec3(point2) + centre2);
        vec3 prev = vec3(point2) + centre2;
        point1 = point1 * rotation;
        point2 = point2 * rotation;
        vertices.push_back(vec3(point1) + centre1);
        vertices.push_back(prev);
        vertices.push_back(vec3(point1) + centre1);
        vertices.push_back(vec3(point2) + centre2);
    }
    return vertices;
}