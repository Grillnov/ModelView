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
template<typename GLclientside, typename GLserverside>
class TextureTable : public TexturePack
{
public:
	void LoadFromBin(std::string Path);
private:
	SamplerPack defaultSampler;

	GLsizei xWidth;
	GLsizei yHeight;
	int Channel;
	GLclientside *Buffer;
};