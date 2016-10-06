//
//  Texture3D.h
//  ModelView
//
//  Created by Bowen Yang on Sept 7, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# ifndef __ModelView__Texture3D__
# define __ModelView__Texture3D__

# include <TexturePack.h>

/**
@brief 3D textures.
*/
class Texture3D : public TexturePack
{
public:
	/**
	@brief Constructor that designates its binding slot.

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
	Texture3D(GLenum Slot, GLenum internalFormat = GL_RGB32F, GLsizei levels = 4, bool generateMipmaps = true)
		: TexturePack(Slot, internalFormat, levels, generateMipmaps) {}

	/**
	@brief Initialize the texture from local pointers.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the 3D texture.

	@param Height The height of the 3D texture.

	@param Depth The depth of the 3D texture.

	@param clientsideFormat The arrangement of the storage buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	By default it's set as GL_RGB.
	*/
	void LoadFromMemory(GLubyte* Pixels, GLsizei Width, GLsizei Height, GLsizei Depth,
		GLenum clientsideFormat = GL_RGB);

	/**
	@brief Initialize the texture from local pointers.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the 3D texture.

	@param Height The height of the 3D texture.

	@param Depth The depth of the 3D texture.

	@param clientsideFormat The arrangement of the storage buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	By default it's set as GL_RGB.
	*/
	void LoadFromMemory(GLbyte* Pixels, GLsizei Width, GLsizei Height, GLsizei Depth,
		GLenum clientsideFormat = GL_RGB);

	/**
	@brief Initialize the texture from local pointers.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the 3D texture.

	@param Height The height of the 3D texture.

	@param Depth The depth of the 3D texture.

	@param clientsideFormat The arrangement of the storage buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	By default it's set as GL_RGB.
	*/
	void LoadFromMemory(GLushort* Pixels, GLsizei Width, GLsizei Height, GLsizei Depth,
		GLenum clientsideFormat = GL_RGB);

	/**
	@brief Initialize the texture from local pointers.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the 3D texture.

	@param Height The height of the 3D texture.

	@param Depth The depth of the 3D texture.

	@param clientsideFormat The arrangement of the storage buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	By default it's set as GL_RGB.
	*/
	void LoadFromMemory(GLshort* Pixels, GLsizei Width, GLsizei Height, GLsizei Depth,
		GLenum clientsideFormat = GL_RGB);

	/**
	@brief Initialize the texture from local pointers.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the 3D texture.

	@param Height The height of the 3D texture.

	@param Depth The depth of the 3D texture.

	@param clientsideFormat The arrangement of the storage buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	By default it's set as GL_RGB.
	*/
	void LoadFromMemory(GLuint* Pixels, GLsizei Width, GLsizei Height, GLsizei Depth,
		GLenum clientsideFormat = GL_RGB);

	/**
	@brief Initialize the texture from local pointers.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the 3D texture.

	@param Height The height of the 3D texture.

	@param Depth The depth of the 3D texture.

	@param clientsideFormat The arrangement of the storage buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	By default it's set as GL_RGB.
	*/
	void LoadFromMemory(GLint* Pixels, GLsizei Width, GLsizei Height, GLsizei Depth,
		GLenum clientsideFormat = GL_RGB);

	/**
	@brief Initialize the texture from local pointers.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the 3D texture.

	@param Height The height of the 3D texture.

	@param Depth The depth of the 3D texture.

	@param clientsideFormat The arrangement of the storage buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	By default it's set as GL_RGB.
	*/
	void LoadFromMemory(GLfloat* Pixels, GLsizei Width, GLsizei Height, GLsizei Depth,
		GLenum clientsideFormat = GL_RGB);

	/**
	@brief Initialize the texture from local pointers.

	@param Pixels The pointer to the texture storage.

	@param Width The width of the 3D texture.

	@param Height The height of the 3D texture.

	@param Depth The depth of the 3D texture.

	@param clientsideFormat The arrangement of the storage buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	By default it's set as GL_RGB.
	*/
	void LoadFromMemory(GLdouble* Pixels, GLsizei Width, GLsizei Height, GLsizei Depth,
		GLenum clientsideFormat = GL_RGB);

	/**
	@brief Initialize the texture from local pointers.
	(Generic version in case you can't find the type you want)

	@param Pixels The pointer to the texture storage.

	@param Width The width of the 3D texture.

	@param Height The height of the 3D texture.

	@param Depth The depth of the 3D texture.

	@param clientsideFormat The arrangement of the storage buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	No default value is given. For it's supposed to be used as a table, it's up to
	programmers to decide what kind of layout on the client side is used to feed the texture.

	@param type The type of the texels you provided from the client side.
	A value among GL_UNSIGNED_SHORT, GL_FLOAT...... etc. is expected.
	*/
	void LoadFromMemory(void* Pixels, GLsizei Width, GLsizei Height, GLsizei Depth,
		GLenum clientsideFormat, GLenum type);

	/**
	@brief (Re)Allocate memory for this 3D texture.

	@param Width The width of the 3D texture.

	@param Height The height of the 3D texture.

	@param Depth The depth of the 3D texture.
	*/
	void Alloc(GLsizei Width, GLsizei Height, GLsizei Depth);
};

# endif