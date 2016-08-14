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
	std::string Path;
	std::string SrcCode;
	void LoadFromText(std::string Path);
public:
	void Load(std::string Path);
	void Compile();
};

# endif