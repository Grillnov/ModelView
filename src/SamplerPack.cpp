# include <TexturePack.h>

void SamplerPack::Attach()
{
	if (this->isAttached)
	{
		Warning(debugMsg, "Sampler %u is already attached, bailing.", this->AssetID);
		return;
	}

	glGenSamplers(1, &this->AssetID);
	CheckStatus(__FUNCTION__);

	Log(debugMsg, "Sampler %u was successfully attached.", this->AssetID);
	this->isAttached = true;
}

void SamplerPack::Detach()
{
	if (!this->isAttached)
	{
		Warning(debugMsg, "Sampler %u is not attached yet, bailing.", this->AssetID);
		return;
	}

	glDeleteSamplers(1, &this->AssetID);
	CheckStatus(__FUNCTION__);

	Log(debugMsg, "Sampler %u was successfully detached.", this->AssetID);
	this->isAttached = false;
}

SamplerPack::operator GLuint()
{
	if (!this->isAttached)
	{
		Warning(debugMsg, "Sampler %u is not attached yet, illegal parameter for GL interface.");
		return 0;
	}
	else
		return this->AssetID;
}

void SamplerPack::Param(GLenum target, GLfloat param)
{
	if (!this->isAttached)
	{
		Error(debugMsg, "Sampler %u is not attached yet, bailing.", this->AssetID);
	}
	glSamplerParameterf(this->AssetID, target, param);
	CheckStatus(__FUNCTION__);
}

void SamplerPack::Param(GLenum target, GLint param)
{
	if (!this->isAttached)
	{
		Error(debugMsg, "Sampler %u is not attached yet, bailing.", this->AssetID);
	}
	glSamplerParameteri(this->AssetID, target, param);
	CheckStatus(__FUNCTION__);
}

void SamplerPack::Param(GLenum target, GLfloat* param)
{
	if (!this->isAttached)
	{
		Error(debugMsg, "Sampler %u is not attached yet, bailing.", this->AssetID);
	}
	glSamplerParameterfv(this->AssetID, target, param);
	CheckStatus(__FUNCTION__);
}

void SamplerPack::Param(GLenum target, GLint* param)
{
	if (!this->isAttached)
	{
		Error(debugMsg, "Sampler %u is not attached yet, bailing.", this->AssetID);
	}
	glSamplerParameteriv(this->AssetID, target, param);
	CheckStatus(__FUNCTION__);
}