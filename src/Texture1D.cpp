//
//  Texture1D.cpp
//  ModelView
//
//  Created by Bowen Yang on Sept 18, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include <TexturePack.h>

void Texture1D::LoadFromMemory(GLubyte* Pixels, size_t Width, GLint internalFormat,
	GLint clientsideFormat)
{
	glBindTexture(GL_TEXTURE_1D, this->AssetID);

	this->xWidth = Width;

	glTexStorage1D(GL_TEXTURE_1D, 1, internalFormat, xWidth);
	glTexSubImage1D(GL_TEXTURE_1D, 0, 0, xWidth, clientsideFormat, GL_UNSIGNED_BYTE, Pixels);

	glActiveTexture(GL_TEXTURE0 + layoutSlot);

	CheckStatus(__FUNCTION__);

	glBindTexture(GL_TEXTURE_1D, this->AssetID);
	glBindSampler(layoutSlot, defaultSampler);

	Param(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	Param(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	Param(GL_TEXTURE_WRAP_S, GL_REPEAT);

	CheckStatus(__FUNCTION__);

	Log(debugMsg, "1D texture %u was successfully attached at layout slot %u.", this->AssetID, this->layoutSlot);
}

void Texture1D::LoadFromMemory(GLbyte* Pixels, size_t Width, GLint internalFormat,
	GLint clientsideFormat)
{
	glBindTexture(GL_TEXTURE_1D, this->AssetID);

	this->xWidth = Width;

	glTexStorage1D(GL_TEXTURE_1D, 1, internalFormat, xWidth);
	glTexSubImage1D(GL_TEXTURE_1D, 0, 0, xWidth, clientsideFormat, GL_BYTE, Pixels);

	glActiveTexture(GL_TEXTURE0 + layoutSlot);

	CheckStatus(__FUNCTION__);

	glBindTexture(GL_TEXTURE_1D, this->AssetID);
	glBindSampler(layoutSlot, defaultSampler);

	Param(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	Param(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	Param(GL_TEXTURE_WRAP_S, GL_REPEAT);

	CheckStatus(__FUNCTION__);

	Log(debugMsg, "1D texture %u was successfully attached at layout slot %u.", this->AssetID, this->layoutSlot);
}

void Texture1D::LoadFromMemory(GLushort* Pixels, size_t Width, GLint internalFormat,
	GLint clientsideFormat)
{
	glBindTexture(GL_TEXTURE_1D, this->AssetID);

	this->xWidth = Width;

	glTexStorage1D(GL_TEXTURE_1D, 1, internalFormat, xWidth);
	glTexSubImage1D(GL_TEXTURE_1D, 0, 0, xWidth, clientsideFormat, GL_UNSIGNED_SHORT, Pixels);

	glActiveTexture(GL_TEXTURE0 + layoutSlot);

	CheckStatus(__FUNCTION__);

	glBindTexture(GL_TEXTURE_1D, this->AssetID);
	glBindSampler(layoutSlot, defaultSampler);

	Param(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	Param(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	Param(GL_TEXTURE_WRAP_S, GL_REPEAT);

	CheckStatus(__FUNCTION__);

	Log(debugMsg, "1D texture %u was successfully attached at layout slot %u.", this->AssetID, this->layoutSlot);
}

void Texture1D::LoadFromMemory(GLshort* Pixels, size_t Width, GLint internalFormat,
	GLint clientsideFormat)
{
	glBindTexture(GL_TEXTURE_1D, this->AssetID);

	this->xWidth = Width;

	glTexStorage1D(GL_TEXTURE_1D, 1, internalFormat, xWidth);
	glTexSubImage1D(GL_TEXTURE_1D, 0, 0, xWidth, clientsideFormat, GL_SHORT, Pixels);

	glActiveTexture(GL_TEXTURE0 + layoutSlot);

	CheckStatus(__FUNCTION__);

	glBindTexture(GL_TEXTURE_1D, this->AssetID);
	glBindSampler(layoutSlot, defaultSampler);

	Param(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	Param(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	Param(GL_TEXTURE_WRAP_S, GL_REPEAT);

	CheckStatus(__FUNCTION__);

	Log(debugMsg, "1D texture %u was successfully attached at layout slot %u.", this->AssetID, this->layoutSlot);
}

void Texture1D::LoadFromMemory(GLuint* Pixels, size_t Width, GLint internalFormat,
	GLint clientsideFormat)
{
	glBindTexture(GL_TEXTURE_1D, this->AssetID);

	this->xWidth = Width;

	glTexStorage1D(GL_TEXTURE_1D, 1, internalFormat, xWidth);
	glTexSubImage1D(GL_TEXTURE_1D, 0, 0, xWidth, clientsideFormat, GL_UNSIGNED_INT, Pixels);

	glActiveTexture(GL_TEXTURE0 + layoutSlot);

	CheckStatus(__FUNCTION__);

	glBindTexture(GL_TEXTURE_1D, this->AssetID);
	glBindSampler(layoutSlot, defaultSampler);

	Param(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	Param(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	Param(GL_TEXTURE_WRAP_S, GL_REPEAT);

	CheckStatus(__FUNCTION__);

	Log(debugMsg, "1D texture %u was successfully attached at layout slot %u.", this->AssetID, this->layoutSlot);
}

void Texture1D::LoadFromMemory(GLint* Pixels, size_t Width, GLint internalFormat,
	GLint clientsideFormat)
{
	glBindTexture(GL_TEXTURE_1D, this->AssetID);

	this->xWidth = Width;

	glTexStorage1D(GL_TEXTURE_1D, 1, internalFormat, xWidth);
	glTexSubImage1D(GL_TEXTURE_1D, 0, 0, xWidth, clientsideFormat, GL_INT, Pixels);

	glActiveTexture(GL_TEXTURE0 + layoutSlot);

	CheckStatus(__FUNCTION__);

	glBindTexture(GL_TEXTURE_1D, this->AssetID);
	glBindSampler(layoutSlot, defaultSampler);

	Param(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	Param(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	Param(GL_TEXTURE_WRAP_S, GL_REPEAT);

	CheckStatus(__FUNCTION__);

	Log(debugMsg, "1D texture %u was successfully attached at layout slot %u.", this->AssetID, this->layoutSlot);
}

void Texture1D::LoadFromMemory(GLfloat* Pixels, size_t Width, GLint internalFormat,
	GLint clientsideFormat)
{
	glBindTexture(GL_TEXTURE_1D, this->AssetID);

	this->xWidth = Width;

	glTexStorage1D(GL_TEXTURE_1D, 1, internalFormat, xWidth);
	glTexSubImage1D(GL_TEXTURE_1D, 0, 0, xWidth, clientsideFormat, GL_FLOAT, Pixels);

	glActiveTexture(GL_TEXTURE0 + layoutSlot);

	CheckStatus(__FUNCTION__);

	glBindTexture(GL_TEXTURE_1D, this->AssetID);
	glBindSampler(layoutSlot, defaultSampler);

	Param(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	Param(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	Param(GL_TEXTURE_WRAP_S, GL_REPEAT);

	CheckStatus(__FUNCTION__);

	Log(debugMsg, "1D texture %u was successfully attached at layout slot %u.", this->AssetID, this->layoutSlot);
}

void Texture1D::LoadFromMemory(GLdouble* Pixels, size_t Width, GLint internalFormat,
	GLint clientsideFormat)
{
	glBindTexture(GL_TEXTURE_1D, this->AssetID);

	this->xWidth = Width;

	glTexStorage1D(GL_TEXTURE_1D, 1, internalFormat, xWidth);
	glTexSubImage1D(GL_TEXTURE_1D, 0, 0, xWidth, clientsideFormat, GL_DOUBLE, Pixels);

	glActiveTexture(GL_TEXTURE0 + layoutSlot);

	CheckStatus(__FUNCTION__);

	glBindTexture(GL_TEXTURE_1D, this->AssetID);
	glBindSampler(layoutSlot, defaultSampler);

	Param(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	Param(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	Param(GL_TEXTURE_WRAP_S, GL_REPEAT);

	CheckStatus(__FUNCTION__);

	Log(debugMsg, "1D texture %u was successfully attached at layout slot %u.", this->AssetID, this->layoutSlot);
}

void Texture1D::LoadFromMemory(void* Pixels, size_t Width, GLint internalFormat,
	GLint clientsideFormat, GLenum type)
{
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

	Log(debugMsg, "1D texture %u was successfully attached at layout slot %u.", this->AssetID, this->layoutSlot);
}