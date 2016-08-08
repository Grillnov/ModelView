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
class BufferPack : public GLAttachable, public GLObject
{
protected:
	void* LocalPtr;/** local pointer to client side memory*/
	size_t BufferSize;/** in bytes*/
	bool isUploaded;/** is server side memory allocated and written by the client yet?*/
public:
	/**
	Default constructor, not supposed to be of any use.
	*/
	BufferPack();

	/**
	Constructor that sets the local pointer to Ptr, with size specified.
	*/
	BufferPack(void* Ptr, size_t Size);

	/**
	Constructor that allocates memory space on the client side.
	*/
	BufferPack(size_t Size);

	/**
	Simply register the asset, without allocating memory or copying anything from client to server.
	*/
	void Attach() override;

	/**
	Unregister the asset.
	*/
	void Detach() override;	

	/**
	Telling whether it's attached or not
	*/
	bool IsAttached() override { return this->isAttached; }

	/**
	Free its memory space allocated on the client side.
	It's always a bad idea to include OpenGL invokes in destructing functions
	So we just simply check that out
	*/
	~BufferPack();

	/**
	Synchorize the local client side memory with server side buffer.
	@ params
	@ bindingPoint the binded target of the buffer.
	@ usage the hinted usage of this buffer area.
	*/
	void Upload2Server(GLenum bindingPoint, GLenum usage = GL_STATIC_DRAW);

	/**
	void* AccessBytes();
	*/
};

/**
Buffer storing GLfloat.
*/
class BufferPackf : public BufferPack
{
public:
	BufferPackf(GLfloat* Src, GLsizei NumofElements);
	BufferPackf(GLsizei NumofElements);
};

/**
Buffer storing GLDouble.
*/
class BufferPackd : public BufferPack
{
public:
	BufferPackd(GLdouble* Src, GLsizei NumofElements);
	BufferPackd(GLsizei NumofElements);
};

/**
Buffer storing GLuint.
*/
class BufferPackui : public BufferPack
{
public:
	BufferPackui(GLuint* Src, GLsizei NumofElements);
	BufferPackui(GLsizei NumofElements);
};

/**
Buffer storing GLint.
*/
class BufferPacki : public BufferPack
{
public:
	BufferPacki(GLint* Src, size_t NumofElements);
	BufferPacki(size_t NumofElements);
};

/**
Buffer storing GLbyte.
*/
class BufferPackb : public BufferPack
{
public:
	BufferPackb(GLbyte* Src, size_t NumofElements);
	BufferPackb(size_t NumofElements);
};
# endif