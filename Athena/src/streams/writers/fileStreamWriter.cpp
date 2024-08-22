#include "fileStreamWriter.h"
#include <exceptions/indexBoundsException.h>
namespace athena 
{
	fileStreamWriter::fileStreamWriter(std::filesystem::path& path) :
		m_path(path)
	{
		m_stream = std::ofstream(path, std::ofstream::out | std::ofstream::binary);
		sections.resize(1);
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
		if (sectionIndex + 1 > sections.size()) 
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
	void fileStreamWriter::flush()
	{
		//TODO flush logic (compress all sections and write to buffer and recompress insid final frame!)
	}
}