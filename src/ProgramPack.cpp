//
//  ProgramPack.cpp
//  ModelView
//
//  Created by Bowen Yang on Aug 13, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include "ProgramPack.h"

static const char* getShaderTypeStr(GLenum type)
{
	switch (type)
	{
	case GL_VERTEX_SHADER:
		return "Vertex shader";
	case GL_FRAGMENT_SHADER:
		return "Fragment shader";
	case GL_TESS_EVALUATION_SHADER:
		return "Tess evaluation shader";
	case GL_TESS_CONTROL_SHADER:
		return "Tess control shader";
	case GL_GEOMETRY_SHADER:
		return "Geometry shader";
	default:
		break;
	}
}

void ProgramPack::AddShader(std::string Path, GLenum type)
{
	ShaderPack* shaderPtr = new ShaderPack(Path, type);
	if (ShaderTable.find(type) == ShaderTable.end())
	{
		ShaderTable[type] = shaderPtr;
	}
	else
	{
		Warning(debugMsg, "Shader of %s type is already present, bailing.", getShaderTypeStr(type));
		return;
	}
}

void ProgramPack::Attach()
{
	this->AssetID = glCreateProgram();
}

void ProgramPack::Detach()
{

}

ProgramPack::~ProgramPack()
{

}