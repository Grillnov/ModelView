//
//  GLAsset.h
//  ModelView
//
//  Created by Bowen Yang on Sept 23.
//  Copyright (c) 2015 Haoyan Huo. All rights reserved.
//
//  Modified by Bowen Yang

# include <Options.h>
# include <GLObject.h>

# ifndef __ModelView__GLAsset__
# define __ModelView__GLAsset__

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
class GLAsset : public GLObject
{
protected:
	/**
	@brief Its OpenGL asset name on the server side.
	*/
	GLuint AssetID;
	/**
	@brief To tell whether it's ready or not.
	*/
	bool isReady;
public:
	/**
	@brief Default constructor.
	*/
	GLAsset() : AssetID(0), isReady(false) {}
	/**
	@brief Attach the asset, so that GL object is created on the server side
	*/
	//virtual void Attach() = 0;
	/**
	@brief Detach the asset, so that GL object ID can be reused.
	*/
	//virtual void Detach() = 0;
	/**
	@brief Telling whether it's attached.
	*/
	virtual bool IsReady()
	{
		return this->isReady;
	}
	/**
	@brief Transformation to GLuint so that assets can be directly used as arguments to invoke raw GL interfaces.
	*/
	virtual operator GLuint()
	{
		return this->AssetID;
	}
};

# endif