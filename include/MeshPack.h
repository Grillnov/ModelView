//
//  MeshPack.h
//  ModelView
//
//  Created by Bowen Yang on Aug 4, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# ifndef __ModelView__MeshPack__
# define __ModelView__MeshPack__

# include <Options.h>
# include <BufferPack.hpp>
# include <VertexArrayPack.h>

enum VertArrs{ Pos, Nor, Tex };

/**
@brief Mesh object that loads mesh from models and render them.
*/
class MeshPack : public GLObject
{
private:
	/*
	The vertex array.
	*/
	VertexArrayPack VertexArray;

	/*
	Vertex Coordinates.
	*/
	BufferPack<GLfloat> VertexCoord;
	/*
	Vertex normal directions.
	*/
	BufferPack<GLfloat> NormalCoord;
	/*
	Texture coordinates.
	*/
	BufferPack<GLfloat> TextureCoord;
	
	/*
	Buffer storing indices of vertex, defining how triangles are assembled.
	*/
	BufferPack<GLuint> ElementArr;

	/*
	We may need this path later as a designator to the mesh.
	*/
	std::string Path;

	/*
	What's the center of the Mesh?
	*/
	GLfloat MassCenter[3];

	/*
	How many triangles and how many vertices are there in the mesh?
	*/
	size_t SizeInTriangles;
	size_t SizeInVertices;

	/*
	Mesh object is not a GLAttachable, for there's no such thing as
	glGenMesh(), and assetID has literally zero meaning.
	*/
	bool isAttached;

	/*
	Parse a plain text 3D model into blobs.
	*/
	void ParseModel(std::string Path, std::fstream& fin);

	/*
	Save the blob to a binary file.
	*/
	void SaveBinary();

	/*
	Load from plain text 3D models.
	*/
	void LoadFromModel(std::string Path, std::fstream& fin);

	/*
	Load from preprocessed blob files.
	*/
	void LoadFromBinary(std::string Path, std::fstream& fout);

public:
	/** 
	@brief Load from a mesh file.

	@param Path The path to the designated Mesh file, a plain-text 3D Model or a blob.
	*/
	MeshPack(std::string Path);

	/**
	@brief Attach this mesh, creating GLVertexArray, AttribPointer and stuff.
	*/
	void Attach();

	/**
	@brief Detach this mesh.
	*/
	void Detach();

	/**
	@brief Invoking drawcalls to render the mesh.

	@param mode The OpenGL primitive mode to draw the mesh.
	Set to GL_TRIANGLES by default.
	*/
	void DrawMesh(GLenum mode = GL_TRIANGLES);

	/**
	@brief Generate tangent for normal mapping.
	*/
	void GenTangent();

	/**
	@brief Add customized buffers as new vertex attrib arrays.

	@param buffer The buffer object.

	@param index The layout location used in the vertex shader.

	@param components How many components of the attribute one vertex can have. A value of 1/2/3/4 is expected.
	*/
	void AddAttribAt(BufferPack<GLfloat>& buffer, GLuint index, GLuint components);

	/**
	@brief Add customized buffers as new vertex attrib arrays.

	@param buffer The buffer object.

	@param index The layout location used in the vertex shader.

	@param components How many components of the attribute one vertex can have. A value of 1/2/3/4 is expected.
	*/
	void AddAttribAt(BufferPack<GLdouble>& buffer, GLuint index, GLuint components);

	/**
	@brief Add customized buffers as new vertex attrib arrays.

	@param buffer The buffer object.

	@param index The layout location used in the vertex shader.

	@param components How many components of the attribute one vertex can have. A value of 1/2/3/4 is expected.
	*/
	void AddAttribAt(BufferPack<GLint>& buffer, GLuint index, GLuint components);

	/**
	@brief Add customized buffers as new vertex attrib arrays.

	@param buffer The buffer object.

	@param index The layout location used in the vertex shader.

	@param components How many components of the attribute one vertex can have. A value of 1/2/3/4 is expected.
	*/
	void AddAttribAt(BufferPack<GLuint>& buffer, GLuint index, GLuint components);

	/**
	@brief Add customized buffers as new vertex attrib arrays.

	@param buffer The buffer object.

	@param index The layout location used in the vertex shader.

	@param components How many components of the attribute one vertex can have. A value of 1/2/3/4 is expected.
	*/
	void AddAttribAt(BufferPack<GLshort>& buffer, GLuint index, GLuint components);

	/**
	@brief Add customized buffers as new vertex attrib arrays.

	@param buffer The buffer object.

	@param index The layout location used in the vertex shader.

	@param components How many components of the attribute one vertex can have. A value of 1/2/3/4 is expected.
	*/
	void AddAttribAt(BufferPack<GLushort>& buffer, GLuint index, GLuint components);
};

# endif