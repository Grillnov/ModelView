//
//  TexturePack.h
//  ModelView
//
//  Created by Bowen Yang on Sept 7, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# ifndef __ModelView__TexturePack__
# define __ModelView__TexturePack__

# include <AllinGL.h>
# include <vector>
# include <unordered_set>

/**
@brief Samplers. You may want to add samplers for textures yourself, or just
use the default sampler and modify its parameters.
*/
class SamplerPack : public GLAttachable
{
public:
	/**
	@brief Attach the sampler. Register its name.
	*/
	void Attach() override;

	/**
	@brief Detach the sampler. Recycling its name for further usage.
	*/
	void Detach() override;

	/**
	@brief Converter to GLuint, so that it can be directly used as an argument in raw GL interfaces.
	*/
	operator GLuint() override;

	/**
	@brief Feeding a single precision floating point parameter to the sampler.
	@param target The name of the parameter.
	@param param The value of the parameter.
	*/
	void Param(GLenum target, GLfloat param);

	/**
	@brief Feeding an integer parameter to the sampler.
	@param target The name of the parameter.
	@param param The value of the parameter.
	*/
	void Param(GLenum target, GLint param);

	/**
	@brief Feeding some single precision floating point parameters to the sampler.
	@param target The name of the parameter.
	@param param The pointer to the value array of the parameter.
	*/
	void Param(GLenum target, GLfloat* param);

	/**
	@brief Feeding some integer parameters to the sampler.
	@param target The name of the parameter.
	@param param The pointer to the value array of the parameter.
	*/
	void Param(GLenum target, GLint* param);
};

/**
@brief Virtual base class for all kinds of textures.
*/
class TexturePack : public GLAttachable
{
public:
	/**
	@brief Default constructor.
	*/
	TexturePack() = default;
protected:
	/**
	@brief Layout index of the sampler in GLSL shader source code.
	*/
	GLuint layout;

	/**
	@brief Preventing from binding two texture objects to one binding slot.
	*/
	static std::unordered_set<GLenum> OccupiedLayouts;

	/**
	@brief Converter to GLuint, so that it can be directly used as an argument in raw GL interfaces.
	*/
	operator GLuint() override;
};

/**
@brief Base class for singular textures, initialized from BMPs or local pointers.
*/
class TexturePic : public TexturePack
{
public:
	/**
	@brief Default constructor.
	*/
	TexturePic();
protected:
	/**
	@brief Load the texture from a BMP file.
	@param Path The path to the bmp file.
	*/
	void LoadFromBMP(std::string Path);

	/**
	@brief Set the texture parameters via the default sampler.
	Feeding a single precision floating point parameter to the sampler.
	@param target The name of the parameter.
	@param param The value of the parameter.
	*/
	void Param(GLenum target, GLfloat param);

	/**
	@brief Set the texture parameters via the default sampler.
	Feeding an integer parameter to the sampler.
	@param target The name of the parameter.
	@param param The value of the parameter.
	*/
	void Param(GLenum target, GLint param);

	/**
	@brief Set the texture parameters via the default sampler.
	Feeding some single precision floating point parameters to the sampler.
	@param target The name of the parameter.
	@param param The pointer to the value array of the parameter.
	*/
	void Param(GLenum target, GLfloat* param);

	/**
	@brief Set the texture parameters via the default sampler.
	Feeding some integer parameters to the sampler.
	@param target The name of the parameter.
	@param param The pointer to the value array of the parameter.
	*/
	void Param(GLenum target, GLint* param);

	/**
	@brief The default sampler.
	*/
	SamplerPack defaultSampler;

	/**
	@brief Its width.
	*/
	GLsizei xWidth;

	/**
	@brief Its height.
	*/
	GLsizei yHeight;

	/**
	@brief Number of channels.
	*/
	int Channel;

	/**
	@brief The temporary BMP pixel buffer storage pointer.
	*/
	unsigned char *Buffer;

	/**
	@brief Is the texture from a file? If so we have to recycle the buffer memory by ourselves...
	*/
	bool isFromFile;
};

/**
@brief Base class for array textures, grouping multiple textures into an array.
*/
class TextureArr : public TexturePack
{
public:
	/**
	@brief Default constructor.
	*/
	TextureArr() = default;
protected:
	/**
	@brief Load the texture from a BMP file.
	*/
	void LoadFromBMP(std::string Path);

	/**
	@brief Set its parameters.
	*/
	void Param(GLenum target, GLfloat param);

	void Param(GLenum target, GLint param);

	void Param(GLenum target, GLfloat* param);

	void Param(GLenum target, GLint* param);

	/**
	@brief The default sampler.
	*/
	SamplerPack defaultSampler;

	/**
	Width.
	*/
	GLsizei xWidth;

	/**
	Height.
	*/
	GLsizei yHeight;

	/**
	Number of channels.
	*/
	int Channel;

	/**
	The BMP pixel buffer.
	*/
	char *Buffer;
};

/**
@brief 1D textures.
*/
class Texture1D : public TexturePic
{
public:
	/**
	@brief Default constructor.
	*/
	Texture1D() = default;

	/**
	@brief Initialize the texture from local pointers.
	@param Buffer The pointer to the texture storage.
	@param width The width of the 1D texture.
	@param layout The index of the sampler in GLSL shader code.
	*/
	Texture1D(unsigned char* Buffer, size_t width, GLenum layout);

	/**
	@brief Initialize the texture from pictures.
	@param Path The path to the texture picture.
	@param layout The index of the sampler in GLSL shader code.
	*/
	Texture1D(std::string Path, GLenum layout);

	/**
	@brief Initialize the texture from pictures.
	internalFormat's set as GL_R8 by default, with client side arrangement set as GL_RED.
	*/
	void Attach() override;

	/**
	@brief Initialize the texture from pictures.
	@param clientsideFormat The arrangement of the local buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA...... etc. is expected.
	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI...... etc. is expected.
	@param generateMipmap Tells OpenGL to generate mipmap automatically or not.
	*/
	void Attach(GLint clientsideFormat, GLint internalFormat, bool generateMipMap = true);

	/**
	@brief Detach the texture, recycling its name for further usage.
	*/
	void Detach() override;
};

/**
@brief 2D textures.
*/
class Texture2D : public TexturePic
{
public:
	/**
	@brief Default constructor.
	*/
	Texture2D() = default;

	/**
	@brief Initialize the texture from local pointers.
	@param Buffer The pointer to the texture storage.
	@param width The width of the 2D texture.
	@param height The height of the 2D texture.
	@param layout The index of the sampler in GLSL shader code.
	*/
	Texture2D(unsigned char* pixels, size_t width, size_t height, GLenum layout);

	/**
	@brief Initialize the texture from pictures.
	@param Path The path to the texture picture.
	@param layout The index of the sampler in GLSL shader code.
	*/
	Texture2D(std::string Path, GLenum layout);

	/**
	@brief Initialize the texture from pictures.
	internalFormat's set as GL_RGB by default, with client side arrangement set as GL_BGR(default BMP protocol).
	*/
	void Attach() override;

	/**
	@brief Initialize the texture from pictures.
	@param clientsideFormat The arrangement of the local buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA...... etc. is expected.
	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI...... etc. is expected.
	@param generateMipmap Tells OpenGL to generate mipmap automatically or not.
	*/
	void Attach(GLint clientsideFormat, GLint internalFormat, bool generateMipMap = true);

	/**
	@brief Detach the texture, recycling its name for further usage.
	*/
	void Detach() override;
};

/**
@brief Rectangular textures.
*/
class TextureRect : public TexturePic
{
public:
	/**
	@brief Default constructor.
	*/
	TextureRect() = default;

	/**
	@brief Initialize the texture from local pointers.
	@param Buffer The pointer to the texture storage.
	@param width The width of the rectangular texture.
	@param height The height of the rectangular texture.
	@param layout The index of the sampler in GLSL shader code.
	*/
	TextureRect(unsigned char* pixels, size_t width, size_t height, GLenum layout);

	/**
	@brief Initialize the texture from pictures.
	@param Path The path to the texture picture.
	@param layout The index of the sampler in GLSL shader code.
	*/
	TextureRect(std::string Path, GLenum layout);

	/**
	@brief Initialize the texture from pictures.
	internalFormat's set as GL_R8 by default, with client side arrangement set as GL_RED.
	*/
	void Attach() override;

	/**
	@brief Initialize the texture from pictures.
	@param clientsideFormat The arrangement of the local buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA...... etc. is expected.
	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI...... etc. is expected.
	@param generateMipmap Tells OpenGL to generate mipmap automatically or not.
	*/
	void Attach(GLint clientsideFormat, GLint internalFormat);

	/**
	@brief Detach the texture, recycling its name for further usage.
	*/
	void Detach() override;
};

/**
@brief Multisampling textures.
*/
class TextureMultiSamp : public TexturePic
{
public:
	/**
	@brief Default constructor.
	*/
	TextureMultiSamp() = default;

	/**
	@brief Initialize the texture from local pointers.
	@param Buffer The pointer to the texture storage.
	@param width The width of the 2D texture.
	@param height The height of the 2D texture.
	@param layout The index of the sampler in GLSL shader code.
	*/
	TextureMultiSamp(unsigned char* Buffer, size_t width, size_t height, GLenum layout);

	/**
	@brief Initialize the texture from pictures.
	*/
	TextureMultiSamp(std::string Path, GLenum layout);

	void Attach() override;

	void Attach(GLint clientsideFormat, GLint internalFormat, bool generateMipMap = true);

	void Detach() override;
};

/**
@brief 3D textures.
*/
class Texture3D : public TexturePic
{
public:
	/**
	@brief Default constructor.
	*/
	Texture3D() = default;

	/**
	@brief Initialize the texture from local pointers.
	@param Buffer The pointer to the texture storage.
	@param width The width of the 3D texture.
	@param height The height of the 3D texture.
	@param depth The depth of the 3D texture.
	@param layout The index of the sampler in GLSL shader code.
	*/
	Texture3D(unsigned char* pixels, size_t width, size_t height, size_t depth, GLenum layout);

	/**
	@brief Initialize the texture from pictures.
	internalFormat's set as GL_R8 by default, with client side arrangement set as GL_RED.
	*/
	void Attach() override;

	/**
	@brief Initialize the texture from pictures.
	@param clientsideFormat The arrangement of the local buffer on the client side.
	A value among GL_RED, GL_RGB, GL_BGRA...... etc. is expected.
	@param internalFormat The storage format on the server side.
	A value among GL_R8, GL_RGB32F, GL_RG8UI...... etc. is expected.
	@param generateMipmap Tells OpenGL to generate mipmap automatically or not.
	*/
	void Attach(GLint clientsideFormat, GLint internalFormat, bool generateMipMap = true);

	/**
	@brief Detach the texture, recycling its name for further usage.
	*/
	void Detach() override;
private:
	GLsizei dDepth;
};

/**
@brief Cube maps.
*/
class TextureCube : public TextureArr
{
public:
	/**
	@brief The default constructor
	*/
	TextureCube() = default;
	/**
	@brief Initialize the texture from local pointers.
	*/
	TextureCube(unsigned char* Buffer, size_t width, size_t height);
	/**
	@brief Initialize the texture from pictures.
	*/
	TextureCube(std::string Path, GLenum layout);

	void Attach() override;
	void Attach(GLint internalFormat, GLboolean generateMipMap);
	void Detach() override;
};

/**
@brief 1D texture arrays.
*/
class Texture1DArray : public TexturePic
{
public:
	void Attach() override;
	void Detach() override;
private:
	void Bind(GLenum target);
	GLsizei size;
	int* Buffer;
};

/**
@brief 2D texture arrays.
*/
class Texture2DArray : public TexturePic
{
public:
	void Attach() override;
	void Detach() override;
private:
	void Bind(GLenum target);
	GLsizei size;
	int* Buffer;
};

# endif