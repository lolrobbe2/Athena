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
	athena::buffer buf2;
	athena::buffer buf3;

	buf.writeObject(header());
	buf2.writeObject(header2());

	buf3.writeObject(buf);
	buf3.writeObject(buf2);
}