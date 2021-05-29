#include <iostream>
#include <fstream>
#include <vector>

#include "Assembler.h"
#include "util.h"


inline bool file_exists(const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}


int main()
{
    const std::string configpath = "./config.txt";
    const std::string inputpath = "./input.txt";
    const std::string outputpath = "./output.txt";

    Assembler assem(configpath);

    if (file_exists(inputpath) && file_exists(configpath)) {

        assem.read_lines(inputpath);

        std::cout << "Translating..." << std::endl;

        assem.first_pass();
        assem.second_pass();

        std::cout << "Writing Output File..." << std::endl;


        assem.write_output(outputpath);

    }
    else {

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

    return 0;
}

