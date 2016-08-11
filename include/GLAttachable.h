//
//  GLAttachable.h
//  ModelView
//
//  Created by Haoyan Huo on 3/27/15.
//  Copyright (c) 2015 Haoyan Huo. All rights reserved.
//
//  Modified by Bowen Yang

# include "AllinGL.h"

# ifndef GLATTACHABLE
# define GLATTACHABLE

/**
 * @brief Interface of a OpenGL attachable resource.
 *
 * A OpenGL resource in "Detached" mode means it's not in
 * OpenGL registry, however OpenGL objects could be created
 * by calling Attach().
 *
 * Before the OpenGL context is created, any call to gl* functions
 * is forbidden, but resources like meshes, textures could have buffer
 * prepared in memory, to reduce OpenGL object init time.
 */
class GLAttachable
{
protected:
	/**
	Its asset name on the server side.
	*/
	GLuint AssetID;
	/**
	To tell whether it's attached or not.
	*/
	bool isAttached;
public:
	GLAttachable() : AssetID(0), isAttached(false) {}
	/**
	Attach the asset, so that GL object is created on the server side
	*/
	virtual void Attach() = 0;
	/**
	Detach the asset, so that GL object ID is recycled.
	*/
	virtual void Detach() = 0;
	/**
	Telling whether it's attached.
	*/
	virtual bool IsAttached() { return this->isAttached; }

	GLuint getGLID(){ return this->AssetID; }
};

# endif