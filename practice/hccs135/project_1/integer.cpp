#include "integer.h"

namespace tul{
namespace practice{
namespace hccs135{
namespace p1{

Integer::Integer(){
}

Integer::Integer(int val_)
		:val(val_){
}

Integer::Integer(const std::string& str){
	val = std::stoi(str);
}

int Integer::evaluate() const{
	return val;
}

}
}
}
}
