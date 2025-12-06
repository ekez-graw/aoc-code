#include "aoc-lib.h"
#include <iostream>
#include <sstream>
#include <cstdint>
#include <algorithm>
#include <cctype>

int main(int argc, char** argv)
{
	AoCOptions options(argc, argv);
	std::vector<std::string> lines;

	std::vector<std::vector<uint64_t>> rows;
	std::vector<std::vector<char>> rows_characters;
	std::vector<char>operators;
	int32_t column;
	int32_t i;
	uint64_t columns_total;
	uint64_t grand_total = 0;
	uint32_t number_of_rows = 0;

	std::cout << "P06: Input file: " << options.get_input_file() << "\n";
	lines = read_lines_from_file(options.get_input_file());

	for (const auto& line : lines) {
		if (!line.empty()) {
			if (!std::any_of(line.begin(), line.end(), [](char ch){ return std::isdigit(static_cast<unsigned char>(ch)); })) {
				char new_operator;
				std::istringstream iss(line);
				while (iss >> new_operator) {
					operators.push_back(new_operator);
				}
			} else {
				std::vector<uint64_t> row;
				std::vector<char> row_chars;
				std::istringstream iss(line);
				uint64_t value;
				while (iss >> value) {
					row.push_back(value);
				}
				row_chars.assign(line.begin(), line.end());
				rows.push_back(std::move(row));
				rows_characters.push_back(std::move(row_chars));
				number_of_rows++;
			}
		}
	}

	for (column = 0; column < operators.size(); column++) {
		if (operators[column] == '+') {
			columns_total = 0;
			for (i = 0; i < rows.size(); i++) {
				if (column < rows[i].size())
					columns_total += rows[i][column];
			}
			grand_total += columns_total;
		} else if (operators[column] == '*') {
			columns_total = 1;
			for (i = 0; i < rows.size(); i++) {
				if (column < rows[i].size())
					columns_total *= rows[i][column];
			}
			grand_total += columns_total;
		}
	}

	std::cout << "P06 Part 1: Grand total: " << grand_total << std::endl;

	grand_total = 0;
	char op;
	bool is_add;
	uint32_t operator_number = 0;
	uint64_t problem_total;
	uint64_t new_value;
	std::string concatenated_number_str;
	column = 0;

	while (column < rows_characters[0].size()) {
		op = operators[operator_number];
		is_add = (op == '+');
		problem_total = is_add ? 0 : 1; // 0 for + and 1 for * as the start in order to be able to += or *= later
		while (true) {
			concatenated_number_str.clear();
			for (i = 0; i < number_of_rows; ++i) {
				if (std::isdigit(rows_characters[i][column]))
					concatenated_number_str += rows_characters[i][column];
			}
			if (concatenated_number_str.empty())
				break;
			new_value = std::stoull(concatenated_number_str);
			if (is_add)
				problem_total += new_value;
			else
				problem_total *= new_value;
			column++;
		}

		// Sum up and prepare for next problem
		grand_total += problem_total;
		operator_number++;
		column++;
	}

	std::cout << "P06 Part 2: Grand total: " << grand_total << std::endl;

	return 0;
}
