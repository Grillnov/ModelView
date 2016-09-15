//
//  BufferPack.h
//  ModelView
//
//  Created by Bowen Yang on Aug 4, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# ifndef BUFFERPACK
# define BUFFERPACK

# include "AllinGL.h"
# include <exception>

/**
Chunks of continuous memory as buffer objects.
Generic class for all kinds of buffers.
*/
template<typename GLclientside>
class BufferPack : public GLObject, public GLAttachable
{
private:
	/**
	Amount of elements.
	*/
	GLsizei num_of_elements;

	/**
	Local pointer to server side memory.
	*/
	GLclientside* MappedPtr;

	/**
	Is there any pointer on the client side mapped to this buffer?
	*/
	bool isMapped;
public:
	/**
	Returns the amount of elements.
	*/
	GLsizei Size()
	{
		return num_of_elements;
	}

	/**
	Constructor that returns a dummy buffer.
	*/
	BufferPack() = default;

	/**
	Constructor that allocates memory space on the client side.
	*/
	BufferPack(GLsizei num_of_elements);

	/**
	A naiver version of Attach().
	Effective, yet may cause some performance issues.
	Simply register the asset, allocate memory on the server side and upload
	local memory, with target hint set as GL_COPY_WRITE_BUFFER, and usage hint
	set as GL_STATIC_DRAW.
	*/
	void Attach() override;

	/**
	When glBufferData is invoked, specified binding target and usage will affect
	the memory location allocated for this buffer.
	Use naiver Attach() is recommended when you're not so sure how to boost memory
	access performance by designating target and usage.
	*/
	void Attach(GLenum hintBindtarget, GLenum hintUsage);

	/**
	Unregister the asset.
	*/
	void Detach() override;	

	/**
	Bind the buffer to some target
	*/
	//void Bind(GLenum target);

	/**
	It's always a bad idea to include OpenGL invokes in destructing functions
	So we just simply detach this in this function.
	*/
	//void DeleteObject() override;

	/**
	Free its memory space allocated on the client side, and destroy the buffer pack.
	*/
	~BufferPack();

	/** Modify the server side memory on the fly.
	@ params
	@ index the index of the element
	*/
	GLclientside& operator[](GLsizei index);
	GLclientside& at(GLsizei index);

	/**
	When you are done with the buffer changing on the fly, invoke this
	to unmap the buffer and save your changes.
	*/
	void Done();

	/**
	Converter to GLuint.
	*/
	operator GLuint()
	{
		return this->AssetID;
	}
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

/*template<typename GLclientside>
void BufferPack<GLclientside>::Bind(GLenum target)
{
	if (!this->isAttached)
	{
		Warning(debugMsg, "Cannot bind buffer %u for it's not attached yet, bailing.", this->AssetID);
		return;
	}
	this->CurrentBindedTarget = target;
	glBindBuffer(target, this->AssetID);
	CheckStatus(__FUNCTION__);
}*/

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

# endif