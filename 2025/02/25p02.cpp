#include "aoc-lib.h"
#include <iostream>
#include <sstream>
#include <algorithm> 
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>

bool check_if_illegal(uint64_t number) {
	std::string num_str = std::to_string(number);
	size_t mid = num_str.size() / 2;
	std::string left_half = num_str.substr(0, mid);
	std::string right_half = num_str.substr(mid);

	return left_half == right_half;
}

bool check_if_illegal_part2(uint64_t number) {
	std::string num_str = std::to_string(number);
	size_t mid = num_str.size() / 2;
	bool ok;

	for (size_t len = 1; len <= mid; ++len) {
		std::string_view sub(num_str.data(), len);
		if (num_str.size() % sub.size() != 0) continue;
		ok = true;
		for (size_t pos = 0; pos < num_str.size(); pos += sub.size()) {
			if (std::string_view(num_str.data() + pos, sub.size()) != sub) {
				ok = false;
				break;
			}
		}
		if (ok)
			return true;
	}

	return false;
}

int main(int argc, char** argv)
{
	AoCOptions options(argc, argv);
	std::vector<std::string> lines;

	boost::char_separator<char> sep{","};
	std::vector<std::string> parts;
	std::string item;
	std::string s;
	uint64_t value1;
	uint64_t value2;
	uint64_t iterator;
	uint64_t sum1 = 0;
	uint64_t sum2 = 0;

	std::cout << "P02: Input file: " << options.get_input_file() << "\n";
	lines = read_lines_from_file(options.get_input_file());

	for (const auto& line : lines) {
		if (!line.empty()) {
			s = line;
			boost::tokenizer<boost::char_separator<char>> tokens(s, sep);
			for (const auto& tok : tokens) {
				item = tok;
				boost::algorithm::trim(item);
				if (item.empty()) continue;
				if (options.is_verbose())
					std::cout << "Range: " << item << '\n';

				value1 = 0;
				value2 = 0;

				boost::split(parts, item, boost::is_any_of("-"));
				if (parts.size() == 2) {
					boost::algorithm::trim(parts[0]);
					boost::algorithm::trim(parts[1]);
					try {
						value1 = static_cast<uint64_t>(std::stoul(parts[0]));
						value2 = static_cast<uint64_t>(std::stoul(parts[1]));
					} catch (const std::exception& e) {
						std::cerr << "Failed to parse numbers from token '" << item << "': " << e.what() << '\n';
					}
				}

				for (iterator = value1; iterator <= value2; ++iterator) {
					if (check_if_illegal(iterator)) {
						sum1+=iterator;
						if (options.is_verbose())
							std::cout << "Number " << iterator << " is illegal for Part 1. Sum1:" << sum1 << "\n";
					}
					if (check_if_illegal_part2(iterator)) {
						sum2+=iterator;
						if (options.is_verbose())
							std::cout << "Number " << iterator << " is illegal for part 2. Sum2:" << sum2 << "\n";
					}
				}
			}
		}
	}

	std::cout << "P01 Part 1: Sum of illegals: " << sum1 << std::endl;
	std::cout << "P01 Part 2: Sum of illegals: " << sum2 << std::endl;

	return 0;
}
