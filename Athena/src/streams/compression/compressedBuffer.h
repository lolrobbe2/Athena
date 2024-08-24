#pragma once
#include <util/buffer.h>
namespace athena 
{
	class compressedBuffer : protected buffer
	{
	public:
		compressedBuffer(buffer buffer);
        compressedBuffer(const char* data, size_t size);
        compressedBuffer() = default;
		size_t size() const;	
		const char* data();

		size_t contentSize();
		buffer& decompress();
        static void serialize(buffer* p_dstBuffer, const compressedBuffer& srcBuffer)
        {
            size_t srcSize = srcBuffer.size();

            p_dstBuffer->writeData((const char*)&srcSize, sizeof(size_t));
            p_dstBuffer->writeData((const char*)srcBuffer.m_data.data(), srcBuffer.size());
        }
        static compressedBuffer& deserialize(athena::buffer* p_srcBuffer)
        {
            compressedBuffer* p_dstBuffer = new compressedBuffer();

            size_t size = *(size_t*)p_srcBuffer->readData(sizeof(size_t));

            p_dstBuffer->writeData(p_srcBuffer->readData(size), size);

            return *p_dstBuffer;
        }
	};
}


