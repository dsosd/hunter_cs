#ifndef uuid_guard_21326ce6_d9b9e39d_3e1e5e88_41350426
#define uuid_guard_21326ce6_d9b9e39d_3e1e5e88_41350426

#include <string>
#include <vector>

namespace tul{
namespace util{

std::vector<std::string> str_split(const std::string& line, const std::string& token);
std::string str_join(const std::vector<std::string>& parts, const std::string& separator);
std::string str_replace(const std::string& line, const std::string& from, const std::string& to);

std::string str_ltrim(std::string str);
std::string str_rtrim(std::string str);
std::string str_trim(std::string str);

}
}

#endif // uuid_guard_21326ce6_d9b9e39d_3e1e5e88_41350426
