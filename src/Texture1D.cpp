//
//  Texture1D.cpp
//  ModelView
//
//  Created by Bowen Yang on Sept 18, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include <Texture1D.h>

void Texture1D::LoadFromMemory(GLubyte* Pixels, GLsizei Width, GLint internalFormat,
	GLint clientsideFormat, GLsizei levels, bool generateMipmap)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, internalFormat
		, clientsideFormat, GL_UNSIGNED_BYTE, levels, generateMipmap);
}

void Texture1D::LoadFromMemory(GLbyte* Pixels, GLsizei Width, GLint internalFormat,
	GLint clientsideFormat, GLsizei levels, bool generateMipmap)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, internalFormat
		, clientsideFormat, GL_BYTE, levels, generateMipmap);
}

void Texture1D::LoadFromMemory(GLushort* Pixels, GLsizei Width, GLint internalFormat,
	GLint clientsideFormat, GLsizei levels, bool generateMipmap)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, internalFormat
		, clientsideFormat, GL_UNSIGNED_SHORT, levels, generateMipmap);
}

void Texture1D::LoadFromMemory(GLshort* Pixels, GLsizei Width, GLint internalFormat,
	GLint clientsideFormat, GLsizei levels, bool generateMipmap)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, internalFormat
		, clientsideFormat, GL_SHORT, levels, generateMipmap);
}

void Texture1D::LoadFromMemory(GLuint* Pixels, GLsizei Width, GLint internalFormat,
	GLint clientsideFormat, GLsizei levels, bool generateMipmap)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, internalFormat
		, clientsideFormat, GL_UNSIGNED_INT, levels, generateMipmap);
}

void Texture1D::LoadFromMemory(GLint* Pixels, GLsizei Width, GLint internalFormat,
	GLint clientsideFormat, GLsizei levels, bool generateMipmap)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, internalFormat
		, clientsideFormat, GL_INT, levels, generateMipmap);
}

void Texture1D::LoadFromMemory(GLfloat* Pixels, GLsizei Width, GLint internalFormat,
	GLint clientsideFormat, GLsizei levels, bool generateMipmap)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, internalFormat
		, clientsideFormat, GL_FLOAT, levels, generateMipmap);
}

void Texture1D::LoadFromMemory(GLdouble* Pixels, GLsizei Width, GLint internalFormat,
	GLint clientsideFormat, GLsizei levels, bool generateMipmap)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, internalFormat
		, clientsideFormat, GL_DOUBLE, levels, generateMipmap);
}

void Texture1D::LoadFromMemory(void* Pixels, GLsizei Width, GLint internalFormat,
	GLint clientsideFormat, GLenum type, GLsizei levels, bool generateMipmap)
{
	if (this->isReady)
	{
		glInvalidateTexImage(this->AssetID, 0);//Reload the texture.
	}

	glBindTexture(GL_TEXTURE_1D, this->AssetID);

	this->xWidth = Width;

	glTexStorage1D(GL_TEXTURE_1D, 1, internalFormat, xWidth);
	glTexSubImage1D(GL_TEXTURE_1D, 0, 0, xWidth, clientsideFormat, type, Pixels);

	glActiveTexture(GL_TEXTURE0 + layoutSlot);

	CheckStatus(__FUNCTION__);

	glBindTexture(GL_TEXTURE_1D, this->AssetID);
	glBindSampler(layoutSlot, defaultSampler);

	Param(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	Param(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	Param(GL_TEXTURE_WRAP_S, GL_REPEAT);

	CheckStatus(__FUNCTION__);

	Log(debugMsg, "1D texture %u at layout slot %u is now ready.", this->AssetID, this->layoutSlot);

	this->isReady = true;
}