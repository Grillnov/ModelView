//
//  BufferPack.h
//  ModelView
//
//  Created by Bowen Yang on Aug 4, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include "MeshPack.h"

MeshPack::MeshPack(std::string Path)
{
	if (Path.find(".bin") == -1)
	{
		if (Path.find(".obj") == -1)
		{
			Error(debugMsg, "Only binary and .obj files are supported.");
			return;
		}
		Log(debugMsg, "Asset %s is not converted to binary yet. Conversion may take some time.", Path);
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