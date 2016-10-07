//
//  Texture2DArray.cpp
//  ModelView
//
//  Created by Bowen Yang on Sept 7, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include <Texture2DArray.h>

void Texture2DArray::LoadFromBMP(GLsizei Index, GLenum clientsideFormat)
{
	if (Index >= this->dDepth)
	{
		Error(debugMsg, "Index %u is out of range: Array %u has only %u slices.", Index, this->AssetID, this->dDepth);
	}

	BMPLoader l = LoadBMP(AllPaths.at(Index));

	if (l.xWidth != this->xWidth || l.yHeight != this->yHeight)
	{
		Error(debugMsg, "BMP size must be identical among all the textures in the array.");
	}

	LoadFromMemory(reinterpret_cast<GLubyte*>(l.Pixels), Index, clientsideFormat, levels);

	delete[] l.Pixels;
}

void Texture2DArray::LoadFromMemory(GLubyte* Pixels, GLsizei Index, GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Index, clientsideFormat, GL_UNSIGNED_BYTE);
}

void Texture2DArray::LoadFromMemory(GLbyte* Pixels, GLsizei Index, GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Index, clientsideFormat, GL_BYTE);
}

void Texture2DArray::LoadFromMemory(GLushort* Pixels, GLsizei Index, GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Index, clientsideFormat, GL_UNSIGNED_SHORT);
}

void Texture2DArray::LoadFromMemory(GLshort* Pixels, GLsizei Index, GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Index, clientsideFormat, GL_SHORT);
}

void Texture2DArray::LoadFromMemory(GLuint* Pixels, GLsizei Index, GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Index, clientsideFormat, GL_UNSIGNED_INT);
}

void Texture2DArray::LoadFromMemory(GLint* Pixels, GLsizei Index, GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Index, clientsideFormat, GL_INT);
}

void Texture2DArray::LoadFromMemory(GLfloat* Pixels, GLsizei Index, GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Index, clientsideFormat, GL_FLOAT);
}

void Texture2DArray::LoadFromMemory(GLdouble* Pixels, GLsizei Index, GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Index, clientsideFormat, GL_DOUBLE);
}

void Texture2DArray::LoadFromMemory(void* Pixels, GLsizei Index, GLenum clientsideFormat, GLenum type)
{
	if (Index >= this->dDepth)
	{
		Error(debugMsg, "Index %u is out of range: Array %u has only %u slices.", Index, this->AssetID, this->dDepth);
	}

	glBindTexture(GL_TEXTURE_2D_ARRAY, this->AssetID);

	if (!this->isReady)
	{
		glTexStorage3D(GL_TEXTURE_2D_ARRAY, levels, internalFormat, xWidth, yHeight, dDepth);
	}
	glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, Index,
		this->xWidth, this->yHeight, 1, clientsideFormat, type, Pixels);

	if (this->generateMipmaps)
	{
		glGenerateTextureMipmap(this->AssetID);
	}

	Activate();

	Param(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	Param(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	Param(GL_TEXTURE_WRAP_S, GL_REPEAT);
	Param(GL_TEXTURE_WRAP_T, GL_REPEAT);

	CheckStatus(__FUNCTION__);

	Log(debugMsg, "2D texture array %u with %u slices at layout slot %u is now ready.", this->AssetID, this->dDepth, this->layoutSlot);
	this->isReady = true;
}

void Texture2DArray::LoadFromMemory(void* Pixels, GLint clientsideFormat, GLenum type)
{
	glBindTexture(GL_TEXTURE_2D_ARRAY, this->AssetID);

	if (!this->isReady)
	{
		glTexStorage3D(GL_TEXTURE_2D_ARRAY, levels, internalFormat, xWidth, yHeight, dDepth);
	}
	glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0,
		this->xWidth, this->yHeight, this->dDepth, clientsideFormat, type, Pixels);

	if (this->generateMipmaps && !this->isReady)
	{
		glGenerateTextureMipmap(this->AssetID);
	}

	Activate();

	glBindSampler(layoutSlot, defaultSampler);

	Param(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	Param(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	Param(GL_TEXTURE_WRAP_S, GL_REPEAT);
	Param(GL_TEXTURE_WRAP_T, GL_REPEAT);

	CheckStatus(__FUNCTION__);

	Log(debugMsg, "2D texture array %u with %u slices at layout slot %u is now ready.", this->AssetID, this->dDepth, this->layoutSlot);
	this->isReady = true;
}

void Texture2DArray::Activate()
{
	glBindSampler(layoutSlot, defaultSampler);
	glActiveTexture(GL_TEXTURE0 + this->layoutSlot);
	glBindTexture(GL_TEXTURE_2D_ARRAY, this->AssetID);
	CheckStatus(__FUNCTION__);
}