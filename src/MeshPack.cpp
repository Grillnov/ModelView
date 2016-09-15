//
//  MeshPack.cpp
//  ModelView
//
//  Created by Bowen Yang on Aug 4, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include "MeshPack.h"

MeshPack::MeshPack(std::string Path) : Path(Path), isAttached(false) {}

void MeshPack::LoadFromModel(std::string Path, std::fstream& fin)
{
	ParseModel(Path, fin);
	SaveBinary();

	Info(debugMsg, "Loading complete. Model %s has %u faces in triangles.", Path.c_str(), this->SizeInTriangles);
}

void MeshPack::LoadFromBinary(std::string binaryPath, std::fstream& fin)
{
	Log(debugMsg, "Loading binary from blob file %s now.", binaryPath.c_str());
	size_t temp;
	
	//Size of vertex position in bytes
	fin.read(reinterpret_cast<char*>(&temp), sizeof(size_t));

	this->SizeInVertices = temp / 3 / sizeof(GLfloat);

	//Vertex positions
	this->VertexCoord = BufferPack<GLfloat>(SizeInVertices * 3);
	VertexCoord.Attach();
	fin.read(reinterpret_cast<char*>(&VertexCoord[0]), temp);
	VertexCoord.Done();
	VertexArray.AddAttribAt(VertexCoord, Pos, 3);

	//Normal positions
	this->NormalCoord = BufferPack<GLfloat>(SizeInVertices * 3);
	NormalCoord.Attach();
	fin.read(reinterpret_cast<char*>(&NormalCoord[0]), SizeInVertices * 3 * sizeof(GLfloat));
	NormalCoord.Done();
	VertexArray.AddAttribAt(NormalCoord, Nor, 3);

	//Texture coordinates
	this->TextureCoord = BufferPack<GLfloat>(SizeInVertices * 3);
	TextureCoord.Attach();
	fin.read(reinterpret_cast<char*>(&TextureCoord[0]), SizeInVertices * 3 * sizeof(GLfloat));
	TextureCoord.Done();
	VertexArray.AddAttribAt(TextureCoord, Tex, 3);

	//Size of element array in bytes
	fin.read(reinterpret_cast<char*>(&temp), sizeof(size_t));
	this->SizeInTriangles = temp / 3 / sizeof(GLuint);
	//Element array
	this->ElementArr = BufferPack<GLuint>(SizeInTriangles * 3);
	ElementArr.Attach();
	fin.read(reinterpret_cast<char*>(&ElementArr[0]), temp);
	ElementArr.Done();

	Info(debugMsg, "Loading complete. Model %s has %u faces in triangles.", Path.c_str(), this->SizeInTriangles);
}

void MeshPack::SaveBinary()
{
	/*
	format: 
	Size of vertex position in bytes - vertex positions - 
	normal directions - 
	texture coordinates - 
	Size of element array in bytes - element array
	*/
	std::string binaryPath = this->Path.substr(0, this->Path.find(".obj")) + ".bin";
	std::fstream fout(binaryPath, std::ios::out | std::ios::binary);

	size_t temp = this->SizeInVertices * 3 * sizeof(GLfloat);
	fout.write(reinterpret_cast<const char*>(&temp), sizeof(size_t));
	fout.write(reinterpret_cast<const char*>(&VertexCoord[0]), temp);
	VertexCoord.Done();

	fout.write(reinterpret_cast<const char*>(&NormalCoord[0]), temp);
	NormalCoord.Done();

	fout.write(reinterpret_cast<const char*>(&TextureCoord[0]), temp);
	TextureCoord.Done();

	temp = this->SizeInTriangles * 3 * sizeof(GLuint);
	fout.write(reinterpret_cast<const char*>(&temp), sizeof(size_t));
	fout.write(reinterpret_cast<const char*>(&ElementArr[0]), temp);
	ElementArr.Done();

	fout.close();
	Log(debugMsg, "Model %s was successfully saved as binary blob. Conversions will be skipped from now.", this->Path.c_str());
}

void MeshPack::Attach()
{
	if (this->isAttached)
	{
		Warning(debugMsg, "Mesh %s is already attached, bailing.", this->Path.c_str());
		return;
	}

	std::string binaryPath = this->Path.substr(0, this->Path.find(".obj")) + ".bin";

	std::fstream fin(Path, std::ios::binary | std::ios::in);

	if (Path.find(".bin") != Path.npos)//A binary blob was ordered to be loaded.
	{
		if (!fin.is_open())
			Error(debugMsg, "Cannot open binary model file %s", Path.c_str());
		LoadFromBinary(Path, fin);
		fin.close();
	}
	else if (Path.find(".obj") != Path.npos)//A model was ordered to be loaded.
	{
		fin.close();
		fin.open(binaryPath, std::ios::binary | std::ios::in);
		if (!fin.is_open())//No correspondent blob was found.
		{
			Log(debugMsg, "Correspondent binary blob for %s was not found.", Path.c_str());
			fin.close();
			fin.open(Path, std::ios::in);
			if (!fin.is_open())
				Error(debugMsg, "Cannot open model file %s", Path.c_str());
			Warning(debugMsg, "Loading from plain text model %s. Conversion may take some time.", Path.c_str());
			LoadFromModel(Path, fin);
			fin.close();
		}
		else//Correspondent blob was found.
		{
			Log(debugMsg, "Correspondent binary blob for %s was found, loading from binary now.", Path.c_str());
			LoadFromBinary(binaryPath, fin);
			fin.close();
		}
	}
	else
		Error(debugMsg, "%s is neither a .obj nor a .bin, incompatible model file format.", Path.c_str());

	VertexArray.Attach();

	//ElementArr->Attach(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);

	CheckStatus(__FUNCTION__);

	Log(debugMsg, "Mesh %s was successfully attached.", this->Path.c_str());
	this->isAttached = true;
}

void MeshPack::Detach()
{
	if (!this->isAttached)
	{
		Warning(debugMsg, "Mesh %s is not attached yet, bailing.", this->Path.c_str());
		return;
	}
	VertexArray.Detach();

	VertexCoord.Detach();
	NormalCoord.Detach();
	TextureCoord.Detach();
	ElementArr.Detach();

	CheckStatus(__FUNCTION__);

	Log(debugMsg, "Mesh %s was successfully detached.", this->Path.c_str());
	this->isAttached = false;
}

void MeshPack::DrawMesh(GLenum mode)
{
	if (!this->isAttached)
	{
		Warning(debugMsg, "Attempting to draw without attaching mesh %s, bailing.", this->Path.c_str());
		return;
	}

	VertexArray.Bind();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementArr);
	glDrawElements(mode, this->SizeInTriangles * 3, GL_UNSIGNED_INT, nullptr);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

/*void MeshPack::AlignCenter()
{
	BufferPack<GLfloat>* ptr = reinterpret_cast<BufferPack<GLfloat>*>(this->Vertices[0]);
	for (unsigned i = 0; i != ptr->Size(); i += 3)
	{
		(*ptr)[i] -= MassCenter[0];
		(*ptr)[i + 1] -= MassCenter[1];
		(*ptr)[i + 2] -= MassCenter[2];
	}
}*/