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


#define PI atan(1)*4

#include "Window.hpp"
#include "Shaders.hpp"
#include "Vector3D.hpp"
#include "Matrix.hpp"
#include "RollMatrix.hpp"
#include "YawMatrix.hpp"
#include "PitchMatrix.hpp"
#include "DirectionMatrix.hpp"
#include "Turtle.hpp"
#include "Symbol.hpp"
#include "D0LRule.hpp"
#include "D0LSystem.hpp"
#include "Reader.hpp"

using namespace std;

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/matrix_transform.hpp"

using namespace glm;

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
    cout<<"PI"<<endl;
    RollMatrix(PI).printState();
    cout<<"-PI"<<endl;
    RollMatrix(-PI).printState();
    cout<<"PI/2"<<endl;
    RollMatrix(PI/2).printState();
    cout<<"PI/4"<<endl;
    RollMatrix(PI/4).printState();
    cout<<"PI/6"<<endl;
    RollMatrix(PI/6).printState();
    cout<<"Yaw Matrix: "<<endl;
    cout<<"PI"<<endl;
    YawMatrix(PI).printState();
    cout<<"-PI"<<endl;
    YawMatrix(-PI).printState();
    cout<<"PI/2"<<endl;
    YawMatrix(PI/2).printState();
    cout<<"PI/4"<<endl;
    YawMatrix(PI/4).printState();
    cout<<"PI/6"<<endl;
    YawMatrix(PI/6).printState();
    cout<<"Pitch Matrix: "<<endl;
    cout<<"PI"<<endl;
    PitchMatrix(PI).printState();
    cout<<"-PI"<<endl;
    PitchMatrix(-PI).printState();
    cout<<"PI/2"<<endl;
    PitchMatrix(PI/2).printState();
    cout<<"PI/4"<<endl;
    PitchMatrix(PI/4).printState();
    cout<<"PI/6"<<endl;
    PitchMatrix(PI/6).printState();
}
void testDirectionMatrix() {
    cout<<"Direction Matrix: "<<endl;
    DirectionMatrix dir = DirectionMatrix();
    dir.printState();
    cout<<"Rotation Matrix: roll by PI "<<endl;
    RollMatrix rotate = RollMatrix(PI);
    rotate.printState();
    dir.rotate(rotate);
    cout<<"Rolled by PI - basically upside down from left side"<<endl;
    dir.printState();
    RollMatrix rotate2 = RollMatrix(-PI/2);
    cout<<"Rotation Matrix: roll by -PI/2 "<<endl;
    rotate2.printState();
    dir.rotate(rotate2);
    cout<<"Rolled by -PI/2 "<<endl;

    dir.printState();
    YawMatrix rotate3 = YawMatrix(PI/2);
    dir.rotate(rotate3);
    cout<<"Yawed by PI/2"<<endl;
    dir.printState();
    PitchMatrix rotate4 = PitchMatrix(-PI/2);
    cout<<"pitch matrix -PI/2"<<endl;
    rotate4.printState();
    dir.rotate(rotate4);
    cout<<"pitched by -PI/2"<<endl;
    dir.printState();
    RollMatrix rotate5 = RollMatrix(PI/4);
    cout<<" roll matrix PI/4"<<endl;
    dir.rotate(rotate5);
    cout<<"Rolled by PI/4"<<endl;
    dir.printState();
    cout<<" roll matrix PI/4"<<endl;
    dir.rotate(rotate5);
    cout<<"Rolled by PI/4"<<endl;
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
    turtle.yaw(PI/2);
    turtle.printState();
    turtle.forward(3);
    turtle.printState();
    cout<<endl;
    turtle.getPos().printState();
    turtle.getHeading().printState();
    turtle.getUp().printState();
    turtle.getLeft().printState();
    turtle.pitch(PI/3);
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
void testSymbol() {
    Symbol s = Symbol('k');
    s.printState();
    cout<<endl<<" Testing parameters: ";
    vector<GLfloat> p = s.getParameters();
    if (p.empty()) {
        cout<<"no parameters ";
    }
    for(vector<GLfloat>::iterator it = p.begin(); it != p.end(); it++){
        cout<<*it<<" "<<*it+1<<" ";
    }
    string para = "(1.0,2.2,3)";
    Symbol s2 = Symbol('h', para);
    s2.printState();
    cout<<endl<<" Testing parameters: ";
    vector<GLfloat> p2 = s2.getParameters();
    for(vector<GLfloat>::iterator it = p2.begin(); it != p2.end(); it++){
        cout<<*it<<" "<<*it+1<<" ";
    }
    cout<<s2.equals(s)<<endl;
    cout<<Symbol().equals(s);
    Symbol().printState();
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
    output.push_back('D');
    output.push_back('B');
    output.push_back('D');
    Rule rule3 = Rule(Symbol('C'), output);
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
    output.push_back('A');
    output.push_back('B');
    output.push_back('A');
    rules.push_back(Rule(Symbol('B'), output));
    LSystem d0l2 = LSystem('B', rules);
    d0l2.applyRules(5);
    
}
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

void testReader(){
    LSystem d0l = createLsystem("/Users/karishmavakil/Documents/Project/LSystemTrees/LSystemTrees/lsystem1.txt");
    cout<<"Current ";
    d0l.printCurrent();
    cout<<endl;
    d0l.applyRules(5);
}

int testGraphics() {
    
    GLFWwindow *window = createWindow();
    
    GLuint shaderProgram = LoadShaders("/Users/karishmavakil/Documents/Project/LSystemTrees/LSystemTrees/vert.shader", "/Users/karishmavakil/Documents/Project/LSystemTrees/LSystemTrees/frag.shader");
        
    // Get a handle for our "MVP" uniform
    GLuint MatrixID = glGetUniformLocation(shaderProgram, "MVP");
    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    // Camera matrix
    glm::mat4 View = glm::lookAt(
                                 glm::vec3(2,0,7), // Camera is at (4,3,3), in World Space
                                 glm::vec3(0,0,0), // and looks at the origin
                                 glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
                                );
    // Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 Model      = glm::mat4(1.0f);
   //glm::mat4 Model = glm::translate(glm::mat4(), glm::vec3(0.4f, 0.6f, 0.0f));
    glm::mat4 MVP        = Projection * View * Model;

    
    GLfloat vertices[1000000] = {};
    GLfloat colors[1000000] = {};

    Turtle turtle = Turtle();
    turtle.setPos(0.0f, -2.0f, 0.0f);
    LSystem tree = createLsystem("/Users/karishmavakil/Documents/Project/LSystemTrees/LSystemTrees/tree.txt");
    tree.applyRules(5);
    vector<Vector3D> vert = turtle.draw3D(tree.current);
    int i = 0 ;
    for (vector<Vector3D>::iterator it = vert.begin(); it != vert.end(); it++){
        vertices[i] = it->getX();
        vertices[i+1] = it->getY();
        vertices[i+2] = it->getZ();
        if (i%2==0){
            colors[i] = 0.0f;
            colors[i+1] = 0.8f;
            colors[i+2] = 0.0f;
        }
        else {
            colors[i] = 0.0f;
            colors[i+1] = 0.5f;
            colors[i+2] = 0.2f;
        }
        i+=3;
    }

    GLuint vertexbuffer, VAO;
    
    glGenVertexArrays( 1, &VAO);
    glGenBuffers(1, &vertexbuffer);
    
    glBindVertexArray(VAO);
    
    glBindBuffer( GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );
    
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 3 * sizeof( GLfloat), (GLvoid *) 0);
    glEnableVertexAttribArray(0);
    glBindBuffer( GL_ARRAY_BUFFER, 0);

    GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        
    
    glBindVertexArray( 0 );
    
    while ((!glfwWindowShouldClose(window))) {
        
        // Enable depth test
        glEnable(GL_DEPTH_TEST);
        // Accept fragment if it closer to the camera than the former one

        glDepthFunc(GL_LESS);
        glfwPollEvents();
        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear( GL_COLOR_BUFFER_BIT |  GL_DEPTH_BUFFER_BIT);
        
        glUseProgram( shaderProgram );
        
        // Send our transformation to the currently bound shader,
        // in the "MVP" uniform
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
        
        glBindVertexArray( VAO );
        glDrawArrays(GL_LINES, 0, 50000);
        glBindVertexArray(0);
        
        glfwSwapBuffers(window);
        
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteVertexArrays(1, &vertexbuffer);
    glDeleteVertexArrays(1, &colorbuffer);

    glfwTerminate();

    return 0;
}
int main () {
//    testVector3D();
//    testMatrix();
//    testDirectionMatrix();
//    testTurtle();
//    testSymbol();
//    testList();
//    testLSystem();
    testGraphics();
//    testD0LSystemTurtle();
//    testReader();
    
}


