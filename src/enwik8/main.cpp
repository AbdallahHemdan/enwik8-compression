#include "LZW.h"

int main(int argc, char *argv[])
{
	LZW lzw;
	if (argc > 1 && std::string(argv[1]) == std::string("encode|decode"))
	{
		auto input = std::ifstream(std::string(argv[2]));
		std::ofstream encoded("./encoded.bin", std::ios::ios_base::binary | std::ios_base::out);
		if (lzw.encode(input, encoded) == false) // failer
			return -1;
		input.close();
		encoded.close();
	}
	if (argc > 1 && std::string(argv[1]) == std::string("encode|decode"))
	{
		auto input = std::ifstream("./encoded.bin", std::ios_base::binary | std::ios_base::in);
		std::ofstream decoded("./decoded.txt", std::ios_base::binary | std::ios_base::out);
		if (lzw.decode(input, decoded) == false) // failer
		{
			return -1;
		}
		input.close();
		decoded.close();
	}

	if (argc > 1 && std::string(argv[1]) == std::string("encode"))
	{
		auto input = std::ifstream(std::string(argv[2]));
		std::ofstream encoded("./encoded.bin", std::ios::ios_base::binary | std::ios_base::out);
		if (lzw.encode(input, encoded) == false) // failer
			return -1;
		input.close();
		encoded.close();
	}

	if (argc > 1 && std::string(argv[1]) == std::string("decode"))
	{
		auto input = std::ifstream("./encoded.bin", std::ios_base::binary | std::ios_base::in);
		std::ofstream decoded("./decoded.txt", std::ios_base::binary | std::ios_base::out);
		if (lzw.decode(input, decoded) == false) // failer
		{
			return -1;
		}
		input.close();
		decoded.close();
	}
}