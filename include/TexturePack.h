//
//  TexturePack.h
//  ModelView
//
//  Created by Bowen Yang on Sept 7, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# ifndef __ModelView__TexturePack__
# define __ModelView__TexturePack__

# include <Options.h>
# include <SamplerPack.h>
# include <vector>
# include <unordered_set>

struct BMPLoader
{
	unsigned char* Pixels;
	GLsizei xWidth;
	GLsizei yHeight;
	GLsizei zSlices;

	BMPLoader(unsigned char* p, GLsizei w, GLsizei h, GLsizei s) 
		: Pixels(p), xWidth(w), yHeight(h), zSlices(s) {}
};

/**
@brief Virtual base class for all kinds of textures.
*/
class TexturePack : public GLAsset
{
public:
	/**
	@brief Set the texture parameters via the default sampler.
	Feed a single precision floating point parameter to the sampler.

	@param target The name of the parameter.

	@param param The value of the parameter.
	*/
	void Param(GLenum target, GLfloat param);

	/**
	@brief Set the texture parameters via the default sampler.
	Feed an integer parameter to the sampler.

	@param pname The name of the parameter.

	@param param The value of the parameter.
	*/
	void Param(GLenum pname, GLint param);

	/**
	@brief Set the texture parameters via the default sampler.
	Feed some single precision floating point parameters to the sampler.

	@param pname The name of the parameter.

	@param param The pointer to the value array of the parameter.
	*/
	void Param(GLenum pname, GLfloat* param);

	/**
	@brief Set the texture parameters via the default sampler.
	Feed some integer parameters to the sampler.

	@param pname The name of the parameter.

	@param param The pointer to the value array of the parameter.
	*/
	void Param(GLenum pname, GLint* param);
protected:
	/**
	@brief Register a texture in the OpenGL context.

	@param Slot The slot of the texture. To sample the texture in fragment shaders:
	Simply invoke texture() with the correspondent sampler assigned with the slot.
	An enumeration between GL_TEXTURE0 and GL_TEXTURE0 + GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS - 1 is expected.
	Note that a value between 0 and GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS - 1 is also recognized and accepted.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI, GL_RGBA...... etc. is expected.
	By default it's set as GL_RGB32F.

	@param levels The total amount of mipmap levels.
	By default it's set as 4.

	@param generateMipmaps Tells OpenGL to generate mipmap automatically or not.
	By default it's set as true, so that mipmaps are generated for you.
	*/
	TexturePack(GLenum Slot, GLint internalFormat = GL_RGB32F, GLsizei levels = 4, bool generateMipmaps = true);

	/**
	@brief Unregister the buffer from the OpenGL context, recycling its name for further use.
	*/
	~TexturePack();

	/**
	@brief Activate the texture.
	*/
	virtual void Activate() = 0;

	/**
	@brief Layout index of the sampler in GLSL shader source code.
	*/
	GLuint layoutSlot;

	/*
	Width.
	*/
	GLsizei xWidth;

	/*
	Height.
	*/
	GLsizei yHeight;

	/*
	Depth.
	*/
	GLsizei dDepth;

	/*
	What's its internal format?
	*/
	GLenum internalFormat;

	/*
	How many levels are there?
	*/
	GLsizei levels;

	/*
	Shall we generate mipmaps?
	*/
	bool generateMipmaps;

	/*
	The default sampler.
	*/
	SamplerPack defaultSampler;

	/**
	@brief Load a BMP image and extract its information.
	*/
	BMPLoader LoadBMP(std::string Path);
};

# endif