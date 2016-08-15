//
//  ProgramPack.h
//  ModelView
//
//  Created by Bowen Yang on Aug 13, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# ifndef PROGRAMPACK
# define PROGRAMPACK

# include "AllinGL.h"
# include "ShaderPack.h"
# include <map>
# include <unordered_map>
# include "UniformPack.h"

class ProgramPack : public GLAttachable, public GLObject
{
private:
	std::unordered_map<GLenum, ShaderPack*> ShaderTable;
	//std::unordered_map<GLuint, UniformPack*> UniformMap;
public:
	/**
	@brief
	Create the program, so that its ID's registered.
	Compile all the shaders and attach them to the program.
	Finally link all these shaders into this program.
	*/
	void Attach() override;

	/**
	Delete the program.
	*/
	void Detach() override;

	/**
	Call glUseProgram.
	*/
	void UseProgramPack();

	/**
	Add some shaders to this program so that it knows where to start.
	Purely consists of client side invokes.
	*/
	void AddShader(std::string Path, GLenum type);

	/**
	Reallocate its resources.
	*/
	~ProgramPack();
};

# endif