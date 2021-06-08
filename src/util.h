#pragma once

std::string int_to_halfprecision(const std::string str);
std::string int_to_halfprecision(int num);
std::string int_to_bin(const std::string& dec, unsigned int n);
std::string int_to_bin(int num, unsigned int n);

int bin_to_int(const std::string& bin);

std::string ones_compliment(const std::string& bin);
std::string bin_to_2s(const std::string& bin);


std::string any_num_to_binary(const std::string& input, int len);

std::vector<std::string> StringToVector(std::string str, char separator);
std::string join_strings(const std::vector<std::string>& v, char delim);
std::string ReverseStr(const std::string& str);
std::string BinToHex12(const std::string& binstr);

inline bool file_exists(const std::string& name);

