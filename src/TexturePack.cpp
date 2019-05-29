//
//  TexturePack.cpp
//  ModelView
//
//  Created by Bowen Yang on Sept 7, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include <TexturePack.h>

TexturePack::TexturePack(GLenum Slot, GLint internalFormat, GLsizei levels, bool generateMipmaps) :
	layoutSlot(Slot > GL_TEXTURE0 ? Slot - GL_TEXTURE0 : Slot), xWidth(0), yHeight(0), dDepth(0),
	defaultSampler(Slot > GL_TEXTURE0 ? Slot - GL_TEXTURE0 : Slot),
	internalFormat(internalFormat), levels(levels), generateMipmaps(generateMipmaps)
{
	if (Slot > GL_TEXTURE0)
		Slot -= GL_TEXTURE0;

	this->layoutSlot = Slot;

	glGenTextures(1, &this->AssetID);

	if (AssetID != 0)
	{
		Log(debugMsg, "Texture %u at slot %u was successfully registered.", this->AssetID, this->layoutSlot);
	}
	else
	{
		Error(debugMsg, "Failed to create a texture.");
	}
}

TexturePack::~TexturePack()
{
	glInvalidateTexImage(this->AssetID, 0);

	glDeleteTextures(1, &this->AssetID);
	CheckStatus(__FUNCTION__);

	Log(debugMsg, "Texture %u at slot %u was successfully unregistered.", this->AssetID, this->layoutSlot);
}

void TexturePack::Param(GLenum pname, GLfloat param)
{
	this->defaultSampler.Param(pname, param);
}

void TexturePack::Param(GLenum pname, GLint param)
{
	this->defaultSampler.Param(pname, param);
}

void TexturePack::Param(GLenum pname, GLfloat* param)
{
	this->defaultSampler.Param(pname, param);
}

void TexturePack::Param(GLenum pname, GLint* param)
{
	this->defaultSampler.Param(pname, param);
}