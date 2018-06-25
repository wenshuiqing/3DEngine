#pragma once

#include "Interface.hpp"
#include "Image.hpp"
#include "Buffer.hpp"


namespace My {

	interface ImageParse
	{
		virtual Image Parser(const Buffer& buffer) = 0;
	};


}