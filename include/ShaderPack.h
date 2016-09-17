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

class ShaderPack : public GLAttachable
{
private:
	std::string Path;//Where do the asset sleep?

	std::string SrcCode;//Source code of the shader. Empty when initialized from compiled binary.

	GLenum ShaderType;//What kind of shader is it anyway? Vertex? Fragment? Compute?

	/**
	@brief
	Load source code from the text.
	@params
	@Path the path of the source code text file.
	*/
	void LoadFromText(std::string Path, std::fstream& fin);

	/**
	@brief
	Load from compiled binary blob.
	@params
	@Path the path of the binary file.
	*/
	void LoadFromBinary(std::string Path, std::fstream& fin);

	/**
	@brief
	Save the binary blob to file.
	*/
	void SaveBinary();

	/**
	@brief
	Compile the source code if you have to.
	*/
	//void Compile();
public:
	/**
	@brief
	Construct the shader.
	@params
	@Path path to the asset.
	@Type type of the shader.
	*/
	ShaderPack(std::string Path, GLenum Type);

	/**
	@brief
	Attach the shader.
	Create the shader to register it on the server side.
	*/
	void Attach() override;

	/**
	Detach the shader.
	Delete this shader so that server is able to reallocate its ID.
	*/
	void Detach() override;

	operator GLuint();

	GLenum getType()
	{
		return this->ShaderType;
	}
};

# endif