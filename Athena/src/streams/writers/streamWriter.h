#pragma once
#ifndef STREAM_WRITER
#define STREAM_WRITER
#include <vector>
namespace luna 
{	/** 
	* @brief this is the interface for all streamWriters
	* sections is the collection of uncompressed athena::buffer objects to write to!
	* when the streamWriter is flushed all of them get transformed into athena::compressedBuffer objects.
	*/
	class streamWriter
	{
	public:
		virtual ~streamWriter();
		virtual bool isStreamGood() const;
		virtual void setStreamPosition();
		virtual void previousStreamSection();
		virtual void nextStreamSection();
		virtual size_t getStreamSectionCount() const;
		virtual bool writeData(const char* data, size_t size);
		template<typename T>
		void writeObject(const T& object) {};
		template<typename T>
		void writeArray(const std::vector<T>& vector) {};
		operator bool() const { return isStreamGood(); }
	};
}
#endif // !STREAM_WRITER
