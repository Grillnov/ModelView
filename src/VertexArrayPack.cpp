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

	for (auto i : this->FloatAttribs)
	{
		i.second.bufferptr->Attach();
		i.second.bufferptr->Bind(GL_ARRAY_BUFFER);
		glVertexAttribPointer(i.first, i.second.components, GL_FLOAT, GL_FALSE, 0, nullptr);
		glEnableVertexAttribArray(i.first);
	}

	for (auto i : this->IntAttribs)
	{
		i.second.bufferptr->Attach();
		i.second.bufferptr->Bind(GL_ARRAY_BUFFER);
		glVertexAttribIPointer(i.first, i.second.components, GL_INT, GL_FALSE, nullptr);
		glEnableVertexAttribArray(i.first);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
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

	for (auto i : this->FloatAttribs)
	{
		i.second.bufferptr->Detach();
	}

	for (auto i : this->IntAttribs)
	{
		i.second.bufferptr->Detach();
	};

	CheckStatus(__FUNCTION__);

	Log(debugMsg, "Vertexarray %u was successfully detached.", this->AssetID);
	this->isAttached = false;
}

void VertexArrayPack::AddBufferWithIndex(BufferPack<GLfloat>* buffer, GLuint index, GLuint components)
{
	if (components > 4 || components == 0)
	{
		Error(debugMsg, "Invalid number of components: %u. A component amount of 1-4 is expected.", components);
		return;
	}
	if (FloatAttribs.find(index) != FloatAttribs.end()
		|| IntAttribs.find(index) != IntAttribs.end())
	{
		Error(debugMsg, "For vertexarray %u, index %u is already occupied by another buffer.", this->AssetID, index);
		return;
	}
	FloatAttribs[index] = VertAttribf(buffer, components);
}

void VertexArrayPack::AddBufferWithIndex(BufferPack<GLint>* buffer, GLuint index, GLuint components)
{
	if (components > 4 || components == 0)
	{
		Error(debugMsg, "Invalid number of components: %u. A component amount of 1-4 is expected.", components);
		return;
	}
	if (FloatAttribs.find(index) != FloatAttribs.end()
		|| IntAttribs.find(index) != IntAttribs.end())
	{
		Error(debugMsg, "For vertexarray %u, index %u is already occupied by another buffer.", this->AssetID, index);
		return;
	}
	IntAttribs[index] = VertAttribi(buffer, components);
}

void* VertexArrayPack::operator[](GLuint index)
{
	if (FloatAttribs.find(index) != FloatAttribs.end())
		return FloatAttribs.at(index).bufferptr;
	else
		return IntAttribs.at(index).bufferptr;
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