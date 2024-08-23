#include "compressedBuffer.h"
#include <exceptions/compressionException.h>
#define LZ4F_HEAPMODE 1 
#include <streams/compression/thirdparty/lz4frame.h>
namespace athena
{
	compressedBuffer::compressedBuffer(buffer buffer)
	{
		m_data.resize(buffer.size() + sizeof(LZ4F_frameInfo_t));

		LZ4F_preferences_t preferences{};
		preferences.compressionLevel = LZ4F_compressionLevel_max();
		preferences.frameInfo = LZ4F_INIT_FRAMEINFO;
		preferences.frameInfo.contentSize = buffer.size();
		preferences.frameInfo.contentChecksumFlag = LZ4F_contentChecksumEnabled;

		size_t size = LZ4F_compressFrame(m_data.data(), m_data.size(), buffer.data(), buffer.size(), &preferences);

		if (LZ4F_isError(size))
			throw new exceptions::compressionException(LZ4F_getErrorName(size));

		m_data.resize(size);
			
	}
	size_t compressedBuffer::size() const
	{
		return m_data.size();
	}
	const char* compressedBuffer::data()
	{
		return (const char*)m_data.data();
	}
	size_t compressedBuffer::contentSize()
	{
		LZ4F_dctx* p_compressionContext = nullptr;
		LZ4F_createDecompressionContext(&p_compressionContext, LZ4F_getVersion());

		LZ4F_frameInfo_t frameInfo = LZ4F_INIT_FRAMEINFO;

		size_t srcSize = size();
		LZ4F_getFrameInfo(p_compressionContext, &frameInfo, m_data.data(), &srcSize);

		return frameInfo.contentSize;
	}
	buffer& compressedBuffer::decompress()
	{
		if (!m_data.size()) throw new exceptions::compressionException("m_data.size() was 0!");
		LZ4F_dctx* p_compressionContext = nullptr;
		LZ4F_createDecompressionContext(&p_compressionContext,LZ4F_getVersion());

		

		size_t dstSize = contentSize();
		void* dstBuffer = malloc(dstSize);

		size_t srcSize = size();
		LZ4F_errorCode_t error = LZ4F_decompress(p_compressionContext, dstBuffer, &dstSize, data(), &srcSize, nullptr);

		if (LZ4F_isError(error))
			throw new exceptions::compressionException(LZ4F_getErrorName(error));

		buffer* p_buffer = new buffer();
		p_buffer->writeData((const char*)dstBuffer, dstSize);
		return *p_buffer;
	}
}