//
//  Texture1D.h
//  ModelView
//
//  Created by Bowen Yang on Sept 7, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# ifndef __ModelView__Texture1D__
# define __ModelView__Texture1D__

# include <TexturePack.h>

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
	@brief Initialize the texture from local pointers as a table.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the 1D texture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI, GL_RGBA...... etc. is expected.
	By default it's set as GL_R32F.

	@param clientsideFormat The arrangement of the storage buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	By default it's set as GL_RGB.

	@param levels The total amount of mipmap levels.
	By default it's set as 4.

	@param generateMipmap Tells OpenGL to generate mipmap automatically or not.
	By default it's set as true, so that mipmaps are generated for you.
	*/
	void LoadFromMemory(GLubyte* Pixels, GLsizei Width,
		GLint internalFormat = GL_R32F, GLint clientsideFormat = GL_RGB, GLsizei levels = 4, bool generateMipmap = false);

	/**
	@brief Initialize the texture from local pointers as a table.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the 1D texture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI, GL_RGBA...... etc. is expected.
	No default value is given. For it's supposed to be used as a table, it's up to
	programmers to decide what kind of format should be chosen in GLSL shaders.

	@param clientsideFormat The arrangement of the storage buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	No default value is given. For it's supposed to be used as a table, it's up to
	programmers to decide what kind of layout on the client side is used to feed the texture.

	@param levels The total amount of mipmap levels.
	By default it's set as 1, for it's a table.

	@param generateMipmap Tells OpenGL to generate mipmap automatically or not.
	By default it's set as false, for it's a table.
	*/
	void LoadFromMemory(GLbyte* Pixels, GLsizei Width,
		GLint internalFormat, GLint clientsideFormat, GLsizei levels = 1, bool generateMipmap = false);

	/**
	@brief Initialize the texture from local pointers as a table.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the 1D texture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI, GL_RGBA...... etc. is expected.
	No default value is given. For it's supposed to be used as a table, it's up to
	programmers to decide what kind of format should be chosen in GLSL shaders.

	@param clientsideFormat The arrangement of the storage buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	No default value is given. For it's supposed to be used as a table, it's up to
	programmers to decide what kind of layout on the client side is used to feed the texture.

	@param levels The total amount of mipmap levels.
	By default it's set as 1, for it's a table.

	@param generateMipmap Tells OpenGL to generate mipmap automatically or not.
	By default it's set as false, for it's a table.
	*/
	void LoadFromMemory(GLushort* Pixels, GLsizei Width,
		GLint internalFormat, GLint clientsideFormat, GLsizei levels = 1, bool generateMipmap = false);

	/**
	@brief Initialize the texture from local pointers as a table.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the 1D texture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI, GL_RGBA...... etc. is expected.
	No default value is given. For it's supposed to be used as a table, it's up to
	programmers to decide what kind of format should be chosen in GLSL shaders.

	@param clientsideFormat The arrangement of the storage buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	No default value is given. For it's supposed to be used as a table, it's up to
	programmers to decide what kind of layout on the client side is used to feed the texture.

	@param levels The total amount of mipmap levels.
	By default it's set as 1, for it's a table.

	@param generateMipmap Tells OpenGL to generate mipmap automatically or not.
	By default it's set as false, for it's a table.
	*/
	void LoadFromMemory(GLshort* Pixels, GLsizei Width,
		GLint internalFormat, GLint clientsideFormat, GLsizei levels = 1, bool generateMipmap = false);

	/**
	@brief Initialize the texture from local pointers as a table.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the 1D texture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI, GL_RGBA...... etc. is expected.
	No default value is given. For it's supposed to be used as a table, it's up to
	programmers to decide what kind of format should be chosen in GLSL shaders.

	@param clientsideFormat The arrangement of the storage buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	No default value is given. For it's supposed to be used as a table, it's up to
	programmers to decide what kind of layout on the client side is used to feed the texture.

	@param levels The total amount of mipmap levels.
	By default it's set as 1, for it's a table.

	@param generateMipmap Tells OpenGL to generate mipmap automatically or not.
	By default it's set as false, for it's a table.
	*/
	void LoadFromMemory(GLuint* Pixels, GLsizei Width,
		GLint internalFormat, GLint clientsideFormat, GLsizei levels = 1, bool generateMipmap = false);

	/**
	@brief Initialize the texture from local pointers as a table.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the 1D texture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI, GL_RGBA...... etc. is expected.
	No default value is given. For it's supposed to be used as a table, it's up to
	programmers to decide what kind of format should be chosen in GLSL shaders.

	@param clientsideFormat The arrangement of the storage buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	No default value is given. For it's supposed to be used as a table, it's up to
	programmers to decide what kind of layout on the client side is used to feed the texture.

	@param levels The total amount of mipmap levels.
	By default it's set as 1, for it's a table.

	@param generateMipmap Tells OpenGL to generate mipmap automatically or not.
	By default it's set as false, for it's a table.
	*/
	void LoadFromMemory(GLint* Pixels, GLsizei Width,
		GLint internalFormat, GLint clientsideFormat, GLsizei levels = 1, bool generateMipmap = false);

	/**
	@brief Initialize the texture from local pointers as a table.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the 1D texture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI, GL_RGBA...... etc. is expected.
	No default value is given. For it's supposed to be used as a table, it's up to
	programmers to decide what kind of format should be chosen in GLSL shaders.

	@param clientsideFormat The arrangement of the storage buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	No default value is given. For it's supposed to be used as a table, it's up to
	programmers to decide what kind of layout on the client side is used to feed the texture.

	@param levels The total amount of mipmap levels.
	By default it's set as 1, for it's a table.

	@param generateMipmap Tells OpenGL to generate mipmap automatically or not.
	By default it's set as false, for it's a table.
	*/
	void LoadFromMemory(GLfloat* Pixels, GLsizei Width,
		GLint internalFormat, GLint clientsideFormat, GLsizei levels = 1, bool generateMipmap = false);

	/**
	@brief Initialize the texture from local pointers as a table.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the 1D texture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI, GL_RGBA...... etc. is expected.
	No default value is given. For it's supposed to be used as a table, it's up to
	programmers to decide what kind of format should be chosen in GLSL shaders.

	@param clientsideFormat The arrangement of the storage buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	No default value is given. For it's supposed to be used as a table, it's up to
	programmers to decide what kind of layout on the client side is used to feed the texture.

	@param levels The total amount of mipmap levels.
	By default it's set as 1, for it's a table.

	@param generateMipmap Tells OpenGL to generate mipmap automatically or not.
	By default it's set as false, for it's a table.
	*/
	void LoadFromMemory(GLdouble* Pixels, GLsizei Width,
		GLint internalFormat, GLint clientsideFormat, GLsizei levels = 1, bool generateMipmap = false);

	/**
	@brief Initialize the texture from local pointers as a table
	(Generic version in case you can't find the type you want).

	@param Pixels The pointer to the texture storage.

	@param Width The width of the 1D texture.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI, GL_RGBA...... etc. is expected.
	No default value is given. For it's supposed to be used as a table, it's up to
	programmers to decide what kind of format should be chosen in GLSL shaders.

	@param clientsideFormat The arrangement of the storage buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	No default value is given. For it's supposed to be used as a table, it's up to
	programmers to decide what kind of layout on the client side is used to feed the texture.

	@param type The type of the texels you provided from the client side.
	A value among GL_UNSIGNED_SHORT, GL_FLOAT...... etc. is expected.

	@param levels The total amount of mipmap levels.
	By default it's set as 1, for it's a table.

	@param generateMipmap Tells OpenGL to generate mipmap automatically or not.
	By default it's set as false, for it's a table.
	*/

	void LoadFromMemory(void* Pixels, GLsizei Width, GLint internalFormat,
		GLint clientsideFormat, GLenum type, GLsizei levels = 1, bool generateMipmap = false);
};
# endif