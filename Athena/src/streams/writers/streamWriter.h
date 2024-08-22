#pragma once
#ifndef STREAM_WRITER
#define STREAM_WRITER
#include <vector>
namespace luna 
{
	class streamWriter
	{
	public:
		virtual ~streamWriter();
		virtual bool isStreamGood() const;
		virtual void setStreamPosition();
		virtual void previousStreamSection();
		virtual void nextStreamSection();
		virtual size_t getStreamSectionCount();
		virtual bool writeData(const char* data, size_t size);
		template<typename T>
		void writeObject(const T& object) {};
		template<typename T>
		void writeArray(const std::vector<T>& vector) {};
		operator bool() const { return isStreamGood(); }
	};
}
#endif // !STREAM_WRITER
