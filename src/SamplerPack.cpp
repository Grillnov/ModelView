//
//  SamplerPack.cpp
//  ModelView
//
//  Created by Bowen Yang on Aug 17, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include <SamplerPack.h>

SamplerPack::SamplerPack()
{
	glGenSamplers(1, &this->AssetID);
	if (AssetID != 0)
	{
		Log(debugMsg, "Sampler %u was successfully registered.", this->AssetID);
	}
	else
	{
		Error(debugMsg, "Failed to create a sampler.");
	}
	CheckStatus(__FUNCTION__);
}

SamplerPack::~SamplerPack()
{
	glDeleteSamplers(1, &this->AssetID);
	CheckStatus(__FUNCTION__);

	Log(debugMsg, "Sampler %u was successfully unregistered.", this->AssetID);
}

void SamplerPack::Param(GLenum target, GLfloat param)
{
	glSamplerParameterf(this->AssetID, target, param);
	CheckStatus(__FUNCTION__);
}

void SamplerPack::Param(GLenum target, GLint param)
{
	glSamplerParameteri(this->AssetID, target, param);
	CheckStatus(__FUNCTION__);
}

void SamplerPack::Param(GLenum target, GLfloat* param)
{
	glSamplerParameterfv(this->AssetID, target, param);
	CheckStatus(__FUNCTION__);
}

void SamplerPack::Param(GLenum target, GLint* param)
{
	glSamplerParameteriv(this->AssetID, target, param);
	CheckStatus(__FUNCTION__);
}