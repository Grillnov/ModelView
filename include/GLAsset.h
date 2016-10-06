//
//  GLAsset.h
//  ModelView
//
//  Created by Bowen Yang on Sept 23.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//
//

# include <Options.h>
# include <GLObject.h>

# ifndef __ModelView__GLAsset__
# define __ModelView__GLAsset__

/**
 * @brief Interface of an OpenGL asset with an ID created by glGen* or glCreate*.
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
	@brief Transformation to GLuint so that assets can be directly used as arguments to invoke raw GL interfaces.
	*/
	virtual operator GLuint()
	{
		return this->AssetID;
	}
};

# endif