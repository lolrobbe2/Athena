#pragma once
#include <util/buffer.h>
namespace athena 
{
	class compressedBuffer : protected buffer
	{
		compressedBuffer(buffer buffer);
	};
}


