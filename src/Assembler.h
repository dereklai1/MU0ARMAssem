#pragma once

#include <vector>
#include <string>
#include <map>


std::vector<std::string> StringToVector(std::string str, char separator);
std::string DecToNBitBin(const std::string& dec, unsigned int n);
std::string BinToHex12(const std::string& binstr);
std::string ReverseStr(const std::string& str);


class Assembler {
public:
	Assembler(const std::string& configpath);
	std::string translate(std::string instr);

private:
	std::map<std::string, std::string> instructionSet;
	std::map<std::string, std::string> shifts;

	std::string LoadStore(const std::vector<std::string>& tokens, bool isLoad);
	std::string DataProcessing(const std::vector<std::string>& tokens, bool sbit);
};

