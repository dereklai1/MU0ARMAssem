#pragma once

#include <vector>
#include <string>
#include <map>


class Assembler {
public:
	Assembler(const std::string& configpath);
	std::string translate(std::string instr);

private:
	std::map<std::string, std::string> instructionSet;
	std::map<std::string, std::string> shifts;

	std::string LoadStore(const std::vector<std::string>& tokens, bool isLoad);
	std::string FloatDataProcessing(const std::vector<std::string>& tokens);
	std::string IntDataProcessing(const std::vector<std::string>& tokens, bool sbit);

	std::string ParseReg(const std::string& token);
};

const std::string config_data = R"(LDR 0000
STR 0000
JMP 0100
JMI 0101
JEQ 0110
STP 0111
ADD 1000
SUB 1001
MUL 1010
DIV 1011
MOV 1100
CMP 1101)";