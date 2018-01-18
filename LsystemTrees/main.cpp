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

#define pi atan(1)*4

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
void testSymbol() {
    Symbol s = Symbol('k');
    s.printState();
    vector<GLfloat> p = vector<GLfloat>(3, 4.65f);
    vector<GLfloat>::iterator it = p.end();
    p.insert(it, 6.9f);
    s = Symbol('h', p);
    s.printState();
    Symbol s2 = Symbol('h', p);
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
    output.push_back(Symbol('F'));
    output.push_back(Symbol('['));
    output.push_back(Symbol('+'));
    output.push_back(Symbol('F'));
    output.push_back(Symbol(']'));
    output.push_back(Symbol('F'));
    output.push_back(Symbol('['));
    output.push_back(Symbol('-'));
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
    d0l.applyRules();
    d0l.applyRules();
    d0l.applyRules();
    d0l.applyRules();
    return d0l.current;
}
int testGraphics() {
    const GLint WIDTH = 800, HEIGHT = 600;
    
    const GLchar *vertexShaderSource = "#version 410 core\n"
    "layout (location = 0 ) in vec3 position;\n"
    "void main( )\n"
    "{\n"
    "gl_Position = vec4( position.x, position.y, position.z, 1.0 );\n"
    "}";
    
    const GLchar *fragmentShaderSource = "#version 410 core\n"
    "out vec4 color;\n"
    "void main( )\n"
    "{\n"
    "color = vec4( 1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}";
    
    {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Learn", nullptr, nullptr);
    
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    
    if (nullptr == window) {
        std::cout <<"Failed to create GLFW window" <<std::endl;
        glfwTerminate();
        
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    glewExperimental = GL_TRUE;
    if ( GLEW_OK != glewInit()) {
        std::cout <<"Failed to initialize GLEW" <<std::endl;
        return -1;
        
    }
    glViewport(0, 0, screenWidth, screenHeight);
    
    GLuint vertexShader = glCreateShader( GL_VERTEX_SHADER );
    glShaderSource( vertexShader, 1, &vertexShaderSource, NULL );
    glCompileShader( vertexShader );
    GLint success;
    GLchar infoLog[512];
    
    glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &success );
    if ( !success )
    {
        glGetShaderInfoLog( vertexShader, 512, NULL, infoLog );
        std::cout <<"ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<infoLog <<std::endl;
        
    }
    
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL );
    glCompileShader( fragmentShader);
    
    glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &success);
    
    if ( !success)
    {
        glGetShaderInfoLog( fragmentShader, 512, NULL, infoLog );
        std::cout <<"ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" <<infoLog <<std::endl;
    }
    
    GLuint shaderProgram = glCreateProgram();
    glAttachShader( shaderProgram, vertexShader);
    glAttachShader( shaderProgram, fragmentShader);
    glLinkProgram( shaderProgram);
    
    glGetProgramiv( shaderProgram, GL_LINK_STATUS, &success );
    
    if ( !success)
    {
        glGetProgramInfoLog( shaderProgram, 512, NULL, infoLog );
        std::cout <<"ERROR::SHADER::PROGRAM::LINKING_FAILED\n" <<infoLog <<std::endl;
    }
    
    glDeleteShader( vertexShader);
    glDeleteShader (fragmentShader);
    
        
    
        
    GLfloat vertices[10000]=
    {
//        -0.5f, -0.5f, 0.0f, //bottom left
//        0.7f, -0.5f, 0.0f,
//        0.0f, 0.5f, 0.0f,
//        0.7f, -0.5f, 0.0f,

    };

        
    Turtle turtle = Turtle();
        turtle.setPos(0.0f, -0.85f, 0.0f);
    vector<Vector3D> vert = turtle.draw2D(testTree());
    int i = 0 ;
    for (vector<Vector3D>::iterator it = vert.begin(); it != vert.end(); it++){
        vertices[i] = it->getX();
        cout<<" "<<i<<" ";
        vertices[i+1] = it->getY();
        vertices[i+2] = it->getZ();
        i+=3;
    }

    GLuint VBO, VAO;
    
    glGenVertexArrays( 1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    
    glBindBuffer( GL_ARRAY_BUFFER, VBO);
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );
    
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 3 * sizeof( GLfloat), (GLvoid *) 0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer( GL_ARRAY_BUFFER, 0);
    
    glBindVertexArray( 0 );
    
    
    while ((!glfwWindowShouldClose(window))) {
        glfwPollEvents();
        glClearColor(0.2f, 0.3f, 0.2f, 1.0f);
        glClear( GL_COLOR_BUFFER_BIT);
        
        glUseProgram( shaderProgram );
        glBindVertexArray( VAO );
        glDrawArrays(GL_LINES, 0, 5000);
        glBindVertexArray(0);
        
        glfwSwapBuffers(window);
        
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteVertexArrays(1, &VBO);
    glfwTerminate();
    }
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
    
}

