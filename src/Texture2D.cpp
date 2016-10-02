//
//  Texture2D.cpp
//  ModelView
//
//  Created by Bowen Yang on Sept 18, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include <Texture2D.h>

void Texture2D::LoadFromBMP(std::string Path, GLint internalFormat,
	GLint clientsideFormat, GLsizei levels, bool generateMipMap)
{
	BMPLoader l = LoadBMP(Path);
	unsigned char* texels = l.Pixels;
	this->xWidth = l.xWidth;
	this->yHeight = l.yHeight;

	LoadFromMemory(texels, xWidth, yHeight, internalFormat, clientsideFormat, levels, generateMipMap);

	delete[] texels;
}

void Texture2D::LoadFromMemory(GLubyte* Pixels, GLsizei Width, GLsizei Height,
	GLint internalFormat, GLint clientsideFormat, GLsizei levels, bool generateMipMap)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, internalFormat, clientsideFormat, GL_UNSIGNED_BYTE, levels, generateMipMap);
}

void Texture2D::LoadFromMemory(GLbyte* Pixels, GLsizei Width, GLsizei Height,
	GLint internalFormat, GLint clientsideFormat, GLsizei levels, bool generateMipMap)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, internalFormat, clientsideFormat, GL_BYTE, levels, generateMipMap);
}

void Texture2D::LoadFromMemory(GLushort* Pixels, GLsizei Width, GLsizei Height,
	GLint internalFormat, GLint clientsideFormat, GLsizei levels, bool generateMipMap)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, internalFormat, clientsideFormat, GL_UNSIGNED_SHORT, levels, generateMipMap);
}

void Texture2D::LoadFromMemory(GLshort* Pixels, GLsizei Width, GLsizei Height,
	GLint internalFormat, GLint clientsideFormat, GLsizei levels, bool generateMipMap)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, internalFormat, clientsideFormat, GL_SHORT, levels, generateMipMap);
}

void Texture2D::LoadFromMemory(GLuint* Pixels, GLsizei Width, GLsizei Height,
	GLint internalFormat, GLint clientsideFormat, GLsizei levels, bool generateMipMap)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, internalFormat, clientsideFormat, GL_UNSIGNED_INT, levels, generateMipMap);
}

void Texture2D::LoadFromMemory(GLint* Pixels, GLsizei Width, GLsizei Height,
	GLint internalFormat, GLint clientsideFormat, GLsizei levels, bool generateMipMap)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, internalFormat, clientsideFormat, GL_INT, levels, generateMipMap);
}

void Texture2D::LoadFromMemory(GLfloat* Pixels, GLsizei Width, GLsizei Height,
	GLint internalFormat, GLint clientsideFormat, GLsizei levels, bool generateMipMap)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, internalFormat, clientsideFormat, GL_FLOAT, levels, generateMipMap);
}

void Texture2D::LoadFromMemory(GLdouble* Pixels, GLsizei Width, GLsizei Height,
	GLint internalFormat, GLint clientsideFormat, GLsizei levels, bool generateMipMap)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, internalFormat, clientsideFormat, GL_DOUBLE, levels, generateMipMap);
}

void Texture2D::LoadFromMemory(void* Pixels, GLsizei Width, GLsizei Height,
	GLint internalFormat, GLint clientsideFormat, GLenum type, GLsizei levels, bool generateMipMap)
{
	if (this->isReady)
	{
		glInvalidateTexImage(this->AssetID, 0);
	}
	glBindTexture(GL_TEXTURE_2D, this->AssetID);

	this->xWidth = Width;
	this->yHeight = Height;

	glTexStorage2D(GL_TEXTURE_2D, levels, internalFormat, xWidth, yHeight);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, xWidth, yHeight, clientsideFormat, type, Pixels);

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

	CheckStatus(__FUNCTION__);

	Log(debugMsg, "2D texture %u at layout slot %u is now ready.", this->AssetID, this->layoutSlot);
	this->isReady = true;
}