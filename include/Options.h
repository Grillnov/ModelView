//
//  Options.h
//  ModelView
//
//  Created by Bowen Yang on Aug 4, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# ifndef __ModelView__Options__
# define __ModelView__Options__

/**
@brief Modify the two macros below to modify OpenGL version.
By default it's set as OpenGL 4.3.
If your device has any difficulties supporting novel versions of OpenGL,
please try and modify this context version.
Note that only OpenGL 3.2 or higher is supported by GLFW3, a value greater than
3.2 is expected.
*/
# define GLMajorVer 4
# define GLMinorVer 3

/**
@brief Modify the two macros below to change the resolution of the window.
*/
# define xWindowWidth 800.0
# define yWindowHeight 600.0

/**
@brief Modify this flag below to switch multisampling on/off.
1 : on
0 : off
*/
# define enableMultiSampling 0

/**
@brief Modify this flag below to make the window fullscreen or windowed.
1 : fullscreened
0 : windowed
*/
# define isFullScreened 0

/**
@brief Modify the string below to change the title of the window.
*/
# define titleofWindow "ModelView"

/**
@brief Comment this macro below to disable log message.
*/
# define LOGDEBUGMSG

/**
@brief GL errors will not be checked if the macro definition below is commented.
Comment this macro below during release build to boost performance.
*/
# define DEBUGBUILD

/**
@brief Try modifying this to USEGL3W if glew initialization failed or you found out that
some nullptr is invoked as a function pointer.
*/
# define USEGLEW
//# define USEGL3W
















/************DO NOT modify the content below this line************/
















/**
Macro for debug message.
*/
# define debugMsg __FILE__, __LINE__, __FUNCTION__

/**
@brief Due to the botched OpenGL support provided by many platforms,
Glew has to be initiated to retrieve function pointers to GL interfaces.
Problems might arise if you are using an Intel graphic device(for instance, HD4000 series) on Windows platform.
If so, try and run the executable with independent video cards(for instance, your ATI or NVIDIA card).
Note that Glew has to be included before any gl headers are included.

TODO: GL3W may work if we fail to initiate glew.
*/
# ifdef USEGLEW
# include <GL/glew.h>
# endif

# ifdef USEGL3W
# include <GL/gl3w.h>
# endif

/**
GLFW is used instead of GLUT.
*/
# include <GLFW/glfw3.h>

/**
GLM is used as client side BLAS.
*/
# include <glm/glm.hpp>
# include <glm/ext.hpp>

/**
Headers from standard library.
*/
# include <iostream>
# include <string>
# include <fstream>

/**
Headers from this project.
*/
# include <BenchmarkTimer.h>
# include <GLObject.h>
# include <GLAsset.h>

/**
Entrance definition.
*/
# define RunInstance(Class) int main(int argc, char** argv) { Class app; app.StartMainLoop(); }

# endif