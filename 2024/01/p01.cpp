#include "aoc-lib.h"
#include <iostream>
#include <sstream>
#include <algorithm> 

int main(int argc, char** argv)
{
    AoCOptions options(argc, argv);
	std::vector<std::string> lines;
	int list1[1000];
	int list2[1000];
	int i;
	int j;
	int k;
	int num1;
	int num2;
	int sum = 0;
	int count;

	std::cout << "P01: Input file: " << options.get_input_file() << "\n";
	lines = read_lines_from_file(options.get_input_file());

	for (const auto& line : lines) {
		std::istringstream iss(line);
		iss >> num1 >> num2;
		list1[i] = num1;
		list2[i] = num2;
		i++;
	}

	std::sort(list1, list1 + i);
	std::sort(list2, list2 + i);

	for (j = 0; j < i; j++) {
		int abs_diff = std::abs(list1[j] - list2[j]);
		sum += abs_diff;
	}

	std::cout << "P01 Part 1: Sum of absolute differences: " << sum << std::endl;

	for (j = 0; j < i; j++) {
		count = 0;
		for (k = 0; k < i; k++) {
			if (list1[j] == list2[k]) {
				count++;
			}
		}
		sum += list1[j] * count;
	}

	std::cout << "P01 Part 2: Sum of products: " << sum << std::endl;

	return 1;
}
