//
//  Texture1DArray.cpp
//  ModelView
//
//  Created by Bowen Yang on Sept 7, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include <Texture1DArray.h>

void Texture1DArray::LoadFromMemory(GLubyte* Pixels, GLsizei Index,
	GLint clientsideFormat, GLsizei levels, bool generateMipMap)
{
	this->LoadFromMemory(Pixels, Index, clientsideFormat, GL_UNSIGNED_BYTE, levels, generateMipMap);
}

void Texture1DArray::LoadFromMemory(GLbyte* Pixels, GLsizei Index,
	GLint clientsideFormat, GLsizei levels, bool generateMipMap)
{
	this->LoadFromMemory(Pixels, Index, clientsideFormat, GL_UNSIGNED_BYTE, levels, generateMipMap);
}

void Texture1DArray::LoadFromMemory(GLushort* Pixels, GLsizei Index,
	GLint clientsideFormat, GLsizei levels, bool generateMipMap)
{
	this->LoadFromMemory(Pixels, Index, clientsideFormat, GL_UNSIGNED_BYTE, levels, generateMipMap);
}

void Texture1DArray::LoadFromMemory(GLshort* Pixels, GLsizei Index,
	GLint clientsideFormat, GLsizei levels, bool generateMipMap)
{
	this->LoadFromMemory(Pixels, Index, clientsideFormat, GL_UNSIGNED_BYTE, levels, generateMipMap);
}

void Texture1DArray::LoadFromMemory(GLuint* Pixels, GLsizei Index,
	GLint clientsideFormat, GLsizei levels, bool generateMipMap)
{
	this->LoadFromMemory(Pixels, Index, clientsideFormat, GL_UNSIGNED_BYTE, levels, generateMipMap);
}

void Texture1DArray::LoadFromMemory(GLint* Pixels, GLsizei Index,
	GLint clientsideFormat, GLsizei levels, bool generateMipMap)
{
	this->LoadFromMemory(Pixels, Index, clientsideFormat, GL_UNSIGNED_BYTE, levels, generateMipMap);
}

void Texture1DArray::LoadFromMemory(GLfloat* Pixels, GLsizei Index,
	GLint clientsideFormat, GLsizei levels, bool generateMipMap)
{
	this->LoadFromMemory(Pixels, Index, clientsideFormat, GL_UNSIGNED_BYTE, levels, generateMipMap);
}

void Texture1DArray::LoadFromMemory(GLdouble* Pixels, GLsizei Index,
	GLint clientsideFormat, GLsizei levels, bool generateMipMap)
{
	this->LoadFromMemory(Pixels, Index, clientsideFormat, GL_UNSIGNED_BYTE, levels, generateMipMap);
}

void Texture1DArray::LoadFromMemory(void* Pixels, GLsizei Index,
	GLint clientsideFormat, GLenum type, GLsizei levels, bool generateMipmap)
{
	if (Index >= this->sSlices)
	{
		Error(debugMsg, "Index %u is out of range: Array %u has only %u slices.", Index, this->AssetID, this->sSlices);
	}

	if (this->isReady)
	{
		glBindTexture(GL_TEXTURE_1D_ARRAY, this->AssetID);
		glTexSubImage2D(GL_TEXTURE_1D_ARRAY, 0, 0, Index, this->xWidth, 1, clientsideFormat, type, Pixels);
	}

	glBindTexture(GL_TEXTURE_1D_ARRAY, this->AssetID);

	glTexStorage2D(GL_TEXTURE_1D_ARRAY, levels, this->internalFormat, this->xWidth, this->sSlices);
	glTexSubImage2D(GL_TEXTURE_1D_ARRAY, 0, 0, Index, this->xWidth, 1, clientsideFormat, type, Pixels);

	glActiveTexture(GL_TEXTURE0 + layoutSlot);

	CheckStatus(__FUNCTION__);

	glBindTexture(GL_TEXTURE_1D_ARRAY, this->AssetID);
	glBindSampler(layoutSlot, defaultSampler);

	Param(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	Param(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	Param(GL_TEXTURE_WRAP_S, GL_REPEAT);

	CheckStatus(__FUNCTION__);

	Log(debugMsg, "1D texture array %u with %u slices at layout slot %u is now ready."
		, this->AssetID, this->sSlices, this->layoutSlot);

	this->isReady = true;
}