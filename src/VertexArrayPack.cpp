//
//  VertexArrayPack.h
//  ModelView
//
//  Created by Bowen Yang on Aug 20, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//
# include "VertexArrayPack.h"

void VertexArrayPack::Attach()
{
	if (this->isAttached)
	{
		Warning(debugMsg, "Vertexarray %u is already attached, bailing.", this->AssetID);
		return;
	}

	glCreateVertexArrays(1, &this->AssetID);

	for (auto i : this->FloatAttribs)
	{
		i.second->Attach(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
		i.second->Bind(GL_ARRAY_BUFFER);
	}
}