//
//  MeshPack.h
//  ModelView
//
//  Created by Bowen Yang on Aug 4, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# ifndef MESHPACK
# define MESHPACK
# include "AllinGL.h"
# include "BufferPack.hpp"
# include "VertexArrayPack.h"

enum VertArrs{ Pos, Nor, Tex };

class MeshPack : public GLObject
{
private:
	/**
	Vertex array.
	*/
	VertexArrayPack Vertices;

	/**
	Buffer storing indices of vertex, defining how triangles are assembled.
	*/
	BufferPack<GLuint>* ElementArr;

	/**
	Buffer storing tangent coordinates for normal mapping
	*/
	//BufferPack TangentCoord; //Wait...Do we actually need this?

	/**
	We may need this path later as a designator to the mesh.
	*/
	std::string Path;

	/**
	What's the center of the Mesh?
	*/
	GLfloat MassCenter[3];

	/**
	Sometimes 3D models in plain text can't fit into NDS coordinates and we have to scale them down.
	*/
	//GLfloat scale;

	/**
	How many triangles and how many vertices are there in the mesh?
	*/
	size_t SizeInTriangles;
	size_t SizeInVertices;

	/**
	*/
	bool isAttached;

	/**
	Parse a plain text 3D model into blobs.
	*/
	void ParseModel(std::string Path, std::fstream& fin);

	/**
	Save the blob to a binary file.
	*/
	void SaveBinary();

	/**
	Load from plain text 3D models.
	*/
	void LoadFromModel(std::string Path, std::fstream& fin);

	/**
	Load from preprocessed blob files.
	*/
	void LoadFromBinary(std::string Path, std::fstream& fout);

	/**
	Generate tangent for normal mapping.
	*/
	void GenTangent();

	/**
	Move the mesh so that it's centered on the origin.
	*/
	//void AlignCenter();
public:
	/** 
	@brief Constructor.
	@params
	@Path specifies the path to the designated asset, can be plain text 3D Model or blob.
	*/
	MeshPack(std::string Path);

	~MeshPack();

	/**
	Attach this mesh, creating GLVertexArray, AttribPointer and stuff.
	*/
	void Attach();

	/**
	Detach this mesh.
	*/
	void Detach();

	/**
	GLDraw. Invoking drawcalls to render the mesh.
	*/
	void DrawMesh(GLenum mode = GL_TRIANGLES);

	/**
	Add customized buffers as new vertex attrib arrays.
	*/
	void AddAttribWithIndex(BufferPack<GLfloat>* buffer, GLuint index, GLuint components);

	void AddAttribWithIndex(BufferPack<GLint>* buffer, GLuint index, GLuint components);
};

# endif