#ifndef uuid_guard_28db5831_be795b77_5ca5509d_084d517b
#define uuid_guard_28db5831_be795b77_5ca5509d_084d517b

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "integer.h"
#include "node.h"
#include "operator.h"

namespace tul{
namespace practice{
namespace hccs135{
namespace p1{

class Calculator{
public:
	//each part of the project can be run individually
	void run_a(std::istream& in, std::ostream& out);
	void run_b(std::istream& in, std::ostream& out);
	void run_c(std::istream& in, std::ostream& out);
	void run_d(std::istream& in, std::ostream& out);

	bool parse_str(const std::string& str);
	Integer get_number(const std::string& str, std::size_t& pos) const;
	Operator get_operator(const std::string& str, std::size_t& pos) const;

	//returns 0 if not parsed
	int evaluate() const;
private:
	//normalizes strings from each part of the project
	std::string fix_a(std::string str) const;
	std::string fix_b(const std::string& str) const;
	std::string fix_c(std::string str) const;
	std::string fix_d(std::string str) const;

	std::vector<std::unique_ptr<Element>> get_parts(const std::string& str) const;

	bool parsed = false;
	Node tree_root;
};

}
}
}
}

#endif // uuid_guard_28db5831_be795b77_5ca5509d_084d517b
