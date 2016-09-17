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
# include <set>

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
protected:
	/**
	Layout index for the sampler in GLSL.
	*/
	GLuint layout;

	/**
	Do not bind two texture objects to one binding slot.
	*/
	static std::set<GLenum> OccupiedLayouts;

	/**
	@brief Convert to GLuint.
	*/
	operator GLuint() override;
};

/**
Textures that are used for 'textures', that is to say, they are sampled as pictures,
not arrays or tables.
*/
class TexturePic : public TexturePack
{
protected:
	/**
	Load the texture from a BMP file.
	*/
	void LoadFromBMP(std::string Path);

	/**
	Set its access parameters.
	*/
	void Param(GLenum target, GLfloat param);
	void Param(GLenum target, GLint param);
	void Param(GLenum target, GLfloat* param);
	void Param(GLenum target, GLint* param);

	~TexturePic();

	/**
	The default sampler.
	*/
	SamplerPack defaultSampler;

	GLsizei xWidth;
	GLsizei yHeight;
	int Channel;
	char *Buffer;
};

/**
1D textures.
Wait... Do we actually need this?
*/
/*
class Texture1D : public TexturePic
{
public:
	Texture1D(std::string Path, GLenum layout);

	void Attach() override;
	void Detach() override;
};
*/

/**
2D textures.
*/
class Texture2D : public TexturePic
{
public:
	Texture2D(std::string Path, GLenum layout);

	void Attach() override;
	void Attach(GLint internalFormat, GLboolean generateMipMap);
	void Detach() override;
};

class TextureRect : public TexturePic
{
public:
	TextureRect(std::string Path, GLenum layout);

	void Attach() override;
	void Attach(GLint internalFormat, GLboolean generateMipMap);
	void Detach() override;
};

class TextureCube : public TexturePic
{
public:
	TextureCube(std::string Path, GLenum layout);

	void Attach() override;
	void Attach(GLint internalFormat, GLboolean generateMipMap);
	void Detach() override;
};

class TextureMultiSamp : public TexturePic
{
public:
	TextureMultiSamp(std::string Path, GLenum layout);

	void Attach() override;
	void Attach(GLint internalFormat, GLboolean generateMipMap);
	void Detach() override;
};

/*
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
*/
# endif