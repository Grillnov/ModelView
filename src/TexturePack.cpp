//
//  TexturePack.cpp
//  ModelView
//
//  Created by Bowen Yang on Sept 7, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include <TexturePack.h>

TexturePack::operator GLuint()
{
	return this->AssetID;
}

void TexturePic::Param(GLenum target, GLfloat param)
{
	this->defaultSampler.Param(target, param);
}
void TexturePic::Param(GLenum target, GLint param)
{
	this->defaultSampler.Param(target, param);
}
void TexturePic::Param(GLenum target, GLfloat* param)
{
	this->defaultSampler.Param(target, param);
}
void TexturePic::Param(GLenum target, GLint* param)
{
	this->defaultSampler.Param(target, param);
}