#ifndef uuid_guard_06a23a75_29faec02_ec5a51bb_f8e8bf17
#define uuid_guard_06a23a75_29faec02_ec5a51bb_f8e8bf17

#include <string>

#include "element.h"

namespace tul{
namespace practice{
namespace hccs135{
namespace p1{

struct Integer: public Element{
	Integer();
	Integer(int val_);
	Integer(const std::string& str);

	int evaluate() const override;

	int val;
};

}
}
}
}

#endif // uuid_guard_06a23a75_29faec02_ec5a51bb_f8e8bf17
