#include "aoc-lib.h"
#include <iostream>
#include <sstream>
#include <algorithm> 

int main(int argc, char** argv)
{
	AoCOptions options(argc, argv);
	std::vector<std::string> lines;
	std::string rest;
	char c;
	int dial = 50;
	int value;
	int full;
	int rem;
	int crossings;
	int extra_crossing;
	int password = 0;

	std::cout << "P01: Input file: " << options.get_input_file() << "\n";
	lines = read_lines_from_file(options.get_input_file());

	for (const auto& line : lines) {
		if (!line.empty()) {
			c = line.front();
			rest = line.substr(1);
			value = std::stoi(rest);
			if (c == 'L')
				dial = (dial - value + 100) % 100;
			else if (c == 'R')
				dial = (dial + value) % 100;

			// std::cout << "Dial turned " << c << value << " to " << dial << "\n";
		}

		if (dial == 0)
			password++;
	}

	std::cout << "P01 Part 1: Password: " << password << std::endl;

	dial = 50;
	password = 0;

	for (const auto& line : lines) {
		if (!line.empty()) {
			c = line.front();
			rest = line.substr(1);
			value = std::stoi(rest);

			full = value / 100;
			rem = value % 100;
			crossings = 0;

			if (c == 'L') {
				extra_crossing = 0;
				if (rem != 0 && dial != 0 && rem >= dial) // Note; if dial is 0 don't count extra crossing
					extra_crossing = 1;
				crossings = full + extra_crossing;
				dial -= rem;
				if (dial < 0)
					dial += 100;
			}
			else if (c == 'R') {
				extra_crossing = 0;
				if (rem != 0 && dial != 0 && (dial + rem) >= 100)
					extra_crossing = 1;
				crossings = full + extra_crossing;
				dial += rem;
				if (dial >= 100)
					dial -= 100;
			}

			password += crossings;
			// std::cout << "Dial turned " << c << value << " to " << dial << " (crossed zero " << crossings << " time(s))\n";
		}
	}

	std::cout << "P01 Part 2: Password: " << password << std::endl;

	return 0;
}
