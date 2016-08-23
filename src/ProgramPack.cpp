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

void ProgramPack::AddShader(std::string Path)
{
	if (Path.find(".vert") != Path.npos ||
		Path.find(".vertex") != Path.npos ||
		Path.find(".vertexshader") != Path.npos)
		AddShader(Path, GL_VERTEX_SHADER);
	else if
		(Path.find(".frag") != Path.npos ||
		Path.find(".fragment") != Path.npos ||
		Path.find(".fragmentshader") != Path.npos)
		AddShader(Path, GL_FRAGMENT_SHADER);
	else if
		(Path.find(".tessc") != Path.npos)
		AddShader(Path, GL_TESS_CONTROL_SHADER);
	else if
		(Path.find(".tesse") != Path.npos)
		AddShader(Path, GL_TESS_EVALUATION_SHADER);
	else if
		(Path.find(".geo") != Path.npos)
		AddShader(Path, GL_GEOMETRY_SHADER);
	else
		Error(debugMsg, "Unrecognized shader postfix: %s", Path.substr(Path.rfind("."), Path.size()).c_str());
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
		Error(debugMsg, "Program linkage failed with link error message:\n%s", InfoLogStr);
		delete[] InfoLogStr;
	}
	else
	{
		CheckStatus(__FUNCTION__);
		glUseProgram(this->AssetID);
		Log(debugMsg, "Program %u was successfully linked and now using.", this->AssetID);
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

/*void ProgramPack::Use()
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
}*/

ProgramPack::~ProgramPack()
{
	for (auto shader : this->ShaderTable)
	{
		delete shader.second;
	}
}

GLint ProgramPack::Fetch(std::string name)
{
	if (!this->isAttached)
	{
		Error(debugMsg, "Program is not linked yet. Unable to get the location of uniform %s.", name.c_str());
		return -1;
	}
	GLint location = glGetUniformLocation(this->AssetID, name.c_str());
	if (location == -1)
		Error(debugMsg, "Unable to fetch location for uniform %s. Does this uniform variable really exist?", name.c_str());
	return location;
}



void ProgramPack::Uniform1(std::string name, GLfloat val)
{
	glUniform1f(Fetch(name), val);
	CheckStatus(__FUNCTION__);
	//Log(debugMsg, "Program %u: Fed uniform %s with a float type value %f.", this->AssetID, name.c_str(), val);
}
void ProgramPack::Uniform1(std::string name, GLdouble val)
{
	glUniform1d(Fetch(name), val);
	CheckStatus(__FUNCTION__);
	//Log(debugMsg, "Program %u: Fed uniform %s with a double type value %f.", this->AssetID, name.c_str(), val);
}
void ProgramPack::Uniform1(std::string name, GLint val)
{
	glUniform1i(Fetch(name), val);
	CheckStatus(__FUNCTION__);
	//Log(debugMsg, "Program %u: Fed uniform %s with an int type value %d.", this->AssetID, name.c_str(), val);
}
void ProgramPack::Uniform1(std::string name, GLuint val)
{
	glUniform1ui(Fetch(name), val);
	CheckStatus(__FUNCTION__);
	//Log(debugMsg, "Program %u: Fed uniform %s with an unsigned int value %u.", this->AssetID, name.c_str(), val);
}



void ProgramPack::Uniform2(std::string name, GLfloat* valLoc)
{
	glUniform2fv(Fetch(name), 1, valLoc);
	CheckStatus(__FUNCTION__);
	//Log(debugMsg, "Program %u: Fed uniform %s with 2 float type values.", this->AssetID, name.c_str());
}
void ProgramPack::Uniform2(std::string name, GLdouble* valLoc)
{
	glUniform2dv(Fetch(name), 1, valLoc);
	CheckStatus(__FUNCTION__);
	//Log(debugMsg, "Program %u: Fed uniform %s with 2 double type values.", this->AssetID, name.c_str());
}
void ProgramPack::Uniform2(std::string name, GLint* valLoc)
{
	glUniform2iv(Fetch(name), 1, valLoc);
	CheckStatus(__FUNCTION__);
	//Log(debugMsg, "Program %u: Fed uniform %s with 2 int type values.", this->AssetID, name.c_str());
}
void ProgramPack::Uniform2(std::string name, GLuint* valLoc)
{
	glUniform2uiv(Fetch(name), 1, valLoc);
	CheckStatus(__FUNCTION__);
	//Log(debugMsg, "Program %u: Fed uniform %s with 2 unsigned int type values.", this->AssetID, name.c_str());
}



void ProgramPack::Uniform3(std::string name, GLfloat* valLoc)
{
	glUniform3fv(Fetch(name), 1, valLoc);
	CheckStatus(__FUNCTION__);
	//Log(debugMsg, "Program %u: Fed uniform %s with 3 float type values.", this->AssetID, name.c_str());
}
void ProgramPack::Uniform3(std::string name, GLdouble* valLoc)
{
	glUniform3dv(Fetch(name), 1, valLoc);
	CheckStatus(__FUNCTION__);
	//Log(debugMsg, "Program %u: Fed uniform %s with 3 double type values.", this->AssetID, name.c_str());
}
void ProgramPack::Uniform3(std::string name, GLint* valLoc)
{
	glUniform3iv(Fetch(name), 1, valLoc);
	CheckStatus(__FUNCTION__);
	//Log(debugMsg, "Program %u: Fed uniform %s with 3 int type values.", this->AssetID, name.c_str());
}
void ProgramPack::Uniform3(std::string name, GLuint* valLoc)
{
	glUniform3uiv(Fetch(name), 1, valLoc);
	CheckStatus(__FUNCTION__);
	//Log(debugMsg, "Program %u: Fed uniform %s with 3 unsigned int type values.", this->AssetID, name.c_str());
}



void ProgramPack::Uniform4(std::string name, GLfloat* valLoc)
{
	glUniform4fv(Fetch(name), 1, valLoc);
	CheckStatus(__FUNCTION__);
	//Log(debugMsg, "Program %u: Fed uniform %s with 4 float type values.", this->AssetID, name.c_str());
}
void ProgramPack::Uniform4(std::string name, GLdouble* valLoc)
{
	glUniform4dv(Fetch(name), 1, valLoc);
	CheckStatus(__FUNCTION__);
	//Log(debugMsg, "Program %u: Fed uniform %s with 4 double type values.", this->AssetID, name.c_str());
}
void ProgramPack::Uniform4(std::string name, GLint* valLoc)
{
	glUniform4iv(Fetch(name), 1, valLoc);
	CheckStatus(__FUNCTION__);
	//Log(debugMsg, "Program %u: Fed uniform %s with 4 int type values.", this->AssetID, name.c_str());
}
void ProgramPack::Uniform4(std::string name, GLuint* valLoc)
{
	glUniform4uiv(Fetch(name), 1, valLoc);
	CheckStatus(__FUNCTION__);
	//Log(debugMsg, "Program %u: Fed uniform %s with 4 unsigned int type values.", this->AssetID, name.c_str());
}



void ProgramPack::UniformMat2(std::string name, GLfloat* valLoc, GLenum isTransposed)
{
	glUniformMatrix2fv(Fetch(name), 1, isTransposed, valLoc);
	CheckStatus(__FUNCTION__);
	//Log(debugMsg, "Program %u: Fed uniform %s with a float type 2x2 matrix.", this->AssetID, name.c_str());
}
void ProgramPack::UniformMat2(std::string name, GLdouble* valLoc, GLenum isTransposed)
{
	glUniformMatrix2dv(Fetch(name), 1, isTransposed, valLoc);
	CheckStatus(__FUNCTION__);
	//Log(debugMsg, "Program %u: Fed uniform %s with a double type 2x2 matrix.", this->AssetID, name.c_str());
}



void ProgramPack::UniformMat3(std::string name, GLfloat* valLoc, GLenum isTransposed)
{
	glUniformMatrix3fv(Fetch(name), 1, isTransposed, valLoc);
	CheckStatus(__FUNCTION__);
	//Log(debugMsg, "Program %u: Fed uniform %s with a float type 3x3 matrix.", this->AssetID, name.c_str());
}
void ProgramPack::UniformMat3(std::string name, GLdouble* valLoc, GLenum isTransposed)
{
	glUniformMatrix3dv(Fetch(name), 1, isTransposed, valLoc);
	CheckStatus(__FUNCTION__);
	//Log(debugMsg, "Program %u: Fed uniform %s with a double type 3x3 matrix.", this->AssetID, name.c_str());
}



void ProgramPack::UniformMat4(std::string name, GLfloat* valLoc, GLenum isTransposed)
{
	glUniformMatrix4fv(Fetch(name), 1, isTransposed, valLoc);
	CheckStatus(__FUNCTION__);
	//Log(debugMsg, "Program %u: Fed uniform %s with a float type 4x4 matrix.", this->AssetID, name.c_str());
}
void ProgramPack::UniformMat4(std::string name, GLdouble* valLoc, GLenum isTransposed)
{
	glUniformMatrix4dv(Fetch(name), 1, isTransposed, valLoc);
	CheckStatus(__FUNCTION__);
	//Log(debugMsg, "Program %u: Fed uniform %s with a double type 4x4 matrix.", this->AssetID, name.c_str());
}