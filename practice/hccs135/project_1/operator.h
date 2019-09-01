#ifndef uuid_guard_8bd86494_49e0a81f_78ba5ef0_66f2901f
#define uuid_guard_8bd86494_49e0a81f_78ba5ef0_66f2901f

#include "element.h"

namespace tul{
namespace practice{
namespace hccs135{
namespace p1{

enum class Operator_t{
	add,
	negate_,
	exponentiate
};

struct Operator: public Element{
	Operator();
	Operator(Operator_t op_t_);

	Operator_t op_t;
};

}
}
}
}

#endif // uuid_guard_8bd86494_49e0a81f_78ba5ef0_66f2901f
