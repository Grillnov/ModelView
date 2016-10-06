//
//  Texture3D.cpp
//  ModelView
//
//  Created by Bowen Yang on Sept 18, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include <Texture3D.h>

void Texture3D::LoadFromMemory(GLubyte* Pixels, GLsizei Width, GLsizei Height, GLsizei Depth,
	GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, Depth,
		clientsideFormat, GL_UNSIGNED_BYTE);
}

void Texture3D::LoadFromMemory(GLbyte* Pixels, GLsizei Width, GLsizei Height, GLsizei Depth,
	GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, Depth,
		clientsideFormat, GL_BYTE);
}

void Texture3D::LoadFromMemory(GLushort* Pixels, GLsizei Width, GLsizei Height, GLsizei Depth,
	GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, Depth,
		clientsideFormat, GL_UNSIGNED_SHORT);
}

void Texture3D::LoadFromMemory(GLshort* Pixels, GLsizei Width, GLsizei Height, GLsizei Depth,
	GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, Depth,
		clientsideFormat, GL_SHORT);
}

void Texture3D::LoadFromMemory(GLuint* Pixels, GLsizei Width, GLsizei Height, GLsizei Depth,
	GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, Depth,
		clientsideFormat, GL_UNSIGNED_INT);
}

void Texture3D::LoadFromMemory(GLint* Pixels, GLsizei Width, GLsizei Height, GLsizei Depth,
	GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, Depth,
		clientsideFormat, GL_INT);
}

void Texture3D::LoadFromMemory(GLfloat* Pixels, GLsizei Width, GLsizei Height, GLsizei Depth,
	GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, Depth,
		clientsideFormat, GL_FLOAT);
}

void Texture3D::LoadFromMemory(GLdouble* Pixels, GLsizei Width, GLsizei Height, GLsizei Depth,
	GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, Depth,
		clientsideFormat, GL_DOUBLE);
}

void Texture3D::Alloc(GLsizei Width, GLsizei Height, GLsizei Depth)
{
	if (this->xWidth != 0 || this->yHeight != 0 || this->dDepth != 0)
	{
		glInvalidateTexImage(this->AssetID, 0);
	}

	glBindTexture(GL_TEXTURE_3D, this->AssetID);
	this->xWidth = Width;
	this->yHeight = Height;
	this->dDepth = Depth;
	glTexStorage3D(GL_TEXTURE_3D, levels, internalFormat, xWidth, yHeight, dDepth);
}

void Texture3D::LoadFromMemory(void* Pixels, GLsizei Width, GLsizei Height, GLsizei Depth,
	GLenum clientsideFormat, GLenum type)
{
	if (this->xWidth != Width || this->yHeight != Height || this->dDepth != Depth)
	{
		Alloc(Width, Height, Depth);
	}
	glBindTexture(GL_TEXTURE_3D, this->AssetID);

	glTexSubImage3D(GL_TEXTURE_3D, 0, 0, 0, 0, xWidth, yHeight, dDepth, clientsideFormat, type, Pixels);

	if (generateMipmaps)
	{
		glGenerateTextureMipmap(this->AssetID);
	}
	
	glActiveTexture(GL_TEXTURE0 + this->layoutSlot);
	glBindTexture(GL_TEXTURE_2D, this->AssetID);

	glBindSampler(layoutSlot, defaultSampler);

	Param(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	Param(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	Param(GL_TEXTURE_WRAP_S, GL_REPEAT);
	Param(GL_TEXTURE_WRAP_T, GL_REPEAT);
	Param(GL_TEXTURE_WRAP_R, GL_REPEAT);

	CheckStatus(__FUNCTION__);

	Log(debugMsg, "3D texture %u at layout slot %u is now ready.", this->AssetID, this->layoutSlot);
}