#include "aoc-lib.h"
#include <boost/program_options.hpp>
#include <fstream> 
#include <iostream>

using namespace std;

class AoCOptions::variables_map {
public:
	boost::program_options::variables_map vm;
};

std::vector<std::string> read_lines_from_file(const std::string& file_name)
{
    std::vector<std::string> lines;
    std::ifstream file(file_name);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    } else {
        std::cerr << "Unable to open file: " << file_name << std::endl;
    }
    return lines;
}

AoCOptions::AoCOptions(int argc, char** argv)
    : vm(new variables_map())
{
    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "Help Message")
        ("verbose", "Verbose")
        ("input-file", po::value<string>(), "input file");

    try {
        po::store(po::parse_command_line(argc, argv, desc), vm->vm);
        po::notify(vm->vm);
    }
    catch (const po::error& ex) {
        std::cerr << ex.what() << '\n';
        std::cerr << desc << '\n';
    }
}

AoCOptions::~AoCOptions()
{
    delete vm;
}

std::string AoCOptions::get_input_file() const
{
    if (vm->vm.count("input-file")) {
        return vm->vm["input-file"].as<string>();
    } else {
        return "";
    }
}

bool AoCOptions::is_verbose() const
{
    return vm->vm.count("verbose") > 0;
}
