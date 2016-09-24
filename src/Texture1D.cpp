//
//  Texture1D.cpp
//  ModelView
//
//  Created by Bowen Yang on Sept 18, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include <TexturePack.h>

void Texture1D::LoadFromMemory(unsigned char* Pixels, size_t Width, GLint internalFormat,
	GLint clientsideFormat)
{
	glBindTexture(GL_TEXTURE_1D, this->AssetID);

	this->xWidth = Width;

	glTexStorage1D(GL_TEXTURE_1D, 1, internalFormat, clientsideFormat);
	glTexImage1D(GL_TEXTURE_1D, 0, internalFormat, this->xWidth, 0,
		clientsideFormat, GL_UNSIGNED_BYTE, Pixels);

	glActiveTexture(GL_TEXTURE0 + layoutSlot);

	CheckStatus(__FUNCTION__);

	glBindTexture(GL_TEXTURE_1D, this->AssetID);
	glBindSampler(layoutSlot, defaultSampler);

	Param(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	Param(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	Param(GL_TEXTURE_WRAP_S, GL_REPEAT);

	CheckStatus(__FUNCTION__);

	Log(debugMsg, "1D texture %u was successfully attached at layout slot %u.", this->AssetID, this->layoutSlot);
}