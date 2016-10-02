//
//  Texture3D.cpp
//  ModelView
//
//  Created by Bowen Yang on Sept 18, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include <Texture3D.h>

void Texture3D::LoadFromMemory(GLubyte* Pixels, size_t Width, size_t Height, size_t Depth,
	GLint internalFormat, GLint clientsideFormat, GLsizei levels, bool generateMipMap)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, Depth,
		internalFormat, clientsideFormat, GL_UNSIGNED_BYTE, levels, generateMipMap);
}

void Texture3D::LoadFromMemory(GLbyte* Pixels, size_t Width, size_t Height, size_t Depth,
	GLint internalFormat, GLint clientsideFormat, GLsizei levels, bool generateMipMap)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, Depth,
		internalFormat, clientsideFormat, GL_BYTE, levels, generateMipMap);
}

void Texture3D::LoadFromMemory(GLushort* Pixels, size_t Width, size_t Height, size_t Depth,
	GLint internalFormat, GLint clientsideFormat, GLsizei levels, bool generateMipMap)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, Depth,
		internalFormat, clientsideFormat, GL_UNSIGNED_SHORT, levels, generateMipMap);
}

void Texture3D::LoadFromMemory(GLshort* Pixels, size_t Width, size_t Height, size_t Depth,
	GLint internalFormat, GLint clientsideFormat, GLsizei levels, bool generateMipMap)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, Depth,
		internalFormat, clientsideFormat, GL_SHORT, levels, generateMipMap);
}

void Texture3D::LoadFromMemory(GLuint* Pixels, size_t Width, size_t Height, size_t Depth,
	GLint internalFormat, GLint clientsideFormat, GLsizei levels, bool generateMipMap)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, Depth,
		internalFormat, clientsideFormat, GL_UNSIGNED_INT, levels, generateMipMap);
}

void Texture3D::LoadFromMemory(GLint* Pixels, size_t Width, size_t Height, size_t Depth,
	GLint internalFormat, GLint clientsideFormat, GLsizei levels, bool generateMipMap)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, Depth,
		internalFormat, clientsideFormat, GL_INT, levels, generateMipMap);
}

void Texture3D::LoadFromMemory(GLfloat* Pixels, size_t Width, size_t Height, size_t Depth,
	GLint internalFormat, GLint clientsideFormat, GLsizei levels, bool generateMipMap)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, Depth, 
		internalFormat, clientsideFormat, GL_FLOAT, levels, generateMipMap);
}

void Texture3D::LoadFromMemory(GLdouble* Pixels, size_t Width, size_t Height, size_t Depth,
	GLint internalFormat, GLint clientsideFormat, GLsizei levels, bool generateMipMap)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, Depth, 
		internalFormat, clientsideFormat, GL_DOUBLE, levels, generateMipMap);
}

void Texture3D::LoadFromMemory(void* Pixels, size_t Width, size_t Height, size_t Depth,
	GLint internalFormat, GLint clientsideFormat, GLenum type, GLsizei levels, bool generateMipMap)
{
	glBindTexture(GL_TEXTURE_3D, this->AssetID);

	this->xWidth = Width;
	this->yHeight = Height;
	this->dDepth = Depth;

	glTexStorage3D(GL_TEXTURE_3D, levels, internalFormat, xWidth, yHeight, dDepth);
	glTexSubImage3D(GL_TEXTURE_3D, 0, 0, 0, 0, xWidth, yHeight, dDepth, clientsideFormat, type, Pixels);

	glActiveTexture(GL_TEXTURE0 + this->layoutSlot);
	glBindTexture(GL_TEXTURE_2D, this->AssetID);

	glBindSampler(layoutSlot, defaultSampler);

	if (generateMipMap)
	{
		glGenerateTextureMipmap(this->AssetID);
	}

	Param(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	Param(GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	Param(GL_TEXTURE_WRAP_S, GL_REPEAT);
	Param(GL_TEXTURE_WRAP_T, GL_REPEAT);
	Param(GL_TEXTURE_WRAP_R, GL_REPEAT);

	CheckStatus(__FUNCTION__);

	Log(debugMsg, "3D texture %u at layout slot %u is now ready.", this->AssetID, this->layoutSlot);
}