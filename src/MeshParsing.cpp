//
//  MeshParsing.cpp
//  ModelView
//
//  Created by Bowen Yang on Aug 8, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include "MeshPack.h"
# include <vector>
# include <set>
# include <sstream>

enum VertexAttrib{ Coord, normalDir, texCoord, vertexID };

struct vec3
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
	vec3(){};
	vec3(float x, float y, float z) :x(x), y(y), z(z){}
};

struct Vertex
{
	GLfloat vertexCoord[3];
	GLfloat normalDir[3];
	GLfloat texCoord[3];
	unsigned ID;

	Vertex(const vec3& Coord, const vec3& Normal, const vec3& tex, unsigned ID)
	{
		this->ID = ID;
		vertexCoord[0] = Coord.x;
		vertexCoord[1] = Coord.y;
		vertexCoord[2] = Coord.z;

		normalDir[0] = Normal.x;
		normalDir[1] = Normal.y;
		normalDir[2] = Normal.z;

		texCoord[0] = tex.x;
		texCoord[1] = tex.y;
		texCoord[2] = tex.z;
	}
};

bool operator<(const Vertex& lhs, const Vertex& rhs)
{
	return lhs.ID < rhs.ID;
}

bool operator==(const Vertex& lhs, const Vertex& rhs)
{
	return lhs.ID == rhs.ID;
}

void MeshPack::ParseModel(std::string Path, std::fstream& fin)
{	
	Log(debugMsg, "Model %s is now being parsed!", Path.c_str());

	//std::string source;
	//source.assign(std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());

	std::vector<vec3> VertexAttribTemp[texCoord + 1];
	std::vector<GLuint> ElementArrayTemp;
	std::set<Vertex> Vertices;

	size_t linesParsed = 0;

	//std::stringstream objStream(source);
	while (!fin.eof())
	{
		std::string line;
		getline(fin, line);
		linesParsed++;
		if (linesParsed % 10000 == 0)
		{
			Info(debugMsg, "Already parsed: %u lines.", linesParsed);
		}
		std::stringstream lineStream(line);

		char numb;
		
		if (line.empty())
			continue;

		switch (line.at(0))
		{
		case 'v':
			switch (line.at(1))
			{
			case ' ':
				float CoordData[3];
				lineStream >> numb >> CoordData[0] >> CoordData[1] >> CoordData[2];
				VertexAttribTemp[Coord].push_back(vec3(CoordData[0], CoordData[1], CoordData[2]));
				break;
			case 'n':
				float normalData[3];
				lineStream >> numb >> numb >> normalData[0] >> normalData[1] >> normalData[2];
				VertexAttribTemp[normalDir].push_back(vec3(normalData[0], normalData[1], normalData[2]));
				break;
			case 't':
				float texCoordData[3];
				char numb;
				lineStream >> numb >> numb >> texCoordData[0] >> texCoordData[1] >> texCoordData[2];
				VertexAttribTemp[texCoord].push_back(vec3(texCoordData[0], texCoordData[1], texCoordData[2]));
				break;
			default:
				break;
			}
			break;
		case 'f':
			lineStream >> numb;
			if (line.find("//") != line.npos)
			{
				for (int i = 0; i != 3; ++i)
				{
					unsigned PosTexNor[3];
					lineStream >> PosTexNor[Coord] >> numb >> numb >> PosTexNor[normalDir];
					for (int i = 0; i != 3; ++i)
					{
						PosTexNor[i]--;
					}
					ElementArrayTemp.push_back(PosTexNor[0]);
					Vertices.insert(Vertex(VertexAttribTemp[Coord].at(PosTexNor[Coord]), VertexAttribTemp[normalDir].at(PosTexNor[normalDir]), vec3(0, 0, 0), PosTexNor[0]));
				}
			}
			else
			{
				for (int i = 0; i != 3; ++i)
				{
					unsigned PosTexNor[3];
					lineStream >> PosTexNor[Coord] >> numb >> PosTexNor[texCoord] >> numb >> PosTexNor[normalDir];
					for (int i = 0; i != 3; ++i)
					{
						PosTexNor[i]--;
					}
					ElementArrayTemp.push_back(PosTexNor[0]);
					Vertices.insert(Vertex(VertexAttribTemp[Coord].at(PosTexNor[Coord]), VertexAttribTemp[normalDir].at(PosTexNor[normalDir]), VertexAttribTemp[texCoord].at(PosTexNor[texCoord]), PosTexNor[0]));
				}
			}
			break;
		default:
			break;
		}
	}

	for (int i = 0; i != texCoord + 1; ++i)
	{
		VertexAttribTemp[i].clear();
	}

	this->SizeInVertices = Vertices.size();
	size_t IndexSum = ElementArrayTemp.size();
	this->SizeInTriangles = IndexSum / 3;

	for (unsigned i = 0; i != 3; ++i)
	{
		MassCenter[i] = 0.0f;
	}

	GLfloat* Coord = new GLfloat[3 * SizeInVertices];
	unsigned counter = 0;
	for (auto a : Vertices)
	{
		Coord[3 * counter] = a.vertexCoord[0] * scale;
		MassCenter[0] += Coord[3 * counter];

		Coord[3 * counter + 1] = a.vertexCoord[1] * scale;
		MassCenter[1] += Coord[3 * counter + 1];

		Coord[3 * counter + 2] = a.vertexCoord[2] * scale;
		MassCenter[2] += Coord[3 * counter + 2];

		++counter;
	}

	for (unsigned i = 0; i != 3; ++i)
	{
		MassCenter[i] = MassCenter[i] / Vertices.size();
	}

	BufferPack<GLfloat>* VertexCoord = new BufferPack<GLfloat>(Coord, 3 * SizeInVertices);
	this->Vertices.AddBufferWithIndex(VertexCoord, Pos, 3);

	GLfloat* Norm = new GLfloat[3 * SizeInVertices];
	counter = 0;
	for (auto a : Vertices)
	{
		Norm[3 * counter] = a.normalDir[0];
		Norm[3 * counter + 1] = a.normalDir[1];
		Norm[3 * counter + 2] = a.normalDir[2];
		++counter;
	}
	BufferPack<GLfloat>* NormalCoord = new BufferPack<GLfloat>(Norm, 3 * SizeInVertices);
	this->Vertices.AddBufferWithIndex(NormalCoord, Nor, 3);

	GLfloat* Texture = new GLfloat[3 * SizeInVertices];
	counter = 0;
	for (auto a : Vertices)
	{
		Texture[3 * counter] = a.texCoord[0];
		Texture[3 * counter + 1] = a.texCoord[1];
		Texture[3 * counter + 2] = a.texCoord[2];
		++counter;
	}
	BufferPack<GLfloat>* TextureCoord = new BufferPack<GLfloat>(Texture, 3 * SizeInVertices);
	this->Vertices.AddBufferWithIndex(TextureCoord, Tex, 3);
	
	Vertices.clear();

	GLuint* EleArr = new GLuint[IndexSum];
	counter = 0;
	for (auto a : ElementArrayTemp)
	{
		EleArr[counter] = a;
		counter++;
	}
	this->ElementArr = new BufferPack<GLuint>(EleArr, IndexSum);

	AlignCenter();

	ElementArrayTemp.clear();
}