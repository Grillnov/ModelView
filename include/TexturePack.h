//
//  TexturePack.cpp
//  ModelView
//
//  Created by Bowen Yang on Sept 7, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# ifndef __ModelView__TexturePack__
# define __ModelView__TexturePack__

# include <AllinGL.h>
# include <unordered_set>

/**
Samplers. You may want to add samplers for textures yourself, or just
use the default sampler and modify its parameters.
*/
class SamplerPack : public GLAttachable
{
public:
	void Attach() override;
	void Detach() override;
	operator GLuint() override;

	void Param(GLenum target, GLfloat param);
	void Param(GLenum target, GLint param);
	void Param(GLenum target, GLfloat* param);
	void Param(GLenum target, GLint* param);
};

/**
Virtual base class for all kinds of textures.
*/
class TexturePack : public GLAttachable
{
public:
	/**
	@brief Default constructor.
	*/
	TexturePack() = default;
protected:
	/**
	Layout index for the sampler in GLSL.
	*/
	GLuint layout;

	/**
	Do not bind two texture objects to one binding slot.
	*/
	static std::unordered_set<GLenum> OccupiedLayouts;

	/**
	Convert to GLuint.
	*/
	operator GLuint() override;
};

/**
Base class for singular textures, initialized from BMPs or local pointers.
*/
class TexturePic : public TexturePack
{
public:
	/**
	@brief Default constructor.
	*/
	TexturePic();
protected:
	/**
	@brief Load the texture from a BMP file.
	*/
	void LoadFromBMP(std::string Path);
	/**
	@brief Set the way the texture is sampled.
	*/
	void Param(GLenum target, GLfloat param);
	void Param(GLenum target, GLint param);
	void Param(GLenum target, GLfloat* param);
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
	Number of channels.
	*/
	int Channel;
	/**
	The BMP pixel buffer.
	*/
	unsigned char *Buffer;
	/**
	Is the texture from a file? If so we have to recycle the buffer memory by ourselves...
	*/
	bool isFromFile;
};

/**
Base class for array textures, grouping multiple textures into an array.
*/
class TextureArr : public TexturePack
{
public:
	/**
	@brief Default constructor.
	*/
	TextureArr() = default;
protected:
	/**
	@brief Load the texture from a BMP file.
	*/
	void LoadFromBMP(std::string Path);
	/**
	@brief Set its parameters.
	*/
	void Param(GLenum target, GLfloat param);
	void Param(GLenum target, GLint param);
	void Param(GLenum target, GLfloat* param);
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
	Number of channels.
	*/
	int Channel;
	/**
	The BMP pixel buffer.
	*/
	char *Buffer;
};

/**
1D textures.
*/
class Texture1D : public TexturePic
{
public:
	/**
	@brief The default constructor
	*/
	Texture1D() = default;
	/**
	@brief Initialize the texture from local pointers.
	*/
	Texture1D(unsigned char* Buffer, size_t width, GLenum layout);
	/**
	@brief Initialize the texture from pictures.
	*/
	Texture1D(std::string Path, GLenum layout);

	void Attach() override;
	void Attach(GLint clientsideFormat, GLint internalFormat, bool generateMipMap = true);
	void Detach() override;
};

/**
2D textures.
*/
class Texture2D : public TexturePic
{
public:
	/**
	@brief The default constructor
	*/
	Texture2D() = default;
	/**
	@brief Initialize the texture from local pointers.
	*/
	Texture2D(unsigned char* pixels, size_t width, size_t height, GLenum layout);
	/**
	@brief Initialize the texture from pictures.
	*/
	Texture2D(std::string Path, GLenum layout);

	void Attach() override;
	void Attach(GLint clientsideFormat, GLint internalFormat, bool generateMipMap = true);
	void Detach() override;
};

/**
Rectangular textures.
*/
class TextureRect : public TexturePic
{
public:
	/**
	@brief The default constructor
	*/
	TextureRect() = default;
	/**
	@brief Initialize the texture from local pointers.
	*/
	TextureRect(unsigned char* pixels, size_t width, size_t height, GLenum layout);
	/**
	@brief Initialize the texture from pictures.
	*/
	TextureRect(std::string Path, GLenum layout);

	void Attach() override;
	void Attach(GLint clientsideFormat, GLint internalFormat);
	void Detach() override;
};

/**
Multisampling textures.
*/
class TextureMultiSamp : public TexturePic
{
public:
	/**
	@brief The default constructor
	*/
	TextureMultiSamp() = default;
	/**
	@brief Initialize the texture from local pointers.
	*/
	TextureMultiSamp(unsigned char* Buffer, size_t width, size_t height, GLenum layout);
	/**
	@brief Initialize the texture from pictures.
	*/
	TextureMultiSamp(std::string Path, GLenum layout);

	void Attach() override;
	void Attach(GLint clientsideFormat, GLint internalFormat, bool generateMipMap = true);
	void Detach() override;
};

/**
3D textures.
*/
class Texture3D : public TexturePic
{
public:
	/**
	@brief The default constructor
	*/
	Texture3D() = default;
	/**
	@brief Initialize the texture from local pointers.
	*/
	Texture3D(unsigned char* pixels, size_t width, size_t height, size_t depth, GLenum layout);

	void Attach() override;
	void Attach(GLint clientsideFormat, GLint internalFormat, bool generateMipMap = true);
	void Detach() override;
private:
	GLsizei dDepth;
};

/**
Cube maps.
*/
class TextureCube : public TextureArr
{
public:
	/**
	@brief The default constructor
	*/
	TextureCube() = default;
	/**
	@brief Initialize the texture from local pointers.
	*/
	TextureCube(unsigned char* Buffer, size_t width, size_t height);
	/**
	@brief Initialize the texture from pictures.
	*/
	TextureCube(std::string Path, GLenum layout);

	void Attach() override;
	void Attach(GLint internalFormat, GLboolean generateMipMap);
	void Detach() override;
};

/**
1D texture arrays.
*/
class Texture1DArray : public TexturePic
{
public:
	void Attach() override;
	void Detach() override;
private:
	void Bind(GLenum target);
	GLsizei size;
	int* Buffer;
};

/**
2D texture arrays.
*/
class Texture2DArray : public TexturePic
{
public:
	void Attach() override;
	void Detach() override;
private:
	void Bind(GLenum target);
	GLsizei size;
	int* Buffer;
};

# endif