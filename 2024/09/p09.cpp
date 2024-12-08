#include "aoc-lib.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
	AoCOptions options(argc, argv);
	vector<string> original_lines;

	cout << "P09: Input file: " << options.get_input_file() << "\n";
	original_lines = read_lines_from_file(options.get_input_file());

	cout << "P09 Part 1: " << endl;

	return 0;
}
