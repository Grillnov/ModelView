//
//  BufferPack.cpp
//  ModelView
//
//  Created by Bowen Yang on Aug 4, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include "BufferPack.h"

BufferPack::BufferPack() : isUploaded(false), LocalPtr(nullptr), BufferSize(0) {}

BufferPack::BufferPack(void* Ptr, size_t Size) : isUploaded(false), LocalPtr(Ptr), BufferSize(Size) {}

BufferPack::BufferPack(size_t Size) : isUploaded(false), BufferSize(Size)
{
	this->LocalPtr = new char[Size];
}

void BufferPack::Attach()
{
	if (this->isAttached)
	{
		Warning(debugMsg, "Buffer %u is already attached, bailing.", this->AssetID);
		return;
	}
	glCreateBuffers(1, &this->AssetID);
	CheckStatus(__FUNCTION__);
	Log(debugMsg, "Attached buffer %u", this->AssetID);
	this->isAttached = true;
}

void BufferPack::Detach()
{
	if (!this->isAttached)
	{
		Warning(debugMsg, "Buffer %u is not attached yet, bailing.", this->AssetID);
		return;
	}
	glDeleteBuffers(1, &this->AssetID);
	CheckStatus(__FUNCTION__);
	Log(debugMsg, "Detached buffer %u", this->AssetID);
	this->isAttached = false;
}

BufferPack::~BufferPack()
{
	if (this->isAttached)
	{
		Warning(debugMsg, "Buffer %u isn't detached before destruction, risk of causing memory leakage on server side.", this->AssetID);
	}
	delete[] this->LocalPtr;
}

void BufferPack::Upload2Server(GLenum bindingPoint, GLenum usage)
{
	if (!this->isUploaded)
	{
		glBufferData(bindingPoint, this->BufferSize, this->LocalPtr, usage);
		this->isUploaded = true;
		CheckStatus(__FUNCTION__);
		Log(debugMsg, "Successfully uploaded %u bytes of data to buffer %u.", this->BufferSize, this->AssetID);
	}
	else
	{
		Warning(debugMsg, "Buffer %u has already been sent to the server, bailing.", this->AssetID);
	}
}