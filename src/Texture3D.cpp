//
//  Texture3D.cpp
//  ModelView
//
//  Created by Bowen Yang on Sept 18, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include <AllinGL.h>
# include <TexturePack.h>

Texture3D::Texture3D(unsigned char* pixel, size_t width, size_t height, size_t depth, GLenum layout)
{
	if (layout > GL_TEXTURE0)
		layout -= GL_TEXTURE0;

	if (OccupiedLayouts.find(layout) != OccupiedLayouts.end())
	{
		Error(debugMsg, "Layout slot %u is already occupied!", layout);
	}

	this->Buffer = pixel;
	this->xWidth = width;
	this->yHeight = height;
	OccupiedLayouts.emplace(layout);
	this->layout = layout;
}

void Texture3D::Attach()
{
	Attach(GL_BGR, GL_RGB, true);
}

void Texture3D::Attach(GLint clientsideFormat, GLint internalFormat, bool generateMipMap)
{
	if (this->isAttached)
	{
		Warning(debugMsg, "Texture %u at layout slot %u is already attached, bailing.", this->AssetID, this->layout);
		return;
	}

	glGenTextures(1, &this->AssetID);
	glBindTexture(GL_TEXTURE_2D, this->AssetID);
	glTexImage3D(GL_TEXTURE_2D, 0, internalFormat, this->xWidth, this->yHeight, 
		this->dDepth, 0, clientsideFormat, GL_UNSIGNED_BYTE, Buffer);

	glActiveTexture(GL_TEXTURE0 + layout);
	glBindTexture(GL_TEXTURE_2D, this->AssetID);

	this->defaultSampler.Attach();
	glBindSampler(layout, defaultSampler);

	if (generateMipMap)
	{
		glGenerateTextureMipmap(this->AssetID);
	}

	Param(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	Param(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	Param(GL_TEXTURE_WRAP_S, GL_REPEAT);
	Param(GL_TEXTURE_WRAP_T, GL_REPEAT);

	CheckStatus(__FUNCTION__);

	Log(debugMsg, "Texture %u was successfully attached at layout slot %u.", this->AssetID, this->layout);
	this->isAttached = true;
	if (this->isFromFile)
		delete[] this->Buffer;
}

void Texture3D::Detach()
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