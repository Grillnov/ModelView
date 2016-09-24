//
//  TexturePack.cpp
//  ModelView
//
//  Created by Bowen Yang on Sept 7, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include <TexturePack.h>

std::unordered_set<GLenum> TexturePack::OccupiedLayouts = std::unordered_set<GLenum>();

TexturePack::operator GLuint()
{
	if (!this->isAttached)
	{
		Error(debugMsg, "Texture %u is not attached yet, illegal parameter for GL interface!", this->AssetID);
		return -1;
	}
	return this->AssetID;
}



TexturePic::TexturePic() : Buffer(nullptr), Channel(0), xWidth(0), yHeight(0), isFromFile(false)
{}

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