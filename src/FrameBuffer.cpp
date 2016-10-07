//
//  FrameBufferPack.cpp
//  ModelView
//
//  Created by Bowen Yang on Oct 6, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include <FrameBuffer.h>

void FrameBuffer::AddRenderTargetAt(RenderBuffer& buffer, GLuint target)
{
	if (Targets.find(target) != Targets.end())
	{
		Error(debugMsg, "Framebuffer %u: Rendering target %u is already occupied.", this->AssetID, target);
		return;
	}

	glBindFramebuffer(this->Usage, this->AssetID);
	glFramebufferRenderbuffer(this->Usage, target, GL_RENDERBUFFER, buffer);
	Targets.emplace(target);

	Log(debugMsg, "Framebuffer %u: Render target(to render buffer) %u was successfully added."
		, this->AssetID, target);
	CheckStatus(__FUNCTION__);

	glBindFramebuffer(this->Usage, 0);
}

void FrameBuffer::AddRenderTargetAt(Texture2D& texture, GLuint target)
{
	if (Targets.find(target) != Targets.end())
	{
		Error(debugMsg, "Framebuffer %u: Rendering target %u is already occupied.", this->AssetID, target);
		return;
	}

	glBindFramebuffer(this->Usage, this->AssetID);
	glBindTexture(GL_TEXTURE_2D, texture);
	glFramebufferTexture2D(this->Usage, target, GL_TEXTURE_2D, texture, 0);
	Targets.emplace(target);

	Log(debugMsg, "Framebuffer %u: Render target(to 2D texture) %u was successfully added."
		, this->AssetID, target);
	CheckStatus(__FUNCTION__);

	glBindFramebuffer(this->Usage, 0);
}

/**
@brief Inform the framebuffer that rendering operations are ready to be performed.
Invoke this interface before calling drawcalls with desired GLSL programs.
*/
void FrameBuffer::DrawFrameBuffer()
{
	GLenum *drawTargets = new GLenum[Targets.size()];
	unsigned index = 0;
	for (auto i : Targets)
	{
		drawTargets[index] = i;
	}
	glBindFramebuffer(this->Usage, this->AssetID);
	glDrawBuffers(Targets.size(), drawTargets);

	if (glCheckFramebufferStatus(this->Usage) != GL_FRAMEBUFFER_COMPLETE)
	{
		Error(debugMsg, "Framebuffer %u is now incomplete. Please refer to the docs of your OpenGL implementation."
			, this->AssetID);
		return;
	}
	delete[] drawTargets;
}

void FrameBuffer::Param(GLenum pname, GLint value)
{
	glBindFramebuffer(this->Usage, this->AssetID);

	glFramebufferParameteri(this->Usage, pname, value);

	glBindFramebuffer(this->Usage, 0);
}

void FrameBuffer::Bind()
{
	glBindFramebuffer(this->Usage, this->AssetID);
}

void FrameBuffer::UnBind()
{
	glBindFramebuffer(this->Usage, 0);
}