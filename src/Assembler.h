#pragma once

#include "Translater.h"


class Assembler {
public:

	Assembler(const std::string& inputpath, const std::string& configpath);

	std::vector<std::string> lines;

	std::vector<std::string> binary_lines;
	std::vector<std::string> hex_lines;

private:
	Translater* translater;
	std::string* inputpath;
	std::string* configpath;
	std::string* outputpath;

	void binarylines_to_hex();

	void generate_files();

};
