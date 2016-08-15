//
//  MeshPack.cpp
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
	
	//Size of vertex position in bytes
	fin.read(reinterpret_cast<char*>(&temp), sizeof(size_t));

	this->SizeInVertices = temp / 3 / sizeof(GLfloat);
	this->VertexCoord = new BufferPack<GLfloat>(SizeInVertices * 3);

	//Vertex positions
	fin.read(reinterpret_cast<char*>(VertexCoord->LocalPtr), temp);

	//Normal positions
	this->NormalCoord = new BufferPack<GLfloat>(SizeInVertices * 3);
	fin.read(reinterpret_cast<char*>(NormalCoord->LocalPtr), SizeInVertices * 3 * sizeof(GLfloat));

	//Texture coordinates
	this->TextureCoord = new BufferPack<GLfloat>(SizeInVertices * 3);
	fin.read(reinterpret_cast<char*>(TextureCoord->LocalPtr), SizeInVertices * 3 * sizeof(GLfloat));

	//Size of element array in bytes
	fin.read(reinterpret_cast<char*>(&temp), sizeof(size_t));
	this->SizeInTriangles = temp / 3 / sizeof(GLuint);
	this->ElementArr = new BufferPack<GLuint>(SizeInTriangles * 3);

	//Element array
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

	size_t temp = this->SizeInVertices * 3 * sizeof(GLfloat);
	fout.write(reinterpret_cast<const char*>(&temp), sizeof(size_t));
	fout.write(reinterpret_cast<const char*>(VertexCoord->LocalPtr), temp);

	fout.write(reinterpret_cast<const char*>(NormalCoord->LocalPtr), temp);
	fout.write(reinterpret_cast<const char*>(TextureCoord->LocalPtr), temp);

	temp = this->SizeInTriangles * 3 * sizeof(GLuint);
	fout.write(reinterpret_cast<const char*>(&temp), sizeof(size_t));
	fout.write(reinterpret_cast<const char*>(ElementArr->LocalPtr), temp);

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

	glGenVertexArrays(1, &VertArray);
	glBindVertexArray(VertArray);

	VertexCoord->Attach();
	VertexCoord->Bind(GL_ARRAY_BUFFER);
	glVertexAttribPointer(Pos, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(Pos);

	NormalCoord->Attach();
	NormalCoord->Bind(GL_ARRAY_BUFFER);
	glVertexAttribPointer(Nor, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(Nor);

	TextureCoord->Attach();
	TextureCoord->Bind(GL_ARRAY_BUFFER);
	glVertexAttribPointer(Tex, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(Tex);

	ElementArr->Attach();

	glBindVertexArray(0);

	CheckStatus(__FUNCTION__);

	Log(debugMsg, "Mesh %s successfully attached.", this->Path.c_str());
	this->isAttached = true;
}

void MeshPack::Detach()
{
	if (!this->isAttached)
	{
		Warning(debugMsg, "Mesh %s is not attached yet, bailing.", this->Path.c_str());
		return;
	}
	glDeleteVertexArrays(1, &VertArray);

	VertexCoord->Detach();
	NormalCoord->Detach();
	TextureCoord->Detach();
	ElementArr->Detach();

	CheckStatus(__FUNCTION__);

	Log(debugMsg, "Mesh %s is successfully detached.", this->Path.c_str());
	this->isAttached = false;
}

void MeshPack::DrawMesh()
{
	if (!this->isAttached)
	{
		Warning(debugMsg, "Attempting to draw without attaching mesh %s, bailing.", this->Path.c_str());
		return;
	}

	glBindVertexArray(this->VertArray);
	ElementArr->Bind(GL_ELEMENT_ARRAY_BUFFER);
	glDrawElements(GL_TRIANGLES, this->SizeInTriangles * 3, GL_UNSIGNED_INT, nullptr);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

MeshPack::~MeshPack()
{
	delete this->VertexCoord;
	delete this->NormalCoord;
	delete this->TextureCoord;
	delete this->ElementArr;
}