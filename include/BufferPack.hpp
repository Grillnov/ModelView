//
//  BufferPack.hpp
//  ModelView
//
//  Created by Bowen Yang on Aug 4, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# ifndef __ModelView__BufferPack__
# define __ModelView__BufferPack__

# include "AllinGL.h"

/**
@brief Buffer object managing chunks of continuous memory on the server side as buffer objects.
Generic class for all kinds of buffers.
Note that this buffer class only serves as a shell injecting data into server side.
There's not a copy at client side.
@param GLclientside the client side types defined by OpenGL standard.
Such as GLint, GLuint, GLfloat, GLdouble, etc.
*/
template<typename GLclientside>
class BufferPack : public GLAttachable
{
private:
	/*
	Amount of elements.
	*/
	GLsizei num_of_elements;

	/*
	Local pointer to server side memory.
	*/
	GLclientside* MappedPtr;

	/*
	Is there any pointer on the client side mapped to this buffer?
	*/
	bool isMapped;
public:
	/**
	@brief Returns how many elements there are in this buffer.
	*/
	GLsizei Size()
	{
		return num_of_elements;
	}

	/**
	@brief Default constructor that returns a dummy buffer.
	*/
	BufferPack() = default;

	/**
	@brief Constructing a buffer object ready for elements.
	@param num_of_elements The number of elements you need.
	*/
	BufferPack(GLsizei num_of_elements);

	/**
	@brief A naiver version of Attach().
	Effective, yet may cause some performance issues.
	Simply register the asset, allocate memory on the server side so that you can assign its data
	via operator[] from local memory, with target hint set as GL_COPY_WRITE_BUFFER, and usage hint
	set as GL_STATIC_DRAW by default.
	*/
	void Attach() override;

	/**
	@brief When glBufferData is invoked, specified binding target and usage will affect
	the memory location allocated for this buffer on the server side.
	Use naiver Attach() is recommended when you're not so sure how to boost memory
	access performance by designating target and usage.
	@param hintBindedtarget The GLenum target the buffer will be binded to when it's created.
	for example, GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER, GL_COPY_WRITE_BUFFER, etc.
	@param hintUsage The GLenum usage the buffer will be used.
	for example, GL_STATIC_DRAW, GL_DYNAMIC_DRAW, etc.
	*/
	void Attach(GLenum hintBindtarget, GLenum hintUsage);

	/**
	@brief Unregister the asset from OpenGL, recycling its name for further use.
	*/
	void Detach() override;	

	/**
	@brief Bind the buffer to some target.
	*/
	void Bind(GLenum target);

	/**
	@brief Deprecated.
	It's always a bad idea to include OpenGL invokes in destructing functions
	So we just simply detach this in this function.
	*/
	void DeleteObject() override;

	/**
	@brief Free its memory space allocated on the client side, and destroy the buffer pack.
	*/
	~BufferPack();

	/**
	@brief Modify the server side memory on the fly.
	@param index The index of the element.
	*/
	GLclientside& operator[](GLsizei index);

	/**
	@brief Modify the server side memory on the fly.
	@param index The index of the element.
	*/
	GLclientside& at(GLsizei index);

	/**
	@brief When you are done with the buffer changing on the fly, invoke Done()
	to unmap the buffer and save your changes.
	*/
	void Done();

	/**
	@brief Converter to GLuint.
	*/
	operator GLuint() override;
};

template<typename GLclientside>
BufferPack<GLclientside>::BufferPack(GLsizei num_of_elements)
	: num_of_elements(num_of_elements), isMapped(false)
{
	if (num_of_elements == 0)
		Error(debugMsg, "Illegal size of elements: %d", num_of_elements);
}

template<typename GLclientside>
void BufferPack<GLclientside>::Attach()
{
	Attach(GL_COPY_WRITE_BUFFER, GL_STATIC_DRAW);
}

template<typename GLclientside>
void BufferPack<GLclientside>::Attach(GLenum hintBindingPoint, GLenum hintUsage)
{
	if (this->isAttached)
	{
		Warning(debugMsg, "Buffer %u is already attached, bailing.", this->AssetID);
		return;
	}
	glGenBuffers(1, &this->AssetID);

	GLsizei bufferSize = this->num_of_elements * sizeof(GLclientside);

	glBindBuffer(hintBindingPoint, this->AssetID);
	glBufferData(hintBindingPoint, bufferSize, nullptr, hintUsage);

	glBindBuffer(hintBindingPoint, 0);

	CheckStatus(__FUNCTION__);
	Log(debugMsg, "Successfully allocated %d bytes of data on server side for buffer %u.", bufferSize, this->AssetID);

	Log(debugMsg, "Buffer %u was successfully attached.", this->AssetID);
	this->isAttached = true;
}

template<typename GLclientside>
void BufferPack<GLclientside>::Detach()
{
	if (!this->isAttached)
	{
		Warning(debugMsg, "Buffer %u is not attached yet, bailing.", this->AssetID);
		return;
	}
	glInvalidateBufferData(this->AssetID);
	glDeleteBuffers(1, &this->AssetID);

	CheckStatus(__FUNCTION__);
	Log(debugMsg, "Buffer %u was successfully detached.", this->AssetID);
	this->isAttached = false;
}

template<typename GLclientside>
void BufferPack<GLclientside>::Bind(GLenum target)
{
	if (!this->isAttached)
	{
		Warning(debugMsg, "Cannot bind buffer %u for it's not attached yet, bailing.", this->AssetID);
		return;
	}

	glBindBuffer(target, this->AssetID);
	CheckStatus(__FUNCTION__);
}

template<typename GLclientside>
BufferPack<GLclientside>::~BufferPack()
{
	if (this->isAttached)
	{
		Warning(debugMsg, "Buffer %u isn't detached before destruction, "
			"risk of causing memory leakage on server side.", this->AssetID);
	}
}

template<typename GLclientside>
GLclientside& BufferPack<GLclientside>::operator[](GLsizei index)
{
	if (index > this->num_of_elements)
	{
		Error(debugMsg, "Cannot access %dth element in buffer %u, out of boundary!", index, this->AssetID);
	}
	if (!this->isAttached)
	{
		Error(debugMsg, "Buffer %u is not attached yet!", this->AssetID);
	}
	if (this->isMapped)
	{
		return *(this->MappedPtr + index);
	}
	else
	{
		glBindBuffer(GL_COPY_WRITE_BUFFER, this->AssetID);
		this->MappedPtr = reinterpret_cast<GLclientside*>(glMapBuffer(GL_COPY_WRITE_BUFFER, GL_READ_WRITE));

		if (MappedPtr == nullptr)
			Error(debugMsg, "Cannot map buffer %u.", this->AssetID);

		CheckStatus(__FUNCTION__);

		this->isMapped = true;
		return *(this->MappedPtr + index);
	}
}

template<typename GLclientside>
GLclientside& BufferPack<GLclientside>::at(GLsizei index)
{
	return (*this)[index];
}

template<typename GLclientside>
void BufferPack<GLclientside>::Done()
{
	if (!this->isMapped)
	{
		Warning(debugMsg, "Buffer %u is not mapped yet, bailing.", this->AssetID);
		return;
	}
	glBindBuffer(GL_COPY_WRITE_BUFFER, this->AssetID);
	glUnmapBuffer(GL_COPY_WRITE_BUFFER);

	CheckStatus(__FUNCTION__);
	Log(debugMsg, "Synchorized memory for buffer %u", this->AssetID);

	this->isMapped = false;
}

template<typename GLclientside>
BufferPack<GLclientside>::operator GLuint()
{
	if (!this->isAttached)
	{
		Error(debugMsg, "Buffer %u is not attached yet, illegal parameter for GL interface!", this->AssetID);
		return -1;
	}
	return this->AssetID;
}

template<typename GLclientside>
void BufferPack<GLclientside>::DeleteObject()
{
	if (this->isAttached)
		this->Detach();
}

# endif