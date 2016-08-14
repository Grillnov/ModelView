//
//  ProgramPack.h
//  ModelView
//
//  Created by Bowen Yang on Aug 13, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# ifndef PROGRAMPACK
# define PROGRAMPACK

# include "AllinGL.h"
# include "ShaderPack.h"
# include <map>
# include <unordered_map>
# include "UniformPack.h"

class ProgramPack : public GLAttachable, public GLObject
{
private:
	std::unordered_map<GLenum, ShaderPack*> ShaderMap;
	std::unordered_map<GLuint, UniformPack*> UniformMap;
public:

};

# endif