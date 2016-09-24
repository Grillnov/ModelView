//
//  TexturePack.cpp
//  ModelView
//
//  Created by Bowen Yang on Sept 7, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include <TexturePack.h>

std::unordered_set<GLenum> TexturePack::OccupiedLayouts = std::unordered_set<GLenum>();

TexturePack::TexturePack(GLenum Slot)
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

void TexturePic::Param(GLenum target, GLfloat param)
{
	this->defaultSampler.Param(target, param);
}

void TexturePic::Param(GLenum target, GLint param)
{
	this->defaultSampler.Param(target, param);
}

void TexturePic::Param(GLenum target, GLfloat* param)
{
	this->defaultSampler.Param(target, param);
}

void TexturePic::Param(GLenum target, GLint* param)
{
	this->defaultSampler.Param(target, param);
}