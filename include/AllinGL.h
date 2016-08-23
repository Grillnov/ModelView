//
//  AllinGL.h
//  ModelView
//
//  Created by Bowen Yang on Aug 4, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# ifndef ALLINGL
# define ALLINGL

/**
Due to the botched OpenGL support provided by Microsoft Windows OS, 
Glew has to be exploited to retrieve pointers to GL interfaces.
*/
# ifdef _MSC_VER
# include <GL\glew.h>
# endif

/**
GLFW is used instead of GLUT.
*/
# include <GLFW\glfw3.h>

/**
Some headers from standard library.
*/
# include <iostream>
# include <string>
# include <fstream>

/**
GLM is used as client side BLAS.
*/
# include "glm/glm.hpp"
# include "glm/ext.hpp"

/**
Customized headers.
*/

# include "BenchmarkTimer.h"
# include "GLObject.h"
# include "GLAttachable.h"

/**
Macro for debug message.
*/
# define debugMsg __FILE__, __LINE__, __FUNCTION__

/**
Comment this macro definition below to disable log message.
*/
# define LOGDEBUGMSG

/**
GL errors will not be checked if the macro definition below is present.
Uncomment this macro definition below during release build to boost performance.
*/
//# define RELEASEBUILD

# endif