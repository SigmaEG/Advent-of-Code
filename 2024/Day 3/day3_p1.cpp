#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "days.h"

int day3_p1() {
	std::ifstream file("day3_input.txt");

	int mul_total = 0;

	std::string full_str;
	std::string curr_str;

	while (std::getline(file, curr_str))
		full_str.append(curr_str);

	while (true) {
		size_t find_pos = full_str.find("mul(");

		if (find_pos == std::string::npos)
			break;

		full_str = full_str.substr(find_pos + 1, full_str.size());

		std::string num1_str = "";
		std::string num2_str = "";

		std::string* curr_edit = &num1_str;

		for (size_t idx = 3; idx < full_str.size(); ++idx) {
			if (full_str[idx] == ',') {
				if (num1_str == "")
					break;

				curr_edit = &num2_str;
			}
			else if (std::isdigit(full_str[idx]))
				(*curr_edit).push_back(full_str[idx]);
			else if (full_str[idx] == ')') {
				if (num1_str != "" && num2_str != "")
					mul_total += (std::stoi(num1_str) * std::stoi(num2_str));

				break;
			}
			else
				break;
		}
	}

	return mul_total;
}