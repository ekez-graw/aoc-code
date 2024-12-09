#include "aoc-lib.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
	AoCOptions options(argc, argv);
	vector<string> original_lines;
	vector<int> blocks;
	vector<int> original_blocks;
	bool is_file = true;
	int id = 0;

	cout << "P09: Input file: " << options.get_input_file() << "\n";
	original_lines = read_lines_from_file(options.get_input_file());

	for (const auto& line : original_lines) {
		for (const auto& ch : line) {
			int amount = ch - '0';

			for (int i = 0; i < amount; ++i) {
				if (is_file)
					blocks.push_back(id);
				else
					blocks.push_back(-1);
			}

			if (is_file) {
				is_file = !is_file;
			} else {
				is_file = !is_file;
				id++;
			}
		}
	}

	original_blocks = blocks;

	int last = blocks.size() - 1;
	int first = 0;

	while (first < last) {
		while (blocks[first] != -1)
			first++;
		while (blocks[last] == -1)
			last--;

		if (first < last) {
			blocks[first] = blocks[last];
			blocks[last] = -1;
		}
	}

	long long checksum = 0;

	for (size_t i = 0; i < blocks.size(); ++i) {
		if (blocks[i] == -1)
			continue;
		long long value = i * blocks[i];
		checksum += value;
	}
	cout << "P09 Part 1: Checksum: " << checksum << endl;

	blocks = original_blocks;
	int first_empty = 0;

	do {
		int start;
		int end = blocks.size() - 1;

		while (end >= 0 && blocks[end] != id)
			end--;
		start = end;
		while (start >= 0 && blocks[start] == id)
			start--;
		start++;

		int size = (end - start) + 1;
		bool found = false;
		for (first_empty = 0; first_empty < blocks.size() && !found && first_empty < start; ++first_empty) {
			if (blocks[first_empty] == -1) {
				found = true;
				for (int j = first_empty; j < first_empty + size; ++j) {
					if (blocks[j] != -1)
						found = false;
				}
			}
		}				

		if (found) {
			first_empty--;
			for (int i = 0; i < size; ++i) {
				blocks[first_empty + i] = id;
				blocks[start + i] = -1;
			}
		}

		id--;
		if (id < 0)
			break;
	} while (true);

	checksum = 0;

	for (size_t i = 0; i < blocks.size(); ++i) {
		if (blocks[i] == -1)
			continue;
		long long value = i * blocks[i];
		checksum += value;
	}
	cout << "P09 Part 2: Checksum: " << checksum << endl;

	return 0;
}
