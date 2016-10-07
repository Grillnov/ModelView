//
//  SamplerPack.h
//  ModelView
//
//  Created by Bowen Yang on Sept 7, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# ifndef __ModelView__SamplerPack__
# define __ModelView__SamplerPack__

# include <Options.h>

/**
@brief Samplers. You may want to add samplers for textures yourself, or just
use the default sampler and modify its parameters.
*/
class SamplerPack : public GLAsset
{
public:
	/**
	@brief Register the sampler.
	*/
	SamplerPack(GLsizei Slot);

	/**
	@brief Unregister the sampler, recycling its name for further usage.
	*/
	~SamplerPack();

	/**
	@brief Feed a single precision floating point parameter to the sampler.

	@param pname The name of the parameter.

	@param param The value of the parameter.
	*/
	void Param(GLenum pname, GLfloat param);

	/**
	@brief Feed an integer parameter to the sampler.

	@param pname The name of the parameter.

	@param param The value of the parameter.
	*/
	void Param(GLenum pname, GLint param);

	/**
	@brief Feed some single precision floating point parameters to the sampler.

	@param pname The name of the parameter.

	@param param The pointer to the value array of the parameter.
	*/
	void Param(GLenum pname, GLfloat* param);

	/**
	@brief Feed some integer parameters to the sampler.

	@param pname The name of the parameter.

	@param param The pointer to the value array of the parameter.
	*/
	void Param(GLenum pname, GLint* param);
private:
	GLenum Slot;
};

# endif