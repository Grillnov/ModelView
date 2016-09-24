//
//  ProgramPack.h
//  ModelView
//
//  Created by Bowen Yang on Aug 13, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# ifndef __ModelView__ProgramPack__
# define __ModelView__ProgramPack__

# include <AllinGL.h>
# include <ShaderPack.h>
# include <unordered_map>

class ProgramPack;

/**
@brief Uniform injector.
*/
class UniformFeeder : public GLObject
{
public:
	GLint location;

	GLuint lastProgramID;

	UniformFeeder() = default;

	UniformFeeder(GLint location, GLuint lastProgramID)
		: location(location), lastProgramID(lastProgramID) {}

	GLfloat operator=(GLfloat val);
	GLdouble operator=(GLdouble val);
	GLint operator=(GLint val);
	GLuint operator=(GLuint val);

	glm::vec2 operator=(const glm::vec2& val);
	glm::dvec2 operator=(const glm::dvec2& val);
	glm::ivec2 operator=(const glm::ivec2& val);
	glm::u32vec2 operator=(const glm::u32vec2& val);

	glm::vec3 operator=(const glm::vec3& val);
	glm::dvec3 operator=(const glm::dvec3& val);
	glm::ivec3 operator=(const glm::ivec3& val);
	glm::u32vec3 operator=(const glm::u32vec3& val);

	glm::vec4 operator=(const glm::vec4& val);
	glm::dvec4 operator=(const glm::dvec4& val);
	glm::ivec4 operator=(const glm::ivec4& val);
	glm::u32vec4 operator=(const glm::u32vec4& val);

	glm::mat2x2 operator=(const glm::mat2x2& val);
	glm::dmat2x2 operator=(const glm::dmat2x2& val);

	glm::mat3x3 operator=(const glm::mat3x3& val);
	glm::dmat3x3 operator=(const glm::dmat3x3& val);

	glm::mat4x4 operator=(const glm::mat4x4& val);
	glm::dmat4x4 operator=(const glm::dmat4x4& val);
};

/**
@brief Shader injector.
*/
class ShaderFeeder : public GLObject
{
private:
	GLenum type;
	ProgramPack* ptr;
public:
	ShaderFeeder(GLenum type, ProgramPack* ptr) : type(type), ptr(ptr) {}
	const char* operator=(const char* Path);
};

/**
@brief Program object that loads, compiles and links several shaders into a GLSL program.
*/
class ProgramPack : public GLAttachable
{
private:
	std::unordered_map<GLenum, ShaderPack*> ShaderTable;
	static GLuint ProgramUsedJustNow;

	GLint Fetch(std::string name);
public:
	/**
	@brief Create the program, so that its ID's registered.
	Compile all the shaders and link them to the program.
	*/
	void Attach() override;

	/**
	@brief Delete the program ID, so that its name can be recycled.
	*/
	void Detach() override;

	/**
	@brief Call glUseProgram to switch programs in effect between the attached programs.
	*/
	void Use();

	/**
	@brief Add some shaders to this program so that it knows where to start.
	Purely consists of client side invokes.
	@param Path The path to the shader source file.
	@param type The type of the shader. A value among GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, etc. is expected.
	*/
	void AddShader(std::string Path, GLenum type);

	/**
	@brief Add some shaders, type told by its filename postfix.
	@param Path The path to the shader source file.
	*/
	void AddShader(std::string Path);

	/**
	@brief Recycle its memory, preventing leakage.
	*/
	~ProgramPack();

	/**
	@brief Feed the program with 1 uniform value(single precision).
	@param name Its variable name in the shader source code.
	@param val The value of the uniform.
	*/
	void Uniform1(std::string name, GLfloat val);

	/**
	@brief Feed the program with 1 uniform value(double precision).
	@param name Its variable name in the shader source code.
	@param val The value of the uniform.
	*/
	void Uniform1(std::string name, GLdouble val);

	/**
	@brief Feed the program with 1 uniform value(signed integer).
	@param name Its variable name in the shader source code.
	@param val The value of the uniform.
	*/
	void Uniform1(std::string name, GLint val);

	/**
	@brief Feed the program with 1 uniform value(unsigned integer).
	@param name Its variable name in the shader source code.
	@param val The value of the uniform.
	*/
	void Uniform1(std::string name, GLuint val);
	
	/**
	@brief Feed the program with 2 uniform values(single precision).
	@param name Its variable name in the shader source code.
	@param valLoc The pointer to the value array of the uniform.
	*/
	void Uniform2(std::string name, GLfloat* valLoc);

	/**
	@brief Feed the program with 2 uniform values(double precision).
	@param name Its variable name in the shader source code.
	@param valLoc The pointer to the value array of the uniform.
	*/
	void Uniform2(std::string name, GLdouble* valLoc);

	/**
	@brief Feed the program with 2 uniform values(signed integer).
	@param name Its variable name in the shader source code.
	@param valLoc The pointer to the value array of the uniform.
	*/
	void Uniform2(std::string name, GLint* valLoc);

	/**
	@brief Feed the program with 2 uniform values(unsigned integer).
	@param name Its variable name in the shader source code.
	@param valLoc The pointer to the value array of the uniform.
	*/
	void Uniform2(std::string name, GLuint* valLoc);

	/**
	@brief Feed the program with 2 uniform values(single precision).
	@param name Its variable name in the shader source code.
	@param val The value of the uniform as a vector.
	*/
	void Uniform2(std::string name, const glm::vec2& val);

	/**
	@brief Feed the program with 2 uniform values(double precision).
	@param name Its variable name in the shader source code.
	@param val The value of the uniform as a vector.
	*/
	void Uniform2(std::string name, const glm::dvec2& val);

	/**
	@brief Feed the program with 2 uniform values(signed integer).
	@param name Its variable name in the shader source code.
	@param val The value of the uniform as a vector.
	*/
	void Uniform2(std::string name, const glm::ivec2& val);

	/**
	@brief Feed the program with 2 uniform values(unsigned 32bit integer).
	@param name Its variable name in the shader source code.
	@param val The value of the uniform as a vector.
	*/
	void Uniform2(std::string name, const glm::u32vec2& val);

	/**
	@brief Feed the program with 3 uniform values(single precision).
	@param name Its variable name in the shader source code.
	@param valLoc The pointer to the value array of the uniform.
	*/
	void Uniform3(std::string name, GLfloat* valLoc);

	/**
	@brief Feed the program with 3 uniform values(double precision).
	@param name Its variable name in the shader source code.
	@param valLoc The pointer to the value array of the uniform.
	*/
	void Uniform3(std::string name, GLdouble* valLoc);

	/**
	@brief Feed the program with 3 uniform values(signed integer).
	@param name Its variable name in the shader source code.
	@param valLoc The pointer to the value array of the uniform.
	*/
	void Uniform3(std::string name, GLint* valLoc);

	/**
	@brief Feed the program with 3 uniform values(unsigned integer).
	@param name Its variable name in the shader source code.
	@param valLoc The pointer to the value array of the uniform.
	*/
	void Uniform3(std::string name, GLuint* valLoc);

	/**
	@brief Feed the program with 3 uniform values(single precision).
	@param name Its variable name in the shader source code.
	@param val The value of the uniform as a vector.
	*/
	void Uniform3(std::string name, const glm::vec3& val);

	/**
	@brief Feed the program with 3 uniform values(double precision).
	@param name Its variable name in the shader source code.
	@param val The value of the uniform as a vector.
	*/
	void Uniform3(std::string name, const glm::dvec3& val);

	/**
	@brief Feed the program with 3 uniform values(signed integer).
	@param name Its variable name in the shader source code.
	@param val The value of the uniform as a vector.
	*/
	void Uniform3(std::string name, const glm::ivec3& val);

	/**
	@brief Feed the program with 3 uniform values(unsigned 32bit integer).
	@param name Its variable name in the shader source code.
	@param val The value of the uniform as a vector.
	*/
	void Uniform3(std::string name, const glm::u32vec3& val);

	/**
	@brief Feed the program with 4 uniform values(single precision).
	@param name Its variable name in the shader source code.
	@param valLoc The pointer to the value array of the uniform.
	*/
	void Uniform4(std::string name, GLfloat* valLoc);

	/**
	@brief Feed the program with 4 uniform values(double precision).
	@param name Its variable name in the shader source code.
	@param valLoc The pointer to the value array of the uniform.
	*/
	void Uniform4(std::string name, GLdouble* valLoc);

	/**
	@brief Feed the program with 4 uniform values(signed integer).
	@param name Its variable name in the shader source code.
	@param valLoc The pointer to the value array of the uniform.
	*/
	void Uniform4(std::string name, GLint* valLoc);

	/**
	@brief Feed the program with 4 uniform values(unsigned integer).
	@param name Its variable name in the shader source code.
	@param valLoc The pointer to the value array of the uniform.
	*/
	void Uniform4(std::string name, GLuint* valLoc);

	/**
	@brief Feed the program with 4 uniform values(single precision).
	@param name Its variable name in the shader source code.
	@param val The value of the uniform as a vector.
	*/
	void Uniform4(std::string name, const glm::vec4& val);

	/**
	@brief Feed the program with 4 uniform values(double precision).
	@param name Its variable name in the shader source code.
	@param val The value of the uniform as a vector.
	*/
	void Uniform4(std::string name, const glm::dvec4& val);

	/**
	@brief Feed the program with 4 uniform values(signed integer).
	@param name Its variable name in the shader source code.
	@param val The value of the uniform as a vector.
	*/
	void Uniform4(std::string name, const glm::ivec4& val);

	/**
	@brief Feed the program with 4 uniform values(unsigned 32bit integer).
	@param name Its variable name in the shader source code.
	@param val The value of the uniform as a vector.
	*/
	void Uniform4(std::string name, const glm::u32vec4& val);

	/**
	@brief Feed the program with a 2x2 uniform matrix(single precision).
	isTransposed is set to GL_TRUE by default, making the matrix row-major.
	@param name Its variable name in the shader source code.
	@param valLoc The pointer to the value array of the uniform.
	@param isTransposed Setting this argument as GL_TRUE will make the matrix row-major. Otherwise column-major.
	*/
	void UniformMat2(std::string name, GLfloat* valLoc, GLenum isTransposed = GL_TRUE);

	/**
	@brief Feed the program with a 2x2 uniform matrix(double precision).
	isTransposed is set to GL_TRUE by default, making the matrix row-major.
	@param name Its variable name in the shader source code.
	@param valLoc The pointer to the value array of the uniform.
	@param isTransposed Setting this argument as GL_TRUE will make the matrix row-major. Otherwise column-major.
	*/
	void UniformMat2(std::string name, GLdouble* valLoc, GLenum isTransposed = GL_TRUE);

	/**
	@brief Feed the program with a 2x2 uniform matrix(single precision).
	isTransposed is set to GL_TRUE by default, making the matrix row-major.
	GLM matrices are column-major so @isTransposed parameter is not needed.
	@param name Its variable name in the shader source code.
	@param val The value of the uniform as a matrix.
	*/
	void UniformMat2(std::string name, const glm::mat2x2& val);

	/**
	@brief Feed the program with a 2x2 uniform matrix(double precision).
	isTransposed is set to GL_TRUE by default, making the matrix row-major.
	GLM matrices are column-major so @isTransposed parameter is not needed.
	@param name Its variable name in the shader source code.
	@param val The value of the uniform as a vector.
	*/
	void UniformMat2(std::string name, const glm::dmat2x2& val);

	/**
	@brief Feed the program with a 3x3 uniform matrix(single precision).
	isTransposed is set to GL_TRUE by default, making the matrix row-major.
	@param name Its variable name in the shader source code.
	@param valLoc The pointer to the value array of the uniform.
	@param isTransposed Setting this argument as GL_TRUE will make the matrix row-major. Otherwise column-major.
	*/
	void UniformMat3(std::string name, GLfloat* valLoc, GLenum isTransposed = GL_TRUE);

	/**
	@brief Feed the program with a 3x3 uniform matrix(double precision).
	isTransposed is set to GL_TRUE by default, making the matrix row-major.
	@param name Its variable name in the shader source code.
	@param valLoc The pointer to the value array of the uniform.
	@param isTransposed Setting this argument as GL_TRUE will make the matrix row-major. Otherwise column-major.
	*/
	void UniformMat3(std::string name, GLdouble* valLoc, GLenum isTransposed = GL_TRUE);

	/**
	@brief Feed the program with a 3x3 uniform matrix(single precision).
	isTransposed is set to GL_TRUE by default, making the matrix row-major.
	GLM matrices are column-major so @isTransposed parameter is not needed.
	@param name Its variable name in the shader source code.
	@param val The value of the uniform as a vector.
	*/
	void UniformMat3(std::string name, const glm::mat3x3& val);

	/**
	@brief Feed the program with a 3x3 uniform matrix(double precision).
	isTransposed is set to GL_TRUE by default, making the matrix row-major.
	GLM matrices are column-major so @isTransposed parameter is not needed.
	@param name Its variable name in the shader source code.
	@param val The value of the uniform as a vector.
	*/
	void UniformMat3(std::string name, const glm::dmat3x3& val);

	/**
	@brief Feed the program with a 4x4 uniform matrix(single precision).
	isTransposed is set to GL_TRUE by default, making the matrix row-major.
	@param name Its variable name in the shader source code.
	@param valLoc The pointer to the value array of the uniform.
	@param isTransposed Setting this argument as GL_TRUE will make the matrix row-major. Otherwise column-major.
	*/
	void UniformMat4(std::string name, GLfloat* valLoc, GLenum isTransposed = GL_TRUE);

	/**
	@brief Feed the program with a 4x4 uniform matrix(double precision).
	isTransposed is set to GL_TRUE by default, making the matrix row-major.
	@param name Its variable name in the shader source code.
	@param valLoc The pointer to the value array of the uniform.
	@param isTransposed Setting this argument as GL_TRUE will make the matrix row-major. Otherwise column-major.
	*/
	void UniformMat4(std::string name, GLdouble* valLoc, GLenum isTransposed = GL_TRUE);

	/**
	@brief Feed the program with a 4x4 uniform matrix(single precision).
	isTransposed is set to GL_TRUE by default, making the matrix row-major.
	GLM matrices are column-major so @isTransposed parameter is not needed.
	@param name Its variable name in the shader source code.
	@param val The value of the uniform as a vector.
	*/
	void UniformMat4(std::string name, const glm::mat4x4& val);

	/**
	@brief Feed the program with a 4x4 uniform matrix(double precision).
	isTransposed is set to GL_TRUE by default, making the matrix row-major.
	GLM matrices are column-major so @isTransposed parameter is not needed.
	@param name Its variable name in the shader source code.
	@param val The value of the uniform as a vector.
	*/
	void UniformMat4(std::string name, const glm::dmat4x4& val);

	/**
	@brief Converter to GLuint, so that it can be directly used as an argument in raw GL interfaces.
	*/
	operator GLuint() override;

	/**
	@brief Directly feed this program with uniforms by indices.
	@param name Its variable name in the shader source code.
	*/
	UniformFeeder operator[](const char* name);

	/**
	@brief Directly feed this program with shaders.
	@param type The shader's type. A value among GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, etc. is expected.
	*/
	ShaderFeeder operator[](GLenum type);
};

# endif