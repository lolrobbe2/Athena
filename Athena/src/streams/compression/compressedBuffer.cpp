#include "compressedBuffer.h"
#include <exceptions/compressionException.h>
#include <streams/compression/thirdparty/lz4frame.h>
namespace athena
{
	compressedBuffer::compressedBuffer(buffer buffer)
	{
		m_data.resize(buffer.size() + sizeof(LZ4F_frameInfo_t));

		LZ4F_preferences_t preferences;
		preferences.frameInfo = LZ4F_INIT_FRAMEINFO;
		preferences.frameInfo.contentChecksumFlag = LZ4F_contentChecksumEnabled;

		size_t size = LZ4F_compressFrame(m_data.data(), m_data.size(), buffer.data(), buffer.size(), &preferences);

		if (LZ4F_isError(size))
			throw new exceptions::compressionException()
			
	}
}