#define AT_C_API

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
int main()
{
	athena::buffer buf;
	
	std::vector<header> headers;
	headers.resize(30);

	buf.writeArray(headers);

	athena::compressedBuffer compressed { buf };

	athena::buffer decompressedBuf = compressed.decompress();

	std::vector<header2> headersDecompressed = decompressedBuf.readArray<header2>();

	for (size_t i = 0; i < 30; i++)
	{
		std::cout << headersDecompressed[i].test << std::endl;
	}
}