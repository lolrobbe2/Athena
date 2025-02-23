#include "buffer.h"
#include <exceptions/indexBoundsException.h>
#include <algorithm>
namespace athena
{
	void buffer::writeData(const char* data, size_t size)
	{
		m_data.insert(m_data.begin() + m_pointerPosition, data, data + size);

		//advance pointer to be at end of data. that way we always append to the back of the buffer.
		m_pointerPosition += size; 
	}
	const char* buffer::readData(size_t size)
	{
		if (m_pointerPosition >= m_data.size())
			m_pointerPosition = 0;

		if (m_pointerPosition + size > m_data.size()) throw exceptions::indexOutOfBoundsException("m_pointerPosition + size > m_data.size() was true!");

		const char* data = (const char*) malloc(size);
		
		memcpy_s((void*)data, size, m_data.data() + m_pointerPosition, size);
		m_pointerPosition = std::max((size_t)0, m_pointerPosition + size);
		return data;
	}
	void buffer::setPointerPosition(size_t index)
	{
		if (m_pointerPosition + index > m_data.size()) throw exceptions::indexOutOfBoundsException("index was out of bounds"); //TODO custom exception with print statement
	}
}
