//
//  Texture2D.cpp
//  ModelView
//
//  Created by Bowen Yang on Sept 18, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include <TexturePack.h>

void Texture2D::LoadFromBMP(std::string Path, GLint internalFormat,
	GLint clientsideFormat, GLsizei levels, bool generateMipMap)
{
	unsigned char* texels = LoadBMP(Path);

	glBindTexture(GL_TEXTURE_2D, this->AssetID);
	glTexStorage2D(GL_TEXTURE_2D, levels, internalFormat, xWidth, yHeight);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, xWidth, yHeight, clientsideFormat, GL_UNSIGNED_BYTE, texels);

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

	Log(debugMsg, "Texture %u at layout slot %u is now ready.", this->AssetID, this->layoutSlot);
	delete[] texels;
}

void Texture2D::LoadFromMemory(unsigned char* Pixels, size_t Width, size_t Height,
	GLint internalFormat, GLint clientsideFormat, GLsizei levels, bool generateMipMap)
{
	glBindTexture(GL_TEXTURE_2D, this->AssetID);

	this->xWidth = Width;
	this->yHeight = Height;

	glTexStorage2D(GL_TEXTURE_2D, levels, internalFormat, xWidth, yHeight);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, xWidth, yHeight, clientsideFormat, GL_UNSIGNED_BYTE, Pixels);

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
}