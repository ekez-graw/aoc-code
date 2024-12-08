#include "aoc-lib.h"
#include <iostream>
#include <limits>
#include <sstream>

using namespace std;

void find_and_set_antinode(const vector<vector<char>>& antennas, vector<vector<char>>& antinodes, int in_y, int in_x)
{
	int max_rows = antennas.size();
	int max_cols = antennas[0].size();
	int slope_x;
	int slope_y;
	int new_x;
	int new_y;
	int x;

	x = in_x + 1;
	for (int y = in_y; y < max_rows; ++y) {
		while (x < max_cols) {
			if (antennas[y][x] == antennas[in_y][in_x]) {
				slope_x = x - in_x;
				slope_y = y - in_y;
				new_x = x + slope_x;
				new_y = y + slope_y;
				if (new_x >= 0 && new_x < max_rows && new_y >= 0 && new_y < max_cols)
					antinodes[new_y][new_x] = '#';

				new_x = in_x - slope_x;
				new_y = in_y - slope_y;
				if (new_x >= 0 && new_x < max_rows && new_y >= 0 && new_y < max_cols)
					antinodes[new_y][new_x] = '#';
				break;
			}
			x++;
		}
		x = 0;
	}
}

int main(int argc, char** argv)
{
	AoCOptions options(argc, argv);
	vector<string> original_lines;
	vector<vector<char>> antennas;
	int total_antinodes = 0;
	int max_rows;
	int max_cols;

	cout << "P08: Input file: " << options.get_input_file() << "\n";
	original_lines = read_lines_from_file(options.get_input_file());

	for (const auto& line : original_lines) {
		vector<char> row(line.begin(), line.end());
		antennas.push_back(row);
	}

	max_rows = antennas.size();
	max_cols = antennas[0].size();

	vector<vector<char>> antinodes(max_rows, vector<char>(max_cols, '.'));

	for (int y = 0; y < max_rows; ++y) {
		for (int x = 0; x < max_cols ; ++x) {
			if (antennas[y][x] != '.') {
				find_and_set_antinode(antennas, antinodes, y, x);
			}
		}
	}

	for (int y = 0; y < max_rows; ++y) {
		for (int x = 0; x < max_cols; ++x) {
			if (antinodes[y][x] == '#') {
				total_antinodes++;
			}
		}
	}

	cout << "P08 Part 1: Total antinodes: " << total_antinodes << endl;

	return 0;
}
