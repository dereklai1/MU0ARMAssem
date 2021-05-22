#pragma once

std::string int_to_halfprecision(const std::string str);
std::string int_to_halfprecision(int num);
std::string int_to_bin(const std::string& dec, unsigned int n);
std::string int_to_bin(int num, unsigned int n);


std::vector<std::string> StringToVector(std::string str, char separator);
std::string join_strings(const std::vector<std::string>& v, char delim);
std::string ReverseStr(const std::string& str);
std::string BinToHex12(const std::string& binstr);

inline bool file_exists(const std::string& name);
