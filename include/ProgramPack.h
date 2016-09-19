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

namespace ModelView
{
	class UniformFeeder : GLObject
	{
	public:
		GLint location;

		GLuint lastProgramID;

		UniformFeeder() = default;

		UniformFeeder(GLint location, GLuint lastProgramID)
			: location(location), lastProgramID(lastProgramID) {}

		//operator GLint() { return this->location; };

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
}

class ProgramPack : public GLAttachable
{
private:
	std::unordered_map<GLenum, ShaderPack*> ShaderTable;
	static GLuint ProgramUsedJustNow;

	GLint Fetch(std::string name);
public:
	/**
	@brief
	Create the program, so that its ID's registered.
	Compile all the shaders and attach them to the program.
	Finally link all these shaders into this program.
	*/
	void Attach() override;

	/**
	Delete the program.
	*/
	void Detach() override;

	/**
	Call glUseProgram to switch programs in effect between attached ones.
	*/
	void Use();

	/**
	Add some shaders to this program so that it knows where to start.
	Purely consists of client side invokes.
	*/
	void AddShader(std::string Path, GLenum type);

	/**
	Add some shaders, type told by its filename postfix.
	*/
	void AddShader(std::string Path);

	/**
	Reallocate its resources.
	*/
	~ProgramPack();

	/**
	A serie of functions that feeds the program with uniforms.
	*/
	void Uniform1(std::string name, GLfloat val);
	void Uniform1(std::string name, GLdouble val);
	void Uniform1(std::string name, GLint val);
	void Uniform1(std::string name, GLuint val);
	
	void Uniform2(std::string name, GLfloat* valLoc);
	void Uniform2(std::string name, GLdouble* valLoc);
	void Uniform2(std::string name, GLint* valLoc);
	void Uniform2(std::string name, GLuint* valLoc);
	void Uniform2(std::string name, const glm::vec2& val);
	void Uniform2(std::string name, const glm::dvec2& val);
	void Uniform2(std::string name, const glm::ivec2& val);
	void Uniform2(std::string name, const glm::u32vec2& val);

	void Uniform3(std::string name, GLfloat* valLoc);
	void Uniform3(std::string name, GLdouble* valLoc);
	void Uniform3(std::string name, GLint* valLoc);
	void Uniform3(std::string name, GLuint* valLoc);
	void Uniform3(std::string name, const glm::vec3& val);
	void Uniform3(std::string name, const glm::dvec3& val);
	void Uniform3(std::string name, const glm::ivec3& val);
	void Uniform3(std::string name, const glm::u32vec3& val);

	void Uniform4(std::string name, GLfloat* valLoc);
	void Uniform4(std::string name, GLdouble* valLoc);
	void Uniform4(std::string name, GLint* valLoc);
	void Uniform4(std::string name, GLuint* valLoc);
	void Uniform4(std::string name, const glm::vec4& val);
	void Uniform4(std::string name, const glm::dvec4& val);
	void Uniform4(std::string name, const glm::ivec4& val);
	void Uniform4(std::string name, const glm::u32vec4& val);

	/**
	A serie of functions that feeds the program with uniform matrices.
	@isTransposed is set to GL_TRUE by default, making the matrix row-major.
	GLM matrices are column-major so @isTransposed parameter is not needed.
	*/
	void UniformMat2(std::string name, GLfloat* valLoc, GLenum isTransposed = GL_TRUE);
	void UniformMat2(std::string name, GLdouble* valLoc, GLenum isTransposed = GL_TRUE);
	void UniformMat2(std::string name, const glm::mat2x2& val);
	void UniformMat2(std::string name, const glm::dmat2x2& val);

	void UniformMat3(std::string name, GLfloat* valLoc, GLenum isTransposed = GL_TRUE);
	void UniformMat3(std::string name, GLdouble* valLoc, GLenum isTransposed = GL_TRUE);
	void UniformMat3(std::string name, const glm::mat3x3& val);
	void UniformMat3(std::string name, const glm::dmat3x3& val);

	void UniformMat4(std::string name, GLfloat* valLoc, GLenum isTransposed = GL_TRUE);
	void UniformMat4(std::string name, GLdouble* valLoc, GLenum isTransposed = GL_TRUE);
	void UniformMat4(std::string name, const glm::mat4x4& val);
	void UniformMat4(std::string name, const glm::dmat4x4& val);

	/**
	Convert to GLuint.
	*/
	operator GLuint() override;

	/**
	Directly feed this program with uniforms by indices.
	*/
	ModelView::UniformFeeder operator[](const char* name);
};

# endif