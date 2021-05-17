#include "Assembler.h";
#include "Translater.h";

#include <fstream>
#include <iostream>


inline bool file_exists(const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}


Assembler::Assembler(const std::string& inputpath, const std::string& configpath) {
	translater = new Translater(configpath);


    if (file_exists(inputpath) && file_exists(configpath)) {

        std::ifstream infile;
        infile.open(inputpath);
        if (!infile.is_open()) {
            std::cout << "file cannot be opened" << std::endl;
            exit(-1);
        }

        std::vector<std::string> lines;

        std::string tmp;
        while (getline(infile, tmp)) {
            lines.push_back(tmp);
        }
        infile.close();

        std::cout << "Translating..." << std::endl;

        std::vector<std::string> binarylines;
        for (std::string line : lines) {
            binarylines.push_back(assem.translate_line(line));
        }

        std::cout << "Writing Output File..." << std::endl;

        std::ofstream outfile(outputpath);
        outfile << "Binary Format:" << "\n";
        for (std::string line : binarylines) {
            outfile << "0b" << line << "\n";
        }


        outfile << "\n" << "Hex format:" << "\n";
        for (std::string line : binarylines) {

            outfile << "0x" << BinToHex12(line) << "\n";
        }

        outfile.close();

    }
    else {
        generate_files();

    }

}


void Assembler::generate_files() {
    std::cout << "input and config files do not exist yet, generating files..." << std::endl;

    if (!file_exists(inputpath)) {
        std::ofstream outfile(inputpath);
        outfile.close();
    }

    if (!file_exists(configpath)) {
        std::ofstream outfile(configpath);
        outfile << config_data;
        outfile.close();
    }
}