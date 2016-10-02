//
//  TextureRect.h
//  ModelView
//
//  Created by Bowen Yang on Sept 7, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# ifndef __ModelView__TextureRect__
# define __ModelView__TextureRect__

# include <TexturePack.h>

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
# endif