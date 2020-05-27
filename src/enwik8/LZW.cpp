#include "LZW.h"


LZW::LZW() {}

void LZW::calculateExecutionTime(std::string encodeOrdecode) {
	if (encodeOrdecode == "encode") {
		time_taken = double(eend - estart);
		std::cout << "Time taken by encoding is : " << std::fixed
			<< time_taken << std::setprecision(5);
	}
	else {
		time_taken = double(dend - dstart);
		std::cout << "Time taken by decoding is : " << std::fixed
			<< time_taken << std::setprecision(5);
	}
	std::cout << " sec " << std::endl;
	std::cout << "end decoding ..." << std::endl;
}

void LZW::initLookup(std::string encodeOrdecode) {
	for (ui i = 0; i < mx; i++) {
		if (encodeOrdecode == "encode") {
			this->lookup_si[std::string(1, char(i))] = i;
		}
		else {
			this->lookup_is[i] = std::string(1, char(i));
		}
	}
}

bool LZW::checkStreamValidation(std::ifstream &input) {
	if (!input.get(curCh)) {
		std::cout << "fails to read from the stream" << std::endl;
		return false;
	}
	return true;
}

void LZW::validateCode(std::string& curMatch, std::string& nxtMatch, std::ofstream &output) {
	// check if the current code exists or not in the table
	if (this->lookup_si.find(nxtMatch) != this->lookup_si.end()) { // it's a known code
		curMatch = nxtMatch;
	}
	else { // it's unknown code

		 // 1st. store it in the file
		ui code = this->lookup_si[curMatch];
		output.put(code & semi);
		output.put((code >> 8) & semi);
		output.put((code >> 16) & semi);

		// 2nd. save it in the table 
		this->lookup_si[nxtMatch] = lstCode++;

		// 3rd. reset current match
		curMatch = std::string(1, this->curCh);
	}
}

void LZW::processLast(std::string& curMatch, std::ofstream &output) {
	ui code = this->lookup_si[curMatch];
	output.put(code & semi);
	output.put((code >> 8) & semi);
	output.put((code >> 16) & semi);
}

bool LZW::encode(std::ifstream &input, std::ofstream &output) {
	std::cout << "start encoding ..." << std::endl;
	time(&estart);
	std::ios_base::sync_with_stdio(false);

	// init the lookup table
	this->initLookup("encode");
	// fails to read from the stream
	if (!this->checkStreamValidation(input)) {
		return false;
	}

	std::string curMatch(1, this->curCh);
	lstCode = mx;

	// process all file
	while (input.get(this->curCh)) {
		std::string nxtMatch = curMatch;
		nxtMatch += this->curCh;
		this->validateCode(curMatch, nxtMatch, output);
	}

	// process and encode last match
	this->processLast(curMatch, output);

	// calculate time take by encoding function to process all the file
	time(&eend);
	this->calculateExecutionTime("encode");
	return true;
}

bool LZW::decode(std::ifstream &input, std::ofstream &output)
{
	std::cout << "start decoding ..." << std::endl;
	time(&dstart);

	// init the lookup table
	this->initLookup("decode");

	ui lstCode = mx;
	ui prvCode = 0;

	if (!input.read((char *)&prvCode, 3)) {
		return false;
	}

	// Decode first symbol
	const char *decodedStr = this->lookup_is[prvCode].c_str();
	output << decodedStr;

	ui code = 0;
	char curCh = this->lookup_is[prvCode][0];
	while (input.read((char *)&code, 3)) {
		std::string curMatch;
		if (this->lookup_is.find(code) == this->lookup_is.end()) {
			curMatch = this->lookup_is[prvCode];
			curMatch.push_back(curCh);
		}
		else {
			curMatch = lookup_is[code];
		}

		// Decode the curMatch
		const char *matchStr = curMatch.c_str();
		output << matchStr;
		curCh = curMatch[0];

		// Append previous curMatch + first read character
		this->lookup_is[lstCode] = this->lookup_is[prvCode];
		this->lookup_is[lstCode++].push_back(curCh);
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
