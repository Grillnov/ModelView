//
//  ShaderPack.cpp
//  ModelView
//
//  Created by Bowen Yang on Aug 4, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include <ShaderPack.h>

ShaderPack::ShaderPack(std::string Path, GLenum type) :Path(Path), ShaderType(type)
{
	std::fstream fin(Path, std::ios::binary | std::ios::in);

	if (Path.find(".bin") != Path.npos)//Pre-compiled binary blob was ordered to be loaded.
	{
		if (!fin.is_open())
			Error(debugMsg, "Cannot open binary shader lib %s", Path.c_str());
		LoadFromBinary(Path, fin);
		fin.close();
	}
	else//A glsl source file was ordered to be loaded.
	{
		fin.close();
		fin.open(Path, std::ios::in);
		if (!fin.is_open())
			Error(debugMsg, "Cannot open shader source file %s", Path.c_str());
		Warning(debugMsg, "Compilation for shader %s from text may take some time.", Path.c_str());
		LoadFromText(Path, fin);
		fin.close();
	}

	this->AssetID = glCreateShader(this->ShaderType);

	if (AssetID != 0)
	{
		Log(debugMsg, "Shader %u was successfully registered.", this->AssetID);
	}
	else
	{
		Error(debugMsg, "Failed to create a shader.");
	}
	CheckStatus(__FUNCTION__);
}

void ShaderPack::LoadFromText(std::string Path, std::fstream& fin)
{
	SrcCode.assign(std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());
	Info(debugMsg, "Shader source %s loaded to memory, length: %u characters.", Path.c_str(), SrcCode.size());
	fin.close();
}

void ShaderPack::LoadFromBinary(std::string Path, std::fstream& fin)
{

}

void ShaderPack::SaveBinary()
{

}

void ShaderPack::Compile()
{
	if (this->isReady)
	{
		Warning(debugMsg, "Shader %s is already attached, bailing.", this->Path.c_str());
		return;
	}
	if (SrcCode.empty())
	{
		//Attach from binary
	}
	else
	{
		//Attach from source code
		const char* SrcPtr = SrcCode.c_str();
		GLint length = static_cast<GLint>(SrcCode.size());
		glShaderSource(this->AssetID, 1, &SrcPtr, &length);

		glCompileShader(this->AssetID);
		GLint shaderStatus;
		glGetShaderiv(this->AssetID, GL_COMPILE_STATUS, &shaderStatus);
		if (shaderStatus != GL_TRUE)
		{
			glGetShaderiv(this->AssetID, GL_INFO_LOG_LENGTH, &shaderStatus);
			char* InfoLogStr = new char[shaderStatus];
			glGetShaderInfoLog(this->AssetID, shaderStatus, nullptr, InfoLogStr);
			Error(debugMsg, "Shader %s compilation failed with compile error message:\n%s", Path.c_str(), InfoLogStr);
			delete[] InfoLogStr;
		}
		else
		{
			Log(debugMsg, "Shader %s was successfully compiled and attached.", this->Path.c_str());

			SaveBinary();
			//Log(debugMsg, "Blob compiled from shader %s was saved.", this->Path.c_str());

			CheckStatus(__FUNCTION__);

			this->isReady = true;
		}
	}
}

ShaderPack::~ShaderPack()
{
	glDeleteShader(this->AssetID);

	CheckStatus(__FUNCTION__);
	Log(debugMsg, "Shader %s was successfully unregistered.", this->Path.c_str());
}