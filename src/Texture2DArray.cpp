//
//  Texture2DArray.cpp
//  ModelView
//
//  Created by Bowen Yang on Sept 7, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include <Texture2DArray.h>

void Texture2DArray::LoadFromBMP(GLsizei Index, GLint clientsideFormat, GLsizei levels, bool generateMipMap)
{
	if (Index >= this->sSlices)
	{
		Error(debugMsg, "Index %u is out of range: Array %u has only %u slices.", Index, this->AssetID, this->sSlices);
	}

	BMPLoader l = LoadBMP(AllPaths.at(Index));
	unsigned char* texels = l.Pixels;
	this->xWidth = l.xWidth;
	this->yHeight = l.yHeight;

	LoadFromMemory(texels, Index, clientsideFormat, levels, generateMipMap);

	delete[] texels;
}

void Texture2DArray::LoadFromMemory(GLubyte* Pixels, GLsizei Index,
	GLint clientsideFormat, GLsizei levels, bool generateMipMap)
{
	this->LoadFromMemory(Pixels, Index, clientsideFormat, GL_UNSIGNED_BYTE, levels, generateMipMap);
}

void Texture2DArray::LoadFromMemory(GLbyte* Pixels, GLsizei Index,
	GLint clientsideFormat, GLsizei levels, bool generateMipMap)
{
	this->LoadFromMemory(Pixels, Index, clientsideFormat, GL_BYTE, levels, generateMipMap);
}

void Texture2DArray::LoadFromMemory(GLushort* Pixels, GLsizei Index,
	GLint clientsideFormat, GLsizei levels, bool generateMipMap)
{
	this->LoadFromMemory(Pixels, Index, clientsideFormat, GL_UNSIGNED_SHORT, levels, generateMipMap);
}

void Texture2DArray::LoadFromMemory(GLshort* Pixels, GLsizei Index,
	GLint clientsideFormat, GLsizei levels, bool generateMipMap)
{
	this->LoadFromMemory(Pixels, Index, clientsideFormat, GL_SHORT, levels, generateMipMap);
}

void Texture2DArray::LoadFromMemory(GLuint* Pixels, GLsizei Index,
	GLint clientsideFormat, GLsizei levels, bool generateMipMap)
{
	this->LoadFromMemory(Pixels, Index, clientsideFormat, GL_UNSIGNED_INT, levels, generateMipMap);
}

void Texture2DArray::LoadFromMemory(GLint* Pixels, GLsizei Index,
	GLint clientsideFormat, GLsizei levels, bool generateMipMap)
{
	this->LoadFromMemory(Pixels, Index, clientsideFormat, GL_INT, levels, generateMipMap);
}

void Texture2DArray::LoadFromMemory(GLfloat* Pixels, GLsizei Index,
	GLint clientsideFormat, GLsizei levels, bool generateMipMap)
{
	this->LoadFromMemory(Pixels, Index, clientsideFormat, GL_FLOAT, levels, generateMipMap);
}

void Texture2DArray::LoadFromMemory(GLdouble* Pixels, GLsizei Index,
	GLint clientsideFormat, GLsizei levels, bool generateMipMap)
{
	this->LoadFromMemory(Pixels, Index, clientsideFormat, GL_DOUBLE, levels, generateMipMap);
}

void Texture2DArray::LoadFromMemory(void* Pixels, GLsizei Index,
	GLint clientsideFormat, GLenum type, GLsizei levels, bool generateMipMap)
{
	if (Index >= this->sSlices)
	{
		Error(debugMsg, "Index %u is out of range: Array %u has only %u slices.", Index, this->AssetID, this->sSlices);
	}

	if (this->isReady)
	{
		glBindTexture(GL_TEXTURE_2D_ARRAY, this->AssetID);
		glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, Index, this->xWidth, this->yHeight, 1, clientsideFormat, type, Pixels);
	}

	glBindTexture(GL_TEXTURE_2D_ARRAY, this->AssetID);

	glTexStorage3D(GL_TEXTURE_2D_ARRAY, levels, this->internalFormat, 
		this->xWidth, this->yHeight, this->sSlices);
	glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, Index, this->xWidth, this->yHeight, 1, clientsideFormat, type, Pixels);

	glActiveTexture(GL_TEXTURE0 + this->layoutSlot);
	glBindTexture(GL_TEXTURE_2D_ARRAY, this->AssetID);

	glBindSampler(layoutSlot, defaultSampler);

	if (generateMipMap)
	{
		glGenerateTextureMipmap(this->AssetID);
	}

	Param(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	Param(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	Param(GL_TEXTURE_WRAP_S, GL_REPEAT);
	Param(GL_TEXTURE_WRAP_T, GL_REPEAT);

	CheckStatus(__FUNCTION__);

	Log(debugMsg, "2D texture array %u with %u slices at layout slot %u is now ready.", this->AssetID, this->sSlices, this->layoutSlot);
	this->isReady = true;
}