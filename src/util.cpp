#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <algorithm>
#include <cmath>

#include "util.h"

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

std::map<char, std::string> binLU = {
	{'0', "0000"},
	{'1', "0001"},
	{'2', "0010"},
	{'3', "0011"},
	{'4', "0100"},
	{'5', "0101"},
	{'6', "0110"},
	{'7', "0111"},
	{'8', "1000"},
	{'9', "1001"},
	{'A', "1010"},
	{'B', "1011"},
	{'C', "1100"},
	{'D', "1101"},
	{'E', "1110"},
	{'F', "1111"},
};

std::string int_to_halfprecision(const std::string str) {
	return int_to_halfprecision(std::stoi(str));
}


std::string int_to_halfprecision(int num) {
	bool negative = (num < 0) ? true : false;
	num = abs(num);

	std::string bin = int_to_bin(num, 15);

	int first1index = bin.find("1");

	std::string fraction;
	fraction = bin.substr(first1index + 1, std::string::npos);
	while (fraction.size() < 10) {
		fraction += "0";
	}

	std::cout << fraction << std::endl;

	return "";
}


std::string int_to_bin(const std::string& dec, unsigned int n) {
	return int_to_bin(std::stoi(dec), n);
}

std::string int_to_bin(int num, unsigned int n) {
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

int bin_to_int(const std::string& bin){
	int ret = 0;
	int len = bin.size();
	for (int i = 0; i < len; i++) {
		ret += (bin[i] == '1') ? std::pow(2.0, len - i - 1.0) : 0;
	}
	return ret;
}

std::string ones_compliment(const std::string& bin) {
	std::string ret = "";
	for (int i = 0; i < bin.size(); i++) {
		if (bin[i] == '1') { ret += '0'; }
		else { ret += '1'; }
	}
	return ret;
}

std::string zero_str(int len) {
	std::string str = "";
	for (int i = 0; i < len; i++) {
		str += '0';
	}
	return str;
}

std::string bin_to_2s(const std::string& bin) {
	std::string ones = ones_compliment(bin);
	std::string twos = zero_str(bin.size());
	bool carry = true;
	for (int i = bin.size() - 1; i >= 0; i--) {
		if (ones[i] == '1' && carry) {
			twos[i] = '0';
		}
		else if (ones[i] == '0' && carry) {
			twos[i] = '1';
			carry = false;
		}
		else {
			twos[i] = ones[i];
		}
	}
	return twos;
}

std::vector<std::string> StringToVector(std::string str, char separator) {
	std::vector<std::string> words;

	std::stringstream ss(str);
	std::string temp;

	while (getline(ss, temp, separator)) {
		words.push_back(temp);
	}

	return words;
}


std::string ReverseStr(const std::string& str) {
	int len = str.length();
	std::string newstr = "";
	for (int i = len - 1; i >= 0; i--) {
		newstr += str[i];
	}
	return newstr;
}

std::string join_strings(const std::vector<std::string>& v, char delim) {
	int size = v.size();
	std::string out = "";
	for (int i = 0; i < size; i++) {
		out += v[i];
		if (i != (size - 1)) {
			out += delim;
		}
	}
	return out;
}


std::string BinToHex12(const std::string& binstr) {

	std::string ret = "";

	for (int i = 0; i < 16; i += 4) {
		std::string part = binstr.substr(i, 4);
		ret += hexLU[part];
	}

	return ret;
}

void trim_binary(std::string& bin, int len) {
	// too short
	while (bin.length() < len) {
		bin = "0" + bin;
	}

	// too long
	while (bin.length() > len) {
		bin = bin.substr(1, std::string::npos);
	}
}

std::string any_num_to_binary(const std::string& input, int len) {
	std::string prefix = input.substr(0, 2);
	if (prefix == "0b") { // binary format
		std::string bin = input.substr(2, std::string::npos);
		trim_binary(bin, len);
		return bin;
	}
	else if (prefix == "0x") { // hex
		std::string hex = input.substr(2, std::string::npos);
		std::string bin = "";
		for (int i = 0; i < hex.size(); i++) {
			bin += binLU[hex[i]];
		}
		trim_binary(bin, len);
		return bin;
	}
	else { // decimal
		return int_to_bin(input, len);
	}
}


inline bool file_exists(const std::string& name) {
	std::ifstream f(name.c_str());
	return f.good();
}

