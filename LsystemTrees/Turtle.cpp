//
//  Turtle.cpp
//  LsystemTrees
//
//  Created by Karishma Vakil on 07/12/2017.
//  Copyright © 2017 Karishma Vakil. All rights reserved.
//

#include "Turtle.hpp"
#include "Vector3D.hpp"
#include "Matrix.hpp"
#include "DirectionMatrix.hpp"
#include "RollMatrix.hpp"
#include "YawMatrix.hpp"
#include "PitchMatrix.hpp"

// third-party libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// standard C++ libraries
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <cmath>

#include <iostream>
using namespace std;
Turtle::Turtle() {
    position = Vector3D();
    direction = DirectionMatrix();
}
    
void Turtle::setPos (GLfloat xpos, GLfloat ypos, GLfloat zpos) {position.set(xpos, ypos, zpos);}
void Turtle::setHeading (GLfloat xpos, GLfloat ypos, GLfloat zpos) {direction.col1.set(xpos, ypos, zpos);}
void Turtle::setUp (GLfloat xpos, GLfloat ypos, GLfloat zpos) {direction.col2.set(xpos, ypos, zpos);}
void Turtle::setLeft (GLfloat xpos, GLfloat ypos, GLfloat zpos) {direction.col3.set(xpos, ypos, zpos);}

void Turtle::forward(GLfloat step) {
    position = position.add(direction.col1.scalar(step));
}
void Turtle::printState() {
    cout<<"(x, y, z): ("<<position.getX()<<", " <<position.getY() <<", " << position.getZ()<<")"<<endl;
    cout<<"direction: "<<endl;
    direction.printState();
}

Vector3D Turtle::getPos() {
    return position;
}
DirectionMatrix Turtle::getDir() {
    return direction;
}
Vector3D Turtle::getHeading() {
    return direction.col1;
}
Vector3D Turtle::getUp() {
    return direction.col2;
}
Vector3D Turtle::getLeft() {
    return direction.col3;
}
void Turtle::roll(GLfloat angle){
    RollMatrix rotation = RollMatrix(angle);
    direction.rotate(rotation);
}
void Turtle::yaw(GLfloat angle){
    YawMatrix rotation = YawMatrix(angle);
    direction.rotate(rotation);
}
void Turtle::pitch(GLfloat angle){
    PitchMatrix rotation = PitchMatrix(angle);
    direction.rotate(rotation);
}