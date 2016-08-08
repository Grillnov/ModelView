//
//  ShaderPack.h
//  ModelView
//
//  Created by Bowen Yang on Aug 4, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# ifndef SHADERPACK
# define SHADERPACK

# include "AllinGL.h"

class ShaderPack : public GLAttachable, public GLObject
{
private:
	std::string SrcCode;
public:
	GLboolean LoadFromText(std::string Path);
	GLboolean Compile();
	GLboolean Attach();
	GLboolean Detach();
};

# endif