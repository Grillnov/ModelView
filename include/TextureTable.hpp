//
//  TextureTable.hpp
//  ModelView
//
//  Created by Bowen Yang on Sept 6, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//


# include <AllinGL.h>
# include <TexturePack.h>

/**
Textures that are used for 'tables', that is to say, they are accessed as arrays,
not pictures.
It's preferred to use this instead of UBOs as tables, to create global variables acress all primitives.
*/
class TextureTable : public TexturePack
{
public:
	void LoadFromBin(std::string Path);
private:
	SamplerPack defaultSampler;

	GLsizei xWidth;
	GLsizei yHeight;
	int Channel;
	char *Buffer;
};

template<typename GLclientside>
class Texture1DArray : public TextureTable
{
public:
	void Attach() override;
	void Detach() override;
private:
	void Bind(GLenum target);
	GLsizei size;
	GLclientside* Buffer;
};

template<typename GLclientside>
class Texture2DArray : public TextureTable
{
public:
	void Attach() override;
	void Detach() override;
private:
	void Bind(GLenum target);
	GLsizei size;
	GLclientside* Buffer;
};