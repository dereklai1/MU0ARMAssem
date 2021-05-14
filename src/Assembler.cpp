#include "Assembler.h"

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <map>


std::map<std::string, std::string> hexLU = {
	{"0000", "0"},
	{"0001", "1"},
	{"0010", "2"},
	{"0011", "3"},
	{"0100", "4"},
	{"0101", "5"},
	{"0110", "6"},
	{"0111", "7"},
	{"1000", "8"},
	{"1001", "9"},
	{"1010", "A"},
	{"1011", "B"},
	{"1100", "C"},
	{"1101", "D"},
	{"1110", "E"},
	{"1111", "F"}
};

Assembler::Assembler(const std::string& configpath) {

	std::ifstream infile;
	infile.open(configpath);
	if (!infile.is_open()) {
		std::cout << "config file not found" << std::endl;
		exit(-1);
	}

	std::string opcode, code;
	while (infile >> opcode >> code) {
		instructionSet.insert( std::pair<std::string, std::string>(opcode, code) );
	}

	infile.close();

	//instructionSet = {
	//	{"LDR", "0000"},
	//	{"STR", "0000"},
	//	{"JMP", "0100"},
	//	{"JMI", "0101"},
	//	{"JEQ", "0110"},
	//	{"STP", "0111"},
	//	{"ADD", "1000"},
	//	{"SUB", "1001"},
	//	{"MUL", "1010"},
	//	{"DIV", "1011"},
	//	{"MOV", "1100"},
	//	{"CMP", "1101"}
	//};

	shifts = {
		{"LSL", "00"},
		{"LSR", "01"},
		{"ASR", "10"},
		{"ROR", "11"}
	};

}



std::string Assembler::translate(std::string instr) {

	// delete trailing comment
	instr = instr.substr(0, instr.find(';'));

	// tokenize string
	auto tokens = StringToVector(instr, ' ');

	// search dictionary for first token (opcode)
	std::string op = tokens[0];
	std::string opcode = instructionSet[op.substr(0, 3)];

	std::string last12;
	if (opcode == "0000") {
		// ldst
		last12 = LoadStore(tokens, (tokens[0] == "LDR") ? true : false);
	}
	else if (opcode[0] == '0') {
		// other pc counter instructions
		// in pc counter instruction only 2 tokens (eg. JMP 0x1234)
		if (tokens.size() == 1) {
			last12 = "000000000000";
		}
		else {
			last12 = DecToNBitBin(tokens[1], 12);
		}
	}
	else if (opcode[0] == '1') {
		// data processing instructions
		last12 = DataProcessing(tokens, (op[op.length() - 1] == 'S') ? true : false);
	}
	else {
		last12 = "BAD OPCODE";
	}

	return opcode + last12;
}


std::string Assembler::LoadStore(const std::vector<std::string>& tokens, bool isLoad) {
	// Instruction format:
	// <OP> <Rd> <Rm> <n> <ldstflags(w/p)>; <comment>
//token  0   1    2    3     4

	std::string d, l, w, p, u, n, m;

	l = (isLoad) ? "1" : "0";

	d = tokens[1];
	d = d.substr(1, std::string::npos);
	d = DecToNBitBin(d, 2);

	m = tokens[2];
	m = m.substr(1, std::string::npos);
	m = DecToNBitBin(m, 2);

	if (tokens[3].find_first_of("+-") != std::string::npos) {
		if (tokens[3][0] == '+') {
			u = "1";
		}
		else if (tokens[3][0] == '-') {
			u = "0";
		}
		else {
			std::cout << "invalid operator before N" << std::endl;
			exit(-1);
		}
		n = DecToNBitBin(tokens[3].substr(1, std::string::npos), 4);
	}
	else {
		n = DecToNBitBin(tokens[3], 4);
		u = "1";
	}

	std::string flags = tokens[4];
	
	w = (flags.find('w') != std::string::npos) ? "1" : "0";
	p = (flags.find('p') != std::string::npos) ? "1" : "0";

	if (!isLoad) {
		std::string tmp = m;
		m = d;
		d = tmp;
	}

	std::string ret = "";
	
	ret += d;
	ret += l;
	ret += w;
	ret += p;
	ret += u;
	ret += n;
	ret += m;

	return ret;
}


std::string Assembler::DataProcessing(const std::vector<std::string>& tokens, bool sbit) {
	// Instruction format:
	// reg: <OP(S)> <Rd> <Rm> <"SHIFT""B">; <comment>
//token        0     1    2*        3     
	// k  : <OP(S)> <Rd> <k> <ROR"ROT">
//token        0     1    2*     3

	int tokennum = tokens.size();
	std::string d, c, s, b, shift, m, rot, k;
	
	s = sbit ? "1" : "0";

	d = tokens[1];
	d = d.substr(1, std::string::npos);
	d = DecToNBitBin(d, 2);

	std::string tk2 = tokens[2];

	std::string ret = "";
	ret += d;

	if (tk2.find('R') != std::string::npos) {
		// register format
		c = "0";

		m = tokens[2];
		m = m.substr(1, std::string::npos);
		m = DecToNBitBin(m, 2);

		if (tokennum > 3) {
			shift = shifts[tokens[3].substr(0, 3)];
			b = DecToNBitBin(tokens[3].substr(3, std::string::npos), 4);
		}
		else {
			shift = "00";
			b = "0000";
		}

		ret += c;
		ret += s;
		ret += b;
		ret += shift;
		ret += m;
	}
	else {
		// immediate format
		c = "1";
		
		// TODO: HEX TO BINARY
		//if(tokens[2].substr(0, 2) == "0x")

		k = DecToNBitBin(tokens[2], 5);
		if (tokennum > 3) {
			rot = DecToNBitBin(tokens[3].substr(3, std::string::npos), 3);
		}
		else {
			rot = "000";
		}
		ret += c;
		ret += s;
		ret += rot;
		ret += k;
	}

	return ret;
}


// UTILITY
std::vector<std::string> StringToVector(std::string str, char separator) {
	std::vector<std::string> words;

	std::stringstream ss(str);
	std::string temp;

	while (getline(ss, temp, separator)) {
		words.push_back(temp);
	}

	return words;
}


std::string DecToNBitBin(const std::string& dec, unsigned int n) {
	int num = std::stoi(dec);
	std::string bin = "";

	while (num > 0) {
		bin += std::to_string(num % 2);
		num = num / 2;
	}

	bin = ReverseStr(bin);

	while (bin.length() < n) {
		bin = "0" + bin;
	}

	return bin;
}


std::string ReverseStr(const std::string& str) {
	int len = str.length();
	std::string newstr = "";
	for (int i = len - 1; i >= 0; i--) {
		newstr += str[i];
	}
	return newstr;
}

std::string BinToHex12(const std::string& binstr) {
	
	std::string ret = "";
	
	for (int i = 0; i < 16; i += 4) {
		std::string part = binstr.substr(i, 4);
		ret += hexLU[part];
	}

	return ret;
}