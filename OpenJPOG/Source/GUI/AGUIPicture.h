#pragma once
#include "TKernel/TObject.h"

class AGUIPicture : public Toshi::TObject
{
	DECLARE_DYNAMIC(AGUIPicture, Toshi::TObject);

public:

	AGUIPicture();

protected:
	static const int split_tile_count    = 6;
	static const int split_texture_count = 6;
	static const int *split_texture_size[2];
	static void* split_rules[6];
};
