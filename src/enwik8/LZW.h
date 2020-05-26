#pragma once
#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <chrono>
#include <fstream>

#define ui unsigned int
#define pb push_back
#define mx (1 << 8)
#define semi (0xFF)

class LZW
{
private:
	time_t estart, eend;
	time_t dstart, dend;
	void calculateExecutionTime(std::string encodeOrdecode);
public:
	LZW();
	bool encode(std::ifstream &buffer, std::ofstream &encoded);
	bool decode(std::ifstream &buffer, std::ofstream &decoded);
	~LZW();
};
