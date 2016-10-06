//
//  RenderBuffer.h
//  ModelView
//
//  Created by Bowen Yang on Oct 5, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# ifndef __ModelView__RenderBuffer__
# define __ModelView__RenderBuffer__

# include <Options.h>

/**
@brief Render buffer object.
*/
class RenderBuffer : public GLAsset
{
public:
	/**
	@brief Register a renderbuffer in the OpenGL context.

	@param internalFormat The storage format on the server side.
	For color-related render buffer: A value among GL_R8, GL_RGB32F,
	GL_RG8UI, GL_RGBA...... etc. is expected.
	For depth-related render buffer: A value among GL_DEPTH_COMPONENT,
	GL_DEPTH_COMPONENT32F...... etc. is expected.
	For stencil-related render buffer: A value among GL_STENCIL_INDEX,
	GL_STENCIL_INDEX1, GL_STENCIL_INDEX4...... etc. is expected.
	By default it's set as GL_RGB32F.
	*/
	RenderBuffer(GLenum internalFormat = GL_RGB32F) : xWidth(0), yHeight(0), internalFormat(GL_RGB32F)
	{
		glGenRenderbuffers(1, &this->AssetID);

		if (AssetID != 0)
		{
			Log(debugMsg, "Renderbuffer %u was successfully registered.", this->AssetID);
		}
		else
		{
			Error(debugMsg, "Failed to create a renderbuffer.");
		}
		glBindRenderbuffer(GL_RENDERBUFFER, this->AssetID);
		CheckStatus(__FUNCTION__);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}

	/**
	@brief Unregister the renderbuffer from the OpenGL context, recycling its name for further use.
	*/
	~RenderBuffer()
	{
		glDeleteRenderbuffers(1, &this->AssetID);
		CheckStatus(__FUNCTION__);

		Log(debugMsg, "Renderbuffer %u was successfully unregistered.", this->AssetID);
	}

	/**
	@brief Allocate memory for this renderbuffer.

	@param Width The width of the render buffer.

	@param Height The height of the render buffer.
	*/
	void Alloc(GLsizei Width, GLsizei Height)
	{
		glBindRenderbuffer(GL_RENDERBUFFER, this->AssetID);

		glRenderbufferStorage(GL_RENDERBUFFER, internalFormat, Width, Height);
		CheckStatus(__FUNCTION__);

		this->xWidth = Width;
		this->yHeight = Height;

		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}

	/**
	@brief Allocate memory for this renderbuffer with multisampling enabled.

	@param Width The width of the render buffer.

	@param Height The height of the render buffer.

	@param Samples The amount of multisampling samples.
	By default it's set as 1.
	*/
	void AllocMS(GLsizei Width, GLsizei Height, GLsizei Samples = 1)
	{
		glBindRenderbuffer(GL_RENDERBUFFER, this->AssetID);

		glRenderbufferStorage(GL_RENDERBUFFER, internalFormat, Width, Height);
		CheckStatus(__FUNCTION__);

		this->xWidth = Width;
		this->yHeight = Height;

		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}
private:
	GLsizei xWidth;
	GLsizei yHeight;
	GLenum internalFormat;
};

# endif