#include "aoc-lib.h"
#include <iostream>
#include <limits>
#include <sstream>

using namespace std;

enum Direction {
	UNKNOWN,	
	UP,
	RIGHT,
	DOWN,
	LEFT
};

void dump_matrix(const vector<vector<unsigned char>>& matrix)
{
	for (const auto& row : matrix) {
		for (const auto& ch : row) {
			cout << ch << ' ';
		}
		cout << '\n';
	}
	cout << "\n";
}

unsigned char get_next_char(const vector<vector<unsigned char>>& matrix, int x, int y, int direction)
{
	switch (direction) {
	case UP:
		if (y - 1 >= 0)
			return matrix[y - 1][x];
		break;
	case DOWN:
		if (y + 1 < matrix.size())
			return matrix[y + 1][x];
		break;
	case LEFT:
		if (x - 1 >= 0)
			return matrix[y][x - 1];
		break;
	case RIGHT:
		if (x + 1 < matrix[0].size())
			return matrix[y][x + 1];
		break;
	default:
		cout << "Unknown direction\n";
		break;
	}

	return UNKNOWN;
}

int rotate(int direction)
{
	switch (direction) {
	case UP:
		return RIGHT;
	case DOWN:
		return LEFT;
	case LEFT:
		return UP;
	case RIGHT:
		return DOWN;
	default:
		cout << "Unknown direction\n";
		break;
	}

	return UNKNOWN;
}

void set_mark_at(vector<vector<unsigned char>>& matrix, int x, int y, int direction)
{
	switch (matrix[y][x]) {
	case '-':
		if (direction == UP || direction == DOWN)
			matrix[y][x] = '+';
		break;
	case '|':
		if (direction == LEFT || direction == RIGHT)
			matrix[y][x] = '+';
		break;
	case '.':
		switch (direction) {
		case UP:
		case DOWN:
			matrix[y][x] = '|';
			break;
		case LEFT:
		case RIGHT:
			matrix[y][x] = '=';
			break;
		}
	}
}

int find_next_direction(const vector<vector<unsigned char>>& matrix, int& in_x, int& in_y, int in_direction)
{
	char next_char;
	int direction = in_direction;

	do {
		next_char = get_next_char(matrix, in_x, in_y, direction);
		if (next_char != '#' && next_char != 'O') {
			break;
		}
		else {
			direction = rotate(direction);
		}

		if (direction == in_direction) {
			cout << "No way out at coordinates: (" << in_x << ", " << in_y << ")\n";
			direction = UNKNOWN;
			break;
		}
	} while (true);

	return direction;
}

int main(int argc, char** argv)
{
	AoCOptions options(argc, argv);
	vector<string> original_lines;
	vector<vector<unsigned char>> matrix;
	vector<vector<int>> direction_matrix;
	int x_max;
	int y_max;
	int direction;
	int y;
	int x; 

	cout << "P06: Input file: " << options.get_input_file() << "\n";
	original_lines = read_lines_from_file(options.get_input_file());

	matrix.resize(original_lines.size());

	for (size_t i = 0; i < original_lines.size(); ++i) 
		matrix[i] = vector<unsigned char>(original_lines[i].begin(), original_lines[i].end());

	x_max = matrix[0].size();
	y_max = matrix.size();

	for (y = 0; y < y_max; ++y) {
		for (x = 0; x < x_max; ++x) {
			if (matrix[y][x] == '^') {
				direction = UP;
				goto end_loops1;
			}
		}
	}

end_loops1:
	while (x >= 0 && x < x_max && y >= 0 && y < y_max) {
		matrix[y][x] = 'X';
		// dump_matrix(matrix);

		switch (direction) {
		case UP:
			if (y - 1 >= 0 && matrix[y - 1][x] == '#') {
				direction = RIGHT;
			}
			break;
		case DOWN:
			if (y + 1 < y_max && matrix[y + 1][x] == '#') {
				direction = LEFT;
			}
			break;
		case LEFT:
			if (x - 1 >= 0 && matrix[y][x - 1] == '#') {
				direction = UP;
			}
			break;
		case RIGHT:
			if (x + 1 < x_max && matrix[y][x + 1] == '#') {
				direction = DOWN;
			}
			break;
		default:
			cout << "Unknown direction\n";
			break;
		}

		switch (direction) {
		case UP:
			y--;
			break;
		case DOWN:
			y++;
			break;
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		default:
			cout << "Unknown direction\n";
			break;
		}
	}

	int count_X = 0;
	for (const auto& row : matrix) {
		for (const auto& ch : row) {
			if (ch == 'X') {
				count_X++;
			}
		}
	}

	cout << "P06 Part 1: Positions visited " << count_X << endl;

	bool loop_found = false;
	bool first_loop = true;
	int total_loops = 0;

	for (int ym = 0; ym < y_max; ++ym) {
		for (int xm = 0; xm < x_max; ++xm) {
			for (size_t i = 0; i < original_lines.size(); ++i) {
				matrix[i] = vector<unsigned char>(original_lines[i].begin(), original_lines[i].end());
			}

			direction_matrix.resize(y_max, vector<int>(x_max, UNKNOWN));
			for (auto& row : direction_matrix) {
				fill(row.begin(), row.end(), UNKNOWN);
			}

			for (y = 0; y < y_max; ++y) {
				for (x = 0; x < x_max; ++x) {
					if (matrix[y][x] == '^') {
						direction = UP;
						goto end_loops2;
					}
				}
			}

	end_loops2:

			if (matrix[ym][xm] == '#') {
				continue;
			}

			matrix[ym][xm] = 'O';

			loop_found = false;
			while (x >= 0 && x < x_max && y >= 0 && y < y_max && !loop_found) {

				//cout << "(" << x << ", " << y << ") " << direction << endl;
				//dump_matrix(matrix);
				//cin.ignore(numeric_limits<streamsize>::max(), '\n');

				if (matrix[y][x] == '.') {
					switch (direction) {
					case UP:
					case DOWN:
						matrix[y][x] = '|';
						break;
					case LEFT:
					case RIGHT:
						matrix[y][x] = '=';
						break;
					}
				}

				if (direction_matrix[y][x] != direction) {
					direction_matrix[y][x] = direction;
					direction = find_next_direction(matrix, x, y, direction);
					if (direction != UNKNOWN) {
						set_mark_at(matrix, x, y, direction);
						switch (direction) {
						case UP:
							y--;
							break;
						case DOWN:
							y++;
							break;
						case LEFT:
							x--;
							break;
						case RIGHT:
							x++;
							break;
						default:
							cout << "Unknown direction\n";
							break;
						}
					}
					else {
						loop_found = true;
						total_loops++;
					}
				}
				else {
					loop_found = true;
					total_loops++;
				}
			} // while
		}
	}

	cout << "P06 Part 2: Loops found: " << total_loops << endl;

	return 0;
}
