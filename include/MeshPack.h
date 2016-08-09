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

class MeshPack : public GLAttachable, public GLObject
{
private:
	/** Buffer storing vertex coordinates*/
	BufferPack<GLfloat> VertexCoord;

	/** Buffer storing normal vector coordinates*/
	BufferPack<GLfloat> NormalCoord;

	/** Buffer storing texture coordinates*/
	BufferPack<GLfloat> TextureCoord;

	/** Buffer storing indices of vertex, defining how triangles are assembled*/
	BufferPack<GLuint> ElementArr;

	/** Buffer storing tangent coordinates for normal mapping*/
	//BufferPack TangentCoord; //Wait...Do we actually need this?

	GLfloat scale;

	/** Parse a plain text 3D model into blobs*/
	void ParseModel(std::string Path);

	/** Save the blob to a binary file*/
	void SaveBinary();

	/** Load from plain text 3D models*/
	void LoadFromModel(std::string Path);

	/** Load from preprocessed blob files*/
	void LoadFromBinary(std::string Path);

	/** Generate tangent for normal mapping*/
	void GenTangent();
public:
	/** 
	@brief Constructor.
	@params
	@Path specifies the path to the designated asset, can be plain text 3D Model or blob.
	*/
	MeshPack(std::string Path, float scale = 1.0f);

	/** Attach this mesh. GLVertexArray, AttribPointer and stuff*/
	void Attach() override;

	/** Detach this mesh.*/
	void Detach() override;

	/** GLDraw. Renders the mesh.*/
	void DrawMesh();
};

# endif