//
//  ProgramPack.cpp
//  ModelView
//
//  Created by Bowen Yang on Aug 18, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include <AllinGL.h>

const char* getGLErrorString(GLenum error)
{
	switch (error)
	{
	case GL_INVALID_ENUM:
		return "GL invalid enumeration";
		break;
	case GL_INVALID_OPERATION:
		return "GL invalid operation";
		break;
	default:
		return "Unknown GL error.";
		break;
	}
}