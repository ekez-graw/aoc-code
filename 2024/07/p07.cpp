#include "aoc-lib.h"
#include <iostream>
#include <limits>
#include <sstream>

using namespace std;

int main(int argc, char** argv)
{
	AoCOptions options(argc, argv);
	vector<string> original_lines;
	long long total;
	long long grand_total = 0;

	cout << "P07: Input file: " << options.get_input_file() << "\n";
	original_lines = read_lines_from_file(options.get_input_file());

	vector<long long> test_values(original_lines.size());
	vector<vector<long long>> numbers(original_lines.size());

	for (size_t i = 0; i < original_lines.size(); ++i) {
		stringstream ss(original_lines[i]);
		string number;
		if (getline(ss, number, ':'))
			test_values[i] = stoll(number);
		vector<long long> values;
		while (getline(ss, number, ' ')) {
			try {
				values.push_back(stoll(number));
			} catch (const invalid_argument& e) {}
		}
		numbers[i] = values;
	}

	for (size_t line = 0; line < original_lines.size(); ++line) {
		unsigned int number_of_permutations = 1 << numbers[line].size() - 1;

		for (size_t i = 0; i < number_of_permutations; ++i) {
			total = numbers[line][0];
			for (size_t j = 0; j < numbers[line].size() - 1; ++j) {
				if (i & (1 << j))
					total *= numbers[line][j+1];
				else
					total += numbers[line][j+1];
			}
			if (total == test_values[line]) {
				grand_total += total;
				break;
			}
		}
	}

	cout << "P07 Part 1: Grand total: " << grand_total << endl;

	return 0;
}
