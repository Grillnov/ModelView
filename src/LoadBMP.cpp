//
//  TexturePack.cpp
//  ModelView
//
//  Created by Bowen Yang on Sept 8, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include <TexturePack.h>

# ifndef _MSC_VER
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef int LONG;
# endif

struct bmpHeader
{
	WORD	bfType;
	DWORD	bFilesize;
	WORD	bfR1;
	WORD	bfR2;
	DWORD	bfOffsetToData;
};

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

void TexturePic::LoadFromBMP(std::string Path)
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

	if (fileInfo.biPlanes != 1 ||
		fileInfo.biCompression != 0 ||
		fileInfo.biBitCount != 24)
	{
		Error(debugMsg, "Format of BMP file %s is not supported yet.", Path.c_str());
	}

	this->xWidth = fileInfo.biWidth;
	this->yHeight = glm::abs(fileInfo.biHeight);
	size_t bufferSize = xWidth * yHeight * 3;
	try
	{
		this->Buffer = new char[bufferSize];
	}
	catch (std::bad_alloc exception)
	{
		Error(debugMsg, "Unable to allocate %u bytes of memory for client side texture storage."
			, bufferSize);
	}

	fin.read(this->Buffer, bufferSize);

	fin.close();

	if (fileInfo.biHeight < 0)
	{
		char* tmp = new char[fileInfo.biWidth * 3];
		int width = fileInfo.biWidth;
		int height = fileInfo.biHeight * -1;

		for (int i = 0; i<(fileInfo.biHeight * -1) / 2; i++)
		{
			memcpy(tmp, &this->Buffer[i * width * 3], width * 3);
			memcpy(&this->Buffer[i * width * 3], &this->Buffer[(height - 1 - i) * width * 3], width * 3);
			memcpy(&this->Buffer[(height - i - 1) * width * 3], tmp, width * 3);
		}
		delete[] tmp;
	}
}












/*
struct header
{
	unsigned char       identifier[12];
	unsigned int        endianness;
	unsigned int        gltype;
	unsigned int        gltypesize;
	unsigned int        glformat;
	unsigned int        glinternalformat;
	unsigned int        glbaseinternalformat;
	unsigned int        pixelwidth;
	unsigned int        pixelheight;
	unsigned int        pixeldepth;
	unsigned int        arrayelements;
	unsigned int        faces;
	unsigned int        miplevels;
	unsigned int        keypairbytes;
};

union keyvaluepair
{
	unsigned int        size;
	unsigned char       rawbytes[4];
};

static const unsigned char identifier[] =
{
	0xAB, 0x4B, 0x54, 0x58, 0x20, 0x31, 0x31, 0xBB, 0x0D, 0x0A, 0x1A, 0x0A
};

static const unsigned int swap32(const unsigned int u32)
{
	union
	{
		unsigned int u32;
		unsigned char u8[4];
	} a, b;

	a.u32 = u32;
	b.u8[0] = a.u8[3];
	b.u8[1] = a.u8[2];
	b.u8[2] = a.u8[1];
	b.u8[3] = a.u8[0];

	return b.u32;
}

static const unsigned short swap16(const unsigned short u16)
{
	union
	{
		unsigned short u16;
		unsigned char u8[2];
	} a, b;

	a.u16 = u16;
	b.u8[0] = a.u8[1];
	b.u8[1] = a.u8[0];

	return b.u16;
}

static unsigned int calculate_stride(const header& h, unsigned int width, unsigned int pad = 4)
{
	unsigned int channels = 0;

	switch (h.glbaseinternalformat)
	{
	case GL_RED:    channels = 1;
		break;
	case GL_RG:     channels = 2;
		break;
	case GL_BGR:
	case GL_RGB:    channels = 3;
		break;
	case GL_BGRA:
	case GL_RGBA:   channels = 4;
		break;
	}

	unsigned int stride = h.gltypesize * channels * width;

	stride = (stride + (pad - 1)) & ~(pad - 1);

	return stride;
}

static unsigned int calculate_face_size(const header& h)
{
	unsigned int stride = calculate_stride(h, h.pixelwidth);

	return stride * h.pixelheight;
}

unsigned int load(const char * filename, unsigned int tex)
{
	FILE * fp;
	GLuint temp = 0;
	GLuint retval = 0;
	header h;
	size_t data_start, data_end;
	unsigned char * data;
	GLenum target = GL_NONE;

	fp = fopen(filename, "rb");

	if (!fp)
		return 0;

	if (fread(&h, sizeof(h), 1, fp) != 1)
		goto fail_read;

	if (memcmp(h.identifier, identifier, sizeof(identifier)) != 0)
		goto fail_header;

	if (h.endianness == 0x04030201)
	{
		// No swap needed
	}
	else if (h.endianness == 0x01020304)
	{
		// Swap needed
		h.endianness = swap32(h.endianness);
		h.gltype = swap32(h.gltype);
		h.gltypesize = swap32(h.gltypesize);
		h.glformat = swap32(h.glformat);
		h.glinternalformat = swap32(h.glinternalformat);
		h.glbaseinternalformat = swap32(h.glbaseinternalformat);
		h.pixelwidth = swap32(h.pixelwidth);
		h.pixelheight = swap32(h.pixelheight);
		h.pixeldepth = swap32(h.pixeldepth);
		h.arrayelements = swap32(h.arrayelements);
		h.faces = swap32(h.faces);
		h.miplevels = swap32(h.miplevels);
		h.keypairbytes = swap32(h.keypairbytes);
	}
	else
	{
		goto fail_header;
	}

	// Guess target (texture type)
	if (h.pixelheight == 0)
	{
		if (h.arrayelements == 0)
		{
			target = GL_TEXTURE_1D;
		}
		else
		{
			target = GL_TEXTURE_1D_ARRAY;
		}
	}
	else if (h.pixeldepth == 0)
	{
		if (h.arrayelements == 0)
		{
			if (h.faces == 0)
			{
				target = GL_TEXTURE_2D;
			}
			else
			{
				target = GL_TEXTURE_CUBE_MAP;
			}
		}
		else
		{
			if (h.faces == 0)
			{
				target = GL_TEXTURE_2D_ARRAY;
			}
			else
			{
				target = GL_TEXTURE_CUBE_MAP_ARRAY;
			}
		}
	}
	else
	{
		target = GL_TEXTURE_3D;
	}

	// Check for insanity...
	if (target == GL_NONE ||                                    // Couldn't figure out target
		(h.pixelwidth == 0) ||                                  // Texture has no width???
		(h.pixelheight == 0 && h.pixeldepth != 0))              // Texture has depth but no height???
	{
		goto fail_header;
	}

	temp = tex;
	if (tex == 0)
	{
		glGenTextures(1, &tex);
	}

	glBindTexture(target, tex);

	data_start = ftell(fp) + h.keypairbytes;
	fseek(fp, 0, SEEK_END);
	data_end = ftell(fp);
	fseek(fp, data_start, SEEK_SET);

	data = new unsigned char[data_end - data_start];
	memset(data, 0, data_end - data_start);

	fread(data, 1, data_end - data_start, fp);

	if (h.miplevels == 0)
	{
		h.miplevels = 1;
	}

	switch (target)
	{
	case GL_TEXTURE_1D:
		glTexStorage1D(GL_TEXTURE_1D, h.miplevels, h.glinternalformat, h.pixelwidth);
		glTexSubImage1D(GL_TEXTURE_1D, 0, 0, h.pixelwidth, h.glformat, h.glinternalformat, data);
		break;
	case GL_TEXTURE_2D:
		glTexStorage2D(GL_TEXTURE_2D, h.miplevels, h.glinternalformat, h.pixelwidth, h.pixelheight);
		{
			unsigned char * ptr = data;
			unsigned int height = h.pixelheight;
			unsigned int width = h.pixelwidth;
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			for (unsigned int i = 0; i < h.miplevels; i++)
			{
				glTexSubImage2D(GL_TEXTURE_2D, i, 0, 0, width, height, h.glformat, h.gltype, ptr);
				ptr += height * calculate_stride(h, width, 1);
				height >>= 1;
				width >>= 1;
				if (!height)
					height = 1;
				if (!width)
					width = 1;
			}
		}
		break;
	case GL_TEXTURE_3D:
		glTexStorage3D(GL_TEXTURE_3D, h.miplevels, h.glinternalformat, h.pixelwidth, h.pixelheight, h.pixeldepth);
		glTexSubImage3D(GL_TEXTURE_3D, 0, 0, 0, 0, h.pixelwidth, h.pixelheight, h.pixeldepth, h.glformat, h.gltype, data);
		break;
	case GL_TEXTURE_1D_ARRAY:
		glTexStorage2D(GL_TEXTURE_1D_ARRAY, h.miplevels, h.glinternalformat, h.pixelwidth, h.arrayelements);
		glTexSubImage2D(GL_TEXTURE_1D_ARRAY, 0, 0, 0, h.pixelwidth, h.arrayelements, h.glformat, h.gltype, data);
		break;
	case GL_TEXTURE_2D_ARRAY:
		glTexStorage3D(GL_TEXTURE_2D_ARRAY, h.miplevels, h.glinternalformat, h.pixelwidth, h.pixelheight, h.arrayelements);
		glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0, h.pixelwidth, h.pixelheight, h.arrayelements, h.glformat, h.gltype, data);
		break;
	case GL_TEXTURE_CUBE_MAP:
		glTexStorage2D(GL_TEXTURE_CUBE_MAP, h.miplevels, h.glinternalformat, h.pixelwidth, h.pixelheight);
		// glTexSubImage3D(GL_TEXTURE_CUBE_MAP, 0, 0, 0, 0, h.pixelwidth, h.pixelheight, h.faces, h.glformat, h.gltype, data);
		{
			unsigned int face_size = calculate_face_size(h);
			for (unsigned int i = 0; i < h.faces; i++)
			{
				glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, 0, 0, h.pixelwidth, h.pixelheight, h.glformat, h.gltype, data + face_size * i);
			}
		}
		break;
	case GL_TEXTURE_CUBE_MAP_ARRAY:
		glTexStorage3D(GL_TEXTURE_CUBE_MAP_ARRAY, h.miplevels, h.glinternalformat, h.pixelwidth, h.pixelheight, h.arrayelements);
		glTexSubImage3D(GL_TEXTURE_CUBE_MAP_ARRAY, 0, 0, 0, 0, h.pixelwidth, h.pixelheight, h.faces * h.arrayelements, h.glformat, h.gltype, data);
		break;
	default:                                               // Should never happen
		goto fail_target;
	}

	if (h.miplevels == 1)
	{
		glGenerateMipmap(target);
	}

	retval = tex;

fail_target:
	delete[] data;

fail_header:;
fail_read:;
	fclose(fp);

	return retval;
}
*/