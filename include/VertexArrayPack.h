//
//  VertexArrayPack.h
//  ModelView
//
//  Created by Bowen Yang on Aug 20, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# ifndef VERTEXARRAYPACK
# define VERTEXARRAYPACK

# include "AllinGL.h"
# include "BufferPack.hpp"
# include <map>

class VertexArrayPack : public GLObject, public GLAttachable
{
private:
	/**
	Due to the botched GL interface design, we'll have to
	include two sets of map, one corresponding to floating
	point attributes, one corresponding to integer attributes.
	*/
	std::map<GLuint, BufferPack<GLfloat>*> FloatAttribs;
	std::map<GLuint, BufferPack<GLint>*> IntAttribs;
public:
	void Attach() override;
	void Detach() override;
	void AddBufferWithIndex(BufferPack<GLfloat>* buffer, GLuint index);
	void AddBufferWithIndex(BufferPack<GLint>* buffer, GLuint index);
};

# endif