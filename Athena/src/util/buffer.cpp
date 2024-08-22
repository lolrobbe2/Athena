#include "buffer.h"

namespace athena
{
	void buffer::writeData(const char* data, size_t size)
	{
		m_data.insert(m_data.begin() + m_pointerPosition, data, data + size);

		//advance pointer to be at end of data. that way we always append to the back of the buffer.
		m_pointerPosition += size; 
	}
	void buffer::setPointerPosition(size_t index)
	{
		if (m_pointerPosition + index > m_data.size()) throw new std::exception(); //TODO custom exception with print statement
	}
}
