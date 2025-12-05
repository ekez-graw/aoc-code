#include "aoc-lib.h"
#include <iostream>
#include <cstdint> 
#include <sstream>
#include <algorithm>

int main(int argc, char** argv)
{
	AoCOptions options(argc, argv);
	std::vector<std::string> lines;

	uint64_t total = 0;

	std::cout << "P05: Input file: " << options.get_input_file() << "\n";
	lines = read_lines_from_file(options.get_input_file());

	static std::vector<std::pair<uint64_t,uint64_t>> fresh_ranges;
	static std::vector<uint64_t> fresh_values;
	bool fresh_range_read = true;

	for (const auto& line : lines) {
		if (!line.empty()) {
			if (fresh_range_read) {
				std::istringstream iss(line);
				uint64_t a = 0, b = 0;
				char separator = 0;
				if (iss >> a >> separator >> b && separator == '-')
					fresh_ranges.emplace_back(a, b);
			} else {
				std::istringstream iss(line);
				uint64_t val = 0;
				if (iss >> val)
					fresh_values.push_back(val);
			}
		}
		else {
			fresh_range_read = false;
		}
	}

	for (size_t i = 0; i < fresh_values.size(); i++) {
		uint64_t val = fresh_values[i];
		bool in_range = false;
		for (size_t j = 0; j < fresh_ranges.size(); j++) {
			const auto &r = fresh_ranges[j];
			if (val >= r.first && val <= r.second) {
				in_range = true;
				break;
			}
		}
		if (in_range) {
			if (options.is_verbose())
				std::cout << "Value " << val << " is in range.\n";
			total++;
		} else {
			if (options.is_verbose())
				std::cout << "Value " << val << " is NOT in range.\n";
		}
	}

	std::cout << "P05 Part 1: Total number of fresh: " << total << std::endl;

	// The idea is to merge each pair of ranges that overlap or are contiguous
	// Iterate until no progress is made.
	std::vector<std::pair<uint64_t,uint64_t>> new_fresh_ranges = fresh_ranges;
	std::vector<std::pair<uint64_t,uint64_t>> merged;
	merged.reserve(new_fresh_ranges.size());

	for (;;) {
		std::sort(new_fresh_ranges.begin(), new_fresh_ranges.end(),
					[](const std::pair<uint64_t,uint64_t>& a, const std::pair<uint64_t,uint64_t>& b){
						return a.first < b.first;
					});

		merged.clear();
		auto new_range = new_fresh_ranges[0];
		bool did_merge = false;

		for (size_t i = 1; i < new_fresh_ranges.size(); ++i) {
			const auto &next = new_fresh_ranges[i];
			if (next.first <= new_range.second + 1) {
				if (next.second > new_range.second) {
					new_range.second = next.second;
				}
				did_merge = true;
			} else {
				merged.push_back(new_range);
				new_range = next;
			}
		}
		merged.push_back(new_range);

		if (!did_merge) {
			new_fresh_ranges.swap(merged);
			break;
		}

		new_fresh_ranges.swap(merged);
	}

	// Now we have only non-overlapping ranges and can sum them up.
	uint64_t range_size = 0;
	for (const auto &r : new_fresh_ranges) {
		if (r.second >= r.first)
			range_size += (r.second - r.first + 1);
	}

	std::cout << "P05 Part 2: Total number of fresh: " << range_size << std::endl;

	return 0;
}
