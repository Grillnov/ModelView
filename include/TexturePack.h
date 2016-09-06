//
//  GLTexture.h
//  libOOGL
//
//  Created by Haoyan Huo on 3/20/15.
//  Copyright (c) 2015 Haoyan Huo. All rights reserved.
//

# ifndef TEXTUREPACK
# define TEXTUREPACK

# include <AllinGL.h>

class TexturePack : public GLObject, public GLAttachable
{
public:
	virtual GLuint GetSampler() = 0;
protected:
	virtual void Bind(GLenum target) = 0;
};

class TexturePack2D : public TexturePack
{

};

class TexturePackArray : public TexturePack
{

};

class TexturePackTable : public TexturePack
{
	
};

class TexturePackRect : public TexturePack
{

};
# endif