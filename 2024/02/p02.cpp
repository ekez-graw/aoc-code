#include "aoc-lib.h"
#include <iostream>
#include <sstream>
#include <algorithm> 

int main(int argc, char** argv)
{
    AoCOptions options(argc, argv);
	std::vector<std::string> original_lines;
    std::vector<std::string> lines;
	int number_of_safe = 0;

	std::cout << "P02: Input file: " << options.get_input_file() << "\n";
	original_lines = read_lines_from_file(options.get_input_file());

    lines = original_lines;

	for (const auto& line : lines) {
		std::istringstream iss(line);
		std::vector<int> numbers;
		int number;
		while (iss >> number) {
			numbers.push_back(number);
			if (iss.peek() == ' ' || iss.peek() == '\t') {
				iss.ignore();
			}
		}

		bool is_increasing = true;
		bool is_safe = true;
		if (numbers[1] < numbers[0])
			is_increasing = false;
		for (size_t i = 1; i < numbers.size(); ++i) {
			if (is_increasing && numbers[i] <= numbers[i - 1])
				is_safe = false;
			if (!is_increasing && numbers[i] >= numbers[i - 1])
				is_safe = false;
			int abs_diff = std::abs(numbers[i] - numbers[i - 1]);
			if (abs_diff == 0 || abs_diff > 3)
				is_safe = false;
		}

		if (is_safe)
			number_of_safe++;

		numbers.clear();
	}

	std::cout << "P02 Part 1: Number of safe levels: " << number_of_safe << std::endl;

	number_of_safe = 0;
    lines = original_lines;

	for (const auto& line : lines) {
		std::istringstream iss(line);
		std::vector<int> numbers;
		int number;
		while (iss >> number) {
			numbers.push_back(number);
			if (iss.peek() == ' ' || iss.peek() == '\t') {
				iss.ignore();
			}
		}

		bool is_safe;
		std::vector<int> original_numbers = numbers;
		for (size_t i = 0; i < numbers.size(); ++i) {
			int removed_number = numbers[i];
			numbers.erase(numbers.begin() + i);

			bool is_increasing = true;
			is_safe = true;
			if (numbers[1] < numbers[0])
				is_increasing = false;
			for (size_t i = 1; i < numbers.size(); ++i) {
				if (is_increasing && numbers[i] <= numbers[i - 1])
					is_safe = false;
				if (!is_increasing && numbers[i] >= numbers[i - 1])
					is_safe = false;
				int abs_diff = std::abs(numbers[i] - numbers[i - 1]);
				if (abs_diff == 0 || abs_diff > 3)
					is_safe = false;
			}

			numbers.insert(numbers.begin() + i, removed_number);
			if (is_safe)
				break;
		}

		if (is_safe)
			number_of_safe++;
	}

	std::cout << "P02 Part 2: Number of safe levels with dampening: " << number_of_safe << std::endl;

	return 0;
}
