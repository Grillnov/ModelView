//
//  ShaderPack.h
//  ModelView
//
//  Created by Bowen Yang on Aug 4, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# ifndef __ModelView__ShaderPack__
# define __ModelView__ShaderPack__

# include <Options.h>

/**
@brief Shader object that loads source code and compile it into a shader.
*/
class ShaderPack : public GLAsset
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
	@brief Load from compiled binary blob.

	@param Path the path of the binary file.
	TODO: implement it
	*/
	void LoadFromBinary(std::string Path, std::fstream& fin);

	/*
	@brief Save the binary blob to file.

	TODO: implement it
	*/
	void SaveBinary();
public:
	/**
	@brief Register a shader in the OpenGL context.
	
	@param Path The path to the shader source code.

	@param Type The type of the shader. A value among GL_VERTEX_SHADER, GL_FRAGMENT_SHADER
	GL_GEOMETRY_SHADER, etc. is expected.
	*/
	ShaderPack(std::string Path, GLenum Type);

	/**
	@brief Unregister the shader from the OpenGL context, recycling its name for further use.
	*/
	~ShaderPack();

	void Compile();

	/**
	@brief Tell its type.
	*/
	GLenum getType()
	{
		return this->ShaderType;
	}
};

# endif