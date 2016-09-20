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

/**
@brief Shader object that loads source code and compile it into a shader.
*/
class ShaderPack : public GLAttachable
{
private:
	std::string Path;//Where do the asset sleep?

	std::string SrcCode;//Source code of the shader. Empty when initialized from compiled binary.

	GLenum ShaderType;//What kind of shader is it anyway? Vertex? Fragment? Compute?

	/*
	Load the source code from a text file.
	@param Path the path of the source code text file.
	*/
	void LoadFromText(std::string Path, std::fstream& fin);

	/*
	@brief
	Load from compiled binary blob.
	@param Path the path of the binary file.
	*/
	void LoadFromBinary(std::string Path, std::fstream& fin);

	/*
	@brief
	Save the binary blob to file.
	*/
	void SaveBinary();
public:
	/**
	@brief Construct the shader.
	@param Path The path to the shader source code.
	@param Type The type of the shader. A value among GL_VERTEX_SHADER, GL_FRAGMENT_SHADER
	GL_GEOMETRY_SHADER, etc. is expected.
	*/
	ShaderPack(std::string Path, GLenum Type);

	/**
	@brief Attach the shader. Register and compile it.
	*/
	void Attach() override;

	/**
	@brief Detach the shader. Delete this shader so that server is able to reallocate its ID.
	*/
	void Detach() override;

	/**
	@brief Converter to GLuint, so that it can be directly used as an argument in raw GL interfaces.
	*/
	operator GLuint();

	/**
	@brief Tell its type.
	*/
	GLenum getType()
	{
		return this->ShaderType;
	}
};

# endif