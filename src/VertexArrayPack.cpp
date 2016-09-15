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

	for (auto i : this->Attribs)
	{
		glBindBuffer(GL_ARRAY_BUFFER, i.second.bufferHandle);

		if
			(
			i.second.type == GL_FLOAT ||
			i.second.type == GL_DOUBLE
			)
			//TODO: There are still many floating types out there
		{
			glVertexAttribPointer(i.first, i.second.components, i.second.type, GL_FALSE, 0, nullptr);
		}
		else if 
			(
			i.second.type == GL_INT ||
			i.second.type == GL_UNSIGNED_INT ||
			i.second.type == GL_SHORT ||
			i.second.type == GL_UNSIGNED_SHORT ||
			i.second.type == GL_BYTE ||
			i.second.type == GL_UNSIGNED_BYTE
			)
		{
			glVertexAttribIPointer(i.first, i.second.components, i.second.type, GL_FALSE, nullptr);
		}
		else
		{
			Error(debugMsg, "Unrecognized type!");
		}
		glEnableVertexAttribArray(i.first);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
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

	/*for (auto i : this->Attribs)
	{
		reinterpret_cast<BufferPack<GLfloat>*>(i.second.bufferptr)->Detach();
	}*/

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
	Attribs[index] = Attrib(buffer, components, type);
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

GLuint VertexArrayPack::operator[](GLuint index)
{
	return Attribs.at(index).bufferHandle;
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

void VertexArrayPack::UnBind()
{
	glBindVertexArray(0);
	CheckStatus(__FUNCTION__);
}

VertexArrayPack::operator GLuint()
{
	return this->AssetID;
}