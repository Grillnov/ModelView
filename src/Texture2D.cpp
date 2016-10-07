//
//  Texture2D.cpp
//  ModelView
//
//  Created by Bowen Yang on Sept 18, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include <Texture2D.h>

void Texture2D::LoadFromBMP(std::string Path, GLenum clientsideFormat)
{
	BMPLoader l = LoadBMP(Path);

	LoadFromMemory(reinterpret_cast<GLubyte*>(l.Pixels), l.xWidth, l.yHeight, clientsideFormat);

	delete[] l.Pixels;
}

void Texture2D::LoadFromMemory(GLubyte* Pixels, GLsizei Width, GLsizei Height, GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, clientsideFormat, GL_UNSIGNED_BYTE);
}

void Texture2D::LoadFromMemory(GLbyte* Pixels, GLsizei Width, GLsizei Height, GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, clientsideFormat, GL_BYTE);
}

void Texture2D::LoadFromMemory(GLushort* Pixels, GLsizei Width, GLsizei Height, GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, clientsideFormat, GL_UNSIGNED_SHORT);
}

void Texture2D::LoadFromMemory(GLshort* Pixels, GLsizei Width, GLsizei Height, GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, clientsideFormat, GL_SHORT);
}

void Texture2D::LoadFromMemory(GLuint* Pixels, GLsizei Width, GLsizei Height, GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, clientsideFormat, GL_UNSIGNED_INT);
}

void Texture2D::LoadFromMemory(GLint* Pixels, GLsizei Width, GLsizei Height, GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, clientsideFormat, GL_INT);
}

void Texture2D::LoadFromMemory(GLfloat* Pixels, GLsizei Width, GLsizei Height, GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, clientsideFormat, GL_FLOAT);
}

void Texture2D::LoadFromMemory(GLdouble* Pixels, GLsizei Width, GLsizei Height, GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, clientsideFormat, GL_DOUBLE);
}

void Texture2D::Alloc(GLsizei Width, GLsizei Height)
{
	if (this->xWidth != 0 || this->yHeight != 0)
	{
		Error(debugMsg, "2D texture %u: Cannot vary texture's dimensions within one texturepack. "
			"You may want to invoke TexImage2D for yourself if you have to."
			, this->AssetID);
		return;
	}

	glBindTexture(GL_TEXTURE_2D, this->AssetID);
	this->xWidth = Width;
	this->yHeight = Height;
	glTexStorage2D(GL_TEXTURE_2D, levels, internalFormat, xWidth, yHeight);

	CheckStatus(__FUNCTION__);
}

void Texture2D::LoadFromMemory(void* Pixels, GLsizei Width, GLsizei Height, GLenum clientsideFormat, GLenum type)
{
	if (this->xWidth != Width || this->yHeight != Height)
	{
		this->Alloc(Width, Height);
	}
	glBindTexture(GL_TEXTURE_2D, this->AssetID);

	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, xWidth, yHeight, clientsideFormat, type, Pixels);

	CheckStatus(__FUNCTION__);

	if (this->generateMipmaps)
	{
		glGenerateTextureMipmap(this->AssetID);
	}

	Activate();

	Param(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	Param(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	Param(GL_TEXTURE_WRAP_S, GL_REPEAT);
	Param(GL_TEXTURE_WRAP_T, GL_REPEAT);

	Log(debugMsg, "2D texture %u at layout slot %u is now ready.", this->AssetID, this->layoutSlot);
	this->isReady = true;
}

void Texture2D::Activate()
{
	glBindSampler(layoutSlot, defaultSampler);
	glActiveTexture(GL_TEXTURE0 + this->layoutSlot);
	glBindTexture(GL_TEXTURE_2D, this->AssetID);
	CheckStatus(__FUNCTION__);
}