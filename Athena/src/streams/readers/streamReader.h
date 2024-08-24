#pragma once
#ifndef STREAM_READER
#define	STREAM_READER

#include <vector>

namespace athena
{
	class streamReader
	{
	public:
		streamReader() = default;
		virtual ~streamReader() = default;
		virtual bool isStreamGood() const = 0;
		virtual void setSectionPointerPosition(size_t index) = 0;
		virtual void setStreamPosition(size_t index) = 0;
		virtual void previousStreamSection() = 0;
		virtual void nextStreamSection() = 0;
		virtual size_t getStreamSectionCount() const = 0;
		virtual const char* readData(size_t size) = 0;
		template<typename T>
		T& readObject() {};
		template<typename T>
		std::vector<T>& readArray() {};
		operator bool() const { return isStreamGood(); }
	};
}
#endif // !STREAM_READER
