//
//  TexturePack.cpp
//  ModelView
//
//  Created by Bowen Yang on Sept 7, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include <TexturePack.h>

std::unordered_set<GLenum> TexturePack::OccupiedLayouts = std::unordered_set<GLenum>();

TexturePack::TexturePack(GLenum Slot, GLint internalFormat, GLsizei levels, bool generateMipmaps) :
	layoutSlot(Slot), xWidth(0), yHeight(0), dDepth(0), internalFormat(internalFormat), levels(levels), generateMipmaps(generateMipmaps)
{
	if (Slot > GL_TEXTURE0)
		Slot -= GL_TEXTURE0;

	if (OccupiedLayouts.find(Slot) != OccupiedLayouts.end())
	{
		Error(debugMsg, "Texture slot %u is already occupied!", Slot);
	}

	OccupiedLayouts.emplace(Slot);
	this->layoutSlot = Slot;

	glGenTextures(1, &this->AssetID);

	if (AssetID != 0)
	{
		Log(debugMsg, "Texture %u at slot %u was successfully registered.", this->AssetID, this->layoutSlot);
	}
	else
	{
		Error(debugMsg, "Failed to create a program.");
	}
}

TexturePack::~TexturePack()
{
	glInvalidateTexImage(this->AssetID, 0);

	glDeleteTextures(1, &this->AssetID);
	CheckStatus(__FUNCTION__);

	Log(debugMsg, "Texture %u at slot %u was successfully unregistered.", this->AssetID, this->layoutSlot);
	OccupiedLayouts.erase(this->layoutSlot);
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