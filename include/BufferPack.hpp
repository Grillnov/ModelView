//
//  BufferPack.hpp
//  ModelView
//
//  Created by Bowen Yang on Aug 4, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# ifndef __ModelView__BufferPack__
# define __ModelView__BufferPack__

# include <Options.h>

/**
@brief Buffer object managing chunks of continuous memory on the server side as buffer objects.
Generic class for all kinds of buffers.
Note that this buffer class only serves as a shell injecting data into server side.
There's not a copy of the memory on the client side.

@param GLclientside the client side types defined by OpenGL standard protocol.
Such as GLint, GLuint, GLfloat, GLdouble, etc.
*/
template<typename GLclientside>
class BufferPack : public GLAsset
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
	@brief Register a buffer in the OpenGL context.
	*/
	BufferPack();

	/**
	@brief Unregister the buffer from the OpenGL context, recycling its name for further use.
	*/
	~BufferPack();

	/**
	@brief A naiver version of Alloc().
	Effective, yet may cause some performance issues.
	Simply allocate memory on the server side so that you can assign it with data from client side
	via operator[] from local memory, with target hint set as GL_COPY_WRITE_BUFFER, and usage hint
	set as GL_STATIC_DRAW by default.

	@param Num_of_elements The number of elements you want to allocate.
	*/
	void Alloc(GLsizei Num_of_elements);

	/**
	@brief When glBufferData is invoked, specified binding target and usage will affect
	the memory location allocated for this buffer on the server side.
	Use naiver Alloc() is recommended when you're not so sure how to boost memory
	access performance by designating target and usage.

	@param Num_of_elements The number of elements you want to allocate.

	@param HintBindedtarget The GLenum target the buffer will be binded to when it's created.
	A value among GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER, GL_COPY_WRITE_BUFFER......etc. is 
	expected.

	@param HintUsage The GLenum usage the buffer will be used.
	A value among GL_STATIC_DRAW, GL_DYNAMIC_DRAW, GL_STREAM_COPY......etc. is expected.
	*/
	void Alloc(GLsizei Num_of_elements, GLenum HintBindtarget, GLenum HintUsage);

	/**
	@brief Bind the buffer to some target.
	Deprecated. Use glBindBuffer() instead.

	@param Target the target you want to bind the buffer to.
	A value among GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER, GL_COPY_WRITE_BUFFER......etc. is
	expected.
	*/
	void Bind(GLenum Target);

	/**
	@brief Modify the server side memory on the fly.

	@param Index The index of the element you want to access.
	*/
	GLclientside& operator[](GLsizei Index);

	/**
	@brief Modify the server side memory on the fly.

	@param Index The index of the element you want to access.
	*/
	GLclientside& at(GLsizei Index);

	/**
	@brief When you are done with the buffer changing on the fly, invoke Done()
	to unmap the buffer and save your changes on the server side.
	Not a necessary move, but might introduce dangerous behaviours from OpenGL implementations.
	*/
	void Done();
};

template<typename GLclientside>
BufferPack<GLclientside>::BufferPack()
	: num_of_elements(0), isMapped(false), MappedPtr(nullptr)
{
	glGenBuffers(1, &this->AssetID);

	if (AssetID != 0)
	{
		Log(debugMsg, "Buffer %u was successfully registered.", this->AssetID);
	}
	else
	{
		Error(debugMsg, "Failed to create a buffer.");
	}
	CheckStatus(__FUNCTION__);
}

template<typename GLclientside>
BufferPack<GLclientside>::~BufferPack()
{
	glInvalidateBufferData(this->AssetID);
	glDeleteBuffers(1, &this->AssetID);

	CheckStatus(__FUNCTION__);
	Log(debugMsg, "Buffer %u was successfully unregistered.", this->AssetID);
}

template<typename GLclientside>
void BufferPack<GLclientside>::Alloc(GLsizei num_of_elements)
{
	Alloc(num_of_elements, GL_ARRAY_BUFFER, GL_STATIC_DRAW);
}

template<typename GLclientside>
void BufferPack<GLclientside>::Alloc(GLsizei Num_of_elements, GLenum HintBindingPoint, GLenum HintUsage)
{
	if (Num_of_elements == 0)
		Error(debugMsg, "Illegal size of elements: %d", Num_of_elements);

	if (this->isReady)
	{
		Warning(debugMsg, "Already allocated memory to buffer %u, bailing.", this->AssetID);
		return;
	}

	this->num_of_elements = Num_of_elements;
	GLsizei bufferSize = this->num_of_elements * sizeof(GLclientside);

	glBindBuffer(HintBindingPoint, this->AssetID);
	glBufferData(HintBindingPoint, bufferSize, nullptr, HintUsage);

	glBindBuffer(HintBindingPoint, 0);

	CheckStatus(__FUNCTION__);
	Log(debugMsg, "Successfully allocated %d bytes of data on server side for buffer %u.", bufferSize, this->AssetID);

	this->isReady = true;
}

template<typename GLclientside>
void BufferPack<GLclientside>::Bind(GLenum Target)
{
	glBindBuffer(Target, this->AssetID);
	CheckStatus(__FUNCTION__);
}

template<typename GLclientside>
GLclientside& BufferPack<GLclientside>::operator[](GLsizei Index)
{
	if (Index > this->num_of_elements)
	{
		Error(debugMsg, "Cannot access %dth element in buffer %u, out of boundary!", Index, this->AssetID);
	}
	
	if (this->isMapped)
	{
		return *(this->MappedPtr + Index);
	}
	else
	{
		glBindBuffer(GL_COPY_WRITE_BUFFER, this->AssetID);
		this->MappedPtr = reinterpret_cast<GLclientside*>(glMapBuffer(GL_COPY_WRITE_BUFFER, GL_READ_WRITE));

		if (MappedPtr == nullptr)
			Error(debugMsg, "Cannot map a pointer for buffer %u.", this->AssetID);

		CheckStatus(__FUNCTION__);

		this->isMapped = true;
		glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
		return *(this->MappedPtr + Index);
	}
}

template<typename GLclientside>
GLclientside& BufferPack<GLclientside>::at(GLsizei Index)
{
	return (*this)[Index];
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
	glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
}

# endif