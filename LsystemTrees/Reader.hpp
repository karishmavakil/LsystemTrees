//
//  Reader.hpp
//  LsystemTrees
//
//  Created by Karishma Vakil on 24/01/2018.
//  Copyright © 2018 Karishma Vakil. All rights reserved.
//

#ifndef Reader_hpp
#define Reader_hpp

#include <stdio.h>
#include "LSystem.hpp"


// standard C++ libraries
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <vector>
#include <list>
#include <fstream>
#include <cstdlib>


LSystem createLsystem(const char * lsystem_file_path);
void readDelimit(const char * file_path);


#endif /* Reader_hpp */
