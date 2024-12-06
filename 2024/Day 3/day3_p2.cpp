#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

#include "days.h"

static bool mul_enabled = true;

enum TOKEN_TYPE {
	TOKEN_DO,
	TOKEN_DONT,
	TOKEN_MUL,
	TOKEN_NONE
};

TOKEN_TYPE tokenize(std::string* input) {
	size_t token_do = (*input).find("do()");
	size_t token_dont = (*input).find("don't()");
	size_t token_mul = (*input).find("mul(");

	if (token_do == std::string::npos && token_dont == std::string::npos && token_mul == std::string::npos)
		return TOKEN_NONE;

	std::map<size_t, TOKEN_TYPE> tokens{ {token_do, TOKEN_DO}, {token_dont, TOKEN_DONT}, {token_mul, TOKEN_MUL} };

	TOKEN_TYPE token = tokens[std::min({ token_do, token_dont, token_mul })];

	if (token == TOKEN_DO) {
		mul_enabled = true;
		(*input) = (*input).substr(token_do + std::string("do()").size(), (*input).size());
	}
	else if (token == TOKEN_DONT) {
		mul_enabled = false;
		(*input) = (*input).substr(token_dont + std::string("don't()").size(), (*input).size());
	}
	else if (token == TOKEN_MUL)
		(*input) = (*input).substr(token_mul + std::string("mul(").size(), (*input).size());

	return token;
}

int day3_p2() {
	std::ifstream file("day3_input.txt");

	int mul_total = 0;

	std::string full_str;
	std::string curr_str;

	while (std::getline(file, curr_str))
		full_str.append(curr_str);

	while (true) {
		TOKEN_TYPE token = tokenize(&full_str);

		if (token == TOKEN_NONE)
			break;

		if (token == TOKEN_MUL && mul_enabled) {
			std::string num1_str = "";
			std::string num2_str = "";

			std::string* curr_edit = &num1_str;

			for (size_t idx = 0; idx < full_str.size(); ++idx) {
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
	}

	return mul_total;
}