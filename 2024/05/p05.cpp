#include "aoc-lib.h"
#include <iostream>
#include <sstream>

int main(int argc, char** argv)
{
	AoCOptions options(argc, argv);
	std::vector<std::string> original_lines;
	std::vector<std::pair<int, int>> page_ordering_rules;
	std::vector<std::vector<int>> incorrect_updates;
	bool correct;
	bool found;
	bool progress;
	int sum = 0;
	int next_row, next_col;

	std::cout << "P05: Input file: " << options.get_input_file() << "\n";

	original_lines = read_lines_from_file(options.get_input_file());

	for (const auto& line : original_lines) {
		if (line.empty())
			break;
		std::stringstream ss(line);
		std::string item;
		std::vector<int> rule;

		while (std::getline(ss, item, '|'))
			rule.push_back(std::stoi(item));

		if (rule.size() == 2)
			page_ordering_rules.push_back(std::make_pair(rule[0], rule[1]));
	}

	std::vector<std::vector<int>> updates(original_lines.size() - page_ordering_rules.size());

	int j = 0;
	for (size_t i = page_ordering_rules.size(); i < original_lines.size(); ++i) {
		const auto& line = original_lines[i];
		if (line.empty())
			continue;
		std::stringstream ss(line);
		std::string item;

		while (std::getline(ss, item, ','))
			updates[j].push_back(std::stoi(item));
		j++;
	}

	for (int u = 0; u < updates.size(); ++u) {
		const auto& update = updates[u];
		if (update.size() == 0)
			continue;

		correct = true;
		for (int i = 0; i < update.size() - 1; ++i) {
			for (int j = i + 1; j < update.size(); ++j) {
				bool found = false;
				for (const auto& rule : page_ordering_rules) {
					if (update[i] == rule.first && update[j] == rule.second) {
						found = true;
						break;
					}
				}
				if (!found) {
					correct = false;
					break;
				}
			}
		}

		if (correct) {
			if (!update.empty()) {
				int middle_index = update.size() / 2;
				int middle_value = update[middle_index];
				sum += middle_value;
			}
		}
		else {
			incorrect_updates.push_back(updates[u]);
		}
	}

	std::cout << "P05 Part 1: Sum of middle page numbers: " << sum << std::endl;

	sum = 0;
	if (!incorrect_updates.empty()) {
		for (auto& update : incorrect_updates) {
			do {
				progress = false;
				for (int i = 0; i < update.size() - 1; ++i) {
					for (const auto& rule : page_ordering_rules) {
						if (update[i] == rule.second && update[i + 1] == rule.first) {
							progress = true;
							int temp = update[i];
							update[i] = update[i + 1];
							update[i + 1] = temp;
							break;
						}
					}
				}
			} while (progress);

			if (!update.empty()) {
				int middle_index = update.size() / 2;
				int middle_value = update[middle_index];
				sum += middle_value;
			}
		}
	}

	std::cout << "P05 Part 2: Sum of middle page numbers after corrections: " << sum << std::endl;

	return 0;
}
