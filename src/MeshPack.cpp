//
//  BufferPack.h
//  ModelView
//
//  Created by Bowen Yang on Aug 4, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include "MeshPack.h"

MeshPack::MeshPack(std::string Path, float scale) : scale(scale)
{
	if (Path.find(".bin") == Path.npos)
	{
		if (Path.find(".obj") == Path.npos)
		{
			Error(debugMsg, "Only binary and .obj files are supported.");
			return;
		}
		Log(debugMsg, "Asset %s is not converted to binary yet. Conversion may take some time.", Path.c_str());
		std::string binaryPath = Path.substr(0, Path.find(".obj")) + ".bin";
		LoadFromModel(Path);
	}
	else//blob found
	{
		LoadFromBinary(Path);
	}
}

void MeshPack::LoadFromModel(std::string Path)
{
	ParseModel(Path);
	SaveBinary();
}

void MeshPack::LoadFromBinary(std::string Path)
{

}

void MeshPack::SaveBinary()
{

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