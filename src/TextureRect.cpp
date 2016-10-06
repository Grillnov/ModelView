//
//  TextureRect.cpp
//  ModelView
//
//  Created by Bowen Yang on Sept 18, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include <TextureRect.h>

void TextureRect::LoadFromBMP(std::string Path, GLenum clientsideFormat)
{
	BMPLoader l = LoadBMP(Path);

	this->LoadFromMemory(reinterpret_cast<GLubyte*>(l.Pixels), l.xWidth, l.yHeight, clientsideFormat);

	delete[] l.Pixels;
}

void TextureRect::LoadFromMemory(GLubyte* Pixels, GLsizei Width, GLsizei Height, GLint clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, clientsideFormat, GL_UNSIGNED_BYTE);
}

void TextureRect::LoadFromMemory(GLbyte* Pixels, GLsizei Width, GLsizei Height, GLint clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, clientsideFormat, GL_BYTE);
}

void TextureRect::LoadFromMemory(GLushort* Pixels, GLsizei Width, GLsizei Height, GLint clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, clientsideFormat, GL_UNSIGNED_SHORT);
}

void TextureRect::LoadFromMemory(GLshort* Pixels, GLsizei Width, GLsizei Height, GLint clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, clientsideFormat, GL_SHORT);
}

void TextureRect::LoadFromMemory(GLuint* Pixels, GLsizei Width, GLsizei Height, GLint clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, clientsideFormat, GL_UNSIGNED_INT);
}

void TextureRect::LoadFromMemory(GLint* Pixels, GLsizei Width, GLsizei Height, GLint clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, clientsideFormat, GL_INT);
}

void TextureRect::LoadFromMemory(GLfloat* Pixels, GLsizei Width, GLsizei Height, GLint clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, clientsideFormat, GL_FLOAT);
}

void TextureRect::LoadFromMemory(GLdouble* Pixels, GLsizei Width, GLsizei Height, GLint clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, clientsideFormat, GL_DOUBLE);
}

void TextureRect::LoadFromMemory(void* Pixels, GLsizei Width, GLsizei Height, GLenum clientsideFormat, GLenum type)
{
	glBindTexture(GL_TEXTURE_RECTANGLE, this->AssetID);

	if (this->xWidth != Width || this->yHeight != Height)
	{
		if (this->xWidth != 0 || this->yHeight != 0)
		{
			glInvalidateTexImage(this->AssetID, 0);
		}
		this->xWidth = Width;
		this->yHeight = Height;
		glTexStorage2D(GL_TEXTURE_RECTANGLE, levels, internalFormat, xWidth, yHeight);
	}
	glTexSubImage2D(GL_TEXTURE_RECTANGLE, 0, 0, 0, xWidth, yHeight, clientsideFormat, type, Pixels);

	glActiveTexture(GL_TEXTURE0 + this->layoutSlot);
	glBindTexture(GL_TEXTURE_RECTANGLE, this->AssetID);

	glBindSampler(layoutSlot, defaultSampler);

	Param(GL_TEXTURE_WRAP_S, GL_REPEAT);
	Param(GL_TEXTURE_WRAP_T, GL_REPEAT);

	CheckStatus(__FUNCTION__);

	Log(debugMsg, "Rectangular texture %u at layout slot %u is now ready.", this->AssetID, this->layoutSlot);
}