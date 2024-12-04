#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "days.h"

static bool _is_safe_report(std::vector<int> report) {
	int positive = -1;
	
	for (int i = 0; i < report.size() - 1; ++i) {
		int diff = report[i] - report[i + 1];
		
		if (std::abs(diff) < 1 || std::abs(diff) > 3)
			return false;

		if (positive == -1)
			positive = (diff > 0) ? 1 : 0;
		else {
			if (
				(positive == 0 && diff > 0) ||
				(positive == 1 && diff < 0)
			) {
				return false;
			}
		}
	}

	return true;
}

int day2_p1() {
	std::ifstream file("day2_input.txt");

	int safe_count = 0;

	std::string curr_str;

	while (std::getline(file, curr_str)) {
		std::istringstream stream(curr_str);
		std::string stream_str;
		std::vector<int> report{};

		while (std::getline(stream, stream_str, ' '))
			report.push_back(std::stoi(stream_str));

		if (_is_safe_report(report))
			++safe_count;
	}

	return safe_count;
}