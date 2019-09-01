#include "calculator.h"

#include <set>
#include <sstream>

#include <util/string_parser.h>

namespace tul{
namespace practice{
namespace hccs135{
namespace p1{

void Calculator::run_a(std::istream& in, std::ostream& out){
	std::stringstream ss;
	ss << in.rdbuf();

	parse_str(fix_a(ss.str()));
	out << evaluate() << "\n";
}

void Calculator::run_b(std::istream& in, std::ostream& out){
	std::stringstream ss;
	ss << in.rdbuf();
	std::string str = util::str_replace(ss.str(), "\n", "");

	parse_str(fix_b(str));
	out << evaluate() << "\n";
}

void Calculator::run_c(std::istream& in, std::ostream& out){
	std::stringstream ss;
	ss << in.rdbuf();
	std::vector<std::string> expressions = util::str_split(ss.str(), ";");
	expressions.erase(expressions.begin() + expressions.size()-1);//remove last expression(empty)

	for (const std::string& expression: expressions){
		parse_str(fix_c(expression));
		out << evaluate() << "\n";
	}
}

void Calculator::run_d(std::istream& in, std::ostream& out){
	std::stringstream ss;
	ss << in.rdbuf();
	std::vector<std::string> expressions = util::str_split(ss.str(), ";");
	expressions.erase(expressions.begin() + expressions.size()-1);//remove last expression(empty)

	for (const std::string& expression: expressions){
		parse_str(fix_d(expression));
		out << evaluate() << "\n";
	}
}

std::string Calculator::fix_a(std::string str) const{
	str = util::str_trim(str);
	str = util::str_replace(str, " -", "-");
	str = util::str_replace(str, " ", "+");
	return str;
}

std::string Calculator::fix_b(const std::string& str) const{
	//luckily no change required
	return str;
}

std::string Calculator::fix_c(std::string str) const{
	str = util::str_trim(str);
	return str;
}

std::string Calculator::fix_d(std::string str) const{
	//spec file states that "^" means "^2"
	str = util::str_replace(str, "^", "^2");
	return fix_c(str);
}

//TODO use make_unique instead of unique_ptr after c++14 upgrade
bool Calculator::parse_str(const std::string& str){
	try{
		//prepend "0+" to ensure that at least 1 node will be created
		std::vector<std::unique_ptr<Element>> parts = get_parts("0+" + str);

		//collapse elements into nodes by how tightly bound each operator is
		auto is_op = [](const std::unique_ptr<Element>& elem){
			return dynamic_cast<Operator*> (elem.get());
		};

		auto get_op_t = [](const std::unique_ptr<Element>& elem){
			return dynamic_cast<Operator*> (elem.get())->op_t;
		};

		//generic loop for operator in the form "lhs op rhs"
		auto binary_op_pass = [&](const std::set<Operator_t> operators){
			for (std::size_t i = 0; i < parts.size(); ++i){
				if (is_op(parts[i]) && operators.count(get_op_t(parts[i]))){
					Operator_t op_t = get_op_t(parts[i]);
					std::unique_ptr<Node> temp(new Node());

					temp->op.op_t = op_t;
					//check prev and next element(must be node or number)
					if (i+1 < parts.size() && !is_op(parts[i-1]) && !is_op(parts[i+1])){
						temp->lhs = std::move(parts[i-1]);
						temp->rhs = std::move(parts[i+1]);
						parts[i-1] = std::move(temp);
					}
					else{
						throw std::exception();
					}

					parts.erase(parts.begin() + i, parts.begin() + i+2);
					--i;//maintain current position
				}
			}
		};

		//exponentiate
		binary_op_pass(std::set<Operator_t> {Operator_t::exponentiate});
		//negate
		for (std::size_t i = 0; i < parts.size(); ++i){
			if (is_op(parts[i]) && get_op_t(parts[i]) == Operator_t::negate_){
				std::unique_ptr<Node> temp(new Node());
				temp->op.op_t = Operator_t::negate_;
				//merge negative into next element(must be number)
				if (i+1 < parts.size() && !is_op(parts[i+1])){
					temp->lhs = std::move(parts[i+1]);
					parts[i+1] = std::move(temp);
				}
				else{
					throw std::exception();
				}

				//number comes before negative sign
				if (i-1 > 0 && !is_op(parts[i-1])){
					//a,-,b becomes a,+,-b
					parts[i] = std::move(std::unique_ptr<Operator> (new Operator(Operator_t::add)));
				}
				//operator comes before negative sign
				else{
					parts.erase(parts.begin() + i, parts.begin() + i+1);
					--i;//maintain current position
				}
			}
		}
		//add
		binary_op_pass(std::set<Operator_t> {Operator_t::add});

		if (parts.size() == 1){
			parsed = true;
			tree_root = std::move(*( dynamic_cast<Node*> (parts[0].get()) ));
		}
		else{
			throw std::exception();
		}
	}
	catch (...){
		parsed = false;
	}
	return parsed;
}

std::vector<std::unique_ptr<Element>> Calculator::get_parts(const std::string& str) const{
	std::vector<std::unique_ptr<Element>> ret;
	std::size_t pos = 0;
	bool find_number = true;

	while (pos != str.size()){
		//skip spaces
		if (str[pos] == ' '){
			++pos;
			continue;
		}

		if (find_number){
			ret.push_back(std::unique_ptr<Integer> (
				new Integer(get_number(str, pos))
			));
		}
		else{
			ret.push_back(std::unique_ptr<Operator> (
				new Operator(get_operator(str, pos))
			));
		}
		find_number ^= true;
	}

	return ret;
}

Integer Calculator::get_number(const std::string& str, std::size_t& pos) const{
	std::stringstream ss;
	while (str[pos] >= '0' && str[pos] <= '9'){
		ss << str[pos];
		++pos;
	}

	return Integer(ss.str());
}

Operator Calculator::get_operator(const std::string& str, std::size_t& pos) const{
	Operator ret;

	switch (str[pos]){
	case '+':
		ret.op_t = Operator_t::add;
		break;
	case '-':
		ret.op_t = Operator_t::negate_;
		break;
	case '^':
		ret.op_t = Operator_t::exponentiate;
		break;
	}
	++pos;

	return ret;
}

int Calculator::evaluate() const{
	if (!parsed){
		return 0;
	}
	return tree_root.evaluate();
}

}
}
}
}
