#include <iostream>
#include <fstream>
#include <vector>

#include "Assembler.h"
#include "util.h"

// TODO:

// 2. Segment different blocks of code using tags, @CPU 1
// 3. add asserts so that program crashes when stuff goes wrong
//


inline bool file_exists(const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}


int main()
{

    std::string inputpath = "./input.txt";
    std::string outputpath = "./output.txt";

    std::string configpath = "./config.txt";

    Assembler assem(configpath);

    if (file_exists(inputpath) && file_exists(configpath)) {

        assem.read_lines(inputpath);

        std::cout << "Translating..." << std::endl;

        assem.first_pass();
        assem.second_pass();

        std::cout << "Writing Output File: "<< outputpath << std::endl;


        assem.write_output(outputpath);

    }
    else {

        std::cout << "input and config files do not exist yet, generating files..." << std::endl;

        if (!file_exists(inputpath)) {
            std::cout << "Generating input.txt...\n";
            std::ofstream outfile(inputpath);
            outfile.close();
        }

        if (!file_exists(configpath)) {
            std::cout << "Generating config.txt...\n";
            std::ofstream outfile(configpath);
            outfile << config_data;
            outfile.close();
        }
    }

    return 0;
}

