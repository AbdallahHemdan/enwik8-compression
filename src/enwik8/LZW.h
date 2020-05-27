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
	char curCh;
	double time_taken;
	ui code;
	ui lstCode;
	ui prvCode;
	time_t estart, eend;
	time_t dstart, dend;
	std::unordered_map<std::string, ui> lookup_si;
	std::unordered_map<ui, std::string> lookup_is;

	void calculateExecutionTime(std::string encodeOrdecode);
	void initLookup(std::string encodeOrdecode);
	bool checkStreamValidation(std::ifstream &input);
	void validateCode(std::string& curMatch, std::string& nxtMatch, std::ofstream &output);
	void processLast(std::string& curMatch, std::ofstream &output);
	bool validateDecodingStream(std::ifstream &input);
	void processCurrentCode(std::ofstream &output);
public:
	LZW();
	bool encode(std::ifstream &input, std::ofstream &encoded);
	bool decode(std::ifstream &input, std::ofstream &decoded);
	~LZW();
};
