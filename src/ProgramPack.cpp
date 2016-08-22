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
		return "Not a valid shader type";
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
	if (this->isAttached)
	{
		Warning(debugMsg, "Program %u is already attached, bailing", this->AssetID);
		return;
	}
	this->AssetID = glCreateProgram();
	for (auto shader : this->ShaderTable)
	{
		shader.second->Attach();
		glAttachShader(this->AssetID, shader.second->getID());
		Log(debugMsg, "Attached a %s to program with ID %u.",
			getShaderTypeStr(shader.second->getType()), this->AssetID);
	}

	glLinkProgram(this->AssetID);

	GLint programStatus;
	glGetProgramiv(this->AssetID, GL_LINK_STATUS, &programStatus);
	if (programStatus != GL_TRUE)
	{
		glGetProgramiv(this->AssetID, GL_INFO_LOG_LENGTH, &programStatus);
		char* InfoLogStr = new char[programStatus];
		glGetProgramInfoLog(this->AssetID, programStatus, nullptr, InfoLogStr);
		Error(debugMsg, "Program linkage failed with link error message: %s", InfoLogStr);
		delete[] InfoLogStr;
	}
	else
	{
		CheckStatus(__FUNCTION__);
		Log(debugMsg, "Program %u was successfully linked and ready to be used.", this->AssetID);
		this->isAttached = true;
	}
}

void ProgramPack::Detach()
{
	if (!this->isAttached)
	{
		Warning(debugMsg, "Program %u is not attached yet, bailing.", this->AssetID);
	}
	for (auto shader : this->ShaderTable)
	{
		glDetachShader(this->AssetID, shader.second->getID());
		shader.second->Detach();
	}
	glDeleteProgram(this->AssetID);
	CheckStatus(__FUNCTION__);

	Log(debugMsg, "Program %u was successfully detached.", this->AssetID);
	this->isAttached = false;
}

void ProgramPack::Use()
{
	if (!IsAttached())
	{
		Warning(debugMsg, "Program is not attached yet, bailing.");
		return;
	}
	else
	{
		glUseProgram(this->AssetID);
		CheckStatus(__FUNCTION__);
	}
}

ProgramPack::~ProgramPack()
{
	for (auto shader : this->ShaderTable)
	{
		delete shader.second;
	}
}