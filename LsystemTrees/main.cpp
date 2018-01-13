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

#define pi atan(1)*4

#include "Vector3D.hpp"
#include "Matrix.hpp"
#include "RollMatrix.hpp"
#include "YawMatrix.hpp"
#include "PitchMatrix.hpp"
#include "DirectionMatrix.hpp"
#include "Turtle.hpp"

using namespace std;

void testVector3D() {
    cout<<"Testing Vector: "<<endl;
    
    Vector3D v = Vector3D(1.0f, 1.0f, 3.55f);
    //    cout<<"v: ";
    //    v.printState();
    Vector3D v2 = Vector3D(1.0f, 2.0f, 3.0f);
    //    cout<<"v2: ";
    //    v2.printState();
    Vector3D v3 = v.add(v2);
    //    cout<<"v3: ";
    //    v3.printState();
    //    cout<<endl;
    cout<<(v3.equals(v)==false)<<endl;;
    cout<<v3.equals(Vector3D(2.0f, 3.0f, 6.55f))<<endl;
    v3.set(1.0f, 2.123f, 2.0f);
    v3 = v3.scalar(1.5f);
    //    cout<<"v3: ";
    //    v3.printState();
    cout<<v3.equals(Vector3D(1.5f, 3.1845f, 3.0f))<<endl;
    cout<<(v3.equals(v)==false)<<endl;;
    cout<<(v3.equals(v3)==true)<<endl;
    //    cout<<(v.dot(v2)==13.65f)<<endl;
    //    cout<<(v2.dot(v)==13.65f)<<endl;
    //    cout<<(v3.getY()==4.5f)<<endl;
    GLfloat a = v3.getY();
    GLfloat b = 3.1845;
    //    cout<<"a: "<<a<<" b: "<<b<<endl;
    GLfloat e = 0.001f;
    cout<<(fabs(v3.getX()-1.5f)<e)<<endl;
    cout<<((fabs(3.1845f-a))< e)<<endl;
    cout<<(fabs(b -a)<e)<<endl;
    cout<<(v3.getY()==a)<<endl;
    cout<<(fabs(v.dot(v2)-13.65f)<e)<<endl;
    cout<<(fabs(v2.dot(v)-13.65f)<e)<<endl;
}
void testMatrix() {
    cout<<"Testing Rotation Matrix"<<endl;
    Matrix r = Matrix();
    r.printState();
    cout<<"Roll Matrix: "<<endl;
    cout<<"pi"<<endl;
    RollMatrix(pi).printState();
    cout<<"-pi"<<endl;
    RollMatrix(-pi).printState();
    cout<<"pi/2"<<endl;
    RollMatrix(pi/2).printState();
    cout<<"pi/4"<<endl;
    RollMatrix(pi/4).printState();
    cout<<"pi/6"<<endl;
    RollMatrix(pi/6).printState();
    cout<<"Yaw Matrix: "<<endl;
    cout<<"pi"<<endl;
    YawMatrix(pi).printState();
    cout<<"-pi"<<endl;
    YawMatrix(-pi).printState();
    cout<<"pi/2"<<endl;
    YawMatrix(pi/2).printState();
    cout<<"pi/4"<<endl;
    YawMatrix(pi/4).printState();
    cout<<"pi/6"<<endl;
    YawMatrix(pi/6).printState();
    cout<<"Pitch Matrix: "<<endl;
    cout<<"pi"<<endl;
    PitchMatrix(pi).printState();
    cout<<"-pi"<<endl;
    PitchMatrix(-pi).printState();
    cout<<"pi/2"<<endl;
    PitchMatrix(pi/2).printState();
    cout<<"pi/4"<<endl;
    PitchMatrix(pi/4).printState();
    cout<<"pi/6"<<endl;
    PitchMatrix(pi/6).printState();
}
void testDirectionMatrix() {
    cout<<"Direction Matrix: "<<endl;
    DirectionMatrix dir = DirectionMatrix();
    dir.printState();
    cout<<"Rotation Matrix: roll by pi "<<endl;
    RollMatrix rotate = RollMatrix(pi);
    rotate.printState();
    dir.rotate(rotate);
    cout<<"Rolled by pi - basically upside down from left side"<<endl;
    dir.printState();
    RollMatrix rotate2 = RollMatrix(-pi/2);
    cout<<"Rotation Matrix: roll by -pi/2 "<<endl;
    rotate2.printState();
    dir.rotate(rotate2);
    cout<<"Rolled by -pi/2 "<<endl;

    dir.printState();
    YawMatrix rotate3 = YawMatrix(pi/2);
    dir.rotate(rotate3);
    cout<<"Yawed by pi/2"<<endl;
    dir.printState();
    PitchMatrix rotate4 = PitchMatrix(-pi/2);
    cout<<"pitch matrix -pi/2"<<endl;
    rotate4.printState();
    dir.rotate(rotate4);
    cout<<"pitched by -pi/2"<<endl;
    dir.printState();
    RollMatrix rotate5 = RollMatrix(pi/4);
    cout<<" roll matrix pi/4"<<endl;
    dir.rotate(rotate5);
    cout<<"Rolled by pi/4"<<endl;
    dir.printState();
    cout<<" roll matrix pi/4"<<endl;
    dir.rotate(rotate5);
    cout<<"Rolled by pi/4"<<endl;
    dir.printState();
}
void testTurtle(){
    Turtle turtle = Turtle();
    turtle.printState();
    cout<<endl;
    turtle.getPos().printState();
    turtle.getHeading().printState();
    turtle.getUp().printState();
    turtle.getLeft().printState();
    
    cout<<"Checking movement of turtle"<<endl;
    turtle.forward(5);
    turtle.printState();
    cout<<endl;
    turtle.getPos().printState();
    turtle.getHeading().printState();
    turtle.getUp().printState();
    turtle.getLeft().printState();
    turtle.yaw(pi/2);
    turtle.printState();
    turtle.forward(3);
    turtle.printState();
    cout<<endl;
    turtle.getPos().printState();
    turtle.getHeading().printState();
    turtle.getUp().printState();
    turtle.getLeft().printState();
    turtle.pitch(pi/3);
    turtle.printState();
    turtle.forward(8);
    turtle.printState();
    
    cout<<"Testing setters"<<endl;
    turtle.setPos(1.0f, 2.3f, 4.5f);
    turtle.setHeading(0, 1, 0);
    turtle.setUp(0, 0, 1);
    turtle.setLeft(-1, 0, 0);
    turtle.printState();
    turtle.getDir().printState();
}
int main () {
//    testVector3D();
//    testMatrix();
//    testDirectionMatrix();
    testTurtle();
    
}

