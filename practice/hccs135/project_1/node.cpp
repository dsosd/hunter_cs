#include "node.h"

#include <cmath>

namespace tul{
namespace practice{
namespace hccs135{
namespace p1{

int Node::evaluate() const{
	if (op.op_t == Operator_t::add){
		return lhs->evaluate() + rhs->evaluate();
	}
	else if (op.op_t == Operator_t::negate_){
		return -1 * lhs->evaluate();
	}
	else if (op.op_t == Operator_t::exponentiate){
		return std::pow(lhs->evaluate(), rhs->evaluate());
	}
}

}
}
}
}
