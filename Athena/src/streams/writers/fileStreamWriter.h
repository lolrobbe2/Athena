#pragma once
#ifndef FILE_STREAM_WRITER
#define FILE_STREAM_WRITER
#include <streams/writers/streamWriter.h>

#include <iostream>
#include <fstream>
#include <filesystem>

#include <util/buffer.h>
namespace athena
{
	class fileStreamWriter : public streamWriter
	{
	public:
		fileStreamWriter(std::filesystem::path& path);
		fileStreamWriter(const fileStreamWriter&) = delete;
		virtual ~fileStreamWriter();
		virtual bool isStreamGood() const override;
		virtual void setSectionPointerPosition(size_t index) override;
		virtual void setStreamPosition(size_t index) override;
		virtual void previousStreamSection() override;
		virtual void nextStreamSection() override;
		virtual size_t getStreamSectionCount() const override;
		virtual void writeData(const char* data, size_t size) override;
		template<typename T>
		void writeObject(const T& object) { sections[sectionIndex].writeObject(object); };
		template<typename T>
		void writeArray(const std::vector<T>& vector) { sections[sectionIndex].writeArray(vector); };
		virtual compressedBuffer flush();
	private:
		size_t sectionIndex = 0;

		std::filesystem::path m_path;
		std::ofstream m_stream;
		std::vector<buffer> sections;
	};
}
#endif // !FILE_STREAM_WRITER




