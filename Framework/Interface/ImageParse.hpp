#pragma once

#include "Interface.hpp"
#include "Image.hpp"
#include "Buffer.hpp"


namespace My {

	Interface ImageParse
	{
		virtual Image Parser(const Buffer& buffer) = 0;
	};


}