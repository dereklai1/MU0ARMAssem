#pragma once

#include <vector>
#include <string>
#include <map>


class Assembler {
public:
	Assembler(const std::string& configpath);
	
	void read_lines(const std::string& inputpath);
	void first_pass();
	void second_pass();
	void write_output(const std::string& outputpath);
	
	std::string translate(std::string instr);

private:
	std::vector<std::string> lines;
	std::vector<std::string> binarylines;
	std::map<std::string, int> labels;

	std::map<std::string, std::string> instructionSet;
	std::map<std::string, std::string> shifts;

	std::string LoadStore(const std::vector<std::string>& tokens, bool isLoad);
	std::string FloatDataProcessing(const std::vector<std::string>& tokens);
	std::string IntDataProcessing(const std::vector<std::string>& tokens, bool sbit);
	std::string FloatingMove(const std::vector<std::string>& tokens);

	std::string ParseReg(const std::string& token);
};

const std::string config_data = R"(LDR 0000
STR 0000
SWP 0011
JMP 0100
JMI 0101
JEQ 0110
STP 0111
ADD 1000
SUB 1001
MUL 1010
DIV 1011
MOV 1100
CMP 1101
FLD 1110)";