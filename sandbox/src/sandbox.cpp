
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

struct backHeader 
{
	const char head[5] = "LPRJ";
};
int main()
{
	std::vector<header> headers;
	headers.resize(100);

	std::vector<header2> headers2;
	headers2.resize(100);
	std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;

	std::filesystem::path path = "./temp.bin";

	athena::fileStreamWriter* streamWriter = new athena::fileStreamWriter(path);
	streamWriter->writeArray(headers);
	streamWriter->nextStreamSection();
	streamWriter->writeArray(headers2);
	streamWriter->flush();
}