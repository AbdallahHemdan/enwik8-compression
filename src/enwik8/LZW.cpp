#include "LZW.h"


void LZW::calculateExecutionTime(std::string encodeOrdecode)
{
	if (encodeOrdecode == "encode") {
		double time_taken = double(eend - estart);
		std::cout << "Time taken by encoding is : " << std::fixed
			<< time_taken << std::setprecision(5);
	}
	else {
		double time_taken = double(dend - dstart);
		std::cout << "Time taken by decoding is : " << std::fixed
			<< time_taken << std::setprecision(5);
	}
	std::cout << " sec " << std::endl;
	std::cout << "end decoding ..." << std::endl;
}

LZW::LZW()
{
}

bool LZW::encode(std::ifstream &buffer, std::ofstream &encoded)
{
	std::cout << "start encoding ..." << std::endl;
	time(&estart);
	std::ios_base::sync_with_stdio(false);

	// declar and init the lookup table
	std::unordered_map<std::string, ui> lookup;
	for (ui i = 0; i < mx; i++) {
		lookup[std::string(1, char(i))] = i;
	}

	// read 
	char c;
	if (!buffer.get(c))
	{ // fails to read from the stream
		std::cout << "fails to read from the stream" << std::endl;
		return false;
	}

	std::string match(1, c);
	ui lstCode = mx;
	while (buffer.get(c))
	{
		// search for match
		std::string nxtMatch = match;
		nxtMatch.push_back(c);

		// known code
		if (lookup.find(nxtMatch) != lookup.end())
		{
			match = nxtMatch;
		}
		else // unknown code
		{
			ui code = lookup[match];
			encoded.put(code & semi);
			encoded.put((code >> 8) & semi);
			encoded.put((code >> 16) & semi);
			lookup[nxtMatch] = lstCode++;
			match = std::string(1, c);
		}
	}

	// process and encode lst match string
	ui code = lookup[match];
	encoded.put(code & semi);
	encoded.put((code >> 8) & semi);
	encoded.put((code >> 16) & semi);

	// calculate time take by encoding function to process all the file
	time(&eend);
	calculateExecutionTime("encode");
	return true;
}

bool LZW::decode(std::ifstream &buffer, std::ofstream &decoded)
{
	std::cout << "start decoding ..." << std::endl;
	time(&dstart);
	std::unordered_map<ui, std::string> table;

	//Initialize codes table
	for (ui i = 0; i < mx; i++)
		table[i] = std::string(1, char(i));

	ui lstCode = mx;
	ui prvCode = 0;

	if (!buffer.read((char *)&prvCode, 3))
	{
		return false;
	}

	// Decode first symbol
	const char *decodedStr = table[prvCode].c_str();
	decoded << decodedStr;

	ui code = 0;
	char c = table[prvCode][0];
	while (buffer.read((char *)&code, 3))
	{
		std::string match;
		if (table.find(code) == table.end())
		{
			match = table[prvCode];
			match.push_back(c);
		}
		else
		{
			match = table[code];
		}

		// Decode the match
		const char *matchStr = match.c_str();
		decoded << matchStr;
		c = match[0];

		// Append previous match + first read character
		table[lstCode] = table[prvCode];
		table[lstCode++].push_back(c);
		prvCode = code;
		code = 0x0000;
	}
	time(&dend);
	calculateExecutionTime("decode");
	return true;
}

LZW::~LZW()
{
}
