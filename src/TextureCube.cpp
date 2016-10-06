//
//  TextureCube.cpp
//  ModelView
//
//  Created by Bowen Yang on Sept 18, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include <TextureCube.h>

void TextureCube::LoadPositiveX(std::string Path, GLenum clientsideFormat)
{
	BMPLoader l = LoadBMP(Path);

	this->LoadFromMemory(reinterpret_cast<void*>(l.Pixels), l.xWidth, l.yHeight,
		GL_TEXTURE_CUBE_MAP_POSITIVE_X, clientsideFormat, GL_UNSIGNED_BYTE);

	delete[] l.Pixels;
}

void TextureCube::LoadNegativeX(std::string Path, GLenum clientsideFormat)
{
	BMPLoader l = LoadBMP(Path);

	this->LoadFromMemory(reinterpret_cast<void*>(l.Pixels), l.xWidth, l.yHeight,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_X, clientsideFormat, GL_UNSIGNED_BYTE);

	delete[] l.Pixels;
}

void TextureCube::LoadPositiveY(std::string Path, GLenum clientsideFormat)
{
	BMPLoader l = LoadBMP(Path);

	this->LoadFromMemory(reinterpret_cast<void*>(l.Pixels), l.xWidth, l.yHeight,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Y, clientsideFormat, GL_UNSIGNED_BYTE);

	delete[] l.Pixels;
}

void TextureCube::LoadNegativeY(std::string Path, GLenum clientsideFormat)
{
	BMPLoader l = LoadBMP(Path);

	this->LoadFromMemory(reinterpret_cast<void*>(l.Pixels), l.xWidth, l.yHeight,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, clientsideFormat, GL_UNSIGNED_BYTE);

	delete[] l.Pixels;
}

void TextureCube::LoadPositiveZ(std::string Path, GLenum clientsideFormat)
{
	BMPLoader l = LoadBMP(Path);

	this->LoadFromMemory(reinterpret_cast<void*>(l.Pixels), l.xWidth, l.yHeight,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Z, clientsideFormat, GL_UNSIGNED_BYTE);

	delete[] l.Pixels;
}

void TextureCube::LoadNegativeZ(std::string Path, GLenum clientsideFormat)
{
	BMPLoader l = LoadBMP(Path);

	this->LoadFromMemory(reinterpret_cast<void*>(l.Pixels), l.xWidth, l.yHeight,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, clientsideFormat, GL_UNSIGNED_BYTE);

	delete[] l.Pixels;
}

void TextureCube::LoadFromMemory(GLubyte* Pixels, GLsizei Width, GLsizei Height, GLenum Target,
	GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, Target,
		clientsideFormat, GL_UNSIGNED_BYTE);
}

void TextureCube::LoadFromMemory(GLbyte* Pixels, GLsizei Width, GLsizei Height, GLenum Target,
	GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, Target,
		clientsideFormat, GL_BYTE);
}

void TextureCube::LoadFromMemory(GLushort* Pixels, GLsizei Width, GLsizei Height, GLenum Target,
	GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, Target,
		clientsideFormat, GL_UNSIGNED_SHORT);
}

void TextureCube::LoadFromMemory(GLshort* Pixels, GLsizei Width, GLsizei Height, GLenum Target,
	GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, Target,
		clientsideFormat, GL_SHORT);
}

void TextureCube::LoadFromMemory(GLuint* Pixels, GLsizei Width, GLsizei Height, GLenum Target,
	GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, Target,
		clientsideFormat, GL_UNSIGNED_INT);
}

void TextureCube::LoadFromMemory(GLint* Pixels, GLsizei Width, GLsizei Height, GLenum Target,
	GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, Target,
		clientsideFormat, GL_INT);
}

void TextureCube::LoadFromMemory(GLfloat* Pixels, GLsizei Width, GLsizei Height, GLenum Target,
	GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, Target,
		clientsideFormat, GL_FLOAT);
}

void TextureCube::LoadFromMemory(GLdouble* Pixels, GLsizei Width, GLsizei Height, GLenum Target,
	GLenum clientsideFormat)
{
	this->LoadFromMemory(reinterpret_cast<void*>(Pixels), Width, Height, Target,
		clientsideFormat, GL_DOUBLE);
}

void TextureCube::LoadFromMemory(void* Pixels, GLsizei Width, GLsizei Height, GLenum Target,
	GLenum clientsideFormat, GLenum type)
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->AssetID);

	if (this->xWidth == 0 && this->yHeight == 0)
	{
		this->xWidth = Width;
		this->yHeight = Height;
		glTexStorage2D(GL_TEXTURE_CUBE_MAP, levels, internalFormat, xWidth, yHeight);
	}

	glTexSubImage2D(Target, 0, 0, 0, this->xWidth, this->yHeight, clientsideFormat, type, Pixels);

	glActiveTexture(GL_TEXTURE0 + this->layoutSlot);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->AssetID);

	glBindSampler(layoutSlot, defaultSampler);

	if (generateMipmaps)
	{
		glGenerateTextureMipmap(this->AssetID);
	}

	Param(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	Param(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	Param(GL_TEXTURE_WRAP_S, GL_REPEAT);
	Param(GL_TEXTURE_WRAP_T, GL_REPEAT);

	CheckStatus(__FUNCTION__);

	char* str = nullptr;
	switch (Target)
	{
	case GL_TEXTURE_CUBE_MAP_POSITIVE_X:
		str = "Positive X";
		break;
	case GL_TEXTURE_CUBE_MAP_POSITIVE_Y:
		str = "Positive Y";
		break;
	case GL_TEXTURE_CUBE_MAP_POSITIVE_Z:
		str = "Positive Z";
		break;
	case GL_TEXTURE_CUBE_MAP_NEGATIVE_X:
		str = "Negative X";
		break;
	case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y:
		str = "Negative Y";
		break;
	case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z:
		str = "Negative Z";
		break;
	}

	Log(debugMsg, "Cube texture %u's face %s at layout slot %u is now ready.", this->AssetID, str, this->layoutSlot);
	this->isReady = true;
}