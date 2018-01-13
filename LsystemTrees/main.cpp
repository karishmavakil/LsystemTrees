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
#include "RotationMatrix.hpp"
#include "RollMatrix.hpp"
#include "YawMatrix.hpp"
#include "PitchMatrix.hpp"

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
void testRotationMatrix() {
    cout<<"Testing Rotation Matrix"<<endl;
    RotationMatrix r = RotationMatrix();
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
int main () {
//    testVector3D();
    testRotationMatrix();
    
}

