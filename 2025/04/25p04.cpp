#include "aoc-lib.h"
#include <iostream>
#include <cstdint> 
#include <sstream>
#include <algorithm> 

uint8_t number_of_adjacent_rolls(const std::vector<std::vector<char>>& grid, size_t x, size_t y) {
	uint8_t count = 0;
	size_t max_y = grid.size();
	size_t max_x = grid[0].size();

	// Check above
	if (y > 0 && grid[y - 1][x] == '@') count++;
	// Check above to the left
	if (y > 0 && x > 0 && grid[y - 1][x - 1] == '@') count++;
	// Check above to the right
	if (y > 0 && x + 1 < max_x && grid[y - 1][x + 1] == '@') count++;
	// Check below
	if (y + 1 < max_y && grid[y + 1][x] == '@') count++;
	// Check below to the left
	if (y + 1 < max_y && x > 0 && grid[y + 1][x - 1] == '@') count++;
	// Check below to the right
	if (y + 1 < max_y && x + 1 < max_x && grid[y + 1][x + 1] == '@') count++;
	// Check left
	if (x > 0 && grid[y][x - 1] == '@') count++;
	// Check right
	if (x + 1 < max_x && grid[y][x + 1] == '@') count++;

	return count;
}

int main(int argc, char** argv)
{
	AoCOptions options(argc, argv);
	std::vector<std::string> lines;

	std::vector<std::vector<char>> grid;
	std::vector<std::vector<char>> changed_grid;
	uint64_t total_rolls = 0;

	std::cout << "P04: Input file: " << options.get_input_file() << "\n";
	lines = read_lines_from_file(options.get_input_file());

	for (const auto& line : lines) {
		if (!line.empty()) {
			grid.emplace_back(line.begin(), line.end());
		}
	}

	changed_grid = grid;

	for (size_t y = 0; y < grid.size(); y++) {
		for (size_t x = 0; x < grid[y].size(); x++) {
			if (grid[y][x] == '@') {
				if (number_of_adjacent_rolls(grid, x, y) < 4) {
					changed_grid[y][x] = 'x';
					total_rolls++;
				}
			}
		}
	}

	std::cout << "P04 Part 1: Total rolls that can be accessed: " << total_rolls << std::endl;

	uint32_t number_of_changed_rolls;

	do {
		grid = changed_grid;
		number_of_changed_rolls = 0;
		for (size_t y = 0; y < grid.size(); y++) {
			for (size_t x = 0; x < grid[y].size(); x++) {
				if (grid[y][x] == '@') {
					if (number_of_adjacent_rolls(grid, x, y) < 4) {
						changed_grid[y][x] = 'x';
						number_of_changed_rolls++;
						total_rolls++;
					}
				}
			}
		}
	} while (number_of_changed_rolls > 0);

	std::cout << "P04 Part 2: Total rolls that can be accessed: " << total_rolls << std::endl;

	return 0;
}
