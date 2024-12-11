#include "aoc-lib.h"
#include <iostream>
#include <algorithm>

using namespace std;

void print_red(const vector<vector<char>>& matrix, int x, int y)
{
	// for (int i = 0; i < matrix.size(); ++i) {
	// 	for (int j = 0; j < matrix[i].size(); ++j) {
	// 		if (i == y && j == x) {
	// 			cout << "\033[31m" << matrix[i][j] << "\033[0m";
	// 		} else {
	// 			cout << matrix[i][j];
	// 		}
	// 	}
	// 	cout << endl;
	// }
	// cout << endl;
}

void print_blue(const vector<vector<char>>& matrix, int x, int y)
{
	// for (int i = 0; i < matrix.size(); ++i) {
	// 	for (int j = 0; j < matrix[i].size(); ++j) {
	// 		if (i == y && j == x) {
	// 			cout << "\033[34m" << matrix[i][j] << "\033[0m";
	// 		} else {
	// 			cout << matrix[i][j];
	// 		}
	// 	}
	// 	cout << endl;
	// }
	// cout << endl;
}

void print_yellow(const vector<vector<char>>& matrix, int x, int y)
{
	// for (int i = 0; i < matrix.size(); ++i) {
	// 	for (int j = 0; j < matrix[i].size(); ++j) {
	// 		if (i == y && j == x) {
	// 			cout << "\033[33m" << matrix[i][j] << "\033[0m";
	// 		} else {
	// 			cout << matrix[i][j];
	// 		}
	// 	}
	// 	cout << endl;
	// }
	// cout << endl;
}

void next_hop(const vector<vector<char>>& matrix, int count, int x, int y, int row_max, int col_max, vector<vector<bool>>& bool_matrix)
{
	int int_matrix = matrix[y][x] - '0';

	print_blue(matrix, x, y);

	// West
	if (x > 0) {
		int_matrix = matrix[y][x-1] - '0';
		if (int_matrix == count + 1) {
			if (int_matrix == 9) {
				if (bool_matrix[y][x-1] == false) {
					bool_matrix[y][x-1] = true;
					print_red(matrix, x - 1, y);
				}
				else {
					print_yellow(matrix, x - 1, y);
				}
			}
			else {
				next_hop(matrix, count + 1, x - 1, y, row_max, col_max, bool_matrix);
			}
		}
	}
	// North
	if (y > 0) {
		int_matrix = matrix[y-1][x] - '0';
		if (int_matrix == count + 1) {
			if (int_matrix == 9) {
				if (bool_matrix[y-1][x] == false) {
					bool_matrix[y-1][x] = true;
					print_red(matrix, x, y - 1);
				}
				else {
					print_yellow(matrix, x, y - 1);
				}
			}
			else {
				next_hop(matrix, count + 1, x, y-1, row_max, col_max, bool_matrix);
			}
		}
	}
	// East
	if (x < col_max - 1) {
		int_matrix = matrix[y][x+1] - '0';
		if (int_matrix == count + 1) {
			if (int_matrix == 9) {
				if (bool_matrix[y][x+1] == false) {
					bool_matrix[y][x+1] = true;
					print_red(matrix, x + 1, y);
				}
				else {
					print_yellow(matrix, x + 1, y);
				}
			}
			else {
				next_hop(matrix, count + 1, x+1, y, row_max, col_max, bool_matrix);
			}
		}
	}
	// South
	if (y < row_max - 1) {
		int_matrix = matrix[y+1][x] - '0';
		if (int_matrix == count + 1) {
			if (int_matrix == 9) {
				if (bool_matrix[y+1][x] == false) {
					bool_matrix[y+1][x] = true;
					print_red(matrix, x, y + 1);
				}
				else {
					print_yellow(matrix, x, y + 1);
				}

			}
			else {
				next_hop(matrix, count + 1, x, y + 1, row_max, col_max, bool_matrix);
			}
		}
	}
}

int main(int argc, char** argv)
{
	AoCOptions options(argc, argv);
	vector<string> original_lines;
	vector<vector<char>> matrix;
	int row_max, col_max;
	int total_trailheads = 0;

	cout << "P10: Input file: " << options.get_input_file() << "\n";
	original_lines = read_lines_from_file(options.get_input_file());

	row_max = original_lines.size();
	col_max = original_lines[0].size();

	matrix.resize(row_max, vector<char>(col_max));

	for (int y = 0; y < row_max; ++y) {
		for (int x = 0; x < col_max; ++x) {
			matrix[y][x] = original_lines[y][x];
		}
	}

	vector<vector<bool>> bool_matrix(row_max, vector<bool>(col_max, false));

	for (int y = 0; y < row_max; ++y) {
		for (int x = 0; x < col_max; ++x) {
			if (matrix[y][x] == '0') {
				fill(bool_matrix.begin(), bool_matrix.end(), vector<bool>(col_max, false));
				next_hop(matrix, 0, x, y, row_max, col_max, bool_matrix);
				int count_true = 0;
				for (const auto& row : bool_matrix) {
					count_true += count(row.begin(), row.end(), true);
				}
				total_trailheads += count_true;
			}
		}
	}

	cout << "P10: Part 1: Trailheads: " << total_trailheads << endl;

    return 0;
}