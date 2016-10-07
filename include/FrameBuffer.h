//
//  FrameBufferPack.h
//  ModelView
//
//  Created by Bowen Yang on Oct 5, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# ifndef __ModelView__FrameBuffer__
# define __ModelView__FrameBuffer__

# include <Options.h>
# include <RenderBuffer.h>
# include <Texture2D.h>
# include <unordered_set>

/**
@brief Frame buffer object that redirects rendering results.
*/
class FrameBuffer : public GLAsset
{
public:
	/**
	@brief Register a framebuffer in the OpenGL context.

	@param Usage Read or write to the frame buffer.
	By default it's set as GL_DRAW_FRAMEBUFFER.
	*/
	FrameBuffer(GLenum Usage = GL_DRAW_FRAMEBUFFER) : Usage(Usage)
	{
		glGenFramebuffers(1, &this->AssetID);

		if (AssetID != 0)
		{
			Log(debugMsg, "Framebuffer %u was successfully registered.", this->AssetID);
		}
		else
		{
			Error(debugMsg, "Failed to create a framebuffer.");
		}
		glBindFramebuffer(Usage, this->AssetID);
		CheckStatus(__FUNCTION__);
		glBindFramebuffer(Usage, 0);
	}

	/**
	@brief Unregister the framebuffer from the OpenGL context, recycling its name for further use.
	*/
	~FrameBuffer()
	{
		glBindFramebuffer(this->Usage, this->AssetID);
		GLenum *drawTargets = new GLenum[Targets.size()];
		unsigned index = 0;
		for (auto i : Targets)
		{
			drawTargets[index] = i;
		}
		glInvalidateFramebuffer(this->Usage, Targets.size(), drawTargets);

		delete[] drawTargets;

		glDeleteFramebuffers(1, &this->AssetID);
		CheckStatus(__FUNCTION__);

		Log(debugMsg, "Framebuffer %u was successfully unregistered.", this->AssetID);
		glBindFramebuffer(this->Usage, 0);
	}

	/**
	@brief
	Register a rendering target at layout target(layout location = index, or depth/stencil).
	Rendering output from the fragment shader at layout target will be redirected to the render buffer.
	Rejects the operation if the target is already occupied.

	@param buffer The render buffer to be filled with rendered results.

	@param target The layout target in GLSL shader code.
	A value among GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_DEPTH_ATTACHMENT...... is expected.
	Note that simply feeding this parameter with a value between 0 and GL_MAX_COLOR_ATTACHMENTS - 1
	is also accepted.
	*/
	void AddRenderTargetAt(RenderBuffer& buffer, GLuint target);

	/**
	@brief
	Register a rendering target at layout target(layout location = index, or depth/stencil).
	Rendering output from the fragment shader at layout target will be redirected to the 2D texture.
	Rejects the operation if the target is already occupied.

	@param buffer The render buffer to be filled with rendered results.

	@param target The layout target in GLSL shader code.
	A value among GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, 
	GL_DEPTH_ATTACHMENT, GL_STENCIL_ATTACHMENT...... is expected.
	*/
	void AddRenderTargetAt(Texture2D& buffer, GLuint target);

	/**
	@brief Inform the framebuffer that rendering operations are ready to be performed.
	Invoke this interface before calling drawcalls with desired GLSL programs.
	*/
	void DrawFrameBuffer();

	/**
	@brief Feed an integer parameter to the framebuffer.

	@param pname The name of the parameter.

	@param param The value of the parameter.
	*/
	void Param(GLenum pname, GLint value);

	/**
	@brief Bind the framebuffer so that off-screen rendering is performed as you wish.
	*/
	void Bind();

	/**
	@brief Unbind the framebuffer so that rendering output is shown on the screen again.
	*/
	void UnBind();
private:
	/**
	@brief Usage of the framebuffer.
	*/
	GLenum Usage;

	/**
	@brief Occupied rendering targets.
	*/
	std::unordered_set<GLenum> Targets;
};

# endif