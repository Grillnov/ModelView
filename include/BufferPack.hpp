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

/**
Base class for all kinds of buffer objects.
Generic class for buffers.
GL type is designated by macros when invoking GL interfaces, thus template is not used.
*/
template<typename GLclientside>
class BufferPack : public GLAttachable, public GLObject
{
private:
	size_t num_of_elements;
public:
	/**
	local pointer to client side memory
	*/
	GLclientside* LocalPtr;

	/**
	Default constructor, not supposed to be of any use.
	*/
	//BufferPack();

	/**
	Constructor that sets the local pointer to Ptr, with size specified.
	*/
	BufferPack(GLclientside* Ptr, size_t num_of_elements);

	/**
	Constructor that allocates memory space on the client side.
	*/
	BufferPack(size_t num_of_elements);

	/**
	Simply register the asset, without allocating memory or copying anything from client to server.
	*/
	void Attach() override;

	/**
	Unregister the asset.
	*/
	void Detach() override;	

	/**
	Bind the buffer to some target
	*/
	void Bind(GLenum target);

	/**
	It's always a bad idea to include OpenGL invokes in destructing functions
	So we just simply detach this in this function.
	*/
	void DeleteObject() override;

	/**
	Free its memory space allocated on the client side, and destroy the buffer pack.
	*/
	~BufferPack();

	/**
	Synchorize the local client side memory with server side buffer.
	@ params
	@ bindingPoint the binded target of the buffer.
	@ usage the hinted usage of this buffer area.
	Currently this function is deprecated.
	*/
	//void Upload2Server(GLenum bindingPoint, GLenum usage = GL_STATIC_DRAW);

	/** Access client side memory
	@ params
	@ index the index of the element
	*/
	GLclientside& operator[](size_t index);

	/** Modify the server side memory
	*/
	GLclientside* at_Server(size_t index);
};

/*
template<typename GLclientside>
BufferPack<GLclientside>::BufferPack()
	: isUploaded(false), LocalPtr(nullptr), num_of_elements(0)
{}
*/

template<typename GLclientside>
BufferPack<GLclientside>::BufferPack(GLclientside* Ptr, size_t num_of_elements)
	: LocalPtr(Ptr), num_of_elements(num_of_elements)
{}

template<typename GLclientside>
BufferPack<GLclientside>::BufferPack(size_t num_of_elements)
	: num_of_elements(num_of_elements)
{
	this->LocalPtr = new GLclientside[num_of_elements];
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
	CheckStatus(__FUNCTION__);

	size_t bufferSize = this->num_of_elements * sizeof(GLclientside);

	glBindBuffer(GL_COPY_WRITE_BUFFER, this->AssetID);
	glBufferData(GL_COPY_WRITE_BUFFER, bufferSize, this->LocalPtr, GL_STATIC_DRAW);

	glBindBuffer(GL_COPY_WRITE_BUFFER, 0);

	CheckStatus(__FUNCTION__);
	Log(debugMsg, "Successfully uploaded %u bytes of data to buffer %u.", bufferSize, this->AssetID);

	Log(debugMsg, "Attached buffer %u", this->AssetID);
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
	Log(debugMsg, "Detached buffer %u", this->AssetID);
	this->isAttached = false;
}

template<typename GLclientside>
void BufferPack<GLclientside>::Bind(GLenum target)
{
	glBindBuffer(target, this->AssetID);
	CheckStatus(__FUNCTION__);
}

template<typename GLclientside>
void BufferPack<GLclientside>::DeleteObject()
{
	this->Detach();
	this->~BufferPack();
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
	if (index * sizeof(GLclientside) > this->BufferSize)
	{
		Warning(debugMsg, "Index %u is out of boundary!", index);
	}
	return this->LocalPtr[index];
}

# endif