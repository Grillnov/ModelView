//
//  BufferPack.h
//  ModelView
//
//  Created by Bowen Yang on Aug 4, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include "MeshPack.h"

MeshPack::MeshPack(std::string Path, float scale) : scale(scale), Path(Path)
{
	std::string binaryPath = this->Path.substr(0, this->Path.find(".obj")) + ".bin";

	std::fstream fin(Path, std::ios::binary | std::ios::in);

	if (Path.find(".bin") != Path.npos)//A binary blob was ordered to be loaded.
	{
		if (!fin.is_open())
			Error(debugMsg, "Cannot open file %s", Path.c_str());
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
				Error(debugMsg, "Cannot open file %s", Path.c_str());
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
		Error(debugMsg, "%s is neither a .obj nor a .bin, incompatible file format.", Path.c_str());
}

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
	
	fin.read(reinterpret_cast<char*>(&temp), sizeof(size_t));
	this->SizeInVertices = temp / 4 / sizeof(GLfloat);
	this->VertexCoord = new BufferPack<GLfloat>(SizeInVertices * 4);
	fin.read(reinterpret_cast<char*>(VertexCoord->LocalPtr), temp);

	this->NormalCoord = new BufferPack<GLfloat>(SizeInVertices * 3);
	fin.read(reinterpret_cast<char*>(NormalCoord->LocalPtr), SizeInVertices * 3 * sizeof(GLfloat));

	this->TextureCoord = new BufferPack<GLfloat>(SizeInVertices * 3);
	fin.read(reinterpret_cast<char*>(TextureCoord->LocalPtr), SizeInVertices * 3 * sizeof(GLfloat));

	fin.read(reinterpret_cast<char*>(&temp), sizeof(size_t));
	this->SizeInTriangles = temp / 3 / sizeof(GLuint);
	this->ElementArr = new BufferPack<GLuint>(SizeInTriangles * 3);
	fin.read(reinterpret_cast<char*>(ElementArr->LocalPtr), temp);

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

	size_t temp = this->SizeInVertices * 4 * sizeof(GLfloat);
	fout.write(reinterpret_cast<const char*>(&temp), sizeof(size_t));
	fout.write(reinterpret_cast<const char*>(VertexCoord->LocalPtr), temp);

	temp = this->SizeInVertices * 3 * sizeof(GLfloat);
	fout.write(reinterpret_cast<const char*>(NormalCoord->LocalPtr), temp);
	fout.write(reinterpret_cast<const char*>(TextureCoord->LocalPtr), temp);

	temp = this->SizeInTriangles * 3 * sizeof(GLuint);
	fout.write(reinterpret_cast<const char*>(&temp), sizeof(size_t));
	fout.write(reinterpret_cast<const char*>(ElementArr->LocalPtr), temp);

	fout.close();
	Log(debugMsg, "Model was successfully converted into binary blob. Conversions will be skipped from now.", this->Path.c_str());
}

void MeshPack::Attach()
{

}

void MeshPack::Detach()
{

}

void MeshPack::DrawMesh()
{

}

MeshPack::~MeshPack()
{
	delete this->VertexCoord;
	delete this->NormalCoord;
	delete this->TextureCoord;
	delete this->ElementArr;
}