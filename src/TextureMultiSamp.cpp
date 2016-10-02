//
//  TextureMultiSamp.h
//  ModelView
//
//  Created by Bowen Yang on Sept 7, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# ifndef __ModelView__TextureMultiSamp__
# define __ModelView__TextureMultiSamp__

# include <TexturePack.h>

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
	By default it's set as 4.

	@param generateMipmap Tells OpenGL to generate mipmap automatically or not.
	By default it's set as true, so that mipmaps are generated for you.
	*/
	void LoadFromMemory(unsigned char* Pixels, size_t Width, size_t Height,
		GLint internalFormat = GL_RGB32F, GLint clientsideFormat = GL_RGB, GLsizei levels = 4, bool generateMipMap = true);

	/**
	@brief Load the texels from BMP files.

	@param Path The path to the texture picture.

	@param clientsideFormat The arrangement of the local buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA, GL_RGBA_INTEGER...... etc. is expected.
	By default it's set as GL_BGR, by default BMP protocol.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI...... etc. is expected.

	@param levels The total amount of mipmap levels.
	By default it's set as 4.

	@param generateMipmap Tells OpenGL to generate mipmap automatically or not.
	By default it's set as true, so that mipmaps are generated for you.
	*/
	void LoadFromBMP(std::string Path, GLint clientsideFormat = GL_BGR,
		GLint internalFormat = GL_RGB32F, GLsizei levels = 4, bool generateMipMap = true);
};
# endif