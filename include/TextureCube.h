//
//  TextureCube.h
//  ModelView
//
//  Created by Bowen Yang on Sept 7, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# ifndef __ModelView__TextureCube__
# define __ModelView__TextureCube__

# include <TexturePack.h>

/**
@brief Cube maps.
*/
class TextureCube : public TextureArr
{
public:
	/**
	@brief Constructor that designates its binding slot and its slices.

	@param Slot The slot of the texture. To sample the texture in fragment shaders:
	Simply invoke texture() with the correspondent sampler assigned with the slot.
	An enumeration between GL_TEXTURE0 and GL_TEXTURE0 + GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS - 1 is expected.
	Note that a value between 0 and GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS - 1 is also recognized and accepted.

	@param Width The width of all the textures.

	@param Height The height of all the textures.

	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI, GL_RGBA...... etc. is expected.
	*/
	TextureCube(GLenum Slot, GLsizei Width, GLsizei Height, GLenum internalFormat) : TextureArr(Slot, 6)
	{
		glBindTexture(GL_TEXTURE_1D_ARRAY, this->AssetID);

		this->xWidth = Width;

		glTexStorage2D(GL_TEXTURE_1D_ARRAY, 1, internalFormat, xWidth, sSlices);

		glActiveTexture(GL_TEXTURE0 + layoutSlot);

		CheckStatus(__FUNCTION__);

		glBindTexture(GL_TEXTURE_1D_ARRAY, this->AssetID);
		glBindSampler(layoutSlot, defaultSampler);

		Param(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		Param(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		Param(GL_TEXTURE_WRAP_S, GL_REPEAT);

		CheckStatus(__FUNCTION__);

		Log(debugMsg, "1D texture array %u was successfully attached at layout slot %u.", this->AssetID, this->layoutSlot);
	}

	void LoadLeftPlane(std::string Path, GLint clientsideFormat = GL_BGR,
		GLint internalFormat = GL_RGB, GLsizei levels = 2, bool generateMipMap = true);

	void LoadRightPlane(std::string Path, GLint clientsideFormat = GL_BGR,
		GLint internalFormat = GL_RGB, GLsizei levels = 2, bool generateMipMap = true);

	void LoadFrontPlane(std::string Path, GLint clientsideFormat = GL_BGR,
		GLint internalFormat = GL_RGB, GLsizei levels = 2, bool generateMipMap = true);

	void LoadBackPlane(std::string Path, GLint clientsideFormat = GL_BGR,
		GLint internalFormat = GL_RGB, GLsizei levels = 2, bool generateMipMap = true);

	void LoadTopPlane(std::string Path, GLint clientsideFormat = GL_BGR,
		GLint internalFormat = GL_RGB, GLsizei levels = 2, bool generateMipMap = true);

	void LoadBottomPlane(std::string Path, GLint clientsideFormat = GL_BGR,
		GLint internalFormat = GL_RGB, GLsizei levels = 2, bool generateMipMap = true);
};
# endif