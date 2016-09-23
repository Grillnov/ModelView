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

/**
@brief VertexArray object that loads and activates several vertex attributes as a vertex array.
*/
class VertexArrayPack : public GLAttachable
{
private:
	/*
	Attributes are stored here, ready for attaching.
	*/
	std::unordered_map<GLuint, GLuint> Attribs;

	/*
	Add an attribute to the vertex array.
	*/
	void AddAttribute(GLuint buffer, GLuint index, GLuint components, GLenum type);

public:
	/**
	@brief Creates the vertex array, registering its name on the server side.
	*/
	void Attach() override;

	/**
	@brief Destroys the vertex array, recycling its name for further usage.
	*/
	void Detach() override;

	/**
	@brief
	Register a buffer object storing single precision floating points as an vertex attribute at layout index(layout location = index).
	Rejects the operation if the index is already occupied.
	@param buffer The buffer storing attribute values.
	@param index The layout index of the attribute in GLSL shader code.
	@param components How many components a vertex can have. A value between 1 to 4 is expected.
	*/
	void AddAttribAt(BufferPack<GLfloat>& buffer, GLuint index, GLuint components);

	/**
	@brief
	Register a buffer object storing double precisions as an vertex attribute at layout index(layout location = index).
	Rejects the operation if the index is already occupied.
	@param buffer The buffer storing attribute values.
	@param index The layout index of the attribute in GLSL shader code.
	@param components How many components a vertex can have. A value between 1 to 4 is expected.
	*/
	void AddAttribAt(BufferPack<GLdouble>& buffer, GLuint index, GLuint components);

	/**
	@brief
	Register a buffer object storing signed integers as an vertex attribute at layout index(layout location = index).
	Rejects the operation if the index is already occupied.
	@param buffer The buffer storing attribute values.
	@param index The layout index of the attribute in GLSL shader code.
	@param components How many components a vertex can have. A value between 1 to 4 is expected.
	*/
	void AddAttribAt(BufferPack<GLint>& buffer, GLuint index, GLuint components);

	/**
	@brief
	Register a buffer object storing unsigned integers as an vertex attribute at layout index(layout location = index).
	Rejects the operation if the index is already occupied.
	@param buffer The buffer storing attribute values.
	@param index The layout index of the attribute in GLSL shader code.
	@param components How many components a vertex can have. A value between 1 to 4 is expected.
	*/
	void AddAttribAt(BufferPack<GLuint>& buffer, GLuint index, GLuint components);

	/**
	@brief
	Register a buffer object storing signed short integers as an vertex attribute at layout index(layout location = index).
	Rejects the operation if the index is already occupied.
	@param buffer The buffer storing attribute values.
	@param index The layout index of the attribute in GLSL shader code.
	@param components How many components a vertex can have. A value between 1 to 4 is expected.
	*/
	void AddAttribAt(BufferPack<GLshort>& buffer, GLuint index, GLuint components);

	/**
	@brief
	Register a buffer object storing unsigned short integers as an vertex attribute at layout index(layout location = index).
	Rejects the operation if the index is already occupied.
	@param buffer The buffer storing attribute values.
	@param index The layout index of the attribute in GLSL shader code.
	@param components How many components a vertex can have. A value between 1 to 4 is expected.
	*/
	void AddAttribAt(BufferPack<GLushort>& buffer, GLuint index, GLuint components);

	/**
	@brief
	Register a buffer object storing signed bytes as an vertex attribute at layout index(layout location = index).
	Rejects the operation if the index is already occupied.
	@param buffer The buffer storing attribute values.
	@param index The layout index of the attribute in GLSL shader code.
	@param components How many components a vertex can have. A value between 1 to 4 is expected.
	*/
	void AddAttribAt(BufferPack<GLbyte>& buffer, GLuint index, GLuint components);

	/**
	@brief
	Register a buffer object storing unsigned bytes as an vertex attribute at layout index(layout location = index).
	Rejects the operation if the index is already occupied.
	@param buffer The buffer storing attribute values.
	@param index The layout index of the attribute in GLSL shader code.
	@param components How many components a vertex can have. A value between 1 to 4 is expected.
	*/
	void AddAttribAt(BufferPack<GLubyte>& buffer, GLuint index, GLuint components);

	/**
	@brief
	Bind the vertex array.
	*/
	void Bind();

	/**
	@brief Converter to GLuint, so that it can be directly used as an argument in raw GL interfaces.
	*/
	operator GLuint();
};

# endif