#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <algorithm>

#include "utility.h"

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


inline bool file_exists(const std::string& name) {
	std::ifstream f(name.c_str());
	return f.good();
}

