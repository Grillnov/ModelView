//
//  Texture2DArray.h
//  ModelView
//
//  Created by Bowen Yang on Sept 7, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# ifndef __ModelView__Texture2DArray__
# define __ModelView__Texture2DArray__

# include <TexturePack.h>

/**
@brief 2D texture fixed-size arrays.
*/
class Texture2DArray : public TexturePack
{
public:
	/**
	@brief Constructor that designates its binding slot and its slices.

	@param Slot The slot of the texture. To sample the texture in fragment shaders:
	Simply invoke texture() with the correspondent sampler assigned with the slot.
	An enumeration between GL_TEXTURE0 and GL_TEXTURE0 + GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS - 1 is expected.
	Note that a value between 0 and GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS - 1 is also recognized and accepted.

	@param Slices The amount of textures you need in this array.

	@param Width The width of all the textures.

	@param Height The height of all the textures.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI, GL_RGBA...... etc. is expected.
	By default it's set as GL_RGB32F.

	@param levels The total amount of mipmap levels.
	By default it's set as 4.

	@param generateMipmap Tells OpenGL to generate mipmap automatically or not.
	By default it's set as true, so that mipmaps are generated for you.
	*/
	Texture2DArray(GLenum Slot, GLsizei Slices, GLsizei Width, GLsizei Height,
		GLenum internalFormat = GL_RGB32F, GLsizei levels = 4, bool generateMipmaps = true) : 
		TexturePack(Slot, internalFormat, levels, generateMipmaps), AllPaths(std::vector<std::string>())
	{
		this->xWidth = Width;
		this->yHeight = Height;
		this->dDepth = Slices;
	}

	/**
	@brief Constructor that designates its binding slot and its slices with paths to pictures given.

	@param Slot The slot of the texture. To sample the texture in fragment shaders:
	Simply invoke texture() with the correspondent sampler assigned with the slot.
	An enumeration between GL_TEXTURE0 and GL_TEXTURE0 + GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS - 1 is expected.
	Note that a value between 0 and GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS - 1 is also recognized and accepted.

	@param Paths A list of all the slices of textures.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI, GL_RGBA...... etc. is expected.
	By default it's set as GL_RGB32F.

	@param levels The total amount of mipmap levels.
	By default it's set as 4.

	@param generateMipmap Tells OpenGL to generate mipmap automatically or not.
	By default it's set as true, so that mipmaps are generated for you.
	*/
	Texture2DArray(GLenum Slot, const std::vector<std::string>& Paths, GLsizei Width, GLsizei Height,
		GLenum internalFormat = GL_RGB32F, GLsizei levels = 4, bool generateMipmaps = true) :
		TexturePack(Slot, internalFormat, levels, generateMipmaps), AllPaths(Paths) 
	{
		this->xWidth = Width;
		this->yHeight = Height;
		this->dDepth = AllPaths.size();
	}

	/**
	@brief Initialize a slice of the texture array from local pointers.

	@param Pixels The pointer to the texture storage.

	@param Index The index of the slice.

	@param clientsideFormat The arrangement of the storage buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	By default it's set as GL_RGB.
	*/
	void LoadFromMemory(GLubyte* Pixels, GLsizei Index, GLenum clientsideFormat = GL_RGB);

	/**
	@brief Initialize a slice of the texture array from local pointers.

	@param Pixels The pointer to the texture storage.

	@param Index The index of the slice.

	@param clientsideFormat The arrangement of the storage buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	By default it's set as GL_RGB.
	*/
	void LoadFromMemory(GLbyte* Pixels, GLsizei Index, GLenum clientsideFormat = GL_RGB);

	/**
	@brief Initialize a slice of the texture array from local pointers.

	@param Pixels The pointer to the texture storage.

	@param Index The index of the slice.

	@param clientsideFormat The arrangement of the storage buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	By default it's set as GL_RGB.
	*/
	void LoadFromMemory(GLushort* Pixels, GLsizei Index, GLenum clientsideFormat = GL_RGB);

	/**
	@brief Initialize a slice of the texture array from local pointers.

	@param Pixels The pointer to the texture storage.

	@param Index The index of the slice.

	@param clientsideFormat The arrangement of the storage buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	By default it's set as GL_RGB.
	*/
	void LoadFromMemory(GLshort* Pixels, GLsizei Index, GLenum clientsideFormat = GL_RGB);

	/**
	@brief Initialize a slice of the texture array from local pointers.

	@param Pixels The pointer to the texture storage.

	@param Index The index of the slice.

	@param clientsideFormat The arrangement of the storage buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	By default it's set as GL_RGB.
	*/
	void LoadFromMemory(GLuint* Pixels, GLsizei Index, GLenum clientsideFormat = GL_RGB);

	/**
	@brief Initialize a slice of the texture array from local pointers.

	@param Pixels The pointer to the texture storage.

	@param Index The index of the slice.

	@param clientsideFormat The arrangement of the storage buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	By default it's set as GL_RGB.
	*/
	void LoadFromMemory(GLint* Pixels, GLsizei Index, GLenum clientsideFormat = GL_RGB);

	/**
	@brief Initialize a slice of the texture array from local pointers.

	@param Pixels The pointer to the texture storage.

	@param Index The index of the slice.

	@param clientsideFormat The arrangement of the storage buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	By default it's set as GL_RGB.
	*/
	void LoadFromMemory(GLfloat* Pixels, GLsizei Index, GLenum clientsideFormat = GL_RGB);

	/**
	@brief Initialize a slice of the texture array from local pointers.

	@param Pixels The pointer to the texture storage.

	@param Index The index of the slice.

	@param clientsideFormat The arrangement of the storage buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	By default it's set as GL_RGB.
	*/
	void LoadFromMemory(GLdouble* Pixels, GLsizei Index, GLenum clientsideFormat = GL_RGB);

	/**
	@brief Initialize a slice of the texture array from local pointers.
	(Generic version in case you can't find the type you want)

	@param Pixels The pointer to the texture storage.

	@param Index The index of the slice.

	@param clientsideFormat The arrangement of the storage buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	No default value is given. For it's supposed to be used as a table, it's up to
	programmers to decide what kind of layout on the client side is used to feed the texture.

	@param type The type of the texels you provided from the client side.
	A value among GL_UNSIGNED_SHORT, GL_FLOAT...... etc. is expected.
	*/
	void LoadFromMemory(void* Pixels, GLsizei Index, GLenum clientsideFormat, GLenum type);

	/**
	@brief Initialize the entire texture array from local pointers.
	(Generic version in case you can't find the type you want)

	@param Pixels The pointer to the texture storage.

	@param clientsideFormat The arrangement of the storage buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	No default value is given. For it's supposed to be used as a table, it's up to
	programmers to decide what kind of layout on the client side is used to feed the texture.

	@param type The type of the texels you provided from the client side.
	A value among GL_UNSIGNED_SHORT, GL_FLOAT...... etc. is expected.
	*/
	void LoadFromMemory(void* Pixels, GLint clientsideFormat, GLenum type);

	/**
	@brief Load the texels from a BMP file into a slice of the texture array.

	@param Index The index of the slice.

	@param clientsideFormat The arrangement of the local buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	By default it's set as GL_BGR, by default BMP protocol.
	*/
	void LoadFromBMP(GLsizei Index, GLenum clientsideFormat = GL_BGR);
private:
	std::vector<std::string> AllPaths;
};

# endif