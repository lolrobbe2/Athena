
#include <athena.h>
#include <iostream>
//represents old version
struct header
{
	const char test[13] = "helping hand";
};

//represents new version
struct header2
{
	const char test[13] = "helping hand";
	size_t size = 250;
};

struct header3
{
	const char test[15] = "sjsefsfessesef";
	size_t size = 250;
	uint32_t subsize = 651516;
};

struct backHeader 
{
	const char head[5] = "LPRJ";
};
int main()
{
	/*
	std::vector<header> headers;
	headers.resize(100);

	std::vector<header2> headers2;
	headers2.resize(100);

	std::vector<header3> headers3;
	headers3.resize(100);
	std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
	*/
	std::filesystem::path path = "./temp.bin";
	/*
	athena::fileStreamWriter* streamWriter = new athena::fileStreamWriter(path);
	streamWriter->writeArray(headers);
	streamWriter->writeArray(headers3);
	streamWriter->nextStreamSection();
	streamWriter->writeArray(headers2);
	streamWriter->writeArray(headers3);
	streamWriter->flush();

	delete streamWriter;
	*/

	athena::fileStreamReader* streamReader = new athena::fileStreamReader(path);

	std::vector<header> headersRead = streamReader->readArray<header>();
	std::vector<header3> headersRead3 = streamReader->readArray<header3>();

	streamReader->nextStreamSection();

	std::vector<header2> headersRead2 = streamReader->readArray<header2>();
	std::vector<header3> headersRead3_2 = streamReader->readArray<header3>();

}