#include "main.h"

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

#include "calculator.h"

namespace tul{
namespace practice{
namespace hccs135{
namespace p1{

int main(int argc, char** argv){
	Calculator calc;
	std::stringstream ss;

	const std::string folder = "practice/hccs135/project_1/test_cases/";
	const std::string suffix_query = "_query";
	const std::string suffix_answer = "_answer";
	std::map<char, int> type_to_amt = {
		{'a', 1},
		{'b', 5},
		{'c', 1},
		{'d', 1},
	};

	std::map<std::string, char> file_to_type;
	for (const auto& it: type_to_amt){
		for (int i = 0; i < it.second; ++i){
			file_to_type[folder + it.first + std::to_string(i+1)] = it.first;
		}
	}

	std::ostream& out = std::cout;

	for (const auto& it: file_to_type){
		std::ifstream query_file(it.first + suffix_query);
		std::ifstream answer_file(it.first + suffix_answer);

		out << " ~ " << it.first << ":\n";

		switch (it.second){
		case 'a':
			calc.run_a(query_file, out);
			break;
		case 'b':
			calc.run_b(query_file, out);
			break;
		case 'c':
			calc.run_c(query_file, out);
			break;
		case 'd':
			calc.run_d(query_file, out);
			break;
		}

		out << " ~ answers:\n";
		out << answer_file.rdbuf();
	}
	return 0;
}

}
}
}
}
