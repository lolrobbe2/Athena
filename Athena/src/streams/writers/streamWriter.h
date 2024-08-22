#pragma once
#ifndef STREAM_WRITER
#define STREAM_WRITER
namespace luna 
{
	class streamWriter
	{
	public:
		virtual ~streamWriter();
		virtual bool isStreamGood() const;
		virtual void setStreamPosition();
		virtual bool writeData(const char* data, size_t size);
		operator bool() const { return isStreamGood(); }
	private:

	};
}
#endif // !STREAM_WRITER
