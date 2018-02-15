//
//  Texture.hpp
//  LsystemTrees
//
//  Created by Karishma Vakil on 14/02/2018.
//  Copyright © 2018 Karishma Vakil. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp
//GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>
#include <stdio.h>
// Load a .BMP file using our custom loader
GLuint loadBMP_custom(const char * imagepath);

#endif /* Texture_hpp */
