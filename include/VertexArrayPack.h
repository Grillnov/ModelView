//
//  VertexArrayPack.h
//  ModelView
//
//  Created by Bowen Yang on Aug 20, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# ifndef VERTEXARRAYPACK
# define VERTEXARRAYPACK

# include "AllinGL.h"
# include "BufferPack.hpp"
# include <map>

struct VertAttribf
{
	BufferPack<GLfloat>* bufferptr;
	GLuint components;
	VertAttribf(){}
	VertAttribf(BufferPack<GLfloat>* bufferptr, GLuint components)
		:bufferptr(bufferptr), components(components){}
}; 

struct VertAttribi
{
	BufferPack<GLint>* bufferptr;
	GLuint components;
	VertAttribi(){}
	VertAttribi(BufferPack<GLint>* bufferptr, GLuint components)
		:bufferptr(bufferptr), components(components){}
};

class VertexArrayPack : public GLObject, public GLAttachable
{
private:
	/**
	Due to the botched GL interface design, we'll have to
	include two sets of map, one corresponding to floating
	point attributes, one corresponding to integer attributes.
	*/
	std::map<GLuint, VertAttribf> FloatAttribs;
	std::map<GLuint, VertAttribi> IntAttribs;

public:
	/**
	Creates the vertex array, attach the buffers, and activate all attributes.
	*/
	void Attach() override;

	/**
	Destroys the vertex array.
	*/
	void Detach() override;

	/**
	Register a buffer object as an vertex attribute with index(layout location = index).
	Rejects the operation if the index is already occupied.
	*/
	void AddBufferWithIndex(BufferPack<GLfloat>* buffer, GLuint index, GLuint components);
	void AddBufferWithIndex(BufferPack<GLint>* buffer, GLuint index, GLuint components);

	/**
	Bind the vertex array.
	*/
	void Bind();

	/**
	Restore the vertexarray binding point to its default state.
	*/
	void UnBind();

	/**
	Just an utility function.
	*/
	void* operator[](GLuint index);

	/**
	Convert to GLuint.
	*/
	operator GLuint();
};

# endif