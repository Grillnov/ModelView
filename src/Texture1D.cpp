//
//  Texture1D.cpp
//  ModelView
//
//  Created by Bowen Yang on Sept 18, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include <Texture1D.h>

void Texture1D::LoadFromMemory(GLubyte* Pixels, GLsizei Width, GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, clientsideFormat, GL_UNSIGNED_BYTE);
}

void Texture1D::LoadFromMemory(GLbyte* Pixels, GLsizei Width, GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, clientsideFormat, GL_BYTE);
}

void Texture1D::LoadFromMemory(GLushort* Pixels, GLsizei Width, GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, clientsideFormat, GL_UNSIGNED_SHORT);
}

void Texture1D::LoadFromMemory(GLshort* Pixels, GLsizei Width, GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, clientsideFormat, GL_SHORT);
}

void Texture1D::LoadFromMemory(GLuint* Pixels, GLsizei Width, GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, clientsideFormat, GL_UNSIGNED_INT);
}

void Texture1D::LoadFromMemory(GLint* Pixels, GLsizei Width, GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, clientsideFormat, GL_INT);
}

void Texture1D::LoadFromMemory(GLfloat* Pixels, GLsizei Width, GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, clientsideFormat, GL_FLOAT);
}

void Texture1D::LoadFromMemory(GLdouble* Pixels, GLsizei Width, GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, clientsideFormat, GL_DOUBLE);
}

void Texture1D::Alloc(GLsizei Width)
{
	if (this->xWidth != 0)
	{
		Error(debugMsg, "1D texture %u: Cannot vary texture's dimensions within one texturepack. "
			"You may want to invoke TexImage2D for yourself if you have to."
			, this->AssetID);
		return;
	}

	glBindTexture(GL_TEXTURE_1D, this->AssetID);
	this->xWidth = Width;
	glTexStorage1D(GL_TEXTURE_1D, levels, internalFormat, xWidth);
}

void Texture1D::LoadFromMemory(void* Pixels, GLsizei Width, GLenum clientsideFormat, GLenum type)
{
	if (this->xWidth != Width)
	{
		this->Alloc(Width);
	}
	glBindTexture(GL_TEXTURE_1D, this->AssetID);

	glTexSubImage1D(GL_TEXTURE_1D, 0, 0, xWidth, clientsideFormat, type, Pixels);

	if (generateMipmaps)
	{
		glGenerateTextureMipmap(this->AssetID);
	}
	
	Activate();

	Param(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	Param(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	Param(GL_TEXTURE_WRAP_S, GL_REPEAT);

	CheckStatus(__FUNCTION__);

	Log(debugMsg, "1D texture %u at layout slot %u is now ready.", this->AssetID, this->layoutSlot);
	this->isReady = true;
}

void Texture1D::Activate()
{
	glBindSampler(layoutSlot, defaultSampler);
	glActiveTexture(GL_TEXTURE0 + layoutSlot);
	glBindTexture(GL_TEXTURE_1D, this->AssetID);
	CheckStatus(__FUNCTION__);
}