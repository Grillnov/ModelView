//
//  VertexArrayPack.h
//  ModelView
//
//  Created by Bowen Yang on Aug 20, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//
# include "VertexArrayPack.h"

void VertexArrayPack::Attach()
{
	if (this->isAttached)
	{
		Warning(debugMsg, "Vertexarray %u is already attached, bailing.", this->AssetID);
		return;
	}

	glGenVertexArrays(1, &this->AssetID);
	glBindVertexArray(this->AssetID);

	CheckStatus(__FUNCTION__);

	Log(debugMsg, "Vertexarray %u was successfully attached.", this->AssetID);
	this->isAttached = true;
}

void VertexArrayPack::Detach()
{
	if (!this->isAttached)
	{
		Warning(debugMsg, "Vertexarray %u is not attached yet, bailing.", this->AssetID);
		return;
	}

	glDeleteVertexArrays(1, &this->AssetID);

	CheckStatus(__FUNCTION__);

	Log(debugMsg, "Vertexarray %u was successfully detached.", this->AssetID);
	this->isAttached = false;
}

void VertexArrayPack::AddAttribute(GLuint buffer, GLuint index, GLuint components, GLenum type)
{
	if (components > 4 || components == 0)
	{
		Error(debugMsg, "Invalid number of components: %u. A component amount of 1-4 is expected.", components);
		return;
	}
	if (Attribs.find(index) != Attribs.end())
	{
		Error(debugMsg, "For vertexarray %u, index %u is already occupied by another attribute.", this->AssetID, index);
		return;
	}

	Attribs[index] = buffer;

	glBindVertexArray(this->AssetID);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	if
		(
		type == GL_FLOAT ||
		type == GL_DOUBLE
		)
		//TODO: There are still many floating types out there
	{
		glVertexAttribPointer(index, components, type, GL_FALSE, 0, nullptr);
	}
	else if
		(
		type == GL_INT ||
		type == GL_UNSIGNED_INT ||
		type == GL_SHORT ||
		type == GL_UNSIGNED_SHORT ||
		type == GL_BYTE ||
		type == GL_UNSIGNED_BYTE
		)
	{
		glVertexAttribIPointer(index, components, type, GL_FALSE, nullptr);
	}
	else
	{
		Error(debugMsg, "Unrecognized type!");
	}
	glEnableVertexAttribArray(index);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexArrayPack::AddAttribAt(BufferPack<GLfloat>& buffer, GLuint index, GLuint components)
{
	AddAttribute(buffer, index, components, GL_FLOAT);
}

void VertexArrayPack::AddAttribAt(BufferPack<GLdouble>& buffer, GLuint index, GLuint components)
{
	AddAttribute(buffer, index, components, GL_DOUBLE);
}

void VertexArrayPack::AddAttribAt(BufferPack<GLint>& buffer, GLuint index, GLuint components)
{
	AddAttribute(buffer, index, components, GL_INT);
}

void VertexArrayPack::AddAttribAt(BufferPack<GLuint>& buffer, GLuint index, GLuint components)
{
	AddAttribute(buffer, index, components, GL_UNSIGNED_INT);
}

void VertexArrayPack::AddAttribAt(BufferPack<GLshort>& buffer, GLuint index, GLuint components)
{
	AddAttribute(buffer, index, components, GL_SHORT);
}

void VertexArrayPack::AddAttribAt(BufferPack<GLushort>& buffer, GLuint index, GLuint components)
{
	AddAttribute(buffer, index, components, GL_UNSIGNED_SHORT);
}

void VertexArrayPack::AddAttribAt(BufferPack<GLbyte>& buffer, GLuint index, GLuint components)
{
	AddAttribute(buffer, index, components, GL_BYTE);
}

void VertexArrayPack::AddAttribAt(BufferPack<GLubyte>& buffer, GLuint index, GLuint components)
{
	AddAttribute(buffer, index, components, GL_UNSIGNED_BYTE);
}

void VertexArrayPack::Bind()
{
	if (!this->isAttached)
	{
		Warning(debugMsg, "Cannot bind vertexarray %u for it's not attached yet, bailing.", this->AssetID);
		return;
	}
	glBindVertexArray(this->AssetID);
	CheckStatus(__FUNCTION__);
}

VertexArrayPack::operator GLuint()
{
	return this->AssetID;
}

GLuint VertexArrayPack::operator[](GLuint index)
{
	return this->Attribs[index];
}