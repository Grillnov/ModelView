//
//  PrintGLError.cpp
//  ModelView
//
//  Created by Bowen Yang on Aug 18, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include <AllinGL.h>

const char* getGLErrorString(GLenum errorId)
{
	switch (errorId)
	{
	case GL_INVALID_ENUM:
		return ("GL Invalid Enum");
	case GL_INVALID_VALUE:
		return ("GL Invalid Value");
	case GL_INVALID_OPERATION:
		return ("GL Invalid Operation");
	case GL_OUT_OF_MEMORY:
		return ("GL Out Of Memory");
	case GL_INVALID_FRAMEBUFFER_OPERATION:  
		return ("GL Invalid FrameBuffer Operation");  
	case GL_STACK_OVERFLOW:
		return ("GL Stack Overflow");
	case GL_STACK_UNDERFLOW:
		return ("GL Stack Underflow");
	case GL_TABLE_TOO_LARGE:  
		return ("GL Table Too Large");  
	default:
		return "Unrecognized OpenGL Error";
	};
}