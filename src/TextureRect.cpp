//
//  TextureRect.cpp
//  ModelView
//
//  Created by Bowen Yang on Sept 18, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include <AllinGL.h>
# include <TexturePack.h>

TextureRect::TextureRect(std::string Path, GLenum layout)
{
	if (layout > GL_TEXTURE0)
		layout -= GL_TEXTURE0;

	if (OccupiedLayouts.find(layout) != OccupiedLayouts.end())
	{
		Error(debugMsg, "Layout slot %u is already occupied!", layout);
	}

	LoadFromBMP(Path);
	this->isFromFile = true;
	OccupiedLayouts.emplace(layout);
	this->layout = layout;
	Log(debugMsg, "Texture at layout slot %u is now ready for attaching.", layout);
}

TextureRect::TextureRect(unsigned char* pixels, size_t width, size_t height, GLenum layout)
{
	if (layout > GL_TEXTURE0)
		layout -= GL_TEXTURE0;

	if (OccupiedLayouts.find(layout) != OccupiedLayouts.end())
	{
		Error(debugMsg, "Layout slot %u is already occupied!", layout);
	}

	this->Buffer = pixels;
	this->xWidth = width;
	this->yHeight = height;
	OccupiedLayouts.emplace(layout);
	this->layout = layout;
}

void TextureRect::Attach()
{
	Attach(GL_BGR, GL_RGB);
}

void TextureRect::Attach(GLint clientsideFormat, GLint internalFormat)
{
	if (this->isAttached)
	{
		Warning(debugMsg, "Texture %u at layout slot %u is already attached, bailing.", this->AssetID, this->layout);
		return;
	}

	glGenTextures(1, &this->AssetID);
	glBindTexture(GL_TEXTURE_RECTANGLE, this->AssetID);
	glTexImage2D(GL_TEXTURE_RECTANGLE, 0, internalFormat,
		this->xWidth, this->yHeight, 0, clientsideFormat, GL_UNSIGNED_BYTE, this->Buffer);

	glActiveTexture(GL_TEXTURE0 + layout);
	glBindTexture(GL_TEXTURE_RECTANGLE, this->AssetID);

	this->defaultSampler.Attach();
	glBindSampler(layout, defaultSampler);

	CheckStatus(__FUNCTION__);

	Log(debugMsg, "Texture %u was successfully attached at layout slot %u.", this->AssetID, this->layout);
	this->isAttached = true;
	if (this->isFromFile)
		delete[] this->Buffer;
}

void TextureRect::Detach()
{
	if (!this->isAttached)
	{
		Warning(debugMsg, "Texture %u at slot %u is already attached, bailing.", this->AssetID, this->layout);
		return;
	}

	glDeleteTextures(1, &this->AssetID);
	CheckStatus(__FUNCTION__);

	Log(debugMsg, "Texture %u at slot %u was successfully attached.", this->AssetID, this->layout);
	this->isAttached = false;
}