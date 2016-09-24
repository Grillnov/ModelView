//
//  TextureRect.cpp
//  ModelView
//
//  Created by Bowen Yang on Sept 18, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include <TexturePack.h>

void TextureRect::LoadFromBMP(std::string Path, GLint clientsideFormat,
	GLint internalFormat)
{
	unsigned char* texels = LoadBMP(Path);

	glBindTexture(GL_TEXTURE_RECTANGLE, this->AssetID);
	glTexStorage2D(GL_TEXTURE_RECTANGLE, 1, internalFormat, xWidth, yHeight);
	glTexSubImage2D(GL_TEXTURE_RECTANGLE, 0, 0, 0, xWidth, yHeight, clientsideFormat, GL_UNSIGNED_BYTE, texels);

	glActiveTexture(GL_TEXTURE0 + this->layoutSlot);
	glBindTexture(GL_TEXTURE_RECTANGLE, this->AssetID);

	glBindSampler(layoutSlot, defaultSampler);

	Param(GL_TEXTURE_WRAP_S, GL_REPEAT);
	Param(GL_TEXTURE_WRAP_T, GL_REPEAT);

	CheckStatus(__FUNCTION__);

	Log(debugMsg, "Texture %u at layout slot %u is now ready.", this->AssetID, this->layoutSlot);
	delete[] texels;
}

void TextureRect::LoadFromMemory(unsigned char* Pixels, size_t Width, size_t Height,
	GLint internalFormat, GLint clientsideFormat)
{
	glBindTexture(GL_TEXTURE_RECTANGLE, this->AssetID);

	this->xWidth = Width;
	this->yHeight = Height;

	glTexStorage2D(GL_TEXTURE_RECTANGLE, 1, internalFormat, xWidth, yHeight);
	glTexSubImage2D(GL_TEXTURE_RECTANGLE, 0, 0, 0, xWidth, yHeight, clientsideFormat, GL_UNSIGNED_BYTE, Pixels);

	glActiveTexture(GL_TEXTURE0 + this->layoutSlot);
	glBindTexture(GL_TEXTURE_RECTANGLE, this->AssetID);

	glBindSampler(layoutSlot, defaultSampler);

	Param(GL_TEXTURE_WRAP_S, GL_REPEAT);
	Param(GL_TEXTURE_WRAP_T, GL_REPEAT);

	CheckStatus(__FUNCTION__);

	Log(debugMsg, "Texture %u at layout slot %u is now ready.", this->AssetID, this->layoutSlot);
}