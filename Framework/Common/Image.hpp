#pragma once

#include "geommath.hpp"

namespace My {

	typedef struct _Image
	{
		uint32_t width;
		uint32_t height;
		R8G8B8A8Unorm * data;
		uint32_t bitcount;
		uint32_t pitch;
		size_t data_size;

	} Image;

}