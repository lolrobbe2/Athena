#pragma once
#include <util/buffer.h>
namespace athena 
{
	class compressedBuffer : protected buffer
	{
	public:
		compressedBuffer(buffer buffer);
		size_t size();	
		const char* data();

		size_t contentSize();
		buffer& decompress();
	};
}


