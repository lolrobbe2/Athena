#define AT_C_API

#include <athena.h>
#include <iostream>
struct header
{
	const char test[5] = "help";
};
struct header2
{
	const char test[13] = "helping hand";
};
int main()
{
	athena::buffer buf;

	for (size_t i = 0; i < 30; i++)
	{
		buf.writeObject(header());
	}
	athena::compressedBuffer compressed { buf };
}