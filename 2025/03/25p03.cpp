#include "aoc-lib.h"
#include <iostream>
#include <sstream>
#include <algorithm> 
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>

int main(int argc, char** argv)
{
	AoCOptions options(argc, argv);
	std::vector<std::string> lines;
	uint32_t i;
	uint32_t j;
	uint32_t largest_jolt;
	uint32_t largest_jolt_first_index;
	uint32_t largest_jolt_second_index;
	uint64_t jolts = 0;

	std::cout << "P03: Input file: " << options.get_input_file() << "\n";
	lines = read_lines_from_file(options.get_input_file());

	for (const auto& line : lines) {
		if (!line.empty()) {
			std::vector<int> row;
			row.reserve(line.size());
			for (char c : line)
				if (c >= '0' && c <= '9') row.push_back(c - '0');

			largest_jolt = 0;
			largest_jolt_first_index = 0;
			largest_jolt_second_index = 0;

			for (i = 0; i < row.size(); i++) {
				for (j = i + 1; j < row.size(); j++) {
					if (row[i] * 10 + row[j] > largest_jolt) {
						largest_jolt = row[i] * 10 + row[j];
						largest_jolt_first_index = i;
						largest_jolt_second_index = j;
					}
				}
			}

			jolts += largest_jolt;

			if (options.is_verbose()) {
				std::cout << "Largest jolt in line: " << line << " is " << largest_jolt
						<< " from digits at positions " << largest_jolt_first_index
						<< " and " << largest_jolt_second_index << ". Total Jolts: " << jolts << "\n";
			}
		}
	}

	std::cout << "P03 Part 1: Total jolts: " << jolts << std::endl;

	jolts = 0;

	for (const auto& line : lines) {
		if (!line.empty()) {
			std::vector<int> row;
			row.reserve(line.size());
			for (char c : line)
				if (c >= '0' && c <= '9') row.push_back(c - '0');

			int32_t k;
			std::vector<size_t> twelve_indicies;
			size_t count = std::min<size_t>(12, row.size());
			twelve_indicies.reserve(count);
			for (int32_t k = 0; k < count; k++)
				twelve_indicies.push_back(row.size() - count + k);

			uint32_t current_index;
			uint32_t new_index;

			for (current_index = 0; current_index < 12; current_index++) {
				for (k = twelve_indicies[current_index], new_index = k; k >= 0; k--) {
					if (current_index > 0 && k <= twelve_indicies[current_index - 1])
						continue;
					if (row[k] >= row[twelve_indicies[current_index]]) {
						new_index = k;
						twelve_indicies[current_index] = new_index;
					}
				}
			}

			uint64_t row_jolt = 0;
			for (size_t idx : twelve_indicies)
				row_jolt = row_jolt * 10 + static_cast<uint64_t>(row[idx]);

			jolts += row_jolt;

			if (options.is_verbose()) {
				std::cout << "Last " << count << " indices: ";
				for (size_t idx : twelve_indicies) {
					std::cout << idx << "(" << row[idx] << ") ";
				}
				std::cout << std::endl;
				std::cout << "Constructed integer from selected digits: " << row_jolt
						  << ". Total Jolts: " << jolts << "\n";
			}
		}
	}

	std::cout << "P03 Part 2: Total jolts: " << jolts << std::endl;

	return 0;
}
