#include "fileStreamReader.h"
#include <exceptions/indexBoundsException.h>
#include <exceptions/badStreamException.h>

namespace athena
{
	//TODO file stream is good check!
	fileStreamReader::fileStreamReader(std::filesystem::path& path) : m_path(path)
	{
		m_stream = std::ifstream(path,std::ifstream::in | std::ifstream::binary);

		if (!m_stream.good()) throw exceptions::badStreamException("reader stream was bad!");
		if (!m_stream.is_open()) throw exceptions::badStreamException("reader stream was not open!");
		if (!std::filesystem::file_size(path)) throw exceptions::badStreamException("m_stream filesize was 0! (check if file is open somewhere else in program!)");
		size_t size = std::filesystem::file_size(path);

		char* data = (char*)malloc(size);
		m_stream.read(data, size);

		compressedBuffer compressedSections{ data,size }; //all compressed sections are compressed togheter in a single buffer;

		buffer sectionsBuffer = compressedSections.decompress();
		m_compressedSections = sectionsBuffer.readArray<compressedBuffer>();
		m_sections.resize(m_compressedSections.size(), nullptr);
	}
	fileStreamReader::~fileStreamReader()
	{
		for (buffer* ptr : m_sections) 
			if(ptr) delete ptr;
		
	}
	bool fileStreamReader::isStreamGood() const
	{
		return m_stream.good();
	}
	void fileStreamReader::setSectionPointerPosition(size_t index)
	{
		m_sections[m_sectionIndex]->setPointerPosition(index);
	}
	void fileStreamReader::setStreamPosition(size_t index)
	{
		if (index < 0 || index > m_sections.size()) throw exceptions::indexOutOfBoundsException("streamPosition was out of bounds");
		m_sectionIndex = index;
	}
	void fileStreamReader::previousStreamSection()
	{
		setStreamPosition(m_sectionIndex - 1);
	}
	void fileStreamReader::nextStreamSection()
	{
		setStreamPosition(m_sectionIndex + 1);
	}
	size_t fileStreamReader::getStreamSectionCount() const
	{
		return m_sectionIndex;
	}
	const char* fileStreamReader::readData(size_t size)
	{
		if (m_sections[m_sectionIndex]) return m_sections[m_sectionIndex]->readData(size);
		m_sections[m_sectionIndex] = &m_compressedSections[m_sectionIndex].decompress();
		return m_sections[m_sectionIndex]->readData(size);
	}
}