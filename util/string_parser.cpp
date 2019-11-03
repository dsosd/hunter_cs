#include "string_parser.h"

#include <algorithm>
#include <sstream>

namespace tul{
namespace util{

std::vector<std::string> str_split(const std::string& line, const std::string& token){
	std::vector<std::string> ret;
	std::size_t prev_pos = 0, curr_pos = 0;

	while ((curr_pos = line.find(token, prev_pos)) != std::string::npos){
		ret.push_back(line.substr(prev_pos, curr_pos - prev_pos));
		prev_pos = curr_pos + token.size();
	}

	ret.push_back(line.substr(prev_pos));
	return ret;
}

std::string str_join(const std::vector<std::string>& parts, const std::string& separator){
	std::stringstream ret;
	if (!parts.size()){
		return "";
	}

	for (std::size_t i = 0; i < parts.size()-1; ++i){
		ret << parts[i] << separator;
	}
	ret << parts[parts.size() - 1];

	return ret.str();
}

std::string str_replace(const std::string& line, const std::string& from, const std::string& to){
	std::vector<std::string> parts = str_split(line, from);
	return str_join(parts, to);
}

std::string str_ltrim(std::string str){
	std::string whitespace = " \n\t\f\r\v";//MAGIC

	str.erase(0, str.find_first_not_of(whitespace));
	return str;
}

std::string str_rtrim(std::string str){
	std::string whitespace = " \n\t\f\r\v";//MAGIC

	str.erase(str.find_last_not_of(whitespace) + 1);
	return str;
}

std::string str_trim(std::string str){
	return str_rtrim(str_ltrim(str));
}

}
}
