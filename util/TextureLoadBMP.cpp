//
//  LoadBMP.cpp
//  ModelView
//
//  Created by Bowen Yang on Sept 8, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include <TexturePack.h>
# include <exception>

# ifndef _MSC_VER
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef int LONG;
# endif

/**
@brief Standard BMP file header.
*/
struct bmpHeader
{
	WORD	bfType;
	DWORD	bFilesize;
	WORD	bfR1;
	WORD	bfR2;
	DWORD	bfOffsetToData;
};

/**
@brief BMP file info header.
*/
struct bmpInfo
{
	DWORD	biSize;
	LONG	biWidth, biHeight;
	WORD	biPlanes;
	WORD	biBitCount;
	DWORD	biCompression;
	DWORD	biSizeImage;
	LONG	ppm[2];
	DWORD	biclrs[2];
};

unsigned char* TexturePic::LoadBMP(std::string Path)
{
	bmpHeader fileHeader;
	bmpInfo fileInfo;
	std::ifstream fin(Path, std::ios::binary);
	if (!fin.is_open())
	{
		Error(debugMsg, "Cannot't open asset: %s!", Path.c_str());
	}
	fin.read(reinterpret_cast<char*>(&fileHeader.bfType), sizeof(WORD));

	if (fileHeader.bfType != 0x4d42)
	{
		Error(debugMsg, "Magic number mismatch. %s is not a valid BMP bitmap file!", Path.c_str());
	}
	fin.seekg(sizeof(WORD) * 2 + sizeof(DWORD) * 3, std::ios::cur);
	fin.read(reinterpret_cast<char*>(&fileInfo.biWidth), sizeof(LONG));
	fin.read(reinterpret_cast<char*>(&fileInfo.biHeight), sizeof(LONG));
	fin.read(reinterpret_cast<char*>(&fileInfo.biPlanes), sizeof(WORD));
	fin.read(reinterpret_cast<char*>(&fileInfo.biBitCount), sizeof(WORD));
	fin.read(reinterpret_cast<char*>(&fileInfo.biCompression), sizeof(DWORD));

	fin.seekg(sizeof(DWORD) * 3 + sizeof(LONG) * 2, std::ios::cur);

	if (fileInfo.biPlanes != 1 || fileInfo.biCompression != 0)
	{
		Error(debugMsg, "Format of BMP file %s is not supported yet.", Path.c_str());
	}

	this->xWidth = fileInfo.biWidth;
	this->yHeight = glm::abs(fileInfo.biHeight);

	size_t bufferSize = xWidth * yHeight * 3;

	unsigned char* buffer = nullptr;
	try
	{
		buffer = new unsigned char[bufferSize];
	}
	catch (std::bad_alloc exception)
	{
		Error(debugMsg, "Unable to allocate %u bytes of memory for client side texture storage."
			, bufferSize);
	}

	fin.read(reinterpret_cast<char*>(buffer), bufferSize);

	fin.close();

	if (fileInfo.biHeight < 0)
	{
		char* tmp = new char[fileInfo.biWidth * 3];
		int width = fileInfo.biWidth;
		int height = fileInfo.biHeight * -1;

		for (int i = 0; i<(fileInfo.biHeight * -1) / 2; i++)
		{
			memcpy(tmp, &buffer[i * width * 3], width * 3);
			memcpy(&buffer[i * width * 3], &buffer[(height - 1 - i) * width * 3], width * 3);
			memcpy(&buffer[(height - i - 1) * width * 3], tmp, width * 3);
		}
		delete[] tmp;
	}

	return buffer;
}