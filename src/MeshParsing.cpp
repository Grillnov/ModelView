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

void MeshPack::ParseModel(std::string Path)
{
	std::fstream fin(Path, std::ios::in);
	if (!fin.is_open())
	{
		fin.close();
		Error(debugMsg, "Asset %s is not found!", Path.c_str());
	}
	else
	{
		Log(debugMsg, "Model %s is now being parsed!", Path.c_str());
	}

	fin.seekg(0, std::ios::end);
	//size_t fileSize = fin.tellg();
	fin.seekg(0);
	std::string source;
	source.assign(std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());
	fin.close();

	std::vector<vec3> VertexAttribTemp[texCoord + 1];
	std::vector<GLuint> ElementArrayTemp;
	std::set<Vertex> Vertices;

	std::stringstream objStream(source);
	while (!objStream.eof())
	{
		std::string line;
		getline(objStream, line);
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

	size_t VertexSum = Vertices.size();
	size_t IndexSum = ElementArrayTemp.size();

	GLfloat* Coord = new GLfloat[4 * VertexSum];
	unsigned counter = 0;
	for (auto a : Vertices)
	{
		Coord[4 * counter] = a.vertexCoord[0] / scale;
		Coord[4 * counter + 1] = a.vertexCoord[1] / scale;
		Coord[4 * counter + 2] = a.vertexCoord[2] / scale;
		Coord[4 * counter + 3] = 1.0f;
		++counter;
	}
	this->VertexCoord = BufferPack<GLfloat>(Coord, 4 * VertexSum);

	GLfloat* Norm = new GLfloat[3 * VertexSum];
	counter = 0;
	for (auto a : Vertices)
	{
		Norm[3 * counter] = a.normalDir[0];
		Norm[3 * counter + 1] = a.normalDir[1];
		Norm[3 * counter + 2] = a.normalDir[2];
		++counter;
	}
	this->NormalCoord = BufferPack<GLfloat>(Norm, 3 * VertexSum);

	GLfloat* Tex = new GLfloat[3 * VertexSum];
	counter = 0;
	for (auto a : Vertices)
	{
		Tex[3 * counter] = a.texCoord[0];
		Tex[3 * counter + 1] = a.texCoord[1];
		Tex[3 * counter + 2] = a.texCoord[2];
		++counter;
	}
	this->TextureCoord = BufferPack<GLfloat>(Tex, 3 * VertexSum);
	
	/*Maybe this could be of use
	counter = 0;
	GLuint* IDnum = new GLuint[VertexSum];
	for (auto a : Vertices)
	{
		IDnum[counter] = a.ID;
		++counter;
	}
	this->VertexID = BufferPack<GLuint>(IDnum, );
	*/

	Vertices.clear();

	GLuint* EleArr = new GLuint[ElementArrayTemp.size()];
	counter = 0;
	for (auto a : ElementArrayTemp)
	{
		EleArr[counter] = a;
	}
	this->ElementArr = BufferPack<GLuint>(EleArr, ElementArrayTemp.size());

	Info(debugMsg, "Model %s has %u faces in triangles.", Path.c_str(), ElementArrayTemp.size());
	ElementArrayTemp.clear();
}