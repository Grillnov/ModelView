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
@brief Samplers. You may want to add samplers for textures yourself, or just
use the default sampler and modify its parameters.
*/
class SamplerPack : public GLAsset
{
public:
	/**
	@brief Register the sampler.
	*/
	SamplerPack();

	/**
	@brief Unregister the sampler, recycling its name for further usage.
	*/
	~SamplerPack();

	/**
	@brief Feed a single precision floating point parameter to the sampler.

	@param target The name of the parameter.

	@param param The value of the parameter.
	*/
	void Param(GLenum target, GLfloat param);

	/**
	@brief Feed an integer parameter to the sampler.

	@param target The name of the parameter.

	@param param The value of the parameter.
	*/
	void Param(GLenum target, GLint param);

	/**
	@brief Feed some single precision floating point parameters to the sampler.

	@param target The name of the parameter.

	@param param The pointer to the value array of the parameter.
	*/
	void Param(GLenum target, GLfloat* param);

	/**
	@brief Feed some integer parameters to the sampler.

	@param target The name of the parameter.

	@param param The pointer to the value array of the parameter.
	*/
	void Param(GLenum target, GLint* param);
};

/**
@brief Virtual base class for all kinds of textures.
*/
class TexturePack : public GLAsset
{
public:
	/**
	@brief Register a texture in the OpenGL context.

	@param Slot The slot of the texture. To sample the texture in fragment shaders:
	Simply invoke texture() with the correspondent sampler assigned with the slot.
	An enumeration between GL_TEXTURE0 and GL_TEXTURE0 + GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS - 1 is expected.
	Note that a value between 0 and GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS - 1 is also recognized and accepted.
	*/
	TexturePack(GLenum Slot);

	/**
	@brief Unregister the buffer from the OpenGL context, recycling its name for further use.
	*/
	~TexturePack();
protected:
	/**
	@brief Layout index of the sampler in GLSL shader source code.
	*/
	GLuint layoutSlot;

	/**
	@brief Preventing from binding two texture objects to one binding slot.
	*/
	static std::unordered_set<GLenum> OccupiedLayouts;

	/**
	@brief Load a BMP image and extract its information.
	*/
	BMPLoader LoadBMP(std::string Path);
};

/**
@brief Base class for singular textures, initialized from BMPs or local pointers.
*/
class TexturePic : public TexturePack
{
public:
	/**
	@brief Constructor that designates its binding slot.

	@param Slot The slot of the texture. To sample the texture in fragment shaders:
	Simply invoke texture() with the correspondent sampler assigned with the slot.
	An enumeration between GL_TEXTURE0 and GL_TEXTURE0 + GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS - 1 is expected.
	Note that a value between 0 and GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS - 1 is also recognized and accepted.
	*/
	TexturePic(GLenum Slot) : TexturePack(Slot), xWidth(0), yHeight(0) {}
protected:
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

	@param target The name of the parameter.

	@param param The value of the parameter.
	*/
	void Param(GLenum target, GLint param);

	/**
	@brief Set the texture parameters via the default sampler.
	Feed some single precision floating point parameters to the sampler.

	@param target The name of the parameter.

	@param param The pointer to the value array of the parameter.
	*/
	void Param(GLenum target, GLfloat* param);

	/**
	@brief Set the texture parameters via the default sampler.
	Feed some integer parameters to the sampler.

	@param target The name of the parameter.

	@param param The pointer to the value array of the parameter.
	*/
	void Param(GLenum target, GLint* param);

	/**
	@brief The default sampler.
	*/
	SamplerPack defaultSampler;

	/**
	@brief Its width.
	*/
	GLsizei xWidth;

	/**
	@brief Its height.
	*/
	GLsizei yHeight;
};

/**
@brief Base class for array textures, grouping multiple textures into an array.
*/
class TextureArr : public TexturePack
{
public:
	/**
	@brief Constructor that designates its binding slot and its slices.

	@param Slot The slot of the texture. To sample the texture in fragment shaders:
	Simply invoke texture() with the correspondent sampler assigned with the slot.
	An enumeration between GL_TEXTURE0 and GL_TEXTURE0 + GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS - 1 is expected.
	Note that a value between 0 and GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS - 1 is also recognized and accepted.

	@param Slices The amount of textures you need in this array.

	@param Width The width of the 1D texture slice.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI, GL_RGBA...... etc. is expected.
	*/
	TextureArr(GLenum Slot, GLsizei Slices, GLsizei Width, GLsizei Height, GLenum internalFormat) : 
		TexturePack(Slot), xWidth(Width), yHeight(Height), sSlices(Slices), internalFormat(internalFormat) {}
protected:
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

	@param target The name of the parameter.

	@param param The value of the parameter.
	*/
	void Param(GLenum target, GLint param);

	/**
	@brief Set the texture parameters via the default sampler.
	Feed some single precision floating point parameters to the sampler.

	@param target The name of the parameter.

	@param param The pointer to the value array of the parameter.
	*/
	void Param(GLenum target, GLfloat* param);

	/**
	@brief Set the texture parameters via the default sampler.
	Feed some integer parameters to the sampler.

	@param target The name of the parameter.

	@param param The pointer to the value array of the parameter.
	*/
	void Param(GLenum target, GLint* param);

	/**
	@brief The default sampler.
	*/
	SamplerPack defaultSampler;

	/**
	Width.
	*/
	GLsizei xWidth;

	/**
	Height.
	*/
	GLsizei yHeight;

	/**
	Slices -- how many textures are there in this array?
	*/
	GLsizei sSlices;

	/**
	What's its internal format?
	*/
	GLenum internalFormat;
};

/**
@brief 1D texture extendable arrays.
*/
class Texture1DVector : public TextureArr
{

};

/**
@brief 2D texture extendable arrays.
*/
class Texture2DVector : public TextureArr
{

};

# endif