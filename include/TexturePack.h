//
//  TexturePack.cpp
//  ModelView
//
//  Created by Bowen Yang on Sept 7, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# ifndef TEXTUREPACK
# define TEXTUREPACK

# include <AllinGL.h>
# include <set>

/**
Samplers. You may want to add samplers for textures yourself, or just
use the default sampler and modify its parameters.
*/
class SamplerPack : public GLObject, public GLAttachable
{
public:
	void Attach() override;
	void Detach() override;

	operator GLuint();

	void Param(GLenum target, GLfloat param);
	void Param(GLenum target, GLint param);
	void Param(GLenum target, GLfloat* param);
	void Param(GLenum target, GLint* param);
private:
	GLuint bindedTarget;
};

/**
Virtual base class for all kinds of textures.
*/
class TexturePack : public GLObject, public GLAttachable
{
public:
	operator GLuint();
protected:
	/**
	Layout index for the sampler in GLSL.
	*/
	GLuint layout;

	/**
	Do not bind two texture objects to one binding point.
	*/
	static std::set<GLenum> bindedTextures;

	/**
	Query which texture binding point is active right now.
	*/
	static GLenum currentActiveTex;
};

/**
Textures that are used for 'textures', that is to say, they are sampled as pictures,
not arrays or tables.
*/
class TexturePic : public TexturePack
{
public:
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
private:
	/**
	The default sampler.
	*/
	SamplerPack defaultSampler;

	GLsizei xWidth;
	GLsizei yHeight;
	int Channel;
	int *Buffer;
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
	void Detach() override;
};

class TextureRect : public TexturePic
{
public:
	TextureRect(std::string Path, GLenum layout);

	void Attach() override;
	void Detach() override;
};

class TextureCube : public TexturePic
{
public:
	TextureCube(std::string Path, GLenum layout);

	void Attach() override;
	void Detach() override;
};

class TextureMultiSamp : public TexturePic
{
public:
	TextureMultiSamp(std::string Path, GLenum layout);

	void Attach() override;
	void Detach() override;
};
# endif