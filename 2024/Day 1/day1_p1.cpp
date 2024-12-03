#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>

#include "days.h"

int day1_p1() {
	std::vector<int> list1{};
	std::vector<int> list2{};

	std::ifstream inputstream("day1_input.txt");

	std::string read_str;
	std::string main_str;

	int count = 1;

	while (std::getline(inputstream, main_str)) {
		std::istringstream stream(main_str);

		while (std::getline(stream, read_str, ' ')) {
			if (read_str == " " || read_str.empty())
				continue;

			if (read_str.back() == ' ')
				read_str.pop_back();

			if (count == 1) {
				count = 2;
				list1.push_back(std::stoi(read_str));
			}
			else if (count == 2) {
				count = 1;
				list2.push_back(std::stoi(read_str));
			}
		}
	}

	inputstream.close();

	std::sort(list1.begin(), list1.end());
	std::sort(list2.begin(), list2.end());

	int total = 0;

	for (std::size_t i = 0; i < list1.size(); ++i)
		total += std::abs(list1.at(i) - list2.at(i));

	std::cout << total << std::endl;

	return total;
}