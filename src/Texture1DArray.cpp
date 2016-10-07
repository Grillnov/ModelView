//
//  Texture1DArray.cpp
//  ModelView
//
//  Created by Bowen Yang on Sept 7, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include <Texture1DArray.h>

void Texture1DArray::LoadFromMemory(GLubyte* Pixels, GLsizei Index, GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Index, clientsideFormat, GL_UNSIGNED_BYTE);
}

void Texture1DArray::LoadFromMemory(GLbyte* Pixels, GLsizei Index, GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Index, clientsideFormat, GL_UNSIGNED_BYTE);
}

void Texture1DArray::LoadFromMemory(GLushort* Pixels, GLsizei Index, GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Index, clientsideFormat, GL_UNSIGNED_BYTE);
}

void Texture1DArray::LoadFromMemory(GLshort* Pixels, GLsizei Index, GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Index, clientsideFormat, GL_UNSIGNED_BYTE);
}

void Texture1DArray::LoadFromMemory(GLuint* Pixels, GLsizei Index, GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Index, clientsideFormat, GL_UNSIGNED_BYTE);
}

void Texture1DArray::LoadFromMemory(GLint* Pixels, GLsizei Index, GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Index, clientsideFormat, GL_UNSIGNED_BYTE);
}

void Texture1DArray::LoadFromMemory(GLfloat* Pixels, GLsizei Index, GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Index, clientsideFormat, GL_UNSIGNED_BYTE);
}

void Texture1DArray::LoadFromMemory(GLdouble* Pixels, GLsizei Index, GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Index, clientsideFormat, GL_UNSIGNED_BYTE);
}

void Texture1DArray::LoadFromMemory(void* Pixels, GLsizei Index, GLenum clientsideFormat, GLenum type)
{
	if (Index >= this->yHeight)
	{
		Error(debugMsg, "Index %u is out of range: Array %u has only %u slices.", Index, this->AssetID, this->yHeight);
	}

	glBindTexture(GL_TEXTURE_1D_ARRAY, this->AssetID);

	if (!this->isReady)
	{
		glTexStorage2D(GL_TEXTURE_1D_ARRAY, this->levels, this->internalFormat, this->xWidth, this->yHeight);
	}
	glTexSubImage2D(GL_TEXTURE_1D_ARRAY, 0, 0, Index, this->xWidth, 1, clientsideFormat, type, Pixels);

	if (this->generateMipmaps)
	{
		glGenerateTextureMipmap(this->AssetID);
	}

	Activate();

	Param(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	Param(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	Param(GL_TEXTURE_WRAP_S, GL_REPEAT);

	CheckStatus(__FUNCTION__);

	Log(debugMsg, "1D texture array %u with %u slices at layout slot %u is now ready."
		, this->AssetID, this->yHeight, this->layoutSlot);

	this->isReady = true;
}

void Texture1DArray::LoadFromMemory(void* Pixels, GLenum clientsideFormat, GLenum type)
{
	glBindTexture(GL_TEXTURE_1D_ARRAY, this->AssetID);

	if (this->isReady)
	{
		glTexSubImage2D(GL_TEXTURE_1D_ARRAY, 0, 0, 0, this->xWidth, this->yHeight, clientsideFormat, type, Pixels);
	}
	else
	{
		glTexStorage2D(GL_TEXTURE_1D_ARRAY, this->levels, this->internalFormat, this->xWidth, this->yHeight);
		glTexSubImage2D(GL_TEXTURE_1D_ARRAY, 0, 0, 0, this->xWidth, this->yHeight, clientsideFormat, type, Pixels);
	}

	if (this->generateMipmaps)
	{
		glGenerateTextureMipmap(this->AssetID);
	}

	Activate();

	glBindSampler(layoutSlot, defaultSampler);

	Param(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	Param(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	Param(GL_TEXTURE_WRAP_S, GL_REPEAT);

	CheckStatus(__FUNCTION__);

	Log(debugMsg, "1D texture array %u with %u slices at layout slot %u is now ready."
		, this->AssetID, this->yHeight, this->layoutSlot);

	this->isReady = true;
}

void Texture1DArray::Activate()
{
	glBindSampler(layoutSlot, defaultSampler);
	glActiveTexture(GL_TEXTURE0 + layoutSlot);
	glBindTexture(GL_TEXTURE_1D_ARRAY, this->AssetID);
	CheckStatus(__FUNCTION__);
}