#pragma once
#include <util/buffer.h>
namespace athena 
{
	class compressedBuffer : protected buffer
	{
	public:
		compressedBuffer(buffer buffer);
		size_t size();	
		size_t contentSize();
		size_t blockSize();
	};
}


