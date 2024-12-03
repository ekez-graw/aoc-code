#include "aoc-lib.h"
#include <iostream>
#include <sstream>
#include <algorithm> 
#include <regex>

enum PatternType {
	MUL,
	DO,
	DONT,
	UNKNOWN
};

PatternType getPatternType(const std::smatch& match) {
	if (match.str().find("mul") != std::string::npos) {
		return MUL;
	} else if (match.str().find("do()") != std::string::npos) {
		return DO;
	} else if (match.str().find("don't()") != std::string::npos) {
		return DONT;
	} else {
		return UNKNOWN;
	}
}

int main(int argc, char** argv)
{
	AoCOptions options(argc, argv);
	std::vector<std::string> original_lines;
	std::vector<std::string> lines;
	int sum = 0;
	int x, y;

	std::cout << "P03: Input file: " << options.get_input_file() << "\n";
	original_lines = read_lines_from_file(options.get_input_file());
	lines = original_lines;

	std::regex mul_pattern(R"(mul\((\d+),(\d+)\))");
	for (const auto& line : lines) {
		auto words_begin = std::sregex_iterator(line.begin(), line.end(), mul_pattern);
		auto words_end = std::sregex_iterator();

		x = y = 0;
		for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
			std::smatch match = *i;
			x = std::stoi(match[1].str());
			y = std::stoi(match[2].str());
			sum += x * y;
		}
	}

	std::cout << "P03 Part 1: Sum of multiplications: " << sum << std::endl;

	lines = original_lines;
	bool do_flag = true;
	sum = 0;

	std::regex patterns(R"((mul\((\d+),(\d+)\))|(do\(\))|(don't\(\)))");
	for (const auto& line : lines) {
		auto words_begin = std::sregex_iterator(line.begin(), line.end(), patterns);
		auto words_end = std::sregex_iterator();

		for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
			std::smatch match = *i;
			PatternType type = getPatternType(match);

			switch (type) {
				case MUL:
					x = std::stoi(match[2].str());
					y = std::stoi(match[3].str());
					if (do_flag)
						sum += x * y;
					break;
				case DO:
					do_flag = true;
					break;
				case DONT:
					do_flag = false;
					break;
				default:
					break;
			}
		}
	}

	std::cout << "P03 Part 2: Sum of multiplications with do's and don'ts: " << sum << std::endl;

	return 0;
}
