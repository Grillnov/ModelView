//
//  MeshParsing.cpp
//  ModelView
//
//  Created by Bowen Yang on Aug 8, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include <MeshPack.h>
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

	this->VertexCoord.Alloc(3 * SizeInVertices, GL_ARRAY_BUFFER, GL_STATIC_DRAW);
	unsigned counter = 0;
	for (auto a : Vertices)
	{
		GLfloat x = a.vertexCoord[0];
		GLfloat y = a.vertexCoord[1];
		GLfloat z = a.vertexCoord[2];

		VertexCoord[3 * counter] = x;
		MassCenter[0] += x;

		VertexCoord[3 * counter + 1] = y;
		MassCenter[1] += y;

		VertexCoord[3 * counter + 2] = z;
		MassCenter[2] += z;

		++counter;
	}
	VertexCoord.Done();
	for (unsigned i = 0; i != 3; ++i)
	{
		MassCenter[i] = MassCenter[i] / Vertices.size();
	}
	this->VertexArray.AddAttribAt(VertexCoord, Pos, 3);


	this->NormalCoord.Alloc(3 * SizeInVertices, GL_ARRAY_BUFFER, GL_STATIC_DRAW);
	counter = 0;
	for (auto a : Vertices)
	{
		NormalCoord[3 * counter] = a.normalDir[0];
		NormalCoord[3 * counter + 1] = a.normalDir[1];
		NormalCoord[3 * counter + 2] = a.normalDir[2];
		++counter;
	}
	NormalCoord.Done();
	this->VertexArray.AddAttribAt(NormalCoord, Nor, 3);


	this->TextureCoord.Alloc(3 * SizeInVertices, GL_ARRAY_BUFFER, GL_STATIC_DRAW);
	counter = 0;
	for (auto a : Vertices)
	{
		TextureCoord[3 * counter] = a.texCoord[0];
		TextureCoord[3 * counter + 1] = a.texCoord[1];
		TextureCoord[3 * counter + 2] = a.texCoord[2];
		++counter;
	}
	TextureCoord.Done();
	this->VertexArray.AddAttribAt(TextureCoord, Tex, 3);


	Vertices.clear();


	this->ElementArr.Alloc(IndexSum, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
	counter = 0;
	for (auto a : ElementArrayTemp)
	{
		ElementArr[counter] = a;
		counter++;
	}
	ElementArr.Done();
	//AlignCenter();

	ElementArrayTemp.clear();
}