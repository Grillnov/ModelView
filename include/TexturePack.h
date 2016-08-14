//
//  TexturePack.h
//  ModelView
//
//  Created by Bowen Yang on Aug 4, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# ifndef TEXTUREPACK
# define TEXTUREPACK

# include "AllinGL.h"
# include "BufferPack.hpp"
// OpenCV support

class TexturePack : public GLAttachable, public GLObject
{
private:
	BufferPack<GLfloat> *Texel;
public:
	GLboolean LoadFromFile(std::string InputFile);
};

# endif