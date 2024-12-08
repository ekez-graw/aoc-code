#ifndef AOC_LIB_H
#define AOC_LIB_H

#include <string>
#include <vector>

class AoCOptions
{
	public:
		AoCOptions(int argc, char** argv);
		~AoCOptions();
		std::string get_input_file() const;

private:
	// Forward declaration of boost::program_options::variables_map
	class variables_map;
	variables_map* vm;
};

std::vector<std::string> read_lines_from_file(const std::string& file_name);

#endif
