#ifndef uuid_guard_4514dcc0_5ef61584_cbfda78e_44d65575
#define uuid_guard_4514dcc0_5ef61584_cbfda78e_44d65575

#include <memory>

#include "element.h"
#include "operator.h"

namespace tul{
namespace practice{
namespace hccs135{
namespace p1{

struct Node: public Element{
	int evaluate() const override;

	Operator op;
	std::unique_ptr<Element> lhs;
	std::unique_ptr<Element> rhs;//if op is a unary operator, rhs should be ignored
};

}
}
}
}

#endif // uuid_guard_4514dcc0_5ef61584_cbfda78e_44d65575
