#include "aoc-lib.h"
#include <iostream>

int check_and_count_all_directions(const std::vector<std::vector<char>>& letters, size_t in_row, size_t in_col)
{
	int sum = 0;
	int directions[8][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}, {-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // diagonals and up, down, left, right
	std::vector<char> xmas = {'X', 'M', 'A', 'S'};
	std::vector<char> samx = {'S', 'A', 'M', 'X'};

	for (const auto& dir : directions) {
		int row = in_row;
		int col = in_col;
		int i;

		for (i = 0; i < xmas.size(); ++i) {
			if (row < 0 || row >= letters.size() || col < 0 || col >= letters[0].size()) {
				break;
			}
			if (letters[row][col] != xmas[i]) {
				break;
			}
			row += dir[0];
			col += dir[1];
		}
		if (i == xmas.size()) {
			sum++;
		}

		row = in_row;
		col = in_col;
		for (i = 0; i < samx.size(); ++i) {
			if (row < 0 || row >= letters.size() || col < 0 || col >= letters[row].size()) {
				break;
			}
			if (letters[row][col] != samx[i]) {
				break;
			}
			row += dir[0];
			col += dir[1];
		}
		if (i < 0) {
			sum++;
		}
	}

	return sum;
}

int check_if_x_mas(const std::vector<std::vector<char>>& letters, size_t in_row, size_t in_col)
{
	int sum = 0;
	int directions[4][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}}; // diagonals
	std::vector<char> mas = { 'M', 'A', 'S'};
	int i;

	for (const auto& dir : directions) {
		int row = in_row - dir[0];
		int col = in_col - dir[1];
		// Check xmas in the current direction
		for (i = 0; i < mas.size(); ++i) {
			if (row < 0 || row >= letters.size() || col < 0 || col >= letters[0].size()) {
				break;
			}
			if (letters[row][col] != mas[i]) {
				break;
			}
			row += dir[0];
			col += dir[1];
		}
		if (i == mas.size()) {
			sum++;
		}
	}

	if (sum == 2)
		return 1;

	return 0;
}

int main(int argc, char** argv)
{
	AoCOptions options(argc, argv);
	std::vector<std::string> original_lines;
	std::vector<std::vector<char>> letters;
	bool found;
	int sum = 0;
	int next_row, next_col;

	std::cout << "P04: Input file: " << options.get_input_file() << "\n";

	original_lines = read_lines_from_file(options.get_input_file());

	for (const auto& line : original_lines) {
		std::vector<char> char_row(line.begin(), line.end());
		letters.push_back(char_row);
	}

	for (size_t row = 0; row < letters.size(); ++row) {
		for (size_t col = 0; col < letters[row].size(); ++col) {
			sum += check_and_count_all_directions(letters, row, col);
		}
	}

	std::cout << "P04 Part 1: XMAS occurs " << sum << " times" << std::endl;

	sum = 0;
	for (size_t row = 0; row < letters.size(); ++row) {
		for (size_t col = 0; col < letters[row].size(); ++col) {
			sum += check_if_x_mas(letters, row, col);
		}
	}

	std::cout << "P04 Part 2: X-MAS occurs " << sum << " times" << std::endl;

	return 0;
}
