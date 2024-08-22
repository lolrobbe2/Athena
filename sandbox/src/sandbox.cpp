#define AT_C_API

#include <athena.h>
#include <iostream>
struct header
{
	const char test[13] = "helping hand";
};
struct header2
{
	const char test[13] = "helping hand";
	size_t size = 250;
};
int main()
{
	athena::buffer buf;

	for (size_t i = 0; i < 30; i++)
	{
		buf.writeObject(header2());
	}
	athena::compressedBuffer compressed { buf };

	athena::buffer decompressedBuf = compressed.decompress();

	for (size_t i = 0; i < 30; i++)
	{
		std::cout << decompressedBuf.readObject<header>().test << std::endl;
	}
}