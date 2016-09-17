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

Texture2D::Texture2D(std::string Path, GLenum layout)
{
	if (OccupiedLayouts.find(layout) != OccupiedLayouts.end())
	{
		Error(debugMsg, "Layout slot %u is already occupied!", layout);
	}
	LoadFromBMP(Path);
	OccupiedLayouts.emplace(layout);
	this->layout = layout;
	Log(debugMsg, "Texture at layout slot %u is now ready for attaching.", layout);
}

void Texture2D::Attach()
{
	Attach(GL_RGB, true);
}

void Texture2D::Attach(GLint GLinternalformat, GLboolean generateMipMap)
{
	if (this->isAttached)
	{
		Warning(debugMsg, "Texture %u at layout slot %u is already attached, bailing.", this->AssetID, this->layout);
		return;
	}

	glGenTextures(1, &this->AssetID);
	glBindTexture(GL_TEXTURE_2D, this->AssetID);
	glTexImage2D(GL_TEXTURE_2D, 0, GLinternalformat,
		this->xWidth, this->yHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, this->Buffer);

	glActiveTexture(GL_TEXTURE0 + layout);
	glBindTexture(GL_TEXTURE_2D, this->AssetID);

	this->defaultSampler.Attach();
	glBindSampler(layout, defaultSampler);

	if (generateMipMap)
	{
		glGenerateTextureMipmap(*this);
	}

	Param(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	Param(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	Param(GL_TEXTURE_WRAP_S, GL_REPEAT);
	Param(GL_TEXTURE_WRAP_T, GL_REPEAT);

	CheckStatus(__FUNCTION__);

	Log(debugMsg, "Texture %u was successfully attached at layout slot %u.", this->AssetID, this->layout);
	this->isAttached = true;
	delete[] this->Buffer;
}

void Texture2D::Detach()
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