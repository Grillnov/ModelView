//
//  VertexArrayPack.h
//  ModelView
//
//  Created by Bowen Yang on Aug 20, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# ifndef __ModelView__VertexArrayPack__
# define __ModelView__VertexArrayPack__

# include <AllinGL.h>
# include <BufferPack.hpp>
# include <unordered_map>

/**struct Attrib
{
	GLuint bufferHandle;
	GLuint components;
	GLenum type;
	Attrib() {}
	Attrib(GLuint buf, GLuint comp, GLenum type) : bufferHandle(buf), components(comp), type(type) {}
};*/

class VertexArrayPack : public GLAttachable
{
private:
	/**
	Attributes are stored here, ready for attaching.
	*/
	std::unordered_map<GLuint, GLuint> Attribs;

	void AddAttribute(GLuint buffer, GLuint index, GLuint components, GLenum type);

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
	void AddAttribAt(BufferPack<GLfloat>& buffer, GLuint index, GLuint components);
	void AddAttribAt(BufferPack<GLdouble>& buffer, GLuint index, GLuint components);
	void AddAttribAt(BufferPack<GLint>& buffer, GLuint index, GLuint components);
	void AddAttribAt(BufferPack<GLuint>& buffer, GLuint index, GLuint components);
	void AddAttribAt(BufferPack<GLshort>& buffer, GLuint index, GLuint components);
	void AddAttribAt(BufferPack<GLushort>& buffer, GLuint index, GLuint components);
	void AddAttribAt(BufferPack<GLbyte>& buffer, GLuint index, GLuint components);
	void AddAttribAt(BufferPack<GLubyte>& buffer, GLuint index, GLuint components);

	/**
	Bind the vertex array.
	*/
	void Bind();

	/**
	Just an utility function.
	*/
	GLuint operator[](GLuint index);

	/**
	Convert to GLuint.
	*/
	operator GLuint();
};

# endif