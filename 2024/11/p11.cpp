#include "aoc-lib.h"
#include <iostream>
#include <sstream>

using namespace std;

void apply_rules(vector<long long>& numbers)
{
	size_t i = 0;
	
	while (i < numbers.size()) {

		if (numbers[i] == 0) {
			numbers[i] = 1;
			i++;
			continue;
		}

		int digit_count = to_string(numbers[i]).length();
		bool even_count = (digit_count % 2 == 0);

		if (even_count) {
			ostringstream oss;
			oss << numbers[i];
			string number_str = oss.str();
			size_t mid = number_str.size() / 2;
			string first_half = number_str.substr(0, mid);
			string second_half = number_str.substr(mid);
			long long first_half_num = stoll(first_half);
			numbers[i] = first_half_num;
			long long second_half_num = stoll(second_half);
			numbers.insert(numbers.begin() + i + 1, second_half_num);
			i += 2;
			continue;
		}

		numbers[i] *= 2024;

		i++;
	}
}

int main(int argc, char** argv)
{
	AoCOptions options(argc, argv);
	vector<string> original_lines;

	cout << "P11: Input file: " << options.get_input_file() << "\n";
	original_lines = read_lines_from_file(options.get_input_file());

	vector<long long> numbers;
	for (const auto& line : original_lines) {
		istringstream iss(line);
		string number;
		while (iss >> number) {
			numbers.push_back(stoll(number));
		}
	}

	for (int i = 0; i < 25; ++i) {
		apply_rules(numbers);
	}

	cout << "P11: Part 1: Number of stones: " << numbers.size() << endl;

	return 0;
}
