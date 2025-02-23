#pragma once
#ifndef MEMORY_STREAM_WRITER
#define MEMORY_STREAM_WRITER
#include <streams/writers/streamWriter.h>

#include <util/buffer.h>
namespace athena
{
	class memoryStreamWriter : public streamWriter
	{
	public:
		virtual ~memoryStreamWriter() = default;
		virtual bool isStreamGood() const override;
		virtual void setSectionPointerPosition(size_t index) override;
		virtual void setStreamPosition(size_t index) override;
		virtual void previousStreamSection() override;
		virtual void nextStreamSection() override;
		virtual size_t getStreamSectionCount() const override;
		virtual void writeData(const char* data, size_t size) override;
		template<typename T>
		void writeObject(const T& object) {};
		template<typename T>
		void writeArray(const std::vector<T>& vector) {};
		operator bool() const { return isStreamGood(); }
		virtual compressedBuffer flush() = 0;
	private:
		size_t sectionIndex = 0;
		std::vector<buffer> sections;
	};
}
#endif // !MEMORY_STREAM_WRITER
