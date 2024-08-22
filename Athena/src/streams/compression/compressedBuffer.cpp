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
		preferences.frameInfo.contentChecksumFlag = LZ4F_contentChecksumEnabled;

		size_t size = LZ4F_compressFrame(m_data.data(), m_data.size(), buffer.data(), buffer.size(), &preferences);

		if (LZ4F_isError(size))
			throw new exceptions::compressionException(LZ4F_getErrorName(size));

		m_data.resize(size);
			
	}
	size_t compressedBuffer::size()
	{
		return m_data.size();
	}
	size_t compressedBuffer::contentSize()
	{
		return ((LZ4F_frameInfo_t*)m_data.data())->contentSize;
	}
	size_t compressedBuffer::blockSize()
	{
		return ((LZ4F_frameInfo_t*)m_data.data())->blockSizeID;
	}
}