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
	/*
	Load the BMP file.
	*/
	unsigned char* LoadBMP(std::string Path);

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
	@brief Constructor that designates its binding slot.

	@param Slot The slot of the texture. To sample the texture in fragment shaders:
	Simply invoke texture() with the correspondent sampler assigned with the slot.
	An enumeration between GL_TEXTURE0 and GL_TEXTURE0 + GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS - 1 is expected.
	Note that a value between 0 and GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS - 1 is also recognized and accepted.
	*/
	TextureArr(GLenum Slot) : TexturePack(Slot), xWidth(0), yHeight(0) {}
protected:
	/**
	@brief Load the texture from a BMP file.
	*/
	void LoadFromBMP(std::string Path);

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
};

/**
@brief 1D textures.
*/
class Texture1D : public TexturePic
{
public:
	/**
	@brief Constructor that designates its binding slot.

	@param Slot The slot of the texture. To sample the texture in fragment shaders:
	Simply invoke texture() with the correspondent sampler assigned with the slot.
	An enumeration between GL_TEXTURE0 and GL_TEXTURE0 + GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS - 1 is expected.
	Note that a value between 0 and GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS - 1 is also recognized and accepted.
	*/
	Texture1D(GLenum Slot) : TexturePic(Slot) {}

	/**
	@brief Initialize the texture from local pointers as an image.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the 1D texture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI...... etc. is expected.
	By default it's set as GL_R8.

	@param clientsideFormat The arrangement of the local storage on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	By default it's set as GL_RED.
	*/
	void LoadFromMemory(GLubyte* Pixels, size_t Width, 
		GLint internalFormat = GL_R8, GLint clientsideFormat = GL_RED);

	/**
	@brief Initialize the texture from local pointers as a table.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the 1D texture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI...... etc. is expected.

	@param clientsideFormat The arrangement of the local storage on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	*/
	void LoadFromMemory(GLbyte* Pixels, size_t Width,
		GLint internalFormat, GLint clientsideFormat);

	/**
	@brief Initialize the texture from local pointers as a table.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the 1D texture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI...... etc. is expected.

	@param clientsideFormat The arrangement of the local storage on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	*/
	void LoadFromMemory(GLushort* Pixels, size_t Width,
		GLint internalFormat, GLint clientsideFormat);

	/**
	@brief Initialize the texture from local pointers as a table.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the 1D texture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI...... etc. is expected.

	@param clientsideFormat The arrangement of the local storage on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	*/
	void LoadFromMemory(GLshort* Pixels, size_t Width,
		GLint internalFormat, GLint clientsideFormat);

	/**
	@brief Initialize the texture from local pointers as a table.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the 1D texture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI...... etc. is expected.

	@param clientsideFormat The arrangement of the local storage on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	*/
	void LoadFromMemory(GLuint* Pixels, size_t Width,
		GLint internalFormat, GLint clientsideFormat);

	/**
	@brief Initialize the texture from local pointers as a table.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the 1D texture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI...... etc. is expected.

	@param clientsideFormat The arrangement of the local storage on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	*/
	void LoadFromMemory(GLint* Pixels, size_t Width,
		GLint internalFormat, GLint clientsideFormat);

	/**
	@brief Initialize the texture from local pointers as a table.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the 1D texture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI...... etc. is expected.

	@param clientsideFormat The arrangement of the local storage on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	*/
	void LoadFromMemory(GLfloat* Pixels, size_t Width,
		GLint internalFormat, GLint clientsideFormat);

	/**
	@brief Initialize the texture from local pointers as a table.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the 1D texture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI...... etc. is expected.

	@param clientsideFormat The arrangement of the local storage on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	*/
	void LoadFromMemory(GLdouble* Pixels, size_t Width,
		GLint internalFormat, GLint clientsideFormat);

	/**
	@brief Initialize the texture from local pointers as a table(Generic version in case you can't find the type you want).

	@param Pixels The pointer to the texture storage.

	@param Width The width of the 1D texture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI...... etc. is expected.

	@param clientsideFormat The arrangement of the local storage on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.

	@param type The type of the texels you provided from the client side.
	A value among GL_UNSIGNED_SHORT, GL_FLOAT...... etc. is expected.
	*/
	void LoadFromMemory(void* Pixels, size_t Width,
		GLint internalFormat, GLint clientsideFormat, GLenum type);
};

/**
@brief 2D textures.
*/
class Texture2D : public TexturePic
{
public:
	/**
	@brief Constructor that designates its binding slot.

	@param Slot The slot of the texture. To sample the texture in fragment shaders:
	Simply invoke texture() with the correspondent sampler assigned with the slot.
	An enumeration between GL_TEXTURE0 and GL_TEXTURE0 + GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS - 1 is expected.
	Note that a value between 0 and GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS - 1 is also recognized and accepted.
	*/
	Texture2D(GLenum Slot) : TexturePic(Slot) {}

	/**
	@brief Initialize the texture from local pointers as an image.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the 2D texture.

	@param Height The height of the 2D texture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI, GL_RGBA...... etc. is expected.
	By default it's set as GL_RGB32F.

	@param clientsideFormat The arrangement of the storage buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	By default it's set as GL_RGB.

	@param levels The total amount of mipmap levels.
	By default it's set as 4.

	@param generateMipmap Tells OpenGL to generate mipmap automatically or not.
	By default it's set as true, so that mipmaps are generated for you.
	*/
	void LoadFromMemory(GLubyte* Pixels, size_t Width, size_t Height, 
		GLint internalFormat = GL_RGB32F, GLint clientsideFormat = GL_RGB, GLsizei levels = 4, bool generateMipMap = true);

	/**
	@brief Initialize the texture from local pointers as a table.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the 2D texture.

	@param Height The height of the 2D texture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI, GL_RGBA...... etc. is expected.

	@param clientsideFormat The arrangement of the storage buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.

	@param levels The total amount of mipmap levels.
	By default it's set as 1, for it's a table.

	@param generateMipmap Tells OpenGL to generate mipmap automatically or not.
	By default it's set as false, for it's a table.
	*/
	void LoadFromMemory(GLbyte* Pixels, size_t Width, size_t Height,
		GLint internalFormat, GLint clientsideFormat, GLsizei levels = 1, bool generateMipMap = false);

	/**
	@brief Initialize the texture from local pointers as a table.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the 2D texture.

	@param Height The height of the 2D texture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI, GL_RGBA...... etc. is expected.

	@param clientsideFormat The arrangement of the storage buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.

	@param levels The total amount of mipmap levels.
	By default it's set as 1, for it's a table.

	@param generateMipmap Tells OpenGL to generate mipmap automatically or not.
	By default it's set as false, for it's a table.
	*/
	void LoadFromMemory(GLushort* Pixels, size_t Width, size_t Height,
		GLint internalFormat, GLint clientsideFormat, GLsizei levels = 1, bool generateMipMap = false);

	/**
	@brief Initialize the texture from local pointers as a table.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the 2D texture.

	@param Height The height of the 2D texture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI, GL_RGBA...... etc. is expected.

	@param clientsideFormat The arrangement of the storage buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.

	@param levels The total amount of mipmap levels.
	By default it's set as 1, for it's a table.

	@param generateMipmap Tells OpenGL to generate mipmap automatically or not.
	By default it's set as false, for it's a table.
	*/
	void LoadFromMemory(GLshort* Pixels, size_t Width, size_t Height,
		GLint internalFormat, GLint clientsideFormat, GLsizei levels = 1, bool generateMipMap = false);

	/**
	@brief Initialize the texture from local pointers as a table.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the 2D texture.

	@param Height The height of the 2D texture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI, GL_RGBA...... etc. is expected.

	@param clientsideFormat The arrangement of the storage buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.

	@param levels The total amount of mipmap levels.
	By default it's set as 1, for it's a table.

	@param generateMipmap Tells OpenGL to generate mipmap automatically or not.
	By default it's set as false, for it's a table.
	*/
	void LoadFromMemory(GLuint* Pixels, size_t Width, size_t Height,
		GLint internalFormat, GLint clientsideFormat, GLsizei levels = 1, bool generateMipMap = false);

	/**
	@brief Initialize the texture from local pointers as a table.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the 2D texture.

	@param Height The height of the 2D texture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI, GL_RGBA...... etc. is expected.

	@param clientsideFormat The arrangement of the storage buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.

	@param levels The total amount of mipmap levels.
	By default it's set as 1, for it's a table.

	@param generateMipmap Tells OpenGL to generate mipmap automatically or not.
	By default it's set as false, for it's a table.
	*/
	void LoadFromMemory(GLint* Pixels, size_t Width, size_t Height,
		GLint internalFormat, GLint clientsideFormat, GLsizei levels = 1, bool generateMipMap = false);

	/**
	@brief Initialize the texture from local pointers as a table.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the 2D texture.

	@param Height The height of the 2D texture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI, GL_RGBA...... etc. is expected.

	@param clientsideFormat The arrangement of the storage buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.

	@param levels The total amount of mipmap levels.
	By default it's set as 1, for it's a table.

	@param generateMipmap Tells OpenGL to generate mipmap automatically or not.
	By default it's set as false, for it's a table.
	*/
	void LoadFromMemory(GLfloat* Pixels, size_t Width, size_t Height,
		GLint internalFormat, GLint clientsideFormat, GLsizei levels = 1, bool generateMipMap = false);

	/**
	@brief Initialize the texture from local pointers as a table.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the 2D texture.

	@param Height The height of the 2D texture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI, GL_RGBA...... etc. is expected.

	@param clientsideFormat The arrangement of the storage buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.

	@param levels The total amount of mipmap levels.
	By default it's set as 1, for it's a table.

	@param generateMipmap Tells OpenGL to generate mipmap automatically or not.
	By default it's set as false, for it's a table.
	*/
	void LoadFromMemory(GLdouble* Pixels, size_t Width, size_t Height,
		GLint internalFormat, GLint clientsideFormat, GLsizei levels = 1, bool generateMipMap = false);

	/**
	@brief Initialize the texture from local pointers as a table(Generic version in case you can't find the type you want).

	@param Pixels The pointer to the texture storage.

	@param Width The width of the 2D texture.

	@param Height The height of the 2D texture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI, GL_RGBA...... etc. is expected.

	@param clientsideFormat The arrangement of the storage buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.

	@param type The type of the texels you provided from the client side.
	A value among GL_UNSIGNED_SHORT, GL_FLOAT...... etc. is expected.

	@param levels The total amount of mipmap levels.
	By default it's set as 1, for it's a table.

	@param generateMipmap Tells OpenGL to generate mipmap automatically or not.
	By default it's set as false, for it's a table.
	*/
	void LoadFromMemory(void* Pixels, size_t Width, size_t Height,
		GLint internalFormat, GLint clientsideFormat, GLenum type, GLsizei levels = 1, bool generateMipMap = false);

	/**
	@brief Load the texels from BMP files as an image.

	@param Path The path to the texture picture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI...... etc. is expected.
	By default it's set as GL_RGB32F.

	@param clientsideFormat The arrangement of the local buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	By default it's set as GL_BGR, by default BMP protocol.

	@param levels The total amount of mipmap levels.
	By default it's set as 4.

	@param generateMipmap Tells OpenGL to generate mipmap automatically or not.
	*/
	void LoadFromBMP(std::string Path, GLint internalFormat = GL_RGB32F, 
		GLint clientsideFormat = GL_BGR, GLsizei levels = 4, bool generateMipMap = true);
};

/**
@brief Rectangular textures.
*/
class TextureRect : public TexturePic
{
public:
	/**
	@brief Constructor that designates its binding slot.

	@param Slot The slot of the texture. To sample the texture in fragment shaders:
	Simply invoke texture() with the correspondent sampler assigned with the slot.
	An enumeration between GL_TEXTURE0 and GL_TEXTURE0 + GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS - 1 is expected.
	Note that a value between 0 and GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS - 1 is also recognized and accepted.
	*/
	TextureRect(GLenum Slot) : TexturePic(Slot) {}

	/**
	@brief Initialize the texture from local pointers.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the rectangular texture.

	@param Height The height of the rectangular texture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI...... etc. is expected.
	By default it's set as GL_RGB32F.

	@param clientsideFormat The arrangement of the local buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	By default it's set as GL_RGB.
	*/
	void LoadFromMemory(unsigned char* Pixels, size_t Width, size_t Height,
		GLint internalFormat = GL_RGB32F, GLint clientsideFormat = GL_RGB);

	/**
	@brief Initialize the texture from local pointers as a table.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the rectangular texture.

	@param Height The height of the rectangular texture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI, GL_RGBA...... etc. is expected.

	@param clientsideFormat The arrangement of the storage buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	*/
	void LoadFromMemory(GLbyte* Pixels, size_t Width, size_t Height,
		GLint internalFormat, GLint clientsideFormat);

	/**
	@brief Initialize the texture from local pointers as a table.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the rectangular texture.

	@param Height The height of the rectangular texture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI, GL_RGBA...... etc. is expected.

	@param clientsideFormat The arrangement of the storage buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	*/
	void LoadFromMemory(GLushort* Pixels, size_t Width, size_t Height,
		GLint internalFormat, GLint clientsideFormat);

	/**
	@brief Initialize the texture from local pointers as a table.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the rectangular texture.

	@param Height The height of the rectangular texture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI, GL_RGBA...... etc. is expected.

	@param clientsideFormat The arrangement of the storage buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	*/
	void LoadFromMemory(GLshort* Pixels, size_t Width, size_t Height,
		GLint internalFormat, GLint clientsideFormat);

	/**
	@brief Initialize the texture from local pointers as a table.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the rectangular texture.

	@param Height The height of the rectangular texture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI, GL_RGBA...... etc. is expected.

	@param clientsideFormat The arrangement of the storage buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	*/
	void LoadFromMemory(GLuint* Pixels, size_t Width, size_t Height,
		GLint internalFormat, GLint clientsideFormat);

	/**
	@brief Initialize the texture from local pointers as a table.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the rectangular texture.

	@param Height The height of the rectangular texture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI, GL_RGBA...... etc. is expected.

	@param clientsideFormat The arrangement of the storage buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	*/
	void LoadFromMemory(GLint* Pixels, size_t Width, size_t Height,
		GLint internalFormat, GLint clientsideFormat);

	/**
	@brief Initialize the texture from local pointers as a table.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the rectangular texture.

	@param Height The height of the rectangular texture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI, GL_RGBA...... etc. is expected.

	@param clientsideFormat The arrangement of the storage buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	*/
	void LoadFromMemory(GLfloat* Pixels, size_t Width, size_t Height,
		GLint internalFormat, GLint clientsideFormat);

	/**
	@brief Initialize the texture from local pointers as a table.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the rectangular texture.

	@param Height The height of the rectangular texture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI, GL_RGBA...... etc. is expected.

	@param clientsideFormat The arrangement of the storage buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	*/
	void LoadFromMemory(GLdouble* Pixels, size_t Width, size_t Height,
		GLint internalFormat, GLint clientsideFormat);

	/**
	@brief Initialize the texture from local pointers as a table(Generic version in case you can't find the type you want).

	@param Pixels The pointer to the texture storage.

	@param Width The width of the rectangular texture.

	@param Height The height of the rectangular texture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI, GL_RGBA...... etc. is expected.

	@param clientsideFormat The arrangement of the storage buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.

	@param type The type of the texels you provided from the client side.
	A value among GL_UNSIGNED_SHORT, GL_FLOAT...... etc. is expected.

	@param levels The total amount of mipmap levels.

	@param generateMipmap Tells OpenGL to generate mipmap automatically or not.
	*/
	void LoadFromMemory(void* Pixels, size_t Width, size_t Height,
		GLint internalFormat, GLint clientsideFormat, GLsizei levels, bool generateMipMap);

	/**
	@brief Load the texels from BMP files.

	@param Path The path to the texture picture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI...... etc. is expected.
	By defualt it's set as GL_RGB32F.

	@param clientsideFormat The arrangement of the local buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	By default it's set as GL_BGR, by default BMP protocol.
	*/
	void LoadFromBMP(std::string Path, GLint internalFormat = GL_RGB32F,
		GLint clientsideFormat = GL_BGR);
};

/**
@brief Multisampling textures.
*/
class TextureMultiSamp : public TexturePic
{
public:
	/**
	@brief Constructor that designates its binding slot.

	@param Slot The slot of the texture. To sample the texture in fragment shaders:
	Simply invoke texture() with the correspondent sampler assigned with the slot.
	An enumeration between GL_TEXTURE0 and GL_TEXTURE0 + GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS - 1 is expected.
	Note that a value between 0 and GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS - 1 is also recognized and accepted.
	*/
	TextureMultiSamp(GLenum Slot) : TexturePic(Slot) {}

	/**
	@brief Initialize the texture from local pointers.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the 2D texture.

	@param Height The height of the 2D texture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI...... etc. is expected.
	By default it's set as GL_RGB32F.

	@param clientsideFormat The arrangement of the local buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	By default it's set as GL_RGB.

	@param levels The total amount of mipmap levels.
	By default it's set as 2.

	@param generateMipmap Tells OpenGL to generate mipmap automatically or not.
	By default it's set as true, so that mipmaps are generated for you.
	*/
	void LoadFromMemory(unsigned char* Pixels, size_t Width, size_t Height,
		GLint internalFormat = GL_RGB, GLint clientsideFormat = GL_BGR, GLsizei levels = 2, bool generateMipMap = true);

	/**
	@brief Load the texels from BMP files.

	@param Path The path to the texture picture.

	@param clientsideFormat The arrangement of the local buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	By default it's set as GL_BGR, by default BMP protocol.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI...... etc. is expected.

	@param levels The total amount of mipmap levels.
	By default it's set as 2.

	@param generateMipmap Tells OpenGL to generate mipmap automatically or not.
	*/
	void LoadFromBMP(std::string Path, GLint clientsideFormat = GL_BGR,
		GLint internalFormat = GL_RGB, GLsizei levels = 2, bool generateMipMap = true);
};

/**
@brief 3D textures.
*/
class Texture3D : public TexturePic
{
public:
	/**
	@brief Constructor that designates its binding slot.

	@param Slot The slot of the texture. To sample the texture in fragment shaders:
	Simply invoke texture() with the correspondent sampler assigned with the slot.
	An enumeration between GL_TEXTURE0 and GL_TEXTURE0 + GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS - 1 is expected.
	Note that a value between 0 and GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS - 1 is also recognized and accepted.
	*/
	Texture3D(GLenum Slot) : TexturePic(Slot) {}

	/**
	@brief Initialize the texture from local pointers as a 3D table.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the 3D texture.

	@param Height The height of the 3D texture.

	@param Depth The depth of the 3D texture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI...... etc. is expected.

	@param clientsideFormat The arrangement of the local buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.

	@param levels The total amount of mipmap levels.
	By default it's set as 1, for it's a table.

	@param generateMipmap Tells OpenGL to generate mipmap automatically or not.
	By default it's set as false, for it's a table.
	*/
	void LoadFromMemory(GLubyte* Pixels, size_t Width, size_t Height, size_t Depth,
		GLint internalFormat, GLint clientsideFormat, GLsizei level = 1, bool generateMipMap = false);

	/**
	@brief Initialize the texture from local pointers as a 3D table.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the 3D texture.

	@param Height The height of the 3D texture.

	@param Depth The depth of the 3D texture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI...... etc. is expected.

	@param clientsideFormat The arrangement of the local buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.

	@param levels The total amount of mipmap levels.
	By default it's set as 1, for it's a table.

	@param generateMipmap Tells OpenGL to generate mipmap automatically or not.
	By default it's set as false, for it's a table.
	*/
	void LoadFromMemory(GLbyte* Pixels, size_t Width, size_t Height, size_t Depth,
		GLint internalFormat, GLint clientsideFormat, GLsizei level = 1, bool generateMipMap = false);

	/**
	@brief Initialize the texture from local pointers as a 3D table.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the 3D texture.

	@param Height The height of the 3D texture.

	@param Depth The depth of the 3D texture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI...... etc. is expected.

	@param clientsideFormat The arrangement of the local buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.

	@param levels The total amount of mipmap levels.
	By default it's set as 1, for it's a table.

	@param generateMipmap Tells OpenGL to generate mipmap automatically or not.
	By default it's set as false, for it's a table.
	*/
	void LoadFromMemory(GLushort* Pixels, size_t Width, size_t Height, size_t Depth,
		GLint internalFormat, GLint clientsideFormat, GLsizei level = 1, bool generateMipMap = false);

	/**
	@brief Initialize the texture from local pointers as a 3D table.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the 3D texture.

	@param Height The height of the 3D texture.

	@param Depth The depth of the 3D texture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI...... etc. is expected.

	@param clientsideFormat The arrangement of the local buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.

	@param levels The total amount of mipmap levels.
	By default it's set as 1, for it's a table.

	@param generateMipmap Tells OpenGL to generate mipmap automatically or not.
	By default it's set as false, for it's a table.
	*/
	void LoadFromMemory(GLshort* Pixels, size_t Width, size_t Height, size_t Depth,
		GLint internalFormat, GLint clientsideFormat, GLsizei level = 1, bool generateMipMap = false);

	/**
	@brief Initialize the texture from local pointers as a 3D table.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the 3D texture.

	@param Height The height of the 3D texture.

	@param Depth The depth of the 3D texture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI...... etc. is expected.

	@param clientsideFormat The arrangement of the local buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.

	@param levels The total amount of mipmap levels.
	By default it's set as 1, for it's a table.

	@param generateMipmap Tells OpenGL to generate mipmap automatically or not.
	By default it's set as false, for it's a table.
	*/
	void LoadFromMemory(GLuint* Pixels, size_t Width, size_t Height, size_t Depth,
		GLint internalFormat, GLint clientsideFormat, GLsizei level = 1, bool generateMipMap = false);

	/**
	@brief Initialize the texture from local pointers as a 3D table.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the 3D texture.

	@param Height The height of the 3D texture.

	@param Depth The depth of the 3D texture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI...... etc. is expected.

	@param clientsideFormat The arrangement of the local buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.

	@param levels The total amount of mipmap levels.
	By default it's set as 1, for it's a table.

	@param generateMipmap Tells OpenGL to generate mipmap automatically or not.
	By default it's set as false, for it's a table.
	*/
	void LoadFromMemory(GLint* Pixels, size_t Width, size_t Height, size_t Depth,
		GLint internalFormat, GLint clientsideFormat, GLsizei level = 1, bool generateMipMap = false);

	/**
	@brief Initialize the texture from local pointers as a 3D table.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the 3D texture.

	@param Height The height of the 3D texture.

	@param Depth The depth of the 3D texture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI...... etc. is expected.

	@param clientsideFormat The arrangement of the local buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.

	@param levels The total amount of mipmap levels.
	By default it's set as 1, for it's a table.

	@param generateMipmap Tells OpenGL to generate mipmap automatically or not.
	By default it's set as false, for it's a table.
	*/
	void LoadFromMemory(GLfloat* Pixels, size_t Width, size_t Height, size_t Depth,
		GLint internalFormat, GLint clientsideFormat, GLsizei level = 1, bool generateMipMap = false);

	/**
	@brief Initialize the texture from local pointers as a 3D table.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the 3D texture.

	@param Height The height of the 3D texture.

	@param Depth The depth of the 3D texture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI...... etc. is expected.

	@param clientsideFormat The arrangement of the local buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.

	@param levels The total amount of mipmap levels.
	By default it's set as 1, for it's a table.

	@param generateMipmap Tells OpenGL to generate mipmap automatically or not.
	By default it's set as false, for it's a table.
	*/
	void LoadFromMemory(GLdouble* Pixels, size_t Width, size_t Height, size_t Depth,
		GLint internalFormat, GLint clientsideFormat, GLsizei level = 1, bool generateMipMap = false);

	/**
	@brief Initialize the texture from local pointers as a 3D table.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the 3D texture.

	@param Height The height of the 3D texture.

	@param Depth The depth of the 3D texture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI...... etc. is expected.

	@param clientsideFormat The arrangement of the local buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.

	@param type The type of the texels you provided from the client side.
	A value among GL_UNSIGNED_SHORT, GL_FLOAT...... etc. is expected.

	@param levels The total amount of mipmap levels.
	By default it's set as 1, for it's a table.

	@param generateMipmap Tells OpenGL to generate mipmap automatically or not.
	By default it's set as false, for it's a table.
	*/
	void LoadFromMemory(void* Pixels, size_t Width, size_t Height, size_t Depth,
		GLint internalFormat, GLint clientsideFormat, GLenum type, GLsizei level = 1, bool generateMipMap = false);

private:
	GLsizei dDepth;
};

/**
@brief Cube maps.
*/
class TextureCube : public TextureArr
{
public:
	/**
	@brief Initialize the texture from local pointers.
	*/
	TextureCube(unsigned char* Buffer, size_t width, size_t height);
	/**
	@brief Initialize the texture from pictures.
	*/
	TextureCube(std::string Path, GLenum layout);

	//void Attach() override;
	void Attach(GLint internalFormat, GLboolean generateMipMap);
	//void Detach() override;
};

/**
@brief 1D texture arrays.
*/
class Texture1DArray : public TexturePic
{
public:
	
private:
	void Bind(GLenum target);
	GLsizei size;
	int* Buffer;
};

/**
@brief 2D texture arrays.
*/
class Texture2DArray : public TexturePic
{
public:
	
private:
	void Bind(GLenum target);
	GLsizei size;
	int* Buffer;
};

# endif