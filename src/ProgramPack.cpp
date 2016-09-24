//
//  ProgramPack.cpp
//  ModelView
//
//  Created by Bowen Yang on Aug 13, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include <ProgramPack.h>

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

GLuint ProgramPack::ProgramUsedJustNow = 0;

void ProgramPack::AddShader(std::string Path, GLenum type)
{
	ShaderPack* shaderPtr = new ShaderPack(Path, type);
	if (ShaderTable.find(type) == ShaderTable.end())
	{
		ShaderTable[type] = shaderPtr;
	}
	else
	{
		Warning(debugMsg, "Shader of %s type is already present in program %u, bailing.",
			getShaderTypeStr(type), this->AssetID);
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

void ProgramPack::Use()
{
	if (!this->isReady)
	{
		Warning(debugMsg, "Program %u is not linked yet, bailing.", this->AssetID);
		return;
	}

	glUseProgram(*this);
	CheckStatus(__FUNCTION__);

	ProgramUsedJustNow = this->AssetID;
}

ProgramPack::ProgramPack()
{
	this->AssetID = glCreateProgram();

	if (AssetID != 0)
	{
		Log(debugMsg, "Program %u was successfully registered.", this->AssetID);
	}
	else
	{
		Error(debugMsg, "Failed to create a program.");
	}
	CheckStatus(__FUNCTION__);
}

ProgramPack::~ProgramPack()
{
	for (auto i : this->ShaderTable)
	{
		glDetachShader(this->AssetID, *i.second);
		delete i.second;
	}
	glDeleteProgram(this->AssetID);
	CheckStatus(__FUNCTION__);

	Log(debugMsg, "Program %u was successfully unregistered.", this->AssetID);
}

void ProgramPack::Link()
{
	if (this->isReady)
	{
		Warning(debugMsg, "Program %u was already compiled and linked, bailing.", this->AssetID);
		return;
	}

	for (auto i : this->ShaderTable)
	{
		i.second->Compile();
		glAttachShader(this->AssetID, *i.second);
		Log(debugMsg, "Linked a %s with ID %u to program with ID %u.",
			getShaderTypeStr(i.second->getType()), i.second->operator GLuint(), this->AssetID);
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
		Log(debugMsg, "Program %u was successfully compiled and linked, now ready to be used.", this->AssetID);
		this->isReady = true;
	}
}

UniformFeeder ProgramPack::operator[](const char* name)
{
	return UniformFeeder(Fetch(name), ProgramUsedJustNow);
}

ShaderFeeder ProgramPack::operator[](GLenum type)
{
	return ShaderFeeder(type, this);
}

GLint ProgramPack::Fetch(std::string name)
{
	if (!this->isReady)
	{
		Error(debugMsg, "Program is not linked yet. Unable to get the location of uniform %s.", name.c_str());
		return -1;
	}

	Use();

	GLint location = glGetUniformLocation(this->AssetID, name.c_str());

	if (location == -1)
		Error(debugMsg, "Unable to fetch location for uniform %s. "
		"Does this uniform variable actually exist in program %u?"
		, name.c_str(), this->AssetID);

	if (ProgramUsedJustNow != 0)
	{
		glUseProgram(ProgramUsedJustNow);
	}

	return location;
}



const char* ShaderFeeder::operator=(const char* Path)
{
	this->ptr->AddShader(Path, this->type);
	return Path;
}

GLfloat UniformFeeder::operator=(GLfloat val)
{
	glUniform1f(this->location, val);
	if (this->lastProgramID != 0)
		glUseProgram(lastProgramID);
	CheckStatus(__FUNCTION__);

	return val;
}

GLdouble UniformFeeder::operator=(GLdouble val)
{
	glUniform1d(this->location, val);
	if (this->lastProgramID != 0)
		glUseProgram(lastProgramID);
	CheckStatus(__FUNCTION__);

	return val;
}

GLint UniformFeeder::operator=(GLint val)
{
	glUniform1i(this->location, val);
	if (this->lastProgramID != 0)
		glUseProgram(lastProgramID);
	CheckStatus(__FUNCTION__);

	return val;
}

GLuint UniformFeeder::operator=(GLuint val)
{
	glUniform1ui(this->location, val);
	if (this->lastProgramID != 0)
		glUseProgram(lastProgramID);
	CheckStatus(__FUNCTION__);

	return val;
}



glm::vec2 UniformFeeder::operator=(const glm::vec2& val)
{
	glUniform2fv(this->location, 1, &val[0]);
	if (this->lastProgramID != 0)
		glUseProgram(lastProgramID);
	CheckStatus(__FUNCTION__);

	return val;
}

glm::dvec2 UniformFeeder::operator=(const glm::dvec2& val)
{
	glUniform2dv(this->location, 1, &val[0]);
	if (this->lastProgramID != 0)
		glUseProgram(lastProgramID);
	CheckStatus(__FUNCTION__);

	return val;
}

glm::ivec2 UniformFeeder::operator=(const glm::ivec2& val)
{
	glUniform2iv(this->location, 1, &val[0]);
	if (this->lastProgramID != 0)
		glUseProgram(lastProgramID);
	CheckStatus(__FUNCTION__);

	return val;
}

glm::u32vec2 UniformFeeder::operator=(const glm::u32vec2& val)
{
	glUniform2uiv(this->location, 1, &val[0]);
	if (this->lastProgramID != 0)
		glUseProgram(lastProgramID);
	CheckStatus(__FUNCTION__);

	return val;
}



glm::vec3 UniformFeeder::operator=(const glm::vec3& val)
{
	glUniform3fv(this->location, 1, &val[0]);
	if (this->lastProgramID != 0)
		glUseProgram(lastProgramID);
	CheckStatus(__FUNCTION__);

	return val;
}

glm::dvec3 UniformFeeder::operator=(const glm::dvec3& val)
{
	glUniform3dv(this->location, 1, &val[0]);
	if (this->lastProgramID != 0)
		glUseProgram(lastProgramID);
	CheckStatus(__FUNCTION__);

	return val;
}

glm::ivec3 UniformFeeder::operator=(const glm::ivec3& val)
{
	glUniform3iv(this->location, 1, &val[0]);
	if (this->lastProgramID != 0)
		glUseProgram(lastProgramID);
	CheckStatus(__FUNCTION__);

	return val;
}

glm::u32vec3 UniformFeeder::operator=(const glm::u32vec3& val)
{
	glUniform3uiv(this->location, 1, &val[0]);
	if (this->lastProgramID != 0)
		glUseProgram(lastProgramID);
	CheckStatus(__FUNCTION__);

	return val;
}



glm::vec4 UniformFeeder::operator=(const glm::vec4& val)
{
	glUniform4fv(this->location, 1, &val[0]);
	if (this->lastProgramID != 0)
		glUseProgram(lastProgramID);
	CheckStatus(__FUNCTION__);

	return val;
}

glm::dvec4 UniformFeeder::operator=(const glm::dvec4& val)
{
	glUniform4dv(this->location, 1, &val[0]);
	if (this->lastProgramID != 0)
		glUseProgram(lastProgramID);
	CheckStatus(__FUNCTION__);

	return val;
}

glm::ivec4 UniformFeeder::operator=(const glm::ivec4& val)
{
	glUniform4iv(this->location, 1, &val[0]);
	if (this->lastProgramID != 0)
		glUseProgram(lastProgramID);
	CheckStatus(__FUNCTION__);

	return val;
}

glm::u32vec4 UniformFeeder::operator=(const glm::u32vec4& val)
{
	glUniform4uiv(this->location, 1, &val[0]);
	if (this->lastProgramID != 0)
		glUseProgram(lastProgramID);
	CheckStatus(__FUNCTION__);

	return val;
}



glm::mat2x2 UniformFeeder::operator=(const glm::mat2x2& val)
{
	glUniformMatrix2fv(this->location, 1, GL_FALSE, &val[0][0]);
	if (this->lastProgramID != 0)
		glUseProgram(lastProgramID);
	CheckStatus(__FUNCTION__);

	return val;
}

glm::dmat2x2 UniformFeeder::operator=(const glm::dmat2x2& val)
{
	glUniformMatrix2dv(this->location, 1, GL_FALSE, &val[0][0]);
	if (this->lastProgramID != 0)
		glUseProgram(lastProgramID);
	CheckStatus(__FUNCTION__);

	return val;
}



glm::mat3x3 UniformFeeder::operator=(const glm::mat3x3& val)
{
	glUniformMatrix3fv(this->location, 1, GL_FALSE, &val[0][0]);
	if (this->lastProgramID != 0)
		glUseProgram(lastProgramID);
	CheckStatus(__FUNCTION__);

	return val;
}

glm::dmat3x3 UniformFeeder::operator=(const glm::dmat3x3& val)
{
	glUniformMatrix3dv(this->location, 1, GL_FALSE, &val[0][0]);
	if (this->lastProgramID != 0)
		glUseProgram(lastProgramID);
	CheckStatus(__FUNCTION__);

	return val;
}



glm::mat4x4 UniformFeeder::operator=(const glm::mat4x4& val)
{
	glUniformMatrix4fv(this->location, 1, GL_FALSE, &val[0][0]);
	if (this->lastProgramID != 0)
		glUseProgram(lastProgramID);
	CheckStatus(__FUNCTION__);

	return val;
}

glm::dmat4x4 UniformFeeder::operator=(const glm::dmat4x4& val)
{
	glUniformMatrix4dv(this->location, 1, GL_FALSE, &val[0][0]);
	if (this->lastProgramID != 0)
		glUseProgram(lastProgramID);
	CheckStatus(__FUNCTION__);

	return val;
}



void ProgramPack::Uniform1(std::string name, GLfloat val)
{
	glUniform1f(Fetch(name), val);
	CheckStatus(__FUNCTION__);
}

void ProgramPack::Uniform1(std::string name, GLdouble val)
{
	glUniform1d(Fetch(name), val);
	CheckStatus(__FUNCTION__);
}

void ProgramPack::Uniform1(std::string name, GLint val)
{
	glUniform1i(Fetch(name), val);
	CheckStatus(__FUNCTION__);
}

void ProgramPack::Uniform1(std::string name, GLuint val)
{
	glUniform1ui(Fetch(name), val);
	CheckStatus(__FUNCTION__);
}



void ProgramPack::Uniform2(std::string name, GLfloat* valLoc)
{
	glUniform2fv(Fetch(name), 1, valLoc);
	CheckStatus(__FUNCTION__);
}

void ProgramPack::Uniform2(std::string name, GLdouble* valLoc)
{
	glUniform2dv(Fetch(name), 1, valLoc);
	CheckStatus(__FUNCTION__);
}

void ProgramPack::Uniform2(std::string name, GLint* valLoc)
{
	glUniform2iv(Fetch(name), 1, valLoc);
	CheckStatus(__FUNCTION__);
}

void ProgramPack::Uniform2(std::string name, GLuint* valLoc)
{
	glUniform2uiv(Fetch(name), 1, valLoc);
	CheckStatus(__FUNCTION__);
}

void ProgramPack::Uniform2(std::string name, const glm::vec2& val)
{
	glUniform2fv(Fetch(name), 1, &val[0]);
	CheckStatus(__FUNCTION__);
}

void ProgramPack::Uniform2(std::string name, const glm::dvec2& val)
{
	glUniform2dv(Fetch(name), 1, &val[0]);
	CheckStatus(__FUNCTION__);
}

void ProgramPack::Uniform2(std::string name, const glm::ivec2& val)
{
	glUniform2iv(Fetch(name), 1, &val[0]);
	CheckStatus(__FUNCTION__);
}

void ProgramPack::Uniform2(std::string name, const glm::u32vec2& val)
{
	glUniform2uiv(Fetch(name), 1, &val[0]);
	CheckStatus(__FUNCTION__);
}



void ProgramPack::Uniform3(std::string name, GLfloat* valLoc)
{
	glUniform3fv(Fetch(name), 1, valLoc);
	CheckStatus(__FUNCTION__);
}

void ProgramPack::Uniform3(std::string name, GLdouble* valLoc)
{
	glUniform3dv(Fetch(name), 1, valLoc);
	CheckStatus(__FUNCTION__);
}

void ProgramPack::Uniform3(std::string name, GLint* valLoc)
{
	glUniform3iv(Fetch(name), 1, valLoc);
	CheckStatus(__FUNCTION__);
}

void ProgramPack::Uniform3(std::string name, GLuint* valLoc)
{
	glUniform3uiv(Fetch(name), 1, valLoc);
	CheckStatus(__FUNCTION__);
}

void ProgramPack::Uniform3(std::string name, const glm::vec3& val)
{
	glUniform3fv(Fetch(name), 1, &val[0]);
	CheckStatus(__FUNCTION__);
}

void ProgramPack::Uniform3(std::string name, const glm::dvec3& val)
{
	glUniform3dv(Fetch(name), 1, &val[0]);
	CheckStatus(__FUNCTION__);
}

void ProgramPack::Uniform3(std::string name, const glm::ivec3& val)
{
	glUniform3iv(Fetch(name), 1, &val[0]);
	CheckStatus(__FUNCTION__);
}

void ProgramPack::Uniform3(std::string name, const glm::u32vec3& val)
{
	glUniform3uiv(Fetch(name), 1, &val[0]);
	CheckStatus(__FUNCTION__);
}



void ProgramPack::Uniform4(std::string name, GLfloat* valLoc)
{
	glUniform4fv(Fetch(name), 1, valLoc);
	CheckStatus(__FUNCTION__);
}

void ProgramPack::Uniform4(std::string name, GLdouble* valLoc)
{
	glUniform4dv(Fetch(name), 1, valLoc);
	CheckStatus(__FUNCTION__);
}

void ProgramPack::Uniform4(std::string name, GLint* valLoc)
{
	glUniform4iv(Fetch(name), 1, valLoc);
	CheckStatus(__FUNCTION__);
}

void ProgramPack::Uniform4(std::string name, GLuint* valLoc)
{
	glUniform4uiv(Fetch(name), 1, valLoc);
	CheckStatus(__FUNCTION__);
}

void ProgramPack::Uniform4(std::string name, const glm::vec4& val)
{
	glUniform4fv(Fetch(name), 1, &val[0]);
	CheckStatus(__FUNCTION__);
}

void ProgramPack::Uniform4(std::string name, const glm::dvec4& val)
{
	glUniform4dv(Fetch(name), 1, &val[0]);
	CheckStatus(__FUNCTION__);
}

void ProgramPack::Uniform4(std::string name, const glm::ivec4& val)
{
	glUniform4iv(Fetch(name), 1, &val[0]);
	CheckStatus(__FUNCTION__);
}

void ProgramPack::Uniform4(std::string name, const glm::u32vec4& val)
{
	glUniform4uiv(Fetch(name), 1, &val[0]);
	CheckStatus(__FUNCTION__);
}



void ProgramPack::UniformMat2(std::string name, GLfloat* valLoc, GLenum isTransposed)
{
	glUniformMatrix2fv(Fetch(name), 1, isTransposed, valLoc);
	CheckStatus(__FUNCTION__);
}

void ProgramPack::UniformMat2(std::string name, GLdouble* valLoc, GLenum isTransposed)
{
	glUniformMatrix2dv(Fetch(name), 1, isTransposed, valLoc);
	CheckStatus(__FUNCTION__);
}

void ProgramPack::UniformMat2(std::string name, const glm::mat2x2& val)
{
	glUniformMatrix2fv(Fetch(name), 1, GL_FALSE, &val[0][0]);
	CheckStatus(__FUNCTION__);
}

void ProgramPack::UniformMat2(std::string name, const glm::dmat2x2& val)
{
	glUniformMatrix2dv(Fetch(name), 1, GL_FALSE, &val[0][0]);
	CheckStatus(__FUNCTION__);
}



void ProgramPack::UniformMat3(std::string name, GLfloat* valLoc, GLenum isTransposed)
{
	glUniformMatrix3fv(Fetch(name), 1, isTransposed, valLoc);
	CheckStatus(__FUNCTION__);
}

void ProgramPack::UniformMat3(std::string name, GLdouble* valLoc, GLenum isTransposed)
{
	glUniformMatrix3dv(Fetch(name), 1, isTransposed, valLoc);
	CheckStatus(__FUNCTION__);
}

void ProgramPack::UniformMat3(std::string name, const glm::mat3x3& val)
{
	glUniformMatrix3fv(Fetch(name), 1, GL_FALSE, &val[0][0]);
	CheckStatus(__FUNCTION__);
}

void ProgramPack::UniformMat3(std::string name, const glm::dmat3x3& val)
{
	glUniformMatrix3dv(Fetch(name), 1, GL_FALSE, &val[0][0]);
	CheckStatus(__FUNCTION__);
}



void ProgramPack::UniformMat4(std::string name, GLfloat* valLoc, GLenum isTransposed)
{
	glUniformMatrix4fv(Fetch(name), 1, isTransposed, valLoc);
	CheckStatus(__FUNCTION__);
}

void ProgramPack::UniformMat4(std::string name, GLdouble* valLoc, GLenum isTransposed)
{
	glUniformMatrix4dv(Fetch(name), 1, isTransposed, valLoc);
	CheckStatus(__FUNCTION__);
}

void ProgramPack::UniformMat4(std::string name, const glm::mat4x4& val)
{
	glUniformMatrix4fv(Fetch(name), 1, GL_FALSE, &val[0][0]);
	CheckStatus(__FUNCTION__);
}

void ProgramPack::UniformMat4(std::string name, const glm::dmat4x4& val)
{
	glUniformMatrix4dv(Fetch(name), 1, GL_FALSE, &val[0][0]);
	CheckStatus(__FUNCTION__);
}