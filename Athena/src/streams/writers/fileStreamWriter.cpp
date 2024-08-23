#include "fileStreamWriter.h"
#include <exceptions/indexBoundsException.h>
#include <future>
#include <streams/compression/compressedBuffer.h>
namespace athena 
{

	fileStreamWriter::fileStreamWriter(std::filesystem::path& path) :
		m_path(path)
	{
		m_stream = std::ofstream(path, std::ofstream::out | std::ofstream::binary);
		sections.resize(1);
	}
	fileStreamWriter::~fileStreamWriter()
	{
		m_stream.close();
	}
	bool fileStreamWriter::isStreamGood() const
	{
		return m_stream.good();
	}
	void fileStreamWriter::setStreamPosition(size_t index)
	{
		if (index < 0 || index > sections.size()) throw new exceptions::indexOutOfBoundsException("streamPosition was out of bounds");
		sectionIndex = index;
	}
	void fileStreamWriter::previousStreamSection()
	{
		sectionIndex = std::max((size_t)0, sectionIndex - 1);
	}
	void fileStreamWriter::nextStreamSection()
	{
		if (sectionIndex + 1 == sections.size()) 
			sections.push_back(buffer());

		sectionIndex++;
	}
	size_t fileStreamWriter::getStreamSectionCount() const
	{
		return sections.size();
	}
	void fileStreamWriter::writeData(const char* data, size_t size)
	{
		sections[sectionIndex].writeData(data,size);
	}
	compressedBuffer fileStreamWriter::flush()
	{
		std::vector<std::future<athena::compressedBuffer>> compressedBufferFutures;
		//TODO flush logic (compress all sections and write to buffer and recompress insid final frame!)
		   // Compress each buffer in a separate thread
		for (const auto& section : sections)
		{
			compressedBufferFutures.push_back(std::async(std::launch::async, [&section]() {
				return athena::compressedBuffer{ section }; // Compress buffer
				}));
		}

		std::vector<compressedBuffer> compressedSections;
		//Collect the compressed buffers.
		for (auto& future : compressedBufferFutures)
			compressedSections.push_back(future.get());

		athena::buffer sectionsBuffer;
		sectionsBuffer.writeArray(compressedSections);

		athena::compressedBuffer sectionsCompressedBuffer{ sectionsBuffer };

	
		m_stream.write(sectionsCompressedBuffer.data(), sectionsCompressedBuffer.size());
		return sectionsCompressedBuffer;
	}
}