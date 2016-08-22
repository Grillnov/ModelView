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
class BufferPack : public GLAttachable, public GLObject
{
private:
	/**
	Amount of elements.
	*/
	size_t num_of_elements;

	/**
	The target the buffer is binded to.
	*/
	GLenum CurrentBindedTarget;

	/**
	Local pointer to client side memory.
	*/
	GLclientside* LocalPtr;
public:
	

	/**
	Returns the amount of elements.
	*/
	size_t Size()
	{
		return num_of_elements;
	}

	/**
	Constructor that sets the local pointer to Ptr, with size specified.
	*/
	BufferPack(GLclientside* Ptr, size_t num_of_elements);

	/**
	Constructor that allocates memory space on the client side.
	*/
	BufferPack(size_t num_of_elements);

	/**
	A naiver version of Attach().
	Effective, yet may cause some performance issues.
	Simply register the asset, allocating memory on the server side and upload
	local memory.
	*/
	void Attach() override;

	/**
	When glBufferData is invoked, current binding target and usage will affect
	the memory location allocated to this buffer.
	*/
	void Attach(GLenum hintBindtarget, GLenum hintUsage);

	/**
	Unregister the asset.
	*/
	void Detach() override;	

	/**
	Bind the buffer to some target
	*/
	void Bind(GLenum target);

	/**
	Restore binded target to its default status
	*/
	void UnBind();

	/**
	It's always a bad idea to include OpenGL invokes in destructing functions
	So we just simply detach this in this function.
	*/
	//void DeleteObject() override;

	/**
	Free its memory space allocated on the client side, and destroy the buffer pack.
	*/
	~BufferPack();

	/** Access client side memory
	@ params
	@ index the index of the element
	*/
	GLclientside& operator[](size_t index);

	/**
	Get the client side local pointer to the buffer.
	*/
	GLclientside* GetLocalPtr()
	{
		return this->LocalPtr;
	}
};

template<typename GLclientside>
BufferPack<GLclientside>::BufferPack(GLclientside* Ptr, size_t num_of_elements)
	: LocalPtr(Ptr), num_of_elements(num_of_elements), CurrentBindedTarget(-1)
{
	if (num_of_elements == 0)
		Error(debugMsg, "Illegal size of elements: %u", num_of_elements);
}

template<typename GLclientside>
BufferPack<GLclientside>::BufferPack(size_t num_of_elements)
	: num_of_elements(num_of_elements), CurrentBindedTarget(-1)
{
	if (num_of_elements == 0)
		Error(debugMsg, "Illegal size of elements: %u", num_of_elements);
	try
	{
		this->LocalPtr = new GLclientside[num_of_elements];
	}
	catch (std::bad_alloc exception)
	{
		Error(debugMsg, "Unable to allocate %u bytes of memory for client side buffer."
			, this->num_of_elements*sizeof(GLclientside));
	}
}

template<typename GLclientside>
void BufferPack<GLclientside>::Attach()
{
	if (this->isAttached)
	{
		Warning(debugMsg, "Buffer %u is already attached, bailing.", this->AssetID);
		return;
	}
	glCreateBuffers(1, &this->AssetID);

	size_t bufferSize = this->num_of_elements * sizeof(GLclientside);

	glBindBuffer(GL_COPY_WRITE_BUFFER, this->AssetID);
	glBufferData(GL_COPY_WRITE_BUFFER, bufferSize, this->LocalPtr, GL_STATIC_DRAW);

	glBindBuffer(GL_COPY_WRITE_BUFFER, 0);

	CheckStatus(__FUNCTION__);
	Log(debugMsg, "Successfully uploaded %u bytes of data to buffer %u.", bufferSize, this->AssetID);

	Log(debugMsg, "Buffer %u was successfully attached.", this->AssetID);
	this->isAttached = true;
}

template<typename GLclientside>
void BufferPack<GLclientside>::Attach(GLenum hintBindingPoint, GLenum hintUsage)
{
	if (this->isAttached)
	{
		Warning(debugMsg, "Buffer %u is already attached, bailing.", this->AssetID);
		return;
	}
	glCreateBuffers(1, &this->AssetID);

	size_t bufferSize = this->num_of_elements * sizeof(GLclientside);

	glBindBuffer(hintBindingPoint, this->AssetID);
	glBufferData(hintBindingPoint, bufferSize, this->LocalPtr, hintUsage);

	glBindBuffer(hintBindingPoint, 0);

	CheckStatus(__FUNCTION__);
	Log(debugMsg, "Successfully uploaded %u bytes of data to buffer %u.", bufferSize, this->AssetID);

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
	this->CurrentBindedTarget = target;
	glBindBuffer(target, this->AssetID);
	CheckStatus(__FUNCTION__);
}

template<typename GLclientside>
void BufferPack<GLclientside>::UnBind()
{
	if (this->CurrentBindedTarget == -1)
		Error(debugMsg, "Buffer %u hasn't been binded to any target yet, bailing.", this->AssetID);
	glBindBuffer(this->CurrentBindedTarget, this->AssetID);
	CheckStatus(__FUNCTION__);
}

template<typename GLclientside>
BufferPack<GLclientside>::~BufferPack()
{
	if (this->isAttached)
	{
		Warning(debugMsg, "Buffer %u isn't detached before destruction, risk of causing memory leakage on server side.", this->AssetID);
	}
	delete[] this->LocalPtr;
}

template<typename GLclientside>
GLclientside& BufferPack<GLclientside>::operator[](size_t index)
{
	if (index > this->num_of_elements)
	{
		Warning(debugMsg, "Index %u is out of boundary!", index);
	}
	return this->LocalPtr[index];
}

# endif